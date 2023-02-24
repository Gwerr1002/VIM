//gcc nombre.c -o nombre -lglut -lGLU -lGL -lm
//sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
#include<stdio.h>
#include<math.h>

#include<GL/glut.h>
#include<GL/gl.h>

void rPolygon(float origin[2], float rad, int lados, float *coor, int iter);
void display(void);

int main(int argc, char**argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(700,580);
  glutInitWindowPosition(350,100); //ancho alto
  glutCreateWindow("Ejemplo1");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

void display(void){
  glClearColor(0.2,0.2,0.2,0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0,1,0);
  //
  glBegin(GL_LINES);
    glVertex2f(-1.0,-1.0);
    glVertex2f(1.0,1.0);
  glEnd();
  //
  glBegin(GL_POLYGON);
    glVertex2f(-.5,.5);
    glVertex2f(-.7,0);
    glVertex2f(0,.1);
  glEnd();
  //
  glBegin(GL_POLYGON);
    glColor3f(.2,.4,.9);//.2 .4 .9
    int lados = 10; float origin[2],coor[2],rad = .3;
    origin[0] = .5; origin[1] = -.5;
    for(int i = 1;i<=lados;i++){
      rPolygon(origin,rad,lados,coor,i);
      glVertex2f(coor[0],coor[1]);
    }
  glEnd();
  glFlush();
}

void rPolygon(float origin[2], float rad, int lados, float *coor, int iter){
  float angle = 2*3.1416*iter/lados, theta = 2*3.1416/lados;
  coor[0] = rad*cosf(angle-theta)+origin[0];
  coor[1] = rad*sinf(angle-theta)+origin[1];
}
