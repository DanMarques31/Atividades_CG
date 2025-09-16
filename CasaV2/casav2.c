#include <GL/glut.h>
#include <math.h>

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

//Desenha um quadrado de lado 1 centrado na origem
void desenhaQuadrado() {
    glBegin(GL_QUADS);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();
}

//Desenha um triângulo equilátero de lado 1 centrado na origem
void desenhaTriangulo() {
    glBegin(GL_TRIANGLES);
        glVertex2d(0.0, 0.5);
        glVertex2d(-0.5, -0.5);
        glVertex2d(0.5, -0.5);
    glEnd();
}

//Desenha um círculo de raio 1 centrado na origem
void desenhaCirculo() {
    glBegin(GL_POLYGON);
        for (int i = 0; i < 30; i++) {
            glVertex2f(cos(i), sin(i));
        }
    glEnd();
}

//Faz o cisalhamento de um objeto em relação ao eixo X
//Basta utilizar como uma das funções do OpenGL como glTranslatef, glRotatef, glScalef
void skewX(GLfloat angle) {
    GLfloat m[16] = {
        1, 0, 0, 0,
        tan(angle), 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0 ,1
    };
    glMultMatrixf(m);
}

//Faz o cisalhamento de um objeto em relação ao eixo Y
//Basta utilizar como uma das funções do OpenGL como glTranslatef, glRotatef, glScalef
void skewY(GLfloat angle) {
    GLfloat m[16] = {
        1, tan(angle), 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    glMultMatrixf(m);
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

    // Deslocamento da casa para o centro da tela
    glTranslatef(windowWidth/2, windowHeight/2, 0);

    // ==========================
    // PAREDE LATERAL AMARELA
    // ==========================
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
        glTranslatef(0.75f, -0.5f, 0.0f);
        glScalef(1.5f, 1.0f, 1.0f);
        skewX(-0.5f); // Inclinação da lateral
        desenhaQuadrado();
    glPopMatrix();

    // ==========================
    // PAREDE FRONTAL AMARELA
    // ==========================
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
        glTranslatef(-0.5f, -0.5f, 0.0f);
        glScalef(1.0f, 1.0f, 1.0f);
        desenhaQuadrado();
    glPopMatrix();

    // ==========================
    // PORTA
    // ==========================
    glPushMatrix();
        glColor3f(0.4f, 0.2f, 0.0f); // Marrom
        glTranslatef(-0.5f, -0.7f, 0.0f);
        glScalef(0.2f, 0.6f, 1.0f);
        desenhaQuadrado();
    glPopMatrix();

    // ==========================
    // JANELAS
    // ==========================
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
            glColor3f(0.0f, 1.0f, 1.0f); // Azul claro
            glTranslatef(0.2f + i*0.4f, -0.3f, 0.0f);
            glScalef(0.3f, 0.3f, 1.0f);
            desenhaQuadrado();
        glPopMatrix();
    }

    // ==========================
    // TELHADO FRONTAL
    // ==========================
    glPushMatrix();
        glColor3f(0.8f, 0.4f, 0.0f); // Laranja
        glTranslatef(-0.5f, 0.0f, 0.0f);
        glScalef(1.0f, 1.0f, 1.0f);
        desenhaTriangulo();
    glPopMatrix();

    // ==========================
    // TELHADO LATERAL
    // ==========================
    glPushMatrix();
        glColor3f(0.8f, 0.4f, 0.0f); // Laranja
        glTranslatef(0.75f, 0.0f, 0.0f);
        glScalef(1.5f, 1.0f, 1.0f);
        skewX(-0.5f);  // mesma inclinação da parede lateral
        desenhaQuadrado();
    glPopMatrix();

    // ==========================
    // CÍRCULO DO TELHADO
    // ==========================
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
        glTranslatef(-0.5f, 0.0f, 0.0f);
        glScalef(0.2f, 0.2f, 1.0f);
        desenhaCirculo();
    glPopMatrix();

    // ==========================
    // CHAMINÉ BASE
    // ==========================
    glPushMatrix();
        glColor3f(0.4f, 0.2f, 0.0f); // Marrom
        glTranslatef(0.4f, 0.6f, 0.0f);
        glScalef(0.1f, 0.4f, 1.0f);
        desenhaQuadrado();
    glPopMatrix();

    // ==========================
    // TOPO DA CHAMINÉ
    // ==========================
    glPushMatrix();
        glColor3f(0.8f, 0.4f, 0.0f); // Laranja
        glTranslatef(0.4f, 0.85f, 0.0f);
        glScalef(0.2f, 0.1f, 1.0f);
        desenhaQuadrado();
    glPopMatrix();

    glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if(h == 0) h = 1;

    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (left, right, bottom, top)
    // Se a largura da janela, em pixels, for menor que a altura, a largura da viewport é fixada em 250 e a altura é escalada para o necessário
    if (w <= h)  {
        windowHeight = 250.0f*h/w;
                windowWidth = 250.0f;
    }
    else  {
    // Se a altura da janela, em pixels, for menor que a largura, a altura da viewport é fixada em 250 e a largura é escalada para o necessário
                windowWidth = 250.0f*w/h;
                windowHeight = 250.0f;
    }

    // As dimensões da janela vão de (0.0, 0.0) até (windowWidth, windowHeight), essas são as coordenadas da tela
    gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

// Programa Principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Minha Casa");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    Inicializa();
    glutMainLoop();
    return 0;
}