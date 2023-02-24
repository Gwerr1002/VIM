
/*
 escena.c
 Este programa muestra como definir un fuente de luz y
 el dibujo de algunas primitivas con sus respectivos materiales
 Ramiro Alcocer
 valcoey@hotmail.com
 www.oocities.org/valcoey/index.html
*/

#include <stdlib.h>
#include <GL/glut.h>

GLfloat elevacion =   0.0f;
GLfloat azimitud  =   0.0f;
GLfloat giro      =   0.0f;

//parametros para construir la grilla
#define DEF_floorGridScale	1.0
#define DEF_floorGridXSteps	10.0
#define DEF_floorGridZSteps	10.0

void polarView(GLfloat distance, GLfloat twist, GLfloat elevation, GLfloat azimuth)
{
glTranslated(0.0, 0.0, -distance);
glRotated(-twist, 0.0, 0.0, 1.0);
glRotated(-elevation, 1.0, 0.0, 0.0);
glRotated(azimuth, 0.0, 0.0, 1.0);
}

//Inicializa las propiedades de la fuente de luz
static void init(void)
{
    GLfloat light_ambient[] = { 0.75, 0.75, 0.75, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };

    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

void display (void)
{
    //Defino un material Rojo
    GLfloat mat_ambient_toro[] = {0.05, 0.05, 0.05, 1.0f};
    GLfloat mat_diffuse_toro[] = { 0.8, 0.0, 0.0, 1.0f};
    GLfloat mat_specular_toro[] = {0.9, 0.8, 0.8, 1.0f};

    //Defino un material Azul
    GLfloat mat_ambient_cubo[] = {0.1, 0.1, 0.1, 1.0f};
    GLfloat mat_diffuse_cubo[] = {0.0, 0.0, 0.8, 1.0f};
    GLfloat mat_specular_cubo[] = {0.9, 0.9, 0.9, 1.0f};

    //Defino un material Verde
    GLfloat mat_ambient_esfera[] = {0.1, 0.1, 0.1, 1.0f};
    GLfloat mat_diffuse_esfera[] = {0.0, 0.7, 0.0, 1.0f};
    GLfloat mat_specular_esfera[] = {0.8, 0.8, 0.8, 1.0f};

    GLfloat zExtent, xExtent, xLocal, zLocal;
    int loopX, loopZ;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW_MATRIX );
    glLoadIdentity();
    polarView(15.0f, giro, elevacion, azimitud);

    //Dibujo la Grilla
    glPushMatrix();
    glPushAttrib( GL_LIGHTING_BIT );
    glDisable( GL_LIGHTING );
    glColor3f( 0.0, 0.7, 0.7 );
    glBegin( GL_LINES );
    zExtent = DEF_floorGridScale * DEF_floorGridZSteps;
    for(loopX = -DEF_floorGridXSteps; loopX <= DEF_floorGridXSteps; loopX++ )
	{
	xLocal = DEF_floorGridScale * loopX;
	glVertex3f( xLocal, 0.0, -zExtent );
	glVertex3f( xLocal, 0.0,  zExtent );
	}
    xExtent = DEF_floorGridScale * DEF_floorGridXSteps;
    for(loopZ = -DEF_floorGridZSteps; loopZ <= DEF_floorGridZSteps; loopZ++ )
	{
	zLocal = DEF_floorGridScale * loopZ;
	glVertex3f( -xExtent, 0.0, zLocal );
	glVertex3f(  xExtent, 0.0, zLocal );
	}
    glEnd();
    glPopAttrib();
    glPopMatrix();

    //Dibuja el Toro
    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient_toro);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse_toro);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular_toro);
    glMaterialf (GL_FRONT, GL_SHININESS, 50.0f);
    glPushMatrix ();
    glTranslatef (-2.0, 1.0, 2.0);
    glRotatef(-45.0, 0.0, 1.0, 0.0);
    glRotatef(-45.0, 1.0, 0.0, 0.0);
    glutSolidTorus (0.3, 0.8, 12, 24);
    glPopMatrix ();

    //Dibuja el cubo
    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient_cubo);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse_cubo);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular_cubo);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
    glPushMatrix ();
    glTranslatef (1.0, 1.0, 1.0);
    glRotatef(15.0, 0.0, 1.0, 0.0);
    glutSolidCube (2.0);
    glPopMatrix ();

    //Dibuja la esfera de radio 2.5
    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient_esfera);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse_esfera);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular_esfera);
    glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);
    glPushMatrix ();
    glTranslatef (-1.0, 1.0, 0.0);
    glutSolidSphere (1.0, 16, 16);
    glPopMatrix ();

    glFlush ();
}

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case 'x':
   case 'X':
      elevacion = elevacion + 10.0f;
      glutPostRedisplay();
      break;
   case 'v':
   case 'V':
      elevacion = elevacion - 10.0f;
      glutPostRedisplay();
      break;
   case 'y':
   case 'Y':
      azimitud = azimitud + 10.0f;
      glutPostRedisplay();
      break;
   case 'u':
   case 'U':
      azimitud = azimitud - 10.0f;
      glutPostRedisplay();
      break;
   case 'z':
   case 'Z':
      giro = giro + 10.0f;
      glutPostRedisplay();
      break;
   case 'c':
   case 'C':
      giro = giro - 10.0f;
      glutPostRedisplay();
      break;
   case 27:
      exit(0);
      break;
   }
}

int main(int argc, char **argv)
{
   glutInitWindowSize(300, 300);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
