#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <complex.h>
#include <math.h>
#include <time.h>

int x_size, y_size, z_size;

void setDimensions(int dimx,int dimy, int dimz){
  x_size = dimx;
  y_size = dimy;
  z_size = dimz;
}

void copyzSlice(unsigned char *vol,unsigned char *slice,int z) {
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      slice[x+x_size*y] = vol[x+x_size*y+x_size*y_size*z];
    }
  }
}

void clean(unsigned char *v) {
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      v[x+x_size*y] = 0;
    }
  }
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

//-----Inicializar Despliegue------
void initDespliegue(void) {
glClearColor(0.0,0.0,0.0,0.0); //pone fondo en negro
glClear(GL_COLOR_BUFFER_BIT); //Habilita la limpieza de pantalla
glOrtho(0,x_size*5-1,0,y_size*3-1,0,1); //Define el sistema de referencia
}

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

//Desplegar 10 imagenes

void imShow_nx(unsigned char *im, int n) {
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      glColor3f((float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256);
      glBegin(GL_POINTS);
      glVertex2i(x+n,y);
      glEnd();
    }
  }
}

void imShow_ny(unsigned char *im, int n) {
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      glColor3f((float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256);
      glBegin(GL_POINTS);
      glVertex2i(x+n,y+y_size);
      glEnd();
    }
  }
}

void imShow_nyo(unsigned char *im, int n) {
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      glColor3f((float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256);
      glBegin(GL_POINTS);
      glVertex2i(x+n,y+y_size*2);
      glEnd();
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

//--------Rotar volumenes---------
void rotatez(int angle) {
  glTranslated((float)x_size/2,(float)y_size/2,0);
  glRotatef(angle,0,0,1);
  //Rota sobre el eje z
  glTranslated(-(float)x_size/2,-(float)y_size/2,0);
}

//-------------Mobius------------
float mobius(int pixel, float complex a, float complex b, float complex c,float complex d, int n) {
  // pixel es la posiciòn no la intensidad en ese punto
  float complex calc;
  float newPixel;
  calc = (float)pixel+0.0*I;
  //printf("%d : ", pixel);
  //printf("%f+%fi ", crealf(calc),cimagf(calc));
  for (int iter = 0; iter < n; iter++){
    calc = (a*calc+b)/(c*calc+d);
  }
  newPixel =  cabsf(calc);
  //printf("%f\n", newPixel);
  return newPixel;
}


void imShowMobius(unsigned char *im, float complex a, float complex b, float complex c,float complex d, int n) {
  float Mobx,Moby;
  glNewList(1,GL_COMPILE);
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      Mobx = mobius(x, a, b, c,d, n);
      Moby = mobius(y, a, b, c,d, n);
      glColor3f((float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256);
      glBegin(GL_POINTS);
      glVertex2i(Mobx,Moby);
      glEnd();
    }
  }
  glEndList();
  glCallList(1); //Se llama a la primera figura de la lista
  glutSwapBuffers(); //Se despliega en doble buffer
}

void imApplyMobius(unsigned char *im, unsigned char *transformation, float complex a, float complex b, float complex c,float complex d, int n) {
  float Mobx,Moby;
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      Mobx = mobius(x, a, b, c,d, n);
      Moby = mobius(y, a, b, c,d, n);
      //printf("%f %f\n", Mobx, Moby);
      if(Mobx <= x_size && Moby <= y_size){
        transformation[(unsigned int)Mobx+ x_size*(unsigned int)Moby] = im[x+x_size*y];
      }
    }
  }
}

//----------------------------------Similitud----------------------------------

//---------correlacion cruazada normalizada---------
double CCN(unsigned char *Ifr,unsigned char *Ifo) {
  int i,j;
  double D1,D2,D,N,R,Ifr_,Ifo_;
  //Variables locales de la función
  //Determinación de los promedios de las imágenes a comparar
  Ifr_=0; Ifo_=0;
  for (j=0; j<y_size; j++) {
    for (i=0; i<x_size; i++) {
      Ifr_=Ifr_+(double)Ifr[i+x_size*j]; //Sumatoria de las intensidades de c/pixel
      Ifo_=Ifo_+(double)Ifo[i+x_size*j];
    }
  }
  Ifr_=Ifr_/(y_size*x_size); //Determinando el promedio de las intensidades
  Ifo_=Ifo_/(y_size*x_size);
  //Determianción del valor de la medida
  N=0; D1=0; D2=0; D=0; R=0;
  //Inicializando las variables
  for (j=0; j<y_size; j++) {
  //Generando el valor de la medida
    for (i=0; i<x_size; i++) {
      N=N+((double)Ifr[i+x_size*j]-Ifr_)*((double)Ifo[i+x_size*j]-Ifo_);
      D1=pow((double)Ifr[i+x_size*j]-Ifr_,2);
      D2=pow((double)Ifo[i+x_size*j]-Ifo_,2);
      D=D+sqrt(D1*D2);
    }
  }
  R=N/D;
  return R;
}
//----------------correlacion de gradiente CG----------------

