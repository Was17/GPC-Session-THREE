#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

void initFunc();
void funReshape(int w, int h);
void funDisplay();
void drawMolino();
void drawTriangulo(char color);
void funKeyboard(int key, int x, int y);

using namespace std;

// Variables globales
int w = 500;
int h = 500;
GLfloat desZ = -5.0f;
GLfloat rotY =  0.0f;

GLfloat rotZ =  0.0f;
void aspa(){
    glLoadIdentity();
   glPushMatrix();
	glTranslatef(0, 0.5, -2.9);
	
        glRotated(rotY, 0,1, 0);
        glRotated(rotZ * (180.0/46), 0, 0, 1);
        int i;
	glColor3f(0.4f, 0.4f, 0.8f);
	for (i = 0; i < 3; i++) {
		glRotated(120, 0, 0, 1);  // Note: These rotations accumulate.
		glBegin(GL_TRIANGLES);
		glVertex3f(0,0,0);
		glVertex3f(1.0f, 1,0);
		glVertex3f(0.5f,1,0);
		glEnd();
	}
           glPopMatrix();}

void drawWindmill() {
	int i;
        
	glColor3f(0.8f, 0.8f, 0.9f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.05f, 0,0);
	glVertex3f(0.05f, 0,0);
	glVertex3f(0.05f, 1,0);
	glVertex3f(-0.05f,1,0);
	glEnd();
}
int main(int argc, char** argv) {

 // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 3");
    
 // Inicializamos GLEW
    GLenum err = glewInit();
    if(GLEW_OK != err) printf("Error: %s\n", glewGetErrorString(err));
    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    printf("This system supports OpenGL Version: %s\n", oglVersion);
    
 // Inicializaciones específicas
    initFunc();
    
 // Configuración CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutSpecialFunc(funKeyboard);
    
 // Bucle principal
    glutMainLoop();
    
    return 0;
}

void initFunc() {
   
 // Test de profundidad
    glEnable(GL_DEPTH_TEST);
    
 // Modelo de sombreado
    glShadeModel(GL_FLAT);
    
}

void funReshape(int wnew, int hnew) {
    
 // Configuración del Viewport
    glViewport(0, 0, wnew, hnew);

 // Captura de w y h
    w = wnew;
    h = hnew;
    
}

void funDisplay() {
    
 // Borramos el buffer de color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
 // Para configurar la matriz matriz P
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
 // Matriz de Proyección P (Cámara)
    GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;    
    GLfloat fovy = 50.0f, nplane = 0.1f, fplane = 20.0f;
    gluPerspective(fovy,aspectRatio,nplane,fplane);
    
 // Para configurar las matrices M y V
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
 // Matriz de Vista V (Cámara)
    // Aquí cargaremos la matriz V
      glPushMatrix();
      
	glTranslatef(0, -0.4, -3);
    glRotatef(rotY,0, 1, 0);
    drawWindmill();
    aspa();
    glPopMatrix();
    
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}
void drawPunto(){
      glPushMatrix();
   glTranslatef(-0.2f, 0.0f, desZ);
    glRotatef(-135.0f,0.0f,0.0f,1.0f);
  glBegin(GL_POINTS);
    
     glColor3f(1.0f, 1.0f, 1.0f);
        glVertex3f( 0.0f,  0.0f, 0.0f);
       

    glEnd();
     glPopMatrix();
}
void drawMolino(){
 
}
void drawTriangulo(char color) {
    
    switch(color) {
        case 'r':
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case 'g':
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case 'b':
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        default:
            glColor3f(1.0f, 1.0f, 1.0f);            
    }
    
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f( 0.5f, -0.5f, 0.0f);
        glVertex3f( 0.0f,  0.5f, 0.0f);
    glEnd();
    
}

void funKeyboard(int key, int x, int y) {
    
    switch(key) {
        case GLUT_KEY_UP:
            if (desZ<=-20.0f){
                desZ=0.0f;
            }
            desZ -= 0.1f;
              rotZ-=5.0f;
            break;
          
            
        case GLUT_KEY_RIGHT:
            rotY -= 5.0f;
            break;

        case GLUT_KEY_LEFT:
            rotY += 5.0f;
            break;
        case GLUT_KEY_DOWN:
            desZ += 0.1f;
            
            rotZ+=5.0f;
            break;
        default:
            desZ = -5.0f;  
            rotY = 0.0f;
            
            rotZ=0.0f;
    }
    
    glutPostRedisplay();
      
}