/* Daniel Luiz Araújo Marques 
  Matrícula: 212050081*/

#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	    // Header File For The OpenGL32 Library
#include <GL/glu.h>	    // Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* ascii code for the escape key */
#define ESCAPE 27

/* The number of our GLUT window */
int window; 

/* A general OpenGL initialization function. Sets all of the initial parameters. */
void InitGL(int Width, int Height)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		
    glClearDepth(1.0);				
    glDepthFunc(GL_LESS);				
    glEnable(GL_DEPTH_TEST);			
    glShadeModel(GL_SMOOTH);			

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();				

    // Set up an orthogonal projection
    glOrtho(-Width / 200.0f, Width / 200.0f, -Height / 200.0f, Height / 200.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

/* Called when the window is resized */
void ReSizeGLScene(int Width, int Height)
{
    if (Height == 0)
        Height = 1;

    glViewport(0, 0, Width, Height);		

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-Width / 200.0f, Width / 200.0f, -Height / 200.0f, Height / 200.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

/* Main drawing function */
void DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();                                    

    // Casa principal - corpo esquerdo
    glColor3f(1.0f, 1.0f, 0.2f); 
    glBegin(GL_QUADS);
        glVertex3f(-0.5f, -0.5f, -5.0f);
        glVertex3f(0.5f, -0.5f, -5.0f);
        glVertex3f(0.5f, 0.0f, -5.0f);
        glVertex3f(-0.5f, 0.0f, -5.0f);
    glEnd();

    // Extensão lateral da casa
    glColor3f(1.0f, 0.9f, 0.0f); 
    glBegin(GL_QUADS);
        glVertex3f(0.5f, -0.5f, -5.0f);
        glVertex3f(2.0f, -0.5f, -5.0f);
        glVertex3f(2.0f, 0.0f, -5.0f);
        glVertex3f(0.5f, 0.0f, -5.0f);
    glEnd();

    // Telhado da parte principal (triangular)
    glColor3f(0.6f, 0.3f, 0.1f);  // Marrom mais escuro para o telhado principal
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.6f, 0.0f, -5.0f);
        glVertex3f(0.6f, 0.0f, -5.0f);
        glVertex3f(0.0f, 0.55f, -5.0f); 
    glEnd();

    // Telhado da extensão lateral (inclinado)
    glColor3f(0.8f, 0.4f, 0.1f);  // Marrom mais claro para o telhado da extensão
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.55f, -5.0f);
        glVertex3f(0.0f, 0.0f, -5.0f);
        glVertex3f(2.0f, 0.0f, -5.0f);
        glVertex3f(1.4f, 0.55f, -5.0f);
    glEnd();

    // Porta da casa
    glColor3f(0.4f, 0.25f, 0.05f);
    glBegin(GL_QUADS);
        glVertex3f(-0.1f, -0.5f, -4.9f);
        glVertex3f(0.1f, -0.5f, -4.9f);
        glVertex3f(0.1f, -0.1f, -4.9f);
        glVertex3f(-0.1f, -0.1f, -4.9f);
    glEnd();

    // Janela esquerda da extensão
    glColor3f(0.0f, 0.9f, 1.0f); 
    glBegin(GL_QUADS);
        glVertex3f(0.7f, -0.3f, -4.9f); 
        glVertex3f(0.9f, -0.3f, -4.9f);
        glVertex3f(0.9f, -0.1f, -4.9f); 
        glVertex3f(0.7f, -0.1f, -4.9f);
    glEnd();

    // Janela direita da extensão
    glBegin(GL_QUADS);
        glVertex3f(1.1f, -0.3f, -4.9f);
        glVertex3f(1.3f, -0.3f, -4.9f);
        glVertex3f(1.3f, -0.1f, -4.9f); 
        glVertex3f(1.1f, -0.1f, -4.9f); 
    glEnd();

    // Janelinha circular na parte superior da casa
    glColor3f(1.0f, 1.0f, 0.0f);
    float angle;
    float radius = 0.11f;  
    float cx = 0.0f;
    float cy = 0.25f; 
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(cx, cy, -4.9f);
        for (int i = 0; i <= 20; i++) {
            angle = i * 2.0f * M_PI / 20;
            glVertex3f(cx + cos(angle) * radius, cy + sin(angle) * radius, -4.9f);
        }
    glEnd();

    // Chaminé base
    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glVertex3f(0.3f, 0.4f, -4.9f);
        glVertex3f(0.4f, 0.4f, -4.9f);
        glVertex3f(0.4f, 0.6f, -4.9f);
        glVertex3f(0.3f, 0.6f, -4.9f);
    glEnd();

    // Parte superior da chaminé
    glBegin(GL_QUADS);
        glVertex3f(0.25f, 0.6f, -4.9f);
        glVertex3f(0.45f, 0.6f, -4.9f);
        glVertex3f(0.45f, 0.7f, -4.9f);
        glVertex3f(0.25f, 0.7f, -4.9f);
    glEnd();

    // Detalhes da janela da chaminé (2 vidros)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(0.28f, 0.62f, -4.8f);
        glVertex3f(0.33f, 0.62f, -4.8f);
        glVertex3f(0.33f, 0.67f, -4.8f);
        glVertex3f(0.28f, 0.67f, -4.8f);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex3f(0.37f, 0.62f, -4.8f);
        glVertex3f(0.42f, 0.62f, -4.8f);
        glVertex3f(0.42f, 0.67f, -4.8f);
        glVertex3f(0.37f, 0.67f, -4.8f);
    glEnd();

    glutSwapBuffers();
}

/* Function called whenever a key is pressed */
void keyPressed(unsigned char key, int x, int y) 
{
    usleep(100);

    if (key == ESCAPE) 
    { 
        glutDestroyWindow(window); 
        exit(0);                   
    }
}

int main(int argc, char **argv) 
{  
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutInitWindowPosition(100, 100);  

    window = glutCreateWindow("Casa em OpenGL");

    glutDisplayFunc(&DrawGLScene);  
    glutIdleFunc(&DrawGLScene);  
    glutReshapeFunc(&ReSizeGLScene);  
    glutKeyboardFunc(&keyPressed);

    InitGL(800, 600);  

    glutMainLoop();  

    return 0;
}