double CG(unsigned char *Ifr, unsigned char *Ifo) {
  double R1,R2,RF;
  unsigned char *Ifr_di = malloc(x_size*y_size);
  unsigned char *Ifr_dj = malloc(x_size*y_size);
  unsigned char *Ifo_di = malloc(x_size*y_size);
  unsigned char *Ifo_dj = malloc(x_size*y_size);
  clean(Ifr_di); clean(Ifr_dj); clean(Ifo_di); clean(Ifo_dj);
  //----Aplicacion de Sobel----
  int a,b,s,x,y,t;
  int m,n;
  //Definiendo las máscaras de sobel con las que realizaremos la diferenciación
  double w1[3][3]={{1,0,-1},{2,0,-2},{1,0,-1}};
  double w2[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}};
  //Mascara horizontal de sobel
  //Mascara vertical de sobel
  //Definiendo los ı́ndices de las sumatorias.
  m=3; n=3;
  a=(int)((m-1)/2);
  b=(int)((n-1)/2);
  for (x=1; x<x_size-1; x++) {
    for (y=1; y<y_size-1; y++) {
      long double d_Ifr_i=0,d_Ifr_j=0,d_Ifo_i=0,d_Ifo_j=0;
      for (t=-b; t<b+1; t++) {
        for (s=-a; s<a+1; s++) {
          //Proceso de Correlación
          //Calculando las derivadas para la imagen Ifr
          double aur = (double)Ifr[x+s+x_size*(y+t)];
          d_Ifr_i+= aur*w1[s][t]; //Gradiente horizontal (i)
          d_Ifr_j+= aur*w2[s][t];
          //Gradiente vertical (j)
          //Calculando las derivadas para la imagen Ifo
          double auo = (double)Ifo[x+s+x_size*(y+t)];
          d_Ifo_i+= (double)Ifo[x+s+x_size*(y+t)]*w1[s][t];
          d_Ifo_j+= (double)Ifo[x+s+x_size*(y+t)]*w2[s][t];
          //printf("%d\t",x+s+x_size*(y+t));
        }
      }
      //Imagenes derivadas
      Ifr_di[x+x_size*y]=(unsigned char)abs(d_Ifr_i); //Sustituyendo el valor del pixel por su derivada
      Ifr_dj[x+x_size*y]=(unsigned char)abs(d_Ifr_j);
      Ifo_di[x+x_size*y]=(unsigned char)abs(d_Ifo_i);
      Ifo_dj[x+x_size*y]=(unsigned char)abs(d_Ifo_j);
    }
  }
  //-----fin sobel------
  R1=CCN(Ifr_di,Ifo_di); //Determinando la CCN entre las imágenes derivadas respecto a i
  R2=CCN(Ifr_dj,Ifo_dj); //Determinando la CCN entre las imágenes derivadas respecto a j
  //Determinando el valor de la medida
  free(Ifr_di); free(Ifr_dj); free(Ifo_di); free(Ifo_dj);
  RF=(R1+R2)/2;
  //Obteniendo el promedio de las correlaciones
  return RF;
}

//----------Entropia de la imagen diferencia--------------
double Entropy(unsigned char *Ifr) {
    int i,j,size=0;
    long double A=0,B=0;
    int ValorHistograma = 256;
    long double ProbabilidadMarginal_fr[ValorHistograma];
    //LLenando el arreglo para el histograma asociado a la imagen
    for(i=0;i<ValorHistograma;i++){
      ProbabilidadMarginal_fr[i] = 0;
    }
    for (i=0; i<x_size; i++) {
      for (j=0; j<y_size; j++) {
      int Index = (int)Ifr[i+x_size*j];
      ProbabilidadMarginal_fr[Index]+=1;
      }
    }
    //Generando el vector de probabilidad asociado a la imagen
    for (i=0; i<ValorHistograma; i++) {
      ProbabilidadMarginal_fr[i]/=(double)(x_size*y_size);
      //printf("%Lf\n", ProbabilidadMarginal_fr[i]);
      //Determinando el valor de su entropı́a
      if(ProbabilidadMarginal_fr[i]!=0) A=log10(ProbabilidadMarginal_fr[i]);
      B+=ProbabilidadMarginal_fr[i]*A;
    }
  return -1*B;
}

