#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <math.h>

int x_size, y_size, z_size;

void setDimensions(int dimx,int dimy, int dimz){
  x_size = dimx;
  y_size = dimy;
  z_size = dimz;
}

//--------Abrir y leer un volumen-------------
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

//-------Copiar un corte-----------
void copyzSlice(unsigned char *vol,unsigned char *slice,int z) {
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      slice[x+x_size*y] = vol[x+x_size*y+x_size*y_size*z];
    }
  }
}

//-----Inicializar Despliegue------
void initDespliegue(void) {
glClearColor(0.0,0.0,0.0,0.0); //pone fondo en negro
glClear(GL_COLOR_BUFFER_BIT); //Habilita la limpieza de pantalla
glOrtho(0,x_size-1,0,y_size-1,0,1); //Define el sistema de referencia
}

//------Mostrar solo un corte------
void imShow(unsigned char *im) {
  glNewList(0,GL_COMPILE_AND_EXECUTE);
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      glColor3f((float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256);
      glBegin(GL_POINTS);
      glVertex2i(x,y);
      glEnd();
    }
  }
  glEndList();
  glCallList(0); //Se llama a la primera figura de la lista
  glutSwapBuffers(); //Se despliega en doble buffer
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


//Funciones para la transformacion castle_angel

double lambda(double x, double y, double centro[2], double radio){
  double lambda = sqrt(pow(x-centro[0],2.0)+pow(y-centro[1],2.0))/(sqrt(2.0)*radio);
  //printf("%fl\n", lambda);
  if(lambda > 1.0){lambda = 1.0;}
  return lambda;
}

//---------Castle Angel-------------

void castel_angel(double *xy,int pixelx, int pixely, double alfa, double a, double b, double c, double d, double centro[2], double radio) {
  double xi = (double)pixelx, yi = (double)pixely;
  double l = lambda(xi, yi, centro, radio);
  xy[0]=(1-pow(l,alfa))*((1+a)*xi+b*yi)+pow(l,alfa)*xi;
  //printf("%fl ",xy[0]);
  xy[1]=(1-pow(l,alfa))*(c*xi+(1+d)*yi)+pow(l,alfa)*yi;
  //printf("%fl\n",xy[1]);
}

void imshowCastel(unsigned char *im, double alpha, double a, double b, double c, double d, double centro[2], double radio) {
  double *xy = malloc(2);
  glNewList(1,GL_COMPILE_AND_EXECUTE);
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      castel_angel(xy,x,y,alpha, a, b, c, d, centro, radio);
      glColor3f((float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256);
      glBegin(GL_POINTS);
        glVertex2i((int)xy[0],(int)xy[1]);
      glEnd();
    }
  }
  glEndList();
  glCallList(1); //Se llama a la primera figura de la lista
  glutSwapBuffers(); //Se despliega en doble buffer
}

void interpola_Hermite(unsigned char *imaT,int k,float R1,float R4,unsigned int paso){
  float gris;
  for (unsigned int y=0; y<y_size; y+=1){
    for (unsigned int x=1; x<x_size-paso; x+=1){
      if (imaT[x+y*x_size]<10) {
        int i=0;
        for (float tx=0; tx<1; tx+=1/(float)paso){
          float B1 = 2*pow(tx,3)-3*pow(tx,2)+1, B2 = -2*pow(tx,3)+3*pow(tx,2), B3 =
          pow(tx,3)-2*pow(tx,2)+tx, B4 = pow(tx,3)-pow(tx,2);
          gris = B1*imaT[x-1+y*x_size] + B2*imaT[x+paso-1+y*x_size] + B3*R1 + B4*R4;
          imaT[x-1+i+y*x_size] = (unsigned char)round(gris);
          i++;
        }
      } //cierra if
    }
  }
}

void interpola_Bezier(unsigned char *imaT,unsigned int paso){
  double gris;
  unsigned char *imaa = malloc(x_size*y_size); //Crea matriz auxiliar
  if (imaa == NULL){
    printf("No se asignó memoria a imagen");
    exit(1);
  }
  for (unsigned int y=0; y<y_size; y+=1){
    for (unsigned int x=1; x<x_size-4*paso; x+=1){
      if (imaT[x+y*x_size]<5) {
        int i=0;
        for (double t=0; t<1; t+=1/(double)(paso*4)){
          double B1 = pow(1-t,3), B2 = 3*t*pow(1-t,2), B3 = 3*pow(t,2)*(1-t), B4 = pow(t,3);
          gris = B1*imaT[x-1+y*x_size] + B2*imaT[x+paso-1+y*x_size] + B3*imaT[x+2*paso-
          1+y*x_size] + B4*imaT[x+3*paso-1+y*x_size];
          imaa[x-1+i+y*x_size] = (unsigned char)round(gris);
          i++;
        } //cierra for
      } //cierra if
    }
  }
  //Copia de la imagen auxiliar la parte interpolada únicamente
  for (unsigned int ind=0; ind<x_size*y_size; ind++){
    if (imaa[ind]>0) imaT[ind]=imaa[ind];
  }
  free(imaa);
}

void interpola_BSpline(unsigned char *imaT,unsigned int paso){
  float gris;
  unsigned char *imaa = malloc(x_size*y_size);
  if (imaa == NULL){
    printf("No se asignó memoria a imagen");
    exit(1);
  }
  //limpia_ima(imaa);
  for (unsigned int y=0; y<y_size; y+=1){
    for (unsigned int x=1; x<x_size-4*paso; x+=1){
      if (imaT[x+y*x_size]<5) {
        int i=0;
        for (float t=0; t<1; t+=1/(float)(paso*4)){
          float B1 = pow(1-t,3)/6, B2 = (3*pow(t,3)-6*pow(t,2)+4)/6, B3 = (-
            3*pow(t,3)+3*pow(t,2)+3*t+1)/6, B4 = pow(t,3)/6;
            gris
            =
            B1*imaT[x-1+y*x_size]
            +
            B2*imaT[x+paso-1+y*x_size]
            +
            B3*imaT[x+2*paso-1+y*x_size] + B4*imaT[x+3*paso-1+y*x_size];
            imaa[x-1+i+y*x_size] = (unsigned char)round(gris);
            i++;
          }
        } //cierra if
      }
    }
    for (unsigned int ind=0; ind<x_size*y_size; ind++){
      if (imaa[ind]>0) imaT[ind]=imaa[ind];
    }
}

//----copyOblique------
/*
void copyzSliceOblique(unsigned char *vol,unsigned char *slice,double theta){
  double radians = theta*3.1516/180;
  double m = tan(radians);
  for(int z = 0; z<z_size; z++){
    for(int x=0; x<x_size; x++){
      double y = m*(double)z;
      if(y<0){continue;}
      if(y>y_size){break;}
      //printf("%fl\n",y );
      //slice[x+x_size*(int)y] = vol[x+x_size*(int)y+x_size*y_size*z];
      slice[(int)y+y_size*x] = vol[x+x_size*(int)y+x_size*y_size*z];
      printf("%d,%d, %d\n",x,(int)y,z );
    }
  }
}
*/

void copyzSliceOblique(unsigned char *vol,unsigned char *slice,double theta){
  double radians = theta*3.1516/180;
  double m = tan(radians);
  int lim_x = (int)((double)z_size/m);
  if(lim_x>x_size){lim_x = x_size;}
  for(int x=0; x<lim_x; x++){
    for(int y=0; y<y_size; y++){
      double z = m*(double)x;
      slice[x+x_size*y] = vol[x+x_size*y+x_size*y_size*(int)z];
    }
  }
}
