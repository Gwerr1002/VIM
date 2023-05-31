#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <math.h>

char name[]="triangles";

void init(){
  float	luz_blanca[]={1,1,1,0},luz_pos[]={1,0,0,0};
  float	lmodel_ambient[]={1,1,1,1.0};	//Color	de	la	luz	ambiental
  float	mat_especular[]={1,1,1,1};
  glClearColor(0,0,0,0.0);			//pone	fondo	en	negro
  glLightfv(GL_LIGHT0,	GL_POSITION,	luz_pos);
  glLightfv(GL_LIGHT0,	GL_DIFFUSE,	luz_blanca);
  glEnable(GL_LIGHTING);				//Habilita	modo	iluminación	con	sombreado
  glEnable(GL_LIGHT0);						//Habilita	la	fuente	de	luz
  glEnable(GL_DEPTH_TEST);		//Habilita	Z-Buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	 //Habilita	 la	limpieza	de	pantalla	y	Z-Buffer
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1,2,-1,2,-2,2);		//Proyección	ortográfica
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void cerebro(void){
  FILE *file;
  int len = 2709333; int i = 0;
  float num[9];
  if ((file = fopen(name, "rb")) == NULL){
    // control del error de apertura
    printf( " Error en la apertura.\n Exit. \n ");
    exit(1);
  }
  for (int i; i<len; i+9){
    fread(num,sizeof(float),9,file);
    glBegin(GL_TRIANGLES);
      glVertex3f(num[0],num[1],num[2]);
      glVertex3f(num[3],num[4],num[5]);
      glVertex3f(num[6],num[7],num[8]);
    glEnd();
  }
  printf("Terminado\n");
  fclose (file);
}
