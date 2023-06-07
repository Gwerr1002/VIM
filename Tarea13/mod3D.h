#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <math.h>

char name[]="cerebro";
int x_size, y_size, z_size;

void init(){
  float	luz_1[]={1,.85,.7,0},luz_pos1[]={-500,-500,0,0};
  float	luz_2[]={.5,.5,.5,0},luz_pos2[]={500,500,0,0};
  float	luz_3[]={.4,.25,.1,0},luz_pos3[]={0,0,500,0};
  float	lmodel_ambient[]={1,1,1,1.0};	//Color	de	la	luz	ambiental
  float	mat_especular[]={1,1,1,1};
  glClearColor(0,0,0,0.0);			//pone	fondo	en	negro
  glLightfv(GL_LIGHT0,	GL_POSITION,	luz_pos1);
  glLightfv(GL_LIGHT0,	GL_DIFFUSE,	luz_1);
  glLightfv(GL_LIGHT1,	GL_POSITION,	luz_pos2);
  glLightfv(GL_LIGHT1,	GL_DIFFUSE,	luz_2);
  glLightfv(GL_LIGHT2,	GL_POSITION,	luz_pos3);
  glLightfv(GL_LIGHT2,	GL_DIFFUSE,	luz_3);
  glEnable(GL_LIGHTING);				//Habilita	modo	iluminación	con	sombreado
  glEnable(GL_LIGHT0);						//Habilita	la	fuente	de	luz
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_DEPTH_TEST);		//Habilita	Z-Buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	 //Habilita	 la	limpieza	de	pantalla	y	Z-Buffer
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-300,300,0,300,-200,300);		//Proyección	ortográfica
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void setDimensions(int dimx,int dimy, int dimz){
  x_size = dimx;
  y_size = dimy;
  z_size = dimz;
}

//-----Abrir volumen de imagenes------
void abrirVOL(unsigned char *vol,char *name) {
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



void show3D(unsigned char *seg,unsigned char *vol){
  float Gx,Gy,Gz,norm;
  glBegin(GL_POINTS);
  for (int z = 0; z < z_size; z++) {
    for (int y = 0; y < y_size; y++) {
      for (int x = 0; x < x_size; x++){
        if(seg[x+x_size*y+x_size*y_size*z]>0){
          Gx = (float)vol[x+1+x_size*y+x_size*y_size*z]-(float)vol[x-1+x_size*y+x_size*y_size*z];
          Gy = (float)vol[x+x_size*(y+1)+x_size*y_size*z]-(float)vol[x+x_size*(y-1)+x_size*y_size*z];
          Gz = (float)vol[x+x_size*y+x_size*y_size*(z+1)]-(float)vol[x+x_size*y+x_size*y_size*(z-1)];
          norm = sqrt(Gx*Gx+Gy*Gy+Gz);
          glNormal3f(Gx/norm,Gy/norm,Gz/norm);
          glVertex3f(x,y,z);
        }
      }
    }
  }
  glEnd();
}

void piramid() {
  glColor3f(0,1,1);//base
  glBegin(GL_QUADS);
    glVertex3f(1,1,.5);
    glVertex3f(1,1.5,.5);
    glVertex3f(.5,1.5,.5);
    glVertex3f(.5,1,.5);
  glEnd();
  glColor3f(1,0,0);
  glBegin(GL_TRIANGLES);
    glVertex3f(0.75,1.25,0);
    glVertex3f(1,1,.5);
    glVertex3f(1,1.5,.5);
  glEnd();
  glColor3f(0,1,0);
  glBegin(GL_TRIANGLES);
    glVertex3f(0.75,1.25,0);
    glVertex3f(1,1.5,.5);
    glVertex3f(.5,1.5,.5);
  glEnd();
  glColor3f(0,0,1);
  glBegin(GL_TRIANGLES);
    glVertex3f(0.75,1.25,0);
    glVertex3f(.5,1.5,.5);
    glVertex3f(.5,1,.5);
  glEnd();
  glColor3f(1,.5,0);
  glBegin(GL_TRIANGLES);
    glVertex3f(.75,1.25,0);
    glVertex3f(.5,1,.5);
    glVertex3f(1,1,.5);
  glEnd();
}
