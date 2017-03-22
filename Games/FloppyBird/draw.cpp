#include <GL/glut.h>
#include <stdio.h>
#include <floppy.h>
#include <iostream>
#include <vector>
#include <string>
#include <SOIL/SOIL.h>

using namespace std;

struct bricks
{
int x,y;
int objdisp;
}obj;

vector<bricks> obstacleBrick;
unsigned char* image;
static GLuint texBird[8],texBac[2],texObj[3];
int width, height,score;
float skyX,treeX,treeX2,groundX;
GLuint dlist[6];
int birdPhys,i,j,tmp,highscore;
double syncBird;

void init()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//............BIRD...............
	glGenTextures(8,texBird);

	glBindTexture(GL_TEXTURE_2D, texBird[0]);  //texture 1 active 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/bird/frame-1.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );


	glBindTexture(GL_TEXTURE_2D, texBird[1]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/bird/frame-2.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );


	glBindTexture(GL_TEXTURE_2D, texBird[2]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/bird/frame-3.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );


	glBindTexture(GL_TEXTURE_2D, texBird[3]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/bird/frame-4.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );


	glBindTexture(GL_TEXTURE_2D, texBird[4]);   
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/bird/frame-5.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );


	glBindTexture(GL_TEXTURE_2D, texBird[5]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/bird/frame-6.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glBindTexture(GL_TEXTURE_2D, texBird[6]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/bird/frame-7.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glBindTexture(GL_TEXTURE_2D, texBird[7]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/bird/frame-8.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

//.......BACKGROUND.............
	glGenTextures(2,texBac);
	glBindTexture(GL_TEXTURE_2D, texBac[0]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/background/cloud.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glBindTexture(GL_TEXTURE_2D, texBac[1]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/background/ground.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

//..OBJECTS	
	glGenTextures(3,texObj);	
	glBindTexture(GL_TEXTURE_2D, texObj[0]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/objects/trees_near.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glBindTexture(GL_TEXTURE_2D, texObj[1]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/objects/brick.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );
	
	glBindTexture(GL_TEXTURE_2D, texObj[2]);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	image = SOIL_load_image( "res/objects/trees_far.png", &width, &height, 0, SOIL_LOAD_RGBA );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

glEnable(GL_TEXTURE_2D);
}


void initialiseList()
{
dlist[0]=glGenLists(1);
dlist[1]=glGenLists(1);
dlist[2]=glGenLists(1);
dlist[3]=glGenLists(1);
dlist[4]=glGenLists(1);
dlist[5]=glGenLists(1);
}

void update(double temp)
{
	syncBird+=temp;
	if(syncBird>=150)  // bird winganimation running at 6fps
		{	
			birdPhys++;
			if(birdPhys==8)
				birdPhys=0;
			syncBird-=150;
		}	

}

void updateSynchronised()
{
		groundX-=4;
		if(groundX<-resX)
			groundX=0;

		skyX-=0.75;
		if(skyX<-resX)
			skyX=0;

		treeX-=2;
		if(treeX<-resX)
			treeX=0;

		treeX2-=1.75;
		if(treeX2<-resX)
			treeX2=0;
		
}

void staticBird()
{
glNewList(dlist[0], GL_COMPILE);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(0,resY/2,0);
		glTexCoord2f(1.0, 0.0); glVertex3f(50,resY/2,0);
		glTexCoord2f(1.0, -1.0); glVertex3f(50,(resY/2)+50,0);                        
		glTexCoord2f(0.0, -1.0); glVertex3f(0,(resY/2)+50,0);
	glEnd();
glEndList();
}

void staticGround()
{
glNewList(dlist[1], GL_COMPILE);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(0,0,0);
		glTexCoord2f(1.0, 0.0); glVertex3f(resX*2,0,0);
		glTexCoord2f(1.0, -1.0); glVertex3f(resX*2,(resY*10)/100,0);                        
		glTexCoord2f(0.0, -1.0); glVertex3f(0,(resY*10)/100,0);
	glEnd();
glEndList();
}

void staticSky()
{
glNewList(dlist[2], GL_COMPILE);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(0,0,0);
		glTexCoord2f(1.0, 0.0); glVertex3f(resX*2,0,0);
		glTexCoord2f(1.0, -1.0); glVertex3f(resX*2,resY,0);                        
		glTexCoord2f(0.0, -1.0); glVertex3f(0,resY,0);
	glEnd();
glEndList();
}

void staticTrees()
{
glNewList(dlist[3], GL_COMPILE);
glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(0,0,0);
		glTexCoord2f(1.0, 0.0); glVertex3f(resX*2,0,0);
		glTexCoord2f(1.0, -1.0); glVertex3f(resX*2,resY,0);                        
		glTexCoord2f(0.0, -1.0); glVertex3f(0,resY,0);
	glEnd();
glEndList();
}

void staticTrees_2()
{
glNewList(dlist[5], GL_COMPILE);
glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(0,0,0);
		glTexCoord2f(1.0, 0.0); glVertex3f(resX*2,0,0);
		glTexCoord2f(1.0, -1.0); glVertex3f(resX*2,resY,0);                        
		glTexCoord2f(0.0, -1.0); glVertex3f(0,resY,0);
	glEnd();
glEndList();
}

void staticBrick()
{
//... BOTTOM BRICK	
glNewList(dlist[4], GL_COMPILE);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(resX,-resY/2,0);
		glTexCoord2f(1.0, 0.0); glVertex3f(resX+50,-resY/2,0);
		glTexCoord2f(1.0, -1.0); glVertex3f(resX+50,resY/2-25,0);                        
		glTexCoord2f(0.0, -1.0); glVertex3f(resX,resY/2-25,0);
	glEnd();

//.... TOP BRICK
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(resX,resY+resY/2,0);
		glTexCoord2f(1.0, 0.0); glVertex3f(resX+50,resY+resY/2,0);
		glTexCoord2f(1.0, -1.0); glVertex3f(resX+50,resY/2+25,0);                        
		glTexCoord2f(0.0, -1.0); glVertex3f(resX,resY/2+25,0);
	glEnd();

glEndList();
}

int hit1,hit2;
void resetFunc()
{

highscore=(highscore<score)?score:highscore;
hit1=0;hit2=0;
movementY=0;
groundX=0;
skyX=0;
treeX=0;
treeX2=0;
obstacleBrick.clear();
score=0;
}

void hitDetection()
{
	for(i=0;i<obstacleBrick.size();i++)
	{		
			//Closest Brick X                      Further Brick X
		if( (resX+obstacleBrick[i].objdisp)>=0 && (resX+50+obstacleBrick[i].objdisp)<=100 )
		{

				//Bottom Brick Y original=(movementY+resY/2)				Top Brick Y	 original=(movementY+resY/2+25)				                           
			if( (movementY+(resY/2)+5) >= ( ((resY/2)-40)+ obstacleBrick[i].y) && (movementY+(resY/2)+45) <= ( ((resY/2)+40) +obstacleBrick[i].y) )
			{
				hit1++;				
	 		}
			else 
			{
				hit2++;
			}
				
		}	
		if(hit1<hit2)
			resetFunc();
		if(movementY<-(resY/2-25))
			resetFunc();

	}
}


GLvoid *font_style = GLUT_STROKE_ROMAN;
void renderStrokeFont(int x,int y,int z,const char* temp)
{
  glPushMatrix();
  glTranslatef(x,y,z);
  glLineWidth(2);
  glScalef(0.1,0.1,0.1);
  const char *c;
  
  for (c=temp; *c != '\0'; c++) {
    glutStrokeCharacter(font_style, *c);
  }

  glPopMatrix();
}


int opt1;
void draw()
{

	glClearColor (1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(opt1==0)
	{
		init();
		initialiseList();
		staticBrick();
		staticGround();
		staticBird();
		staticSky();
		staticTrees();
		staticTrees_2();
		opt1=1;
	}
	else
	{

	//...SKY	
	glPushMatrix();
	glTranslatef(skyX,0,0);
	glBindTexture(GL_TEXTURE_2D, texBac[0]);
	glCallList(dlist[2]);
	glPopMatrix();

	//...SCORE & TEXT
	glColor3f(0.5,0.5,0.5);
	string str2=">FLOPPY BIRD >Movement: Up key >Exit: ESC ";
	if(score==0)
	{
	const char * t2 = str2.c_str();
	renderStrokeFont(100,400,0,t2);
	}
	string str="Score: "+to_string(score)+"  HighScore: "+to_string(highscore);
	const char * c = str.c_str();
	renderStrokeFont(10,resY-25,0,c);
	glColor3f(1,1,1);

	//..TREES
	glPushMatrix();
	glTranslatef(treeX2,0,0);
	glBindTexture(GL_TEXTURE_2D, texObj[2]);
	glCallList(dlist[5]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(treeX,0,0);
	glBindTexture(GL_TEXTURE_2D, texObj[0]);
	glCallList(dlist[3]);
	glPopMatrix();

	//..BRICK GENERATION
	if(tmp==100)
	{
		tmp=0;
		obj.x=0;
		obj.y= -100+rand()%200;
		obj.objdisp=0;
		obstacleBrick.push_back(obj);

	}
	else
	{
		tmp++;
	}

	//..BRICK
	for(j=0;j<obstacleBrick.size();j++)
	{
	obstacleBrick[j].objdisp-=4;
	if(obstacleBrick[j].objdisp<-(resX+100))
	{
	score++;hit1=0;hit2=0;
	obstacleBrick.erase(obstacleBrick.begin()+j);
	}	
	else
	{
	glPushMatrix();
	glTranslatef(obstacleBrick[j].objdisp,obstacleBrick[j].y,0);
	glBindTexture(GL_TEXTURE_2D, texObj[1]);
	glCallList(dlist[4]);
	glPopMatrix();
	}
	}

	//..GROUND	
	glPushMatrix();
	glTranslatef(groundX,0,0);
	glBindTexture(GL_TEXTURE_2D, texBac[1]);
	glCallList(dlist[1]);
	glPopMatrix();

	//...BIRD
	glPushMatrix();
	glTranslatef(movementX,movementY,0);
	glBindTexture(GL_TEXTURE_2D, texBird[birdPhys]);
	glCallList(dlist[0]);
	glPopMatrix();		
	
	}

	hitDetection();
glFinish();
glutSwapBuffers();
}