double EID(unsigned char *Ifr,unsigned char *Ifo) {
  unsigned char *Idiff = malloc(x_size*y_size);
  int ValorHistograma = 256;
  long double Probabilidadiff[ValorHistograma];
  int i,j;
  double ED;
  //Determinación de la imagen diferencia
  double s=1;
  //Factor de ajuste de intensidad
  int maxd=0;
  for (j=0; j<y_size; j++) {
    for (i=0; i<x_size; i++) {
      Idiff[i+x_size*j]=abs(Ifr[i+x_size*j]-s*Ifo[i+x_size*j]); //Calculando la imagen diferencia
    }
  }
  ED=Entropy(Idiff);
  free(Idiff);
  return ED;
}

//Informaciòn mutua normalizada
/*
double IM2O(unsigned char *Ifr,unsigned char *Ifo) {
  unsigned char ifr[x_size][y_size];
  unsigned char ifo[x_size][y_size];
  int i,j,k,l,m,n;
  float size,Ar,Ao,Br,Bo,Aro,Bro,IME,e,aux;
  size=0; Ar=0; Br=0; Ao=0; Bo=0; Bro=0; Aro=0; e=0;
  int ValorHistograma2 = 256;
  aux=(float)(ValorHistograma2-1)/(255);
  for (n=0; n<y_size; n++) {
    for (m=0; m<x_size; m++) {
      ifr[m][n] = aux*(float)Ifr[m+x_size*n];
      ifo[m][n] = aux*(float)Ifo[m+x_size*n];
    }
  }
  long double Pc_Ifr[x_size][y_size],Pc_Ifo[x_size][y_size];
  for (n=0; n<y_size; n++){
    for (m=0; m<x_size; m++) {
      for (j=0; j<y_size; j++) {
        for (i=0; i<x_size; i++) {
          //Acumulando las apariciones de cada intensidad en los siguientes arreglos
          Pc_Ifr[ifr[m][n]][ifr[i][j]]+=1;
          Pc_Ifo[ifo[m][n]][ifo[i][j]]+=1;
          size++;
        }
      }
    }
  }
  //Determinando las entropias de segundo orden de cada una de las imagenes
  for (j=0; j<ValorHistograma2; j++) {
    for (i=0; i<ValorHistograma2; i++) {
      //Obteniendo el arreglo de probabilidades
      Pc_Ifr[i][j]/=size;
      Pc_Ifo[i][j]/=size;
      //Evitando los logaritmos de cero
      if (Pc_Ifr[i][j]!=0) {
        Ar=log10(Pc_Ifr[i][j]);
      }
      //Determinando la entropia de segundo orden de Ifr
      Br+=Pc_Ifr[i][j]*Ar;
      if (Pc_Ifo[i][j]!=0) {
        Ao=log10(Pc_Ifo[i][j]);
      }
      //Determinando la entropia de segundo orden de Ifo
      Bo+=Pc_Ifo[i][j]*Ao;
    }
  }
  //Determinando la Entropia conjunta de segundo orden para el par de imagenes
  unsigned char *Pc_Ifr_Ifo=malloc(x_size * y_size * z_size);
  //clean(Pc_Ifr_Ifo);
  for (n=0; n<y_size; n++){
    for (m=0; m<x_size; m++) {
      for (j=0; j<y_size; j++) {
        for (i=0; i<x_size; i++) {
          Pc_Ifr_Ifo[ifr[m][n]][ifr[i][j]][ifo[m][n ]][ifo[i][j]]+=1;
        }
      }
    }
  }
  for (j=0; j<ValorHistograma2; j++) {
    for (i=0; i<ValorHistograma2; i++) {
      for (l=0; l<ValorHistograma2; l++) {
        for (k=0; k<ValorHistograma2; k++) {
        Pc_Ifr_Ifo[i][j][k][l]/=size;
        if (Pc_Ifr_Ifo[i][j][k][l]!=0) {
          Aro=log10(Pc_Ifr_Ifo[i][j][k][l]);
        }
        //Determinando la entropia conjunta de segundo orden
        Bro+=Pc_Ifr_Ifo[i][j][k][l]*Aro;
        }
      }
    }
  }
  free(Pc_Ifr_Ifo);
  //Determinando la medida de IM basada en la entropia de segundo orden
  IME=(-Br+(-Bo))/(-Bro);
  return IME;
}
*/

//--------------Diferencia cuadràtica media---------------
double DCM(unsigned char *Ifr, unsigned char *Ifo){
  double dcm;
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      unsigned char dif = Ifr[x+x_size*y] - Ifo[x+x_size*y];
      dcm +=  pow((double)dif,2);
      //printf("%Lf\n", dcm);
    }
  }
  return sqrt(dcm/((double)x_size*(double)y_size));
}

