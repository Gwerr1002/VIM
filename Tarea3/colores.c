//Ejemplo que despliega un mapa de colores en 2D
//Emplea doble buffer para mejorar la velocidad de despliegue en unión
//con la formación de listas de despliegue

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>

#define tam_ima 256     //Establece la longitud en x y y de la imagen

void inicializa_despliegue(void)
{
  glClearColor(0.0,0.0,0.0,0.0);   //pone fondo en negro
  glClear(GL_COLOR_BUFFER_BIT); //Habilita la limpieza de pantalla
  glOrtho(0,tam_ima-1,0,tam_ima-1,0,1);  //Define el sistema de referencia
}

void Forma_imagen(void)
{
  glNewList(1,GL_COMPILE_AND_EXECUTE);
  //glNewList(1,GL_COMPILE);
    for (int y=0; y<tam_ima; y++){
      for (int x=0; x<tam_ima; x++){
        glColor3f((float)x/tam_ima,(float)y/tam_ima,1); //Debe ir anter de definir la figura RGB
        glBegin(GL_POINTS);
          glVertex2i(x,y);
        glEnd();
      }
    }
  glEndList();
}

void display(void)
{
  inicializa_despliegue();
  Forma_imagen();
  glCallList(1); //Se llama a la primera figura de la lista
  glutSwapBuffers();  //Se despliega en doble buffer
}

int main(int argc, char **argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(tam_ima,tam_ima);
  glutInitWindowPosition(500,100);
  glutCreateWindow("Demo");
  glutDisplayFunc(display);
  glutMainLoop();  //hasta aquí se crea la ventana
}
