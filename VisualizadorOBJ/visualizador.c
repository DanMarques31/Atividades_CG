//Aluno: Daniel Luiz Araújo Marques
//Matrícula: 212050081
//Professor: Daniel Luiz Madeira

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>   // Para sqrt, fabs, etc.

int win_id;

// --- STRUCTS E VARIÁVEIS GLOBAIS PARA O MODELO .OBJ ---

typedef struct {
    float x, y, z;
} Vertex;

typedef struct {
    float x, y, z;
} Normal;

typedef struct {
    // Índices para vértices, normais e texturas 
    int v1, n1, vt1;
    int v2, n2, vt2;
    int v3, n3, vt3;
} Face;

Vertex* vertices = NULL;
Normal* normals = NULL;
Face* faces = NULL;
int numVertices = 0;
int numNormals = 0;
int numFaces = 0;

float scaleFactor = 1.0f;

// --- FUNÇÃO PARA CALCULAR AS NORMAIS QUANDO ELAS NÃO EXISTEM NO ARQUIVO ---

void calculateNormals() {
    // Se já tem normais, não precisa recalcular
    if (numNormals != 0) return;

    printf("Arquivo nao contem normais. Calculando normais por face...\n");
    
    // uma normal para cada face
    numNormals = numFaces;
    normals = (Normal*)malloc(numNormals * sizeof(Normal));
    if (!normals) {
        perror("Falha ao alocar memoria para normais calculadas");
        exit(1);
    }

    for (int i = 0; i < numFaces; i++) {
        // Obter os vértices da face
        Vertex p1 = vertices[faces[i].v1];
        Vertex p2 = vertices[faces[i].v2];
        Vertex p3 = vertices[faces[i].v3];

        // Calcular dois vetores na face
        Vertex vecA = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
        Vertex vecB = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};

        // Calcular o produto vetorial para obter a normal
        Normal normal;
        normal.x = (vecA.y * vecB.z) - (vecA.z * vecB.y);
        normal.y = (vecA.z * vecB.x) - (vecA.x * vecB.z);
        normal.z = (vecA.x * vecB.y) - (vecA.y * vecB.x);
        normals[i] = normal;

        // Atribuir o índice desta nova normal a todos os vértices desta face
        faces[i].n1 = i;
        faces[i].n2 = i;
        faces[i].n3 = i;
    }
}


// --- FUNÇÃO DE CARREGAMENTO DO MODELO ---

