#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <floppy.h>

double queuedMilliseconds,prev0,fps,responseTime;
int resX,resY,movementX;
double movementY;
void reshape(int w, int h)
{
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glOrtho(0,resX,0,resY,-5,10);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   //..frame-update setup
   queuedMilliseconds=0;
   prev0=0;
   fps=60.05;
   responseTime=(1/fps)*1000;

//... Rendering resoultion
   resX=854;resY=480;

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
 //  glutInitWindowSize(1280, 720);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Floppy Bird");
   glutFullScreen();
   glutDisplayFunc(draw); 
   glutIdleFunc(mixedStepLoop); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard); 
   glutSpecialFunc(processSpecialKeys);
   glutMainLoop();
   return 0; 
}