//llenar vector complejos aleatorios

void fillmoeb_param(float complex v[10][4], int n[10]) {
  for(int i=0;i<10;i++){
    n[i]=rand()%3+1;
    float real = rand()%11+1, imag = rand()%10+1;
    v[i][1] = real + imag*I;
    real = rand()%11+1; imag = rand()%10+1;
    v[i][2] = real + imag*I;
    real = rand()%11+1; imag = rand()%10+1;
    v[i][3] = 0+0*I;//real + imag*I;
    real = rand()%11+1; imag = rand()%10+1;
    v[i][0] = 1+0*i;//(real + imag*I+v[i][1]*v[i][2])/v[i][3];
  }
}

void fill_res(double res[10][4], unsigned char *slice,unsigned char *transfo, int row) {
  res[row][0] = CCN(slice,transfo);
  res[row][1] = CG(slice,transfo);
  res[row][2] = EID(slice,transfo);
  res[row][3] = DCM(slice,transfo);
}

double lambda(double x, double y, double centro[2], double radio){
  double lambda = sqrt(pow(x-centro[0],2.0)+pow(y-centro[1],2.0))/(sqrt(2.0)*radio);
  //printf("%fl\n", lambda);
  if(lambda > 1.0){lambda = 1.0;}
  return lambda;
}

void castel_angel(double *xy,int pixelx, int pixely, double alfa, double a, double b, double c, double d, double centro[2], double radio) {
  double xi = (double)pixelx, yi = (double)pixely;
  double l = lambda(xi, yi, centro, radio);
  xy[0]=(1-pow(l,alfa))*((1+a)*xi+b*yi)+pow(l,alfa)*xi;
  //printf("%fl ",xy[0]);
  xy[1]=(1-pow(l,alfa))*(c*xi+(1+d)*yi)+pow(l,alfa)*yi;
  //printf("%fl\n",xy[1]);
}

void imApplyCastel(unsigned char *im, unsigned char *transfo,double alpha, double a, double b, double c, double d, double centro[2], double radio) {
  double *xy = malloc(2);
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      castel_angel(xy,x,y,alpha, a, b, c, d, centro, radio);
      if(xy[0] <= x_size && xy[1] <= y_size){
        transfo[(unsigned int)xy[0]+ x_size*(unsigned int)xy[1]] = im[x+x_size*y];
      }
    }
  }
}

void fillcastle_param(double v[10][5]){
  for(int i=0;i<10;i++){
    for(int j=0;j<4;j++){
      FILE *file;
      unsigned char rand;
      system("python3 rand.py");
      if ((file = fopen("seeds.r", "rb")) == NULL){
        // control del error de apertura
        printf( " Error en la apertura.\n Exit. \n ");
        exit(1);
      }
      fread(&rand,1,1,file);
      fclose (file);
      v[i][j]= ((double)(rand))/10;
    }
    FILE *file;
    unsigned char rand;
    system("python3 rand.py");
    if ((file = fopen("seeds.r", "rb")) == NULL){
      // control del error de apertura
      printf( " Error en la apertura.\n Exit. \n ");
      exit(1);
    }
    fread(&rand,1,1,file);
    fclose (file);
    v[i][4] = ((double)(rand))/10;
  }
}

void table(double res[10][4],double v[10][5]) {
  double best[2][10];
  printf("Imagen\t\t\t\tParametro\t\t\tCCN\t\tCG\t\tEID\t\tDCM\n");
  for(int i = 0;i<10;i++){
    printf("%d\t",i);
    printf("alpha=%0.3fl,a=%0.3fl, b=%0.3fl,c=%0.3fl,d=%0.3fl  ",v[i][4],v[i][0],v[i][1],v[i][2],v[i][3]);
    for(int j=0;j<4;j++){
      printf("%fl\t",res[i][j]);
    }
    printf("\n");
    best[0][i] = res[i][1];
    best[1][i] = (double)i;
  }
  printf("Imagenes ordenadas por grado de Similitud:\n");
  double aux,n;
  for(int i=0;i<10;i++){
    int max=0;
    for(int j=0;j<9;j++){
      int indsig = j+1;
      if(best[0][j]>best[0][j+1]){
        double aux = best[0][j];
        best[0][j] = best[0][j+1];
        best[0][j+1] = aux;
        double auxi = best[1][j];
        best[1][j] = best[1][j+1];
        best[1][j+1] = auxi;
      }
    }
  }
  for (int i = 9; i >= 0; i--) {
    printf("%d, ",(int)best[1][i]);
  }
  printf("\n");
}
