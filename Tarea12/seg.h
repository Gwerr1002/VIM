#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <math.h>

int x_size, y_size, z_size;
char name[] = "../RMHEA109S";

void setDimensions(int dimx,int dimy, int dimz){
  x_size = dimx;
  y_size = dimy;
  z_size = dimz;
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
  glOrtho(0,x_size,0,y_size,0,1); //Define el sistema de referencia
}

//---------Limpiar arreglo---------

void clean(unsigned char *v) {
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      v[x+x_size*y] = 0;
    }
  }
}

//-----Segmentacion binaria---------
void segmentar(unsigned char *segment,unsigned char *vol,unsigned char inf, unsigned char sup){
  for(int z = 0 ; z < z_size; z++){
    for(int x = 0; x < x_size; x++){
      for(int y = 0; y < y_size; y++){
        if(vol[x+x_size*y+x_size*y_size*z] >= inf && vol[x+x_size*y+x_size*y_size*z] <= sup){
          segment[x+x_size*y+x_size*y_size*z] = 255;
        }
      }
    }
  }
}

void sigmoidFilter(unsigned char *res, char *vol,double max,double min,double beta,double alpha){
  double pixel,sig1,sig2,beta1;
  //beta1 = -alpha*log(1/0.99999999-1)+beta;
  for(int z = 0 ; z < z_size; z++){
    for(int x = 0; x < x_size; x++){
      for(int y = 0; y < y_size; y++){
        sig1 = 1/(1+exp(-((double) vol[x+x_size*y+x_size*y_size*z]-beta)/alpha));
        //sig2 = 1/(1+exp(-((double) vol[x+x_size*y+x_size*y_size*z]-beta1)/-alpha));
        pixel = (max-min)*sig1+min;
        res[x+x_size*y+x_size*y_size*z] = (unsigned char) pixel;
      }
    }
  }
}

void sigmoidFilterBilateral(unsigned char *res, char *vol,double max,double min,double beta,
  double beta1,double alpha,double alpha1){
  double pixel,sig1,sig2;
  for(int z = 0 ; z < z_size; z++){
    for(int x = 0; x < x_size; x++){
      for(int y = 0; y < y_size; y++){
        sig1 = 1/(1+exp(-((double) vol[x+x_size*y+x_size*y_size*z]-beta)/alpha));
        sig2 = 1/(1+exp(-((double) vol[x+x_size*y+x_size*y_size*z]-beta1)/-alpha1));
        pixel = (max-min)*sig1*sig2+min;
        res[x+x_size*y+x_size*y_size*z] = (unsigned char) pixel;
      }
    }
  }
}

void resta_bin(unsigned char *res, char *im1, unsigned char *im2){
  for(int z = 0 ; z < z_size; z++){
    for(int x = 0; x < x_size; x++){
      for(int y = 0; y < y_size; y++){
        if (im2[x+x_size*y+x_size*y_size*z]>0){
          res[x+x_size*y+x_size*y_size*z] = 0;
          //printf("paso1\n");
        }else{
          res[x+x_size*y+x_size*y_size*z] = im1[x+x_size*y+x_size*y_size*z];
          //printf("paso2\n");
        }
      }
    }
  }
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
