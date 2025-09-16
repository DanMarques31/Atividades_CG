//------------------------- ALGORITMO DE RECORTE DE LINHAS DE COHEN-SUTHERLAND -------------------------
// Aluno: Daniel Luiz Araújo Marques
// Matrícula: 212050081
// Disciplina: Computação Gráfica
// Professor: Daniel Madeira

#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Dimensões da janela e do retângulo de recorte (globais)
int windowWidth = 800, windowHeight = 600;
float rectWidth = 400.0f, rectHeight = 300.0f;

// Constantes para os códigos de região do Cohen-Sutherland
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Limites do retângulo de recorte (são globais para as funções acessarem)
float left, right, bottom, top;

// Estrutura para representar um ponto bidimensional [x,y]
typedef struct {
    float x, y;
} Ponto;

// Função para calcular o código de região de um ponto
int computeCode(Ponto p) {
    int code = INSIDE;
    if (p.x < left)
        code |= LEFT;
    else if (p.x > right)
        code |= RIGHT;
    if (p.y < bottom)
        code |= BOTTOM;
    else if (p.y > top)
        code |= TOP;
    return code;
}

// Função principal do algoritmo de Cohen-Sutherland
void cohenSutherlandClipAndDraw(Ponto p1, Ponto p2) {
    Ponto original_p1 = p1;
    Ponto original_p2 = p2;

    int code1 = computeCode(p1);
    int code2 = computeCode(p2);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int code_out;
            Ponto new_p = {0, 0};

            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            if (code_out & TOP) {
                new_p.x = p1.x + (p2.x - p1.x) * (top - p1.y) / (p2.y - p1.y);
                new_p.y = top;
            } else if (code_out & BOTTOM) {
                new_p.x = p1.x + (p2.x - p1.x) * (bottom - p1.y) / (p2.y - p1.y);
                new_p.y = bottom;
            } else if (code_out & RIGHT) {
                new_p.y = p1.y + (p2.y - p1.y) * (right - p1.x) / (p2.x - p1.x);
                new_p.x = right;
            } else if (code_out & LEFT) {
                new_p.y = p1.y + (p2.y - p1.y) * (left - p1.x) / (p2.x - p1.x);
                new_p.x = left;
            }

            if (code_out == code1) {
                p1 = new_p;
                code1 = computeCode(p1);
            } else {
                p2 = new_p;
                code2 = computeCode(p2);
            }
        }
    }

    if (accept) {
        glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
        glBegin(GL_LINES);
            glVertex2f(original_p1.x, original_p1.y);
            glVertex2f(p1.x, p1.y);
        glEnd();

        glColor3f(0.0f, 0.0f, 1.0f); // Azul
        glBegin(GL_LINES);
            glVertex2f(p1.x, p1.y);
            glVertex2f(p2.x, p2.y);
        glEnd();
        
        glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
        glBegin(GL_LINES);
            glVertex2f(p2.x, p2.y);
            glVertex2f(original_p2.x, original_p2.y);
        glEnd();

    } else {
        glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
        glBegin(GL_LINES);
            glVertex2f(original_p1.x, original_p1.y);
            glVertex2f(original_p2.x, original_p2.y);
        glEnd();
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    float centerX = windowWidth / 2.0f;
    float centerY = windowHeight / 2.0f;
    left = centerX - rectWidth / 2.0f;
    right = centerX + rectWidth / 2.0f;
    bottom = centerY - rectHeight / 2.0f;
    top = centerY + rectHeight / 2.0f;

    glBegin(GL_LINE_LOOP);
        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glVertex2f(right, top);
        glVertex2f(left, top);
    glEnd();

    glLineWidth(1.0f);
    
    for (int i = 0; i < 10; i++) {
        Ponto p1 = { (float)(rand() % windowWidth), (float)(rand() % windowHeight) };
        Ponto p2 = { (float)(rand() % windowWidth), (float)(rand() % windowHeight) };
        cohenSutherlandClipAndDraw(p1, p2);
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    srand(time(NULL)); 

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Retângulo base de recorte - Cohen-Sutherland");
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
    glutMainLoop();
    return 0;
}