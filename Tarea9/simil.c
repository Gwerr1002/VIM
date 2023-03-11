#include "open.h"

char name[] = "../RMHEA109S";
void display();

void main(int argc,char **argv){
  glutInit(&argc,argv);
  setDimensions(256,256,109);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(x_size*4,y_size*2);
  glutInitWindowPosition(50,100);
  glutCreateWindow("Apertura de archivos");
  glutDisplayFunc(display);
  glutMainLoop(); //hasta aquí se crea la ventana
}

void display(/* arguments */) {
  unsigned char *volumen = malloc(x_size * y_size * z_size);
  unsigned char *slice = malloc(x_size*y_size);
  double centro[2] = {150,150};
  double v[10][5];
  fillcastle_param(v);
  double res[10][4];
  abrirVOL(volumen,name);
  copyzSlice(volumen,slice,40);
  free(volumen);
  unsigned char *transformation = malloc(x_size*y_size);
  initDespliegue();
  int selec = 0;
  glNewList(0,GL_COMPILE_AND_EXECUTE);
    //original
    imShow_nyo(slice,2*x_size);
    //primer transformacion
    clean(transformation);
    imApplyCastel(slice, transformation,v[selec][4],v[selec][0],v[selec][1],v[selec][2],v[selec][0],centro,50);
    //imApplyCastel(slice, transformation,.5, -0.2, 0.1, 0.1, -0.2, centro, 50);
    selec++;
    imShow_ny(transformation,0);
    //segunda transformacion
    clean(transformation);
    imApplyCastel(slice, transformation,v[selec][4],v[selec][0],v[selec][1],v[selec][2],v[selec][0],centro,50);
    fill_res(res,slice,transformation,selec);
    selec++;
    imShow_ny(transformation,x_size);
    //tercer transformacion
    clean(transformation);
    imApplyCastel(slice, transformation,v[selec][4],v[selec][0],v[selec][1],v[selec][2],v[selec][0],centro,50);
    fill_res(res,slice,transformation,selec);
    selec++;
    imShow_ny(transformation,x_size*2);
    //cuarta transformacion
    clean(transformation);
    imApplyCastel(slice, transformation,v[selec][4],v[selec][0],v[selec][1],v[selec][2],v[selec][0],centro,50);
    fill_res(res,slice,transformation,selec);
    selec++;
    imShow_ny(transformation,x_size*3);
    //quinta transformacion
    clean(transformation);
    imApplyCastel(slice, transformation,v[selec][4],v[selec][0],v[selec][1],v[selec][2],v[selec][0],centro,50);
    fill_res(res,slice,transformation,selec);
    selec++;
    imShow_ny(slice,x_size*4);
    //sexta transformacion
    clean(transformation);
    imApplyCastel(slice, transformation,v[selec][4],v[selec][0],v[selec][1],v[selec][2],v[selec][0],centro,50);
    fill_res(res,slice,transformation,selec);
    selec++;
    imShow_nx(slice,0);
    //septima transformacion
    clean(transformation);
    imApplyCastel(slice, transformation,v[selec][4],v[selec][0],v[selec][1],v[selec][2],v[selec][0],centro,50);
    fill_res(res,slice,transformation,selec);
    selec++;
    imShow_nx(transformation,x_size);
    //octava transformacion
    clean(transformation);
    imApplyCastel(slice, transformation,v[selec][4],v[selec][0],v[selec][1],v[selec][2],v[selec][0],centro,50);
    fill_res(res,slice,transformation,selec);
    selec++;
    imShow_nx(slice,x_size*2);
    //novena transformacion
    clean(transformation);
    imApplyCastel(slice, transformation,v[selec][4],v[selec][0],v[selec][1],v[selec][2],v[selec][0],centro,50);
    fill_res(res,slice,transformation,selec);
    selec++;
    imShow_nx(transformation,x_size*3);
    //decima transformacion
    clean(transformation);
    imApplyCastel(slice, transformation,v[selec][4],v[selec][0],v[selec][1],v[selec][2],v[selec][0],centro,50);
    fill_res(res,slice,transformation,selec);
    selec++;
    imShow_nx(transformation,x_size*4);
    table(res,v);
    glEndList();
    glCallList(0); //Se llama a la primera figura de la lista
  glutSwapBuffers(); //Se despliega en doble buffer
  free(slice);
  free(transformation);
}