void loadObj(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char line[1024];
    float minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9, minZ = 1e9, maxZ = -1e9;

    // Primeira passagem: contar
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) numVertices++;
        else if (strncmp(line, "vn ", 3) == 0) numNormals++;
        else if (strncmp(line, "f ", 2) == 0) numFaces++;
    }

    // Alocação de memória
    vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));
    if (numNormals > 0) { // Só aloca normais se existirem no arquivo
        normals = (Normal*)malloc(numNormals * sizeof(Normal));
    }
    faces = (Face*)malloc(numFaces * sizeof(Face));

    if (!vertices || !faces) {
        perror("Erro de alocacao de memoria (vertices/faces)");
        exit(1);
    }

    // Segunda passagem: ler os dados
    fseek(file, 0, SEEK_SET);
    int vertexIndex = 0;
    int normalIndex = 0;
    int faceIndex = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) {
            sscanf(line, "v %f %f %f", &vertices[vertexIndex].x, &vertices[vertexIndex].y, &vertices[vertexIndex].z);
            if (vertices[vertexIndex].x < minX) minX = vertices[vertexIndex].x;
            if (vertices[vertexIndex].x > maxX) maxX = vertices[vertexIndex].x;
            if (vertices[vertexIndex].y < minY) minY = vertices[vertexIndex].y;
            if (vertices[vertexIndex].y > maxY) maxY = vertices[vertexIndex].y;
            if (vertices[vertexIndex].z < minZ) minZ = vertices[vertexIndex].z;
            if (vertices[vertexIndex].z > maxZ) maxZ = vertices[vertexIndex].z;
            vertexIndex++;
        } else if (strncmp(line, "vn ", 3) == 0) {
            sscanf(line, "vn %f %f %f", &normals[normalIndex].x, &normals[normalIndex].y, &normals[normalIndex].z);
            normalIndex++;
        } else if (strncmp(line, "f ", 2) == 0) {
            // Tenta ler os 3 formatos mais comuns.
            int matches = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faces[faceIndex].v1, &faces[faceIndex].vt1, &faces[faceIndex].n1, &faces[faceIndex].v2, &faces[faceIndex].vt2, &faces[faceIndex].n2, &faces[faceIndex].v3, &faces[faceIndex].vt3, &faces[faceIndex].n3);
            if (matches != 9) {
                matches = sscanf(line, "f %d//%d %d//%d %d//%d", &faces[faceIndex].v1, &faces[faceIndex].n1, &faces[faceIndex].v2, &faces[faceIndex].n2, &faces[faceIndex].v3, &faces[faceIndex].n3);
                if (matches != 6) {
                    matches = sscanf(line, "f %d %d %d", &faces[faceIndex].v1, &faces[faceIndex].v2, &faces[faceIndex].v3);
                    if (matches != 3) {
                         // Alguns testes não deram certo, então se o formato não for reconhecido, ignora a linha
                         continue;
                    }
                    // Se leu só vértices, os índices das normais são 0 (inválido por enquanto)
                    faces[faceIndex].n1 = faces[faceIndex].n2 = faces[faceIndex].n3 = 0;
                }
            }
            
            // Corrige os índices (de base 1 para base 0)
            faces[faceIndex].v1--; faces[faceIndex].n1--;
            faces[faceIndex].v2--; faces[faceIndex].n2--;
            faces[faceIndex].v3--; faces[faceIndex].n3--;
            faceIndex++;
        }
    }
    fclose(file);

    // --- VERIFICA E CALCULA AS NORMAIS SE NECESSÁRIO ---
    calculateNormals();

    // --- CÁLCULO DA ESCALA AUTOMÁTICA ---
    float deltaX = maxX - minX;
    float deltaY = maxY - minY;
    float deltaZ = maxZ - minZ;
    float maxDelta = deltaX;
    if (deltaY > maxDelta) maxDelta = deltaY;
    if (deltaZ > maxDelta) maxDelta = deltaZ;
    if (maxDelta > 0) scaleFactor = 20.0f / maxDelta;

    printf("Modelo carregado: %d vertices, %d normais, %d faces.\n", numVertices, numNormals, numFaces);
    printf("Fator de escala automatico aplicado: %.4f\n", scaleFactor);
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'R': case 'r': glColor3f(1.0f, 0.0f, 0.0f); break;
        case 'G': case 'g': glColor3f(0.0f, 1.0f, 0.0f); break;
        case 'B': case 'b': glColor3f(0.0f, 0.0f, 1.0f); break;
        case 27: // Tecla ESC
            free(vertices);
            if(normals) free(normals);
            free(faces);
            glutDestroyWindow(win_id);
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void myKeyboardSpecial(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: glutFullScreen(); break;
        case GLUT_KEY_DOWN: glutReshapeWindow(800, 600); break;
        default: printf("Tecla especial pressionada: %d\n", key); break;
    }
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float r = (double)rand() / (double)RAND_MAX;
        float g = (double)rand() / (double)RAND_MAX;
        float b = (double)rand() / (double)RAND_MAX;
        glColor3f(r, g, b);
        printf("Cor aleatoria (%.2f, %.2f, %.2f) aplicada na posicao do mouse (%d, %d)\n", r, g, b, x, y);
    }
    glutPostRedisplay();
}

void init(void) {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 50.0, 50.0, 50.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glColor3f(0.8f, 0.8f, 0.8f);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 10.0f, 50.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glScalef(scaleFactor, scaleFactor, scaleFactor);
    
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < numFaces; i++) {
        glNormal3fv((GLfloat*)&normals[faces[i].n1]);
        glVertex3fv((GLfloat*)&vertices[faces[i].v1]);

        glNormal3fv((GLfloat*)&normals[faces[i].n2]);
        glVertex3fv((GLfloat*)&vertices[faces[i].v2]);

        glNormal3fv((GLfloat*)&normals[faces[i].n3]);
        glVertex3fv((GLfloat*)&vertices[faces[i].v3]);
    }
    glEnd();
    
    glFlush();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0 * w / h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ratio, 1.0, 500.0);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <caminho_para_o_arquivo.obj>\n", argv[0]);
        return 1;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    win_id = glutCreateWindow("Visualizador de Modelos .obj");
    init();
    loadObj(argv[1]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(myKeyboardSpecial);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}