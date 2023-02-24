#include<stdio.h>
#include<GL/glut.h>
#include<GL/gl.h>

//Constantes para la cuadricula
#define DEF_floorGridScale	1.0
#define DEF_floorGridXSteps	10.0
#define DEF_floorGridZSteps	10.0

//variables del programa
GLfloat elevacion =   0.0f;
GLfloat azimitud  =   0.0f;
GLfloat giro      =   0.0f;

void display(void);
void polarView(GLfloat distance, GLfloat twist, GLfloat elevation, GLfloat azimuth);

void main(){

}

void polarView(GLfloat distance, GLfloat twist, GLfloat elevation, GLfloat azimuth)
{
glTranslated(0.0, 0.0, -distance);
glRotated(-twist, 0.0, 0.0, 1.0);
glRotated(-elevation, 1.0, 0.0, 0.0);
glRotated(azimuth, 0.0, 0.0, 1.0);
}

void display(void){
  //Defino un material Verde
  GLfloat mat_ambient_esfera[] = {0.1, 0.1, 0.1, 1.0f};
  GLfloat mat_diffuse_esfera[] = {0.0, 0.7, 0.0, 1.0f};
  GLfloat mat_specular_esfera[] = {0.8, 0.8, 0.8, 1.0f};
  //
  GLfloat zExtent, xExtent, xLocal, zLocal;
  int loopX, loopZ;
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode( GL_MODELVIEW_MATRIX );
  glLoadIdentity();
  polarView(15.0f, giro, elevacion, azimitud);
  //cuadricula
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
