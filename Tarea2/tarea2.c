//Ejemplo que despliega en gráfica de barras el código binario introducido por el usuario,
//puede introducir hasta 24 bits. También despliega en modo gráfico la conversión a decimal.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/gl.h>

#define LARGO 1000
#define ANCHO 200

//Procedimiento de conversion de binario a decimal
long int binario_a_decimal(char *binario)
{
  char *uno = "1";
  long int suma = 0;

  int len = strlen(binario);
  for (int i=len-1;i>=0;i--){
    if  (binario[i]==uno[0]){
      suma += pow(2,len-1-i);
    }
  }
  return suma;
}

//Imprime en modo gráfico una cadena de caracteres
void Despliega_cadena(char *cad)
{
  int len = strlen(cad);   //Obtiene longitud de cadena de carateres
  float x=-0.9;

  glColor3f(0,0,0);
  for (int i=0;i<len;i++){
    glRasterPos2f(x,0.8);   //Posicion de escritura de caracter
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15,cad[i]);   //Despliega caracter
    x+=.04;   //Incrementa el espacio que ocupo un caracter
    glFlush();   //Habilita los comandos de despleigue en ventana
  }
}

void display(void)
{
  char binario[32];   //Convierte hasta 24 bits (3 bytes)
  char *uno="1",*cero="0";
  char str_dec[10];
  float x;

  glClearColor(0.9,0.9,0.9,0.0);   //pone fondo en negro
  glClear(GL_COLOR_BUFFER_BIT); //Habilita la limpieza de pantalla

  //Adquiere el dato en modo texto y despliega la conversion a decimal
  printf("Introduce un numero binario de hasta 32 bits: ");
  scanf("%s",binario);
  int long_cad = strlen(binario);  //Obtiene el numero de bits d10101010101010101010101010101011el codigo binario introducido
  printf("Numero de %d bits\n",long_cad);
  long int dec = binario_a_decimal(binario);
  sprintf(str_dec,"%ld",dec); //Convierte entero a cadena de caracteres
  Despliega_cadena(str_dec);  //Imprime en ventana

  //Genera una grafica de barras con el codigo binario
  for (int i=0;i<long_cad;i++){
    //printf("%c",binario[i]);
    if (long_cad > 29 && i==0){
      glColor3f(0.0,0.0,0.8);
      glBegin(GL_POLYGON);
        glVertex2f(-1+(float)(i*2)/32,-1);
        glVertex2f(-1+(float)((i+1)*2)/32,-1);
        glVertex2f(-1+(float)((i+1)*2)/32,.5);
        glVertex2f(-1+(float)(i*2)/32,.5); //la pantalla esta normalizada de -1.0 a 1.0
      glEnd();
      glFlush();
      //Despliga caracter binario
      glRasterPos2f(-.975+(float)(i*2)/32,0.6);   //Posicion de escritura de caracter
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13,uno[0]);   //Despliega caracter
      glFlush(); //Hasta aquí se despliega todo
    }else{
    if (binario[i]=='1'){
      glColor3f(0.0,0.0,0.8);
      glBegin(GL_POLYGON);
        glVertex2f(-1+(float)(i*2)/32,-1);
        glVertex2f(-1+(float)((i+1)*2)/32,-1);
        glVertex2f(-1+(float)((i+1)*2)/32,.5);
        glVertex2f(-1+(float)(i*2)/32,.5); //la pantalla esta normalizada de -1.0 a 1.0
      glEnd();
      glFlush();
      //Despliga caracter binario
      glRasterPos2f(-.975+(float)(i*2)/32,0.6);   //Posicion de escritura de caracter
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13,uno[0]);   //Despliega caracter
      glFlush(); //Hasta aquí se despliega todo
    }
    else{
      glColor3f(0.0,0.8,0.8);
      glBegin(GL_POLYGON);
        glVertex2f(-1+(float)(i*2)/32,-1);
        glVertex2f(-1+(float)((i+1)*2)/32,-1);
        glVertex2f(-1+(float)((i+1)*2)/32,.5);
        glVertex2f(-1+(float)(i*2)/32,.5); //la pantalla esta normalizada de -1.0 a 1.0
      glEnd();
      glFlush(); //Hasta aquí se despliega todo
           //Despliga caracter binario
      glRasterPos2f(-0.975+(float)(i*2)/32,0.6);   //Posicion de escritura de caracter
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13,cero[0]);   //Despliega caracter
      glFlush(); //Hasta aquí se despliega todo
    }
  }
  }
}

int main(int argc, char **argv){

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(LARGO,ANCHO);
  glutInitWindowPosition(50,200);
  glutCreateWindow("Binario y decimal");
  glutDisplayFunc(display);
  glutMainLoop();  //hasta aquí se crea la ventana
}

//Para compilar en OS X El Capitan v 10.11.5
// cc ejemplo2.c -o ejemplo2 -L/opt/X11/lib/ -lglut -lGL
