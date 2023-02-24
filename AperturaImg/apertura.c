#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h> //para linux
//#include <Windows.h> //para Windows

//-----Declaracion de funciones----
void abrirVOL(unsigned char *vol);
void display(void);
void initDespliegue(void);
//-------Variables globales--------
int x_size = 256, y_size = 256, z_size = 109;
char name[] = "RMHEA109S";


//-------------Main----------------
void main(int argc,char **argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(x_size,y_size);
  glutInitWindowPosition(500,100);
  glutCreateWindow("Apertura de archivos");
  glutDisplayFunc(display);
  glutMainLoop(); //hasta aquí se crea la ventana
}


//----------Abrir Volumen----------
void abrirVOL(unsigned char *vol) {
  FILE *file;
  //256 256 190
  if ((file = fopen(name, "rb")) == NULL){
    // control del error de apertura
    printf( " Error en la apertura.\n Exit. \n ");
    exit(1);
  }
  for(int z = 0 ; z < z_size; z++){
    for(int x = 0; x < x_size; x++){
      for(int y = 0; y < y_size; y++){
        fread(&vol[x+x_size*y+x_size*y_size*z],1,1,file);
      }
    }
  }
  fclose (file);
}

//-----Inicializar Despliegue------
void initDespliegue(void) {
glClearColor(0.0,0.0,0.0,0.0); //pone fondo en negro
glClear(GL_COLOR_BUFFER_BIT); //Habilita la limpieza de pantalla
glOrtho(0,x_size-1,0,y_size-1,0,1); //Define el sistema de referencia
}
//---------Formar Cortes-----------
void shapeSlices(unsigned char *vol) {
  for(int z = 0; z<z_size; z++){
    glNewList(z,GL_COMPILE_AND_EXECUTE);
    for (int y=0; y<y_size; y++){
      for (int x=0; x<x_size; x++){
        glColor3f((float)vol[x+x_size*y+x_size*y_size*z]/256,(float)vol[x+x_size*y+x_size*y_size*z]/256,(float)vol[x+x_size*y+x_size*y_size*z]/256);
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
      }
    }
    glEndList();
    glCallList(z); //Se llama a la primera figura de la lista
    glutSwapBuffers(); //Se despliega en doble buffer
    //sleep(.01);
  }
}
//------------Display--------------
void display(void) {
  unsigned char *volumen = malloc(x_size * y_size * z_size);
  printf("Abriendo volumen\n");
  abrirVOL(volumen);
  printf("Volumen abierto\nDespliegue\n");
  initDespliegue();
  shapeSlices(volumen);
  /*
  for(int z=0; z<z_size; z++){
    glCallList(z); //Se llama a la primera figura de la lista
    glutSwapBuffers(); //Se despliega en doble buffer
    sleep(.1);
  }
  */
}
