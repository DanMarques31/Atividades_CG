// Aluno: Daniel Luiz Araújo Marques
// Matricula: 212050081
// Disciplina: Computação Gráfica
// Professor: Daniel Madeira

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int win_id;

float rotacao_braco_direito = 0.0f;
float rotacao_braco_esquerdo = 0.0f;


//Capturam as teclas de movimento do teclado
void myKeyboard(unsigned char key, int x, int y)
{
  switch (key) {
    // --- CONTROLES DE MOVIMENTO DOS BRAÇOS ---
    case 'w': // Move o braço direito para frente
    case 'W':
        rotacao_braco_direito += 5.0f;
        break;
    case 's': // Move o braço direito para trás
    case 'S':
        rotacao_braco_direito -= 5.0f;
        break;
    case 'a': // Move o braço esquerdo para frente
    case 'A':
        rotacao_braco_esquerdo += 5.0f;
        break;
    case 'd': // Move o braço esquerdo para trás
    case 'D':
        rotacao_braco_esquerdo -= 5.0f;
        break;

    case 27: // ESC
      glutDestroyWindow(win_id);
      exit(0);
      break;
  }
  glutPostRedisplay();
}

void init(void) 
{
  // Define a cor de fundo da janela de visualização como um azul claro
  glClearColor (0.5f, 0.7f, 1.0f, 1.0f);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_COLOR_MATERIAL);

  GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 20.0, 30.0, 20.0, 0.0 };

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0f, 15.0f, 55.0f, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  
  // Objeto para desenhar cilindros e cones
  GLUquadric* quad = gluNewQuadric();

  // --- spongebob squarepants meu bom ---

  // Corpo principal 
  glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
    glTranslatef(0.0f, 13.0f, 0.0f);
    glScalef(1.0f, 1.2f, 0.5f);
    glutSolidCube(12.0);
  glPopMatrix();

  // Camisa e Calça
  glPushMatrix();
    // Calça
    glColor3f(0.5f, 0.35f, 0.05f); // Marrom
    glTranslatef(0.0f, 5.0f, 0.0f);
    glScalef(1.05f, 0.4f, 0.55f);
    glutSolidCube(12.0);
    
    // Camisa
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    glTranslatef(0.0f, 4.0f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    glutSolidCube(12.0);
  glPopMatrix();

  // Braço Direito
  glPushMatrix();
    glTranslatef(7.0f, 9.5f, 0.0f); // Posição do ombro
    glRotatef(rotacao_braco_direito, 1.0, 0.0, 0.0); // Rotação interativa
    // Braço (cilindro)
    glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
    gluCylinder(quad, 0.8, 0.8, 7.0, 10, 10);
    // Mão (esfera)
    glTranslatef(0.0f, 0.0f, 7.0f);
    glutSolidSphere(1.2, 10, 10);
  glPopMatrix();

  // Braço Esquerdo
  glPushMatrix();
    glTranslatef(-7.0f, 9.5f, 0.0f); // Posição do ombro
    glRotatef(rotacao_braco_esquerdo, 1.0, 0.0, 0.0); // Rotação interativa
    // Braço (cilindro)
    glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
    gluCylinder(quad, 0.8, 0.8, 7.0, 10, 10);
    // Mão (esfera)
    glTranslatef(0.0f, 0.0f, 7.0f);
    glutSolidSphere(1.2, 10, 10);
  glPopMatrix();

  // Perna Direita
  glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
    glTranslatef(3.0f, 2.6f, 0.0f);
    glRotatef(90, 1, 0, 0); // Rotaciona para apontar para baixo
    gluCylinder(quad, 0.8, 0.8, 5.0, 10, 10);
    // Sapato
    glTranslatef(0.0f, 0.0f, 5.0f);
    glColor3f(0.0f, 0.0f, 0.0f); // Preto
    glScalef(1.5f, 2.5f, 1.0f);
    glutSolidCube(1.2);
  glPopMatrix();

  // Perna Esquerda
  glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
    glTranslatef(-3.0f, 2.6f, 0.0f);
    glRotatef(90, 1, 0, 0); // Rotaciona para apontar para baixo
    gluCylinder(quad, 0.8, 0.8, 5.0, 10, 10);
    // Sapato
    glTranslatef(0.0f, 0.0f, 5.0f);
    glColor3f(0.0f, 0.0f, 0.0f); // Preto
    glScalef(1.5f, 2.5f, 1.0f);
    glutSolidCube(1.2);
  glPopMatrix();

  // Olho Direito
  glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    glTranslatef(2.5f, 15.0f, 2.8f);
    glutSolidSphere(2.0, 20, 20);
    // Pupila
    glColor3f(0.1f, 0.5f, 1.0f); // Azul
    glTranslatef(0.0f, 0.0f, 1.5f);
    glutSolidSphere(0.8, 20, 20);
  glPopMatrix();

  // Olho Esquerdo
  glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    glTranslatef(-2.5f, 15.0f, 2.8f);
    glutSolidSphere(2.0, 20, 20);
    // Pupila
    glColor3f(0.1f, 0.5f, 1.0f); // Azul
    glTranslatef(0.0f, 0.0f, 1.5f);
    glutSolidSphere(0.8, 20, 20);
  glPopMatrix();

  // Nariz
  glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
    glTranslatef(0.0f, 12.5f, 3.0f);
    gluCylinder(quad, 0.5, 0.5, 3.0, 10, 10);
  glPopMatrix();

  // Gravata
  glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
    glTranslatef(0.0f, 7.5f, 2.8f);
    glRotatef(90, 1, 0, 0);
    gluCylinder(quad, 0.8, 0.0, 2.0, 10, 1); // Um cone é um cilindro com raio do topo = 0
  glPopMatrix();

  // Libera o objeto quadric
  gluDeleteQuadric(quad);

  glFlush();
}

void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 200.0);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize (640, 480); 
  glutInitWindowPosition (100, 100);
  win_id = glutCreateWindow ("Bob Esponja 3D");
  init ();
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutKeyboardFunc(myKeyboard);
  glutMainLoop();
  return 0;
}