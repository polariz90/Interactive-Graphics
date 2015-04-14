#include <windows.h>
#include <gl/glut.h>
#include <ctime>
#include <math.h> 
#include <iostream>

using namespace std;

GLfloat pos = 0;// variable for coordinate position.
GLfloat dc = 0.01;//variable set to 0.01 which is added to color variable to change colors.
GLfloat col = 0;//variable for color changes.
int nFPS = 30;
int dipMode=1;
long long int prevF=0,curF=0;
clock_t startClock=0,curClock;

void init(void)
{
	// init your data, setup OpenGL environment here
	glClearColor(0.9,0.9,0.9,1.0); // clear color is gray		
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // uncomment this function if you only want to draw wireframe model

	//glPointSize(4.0);
}

void timer(int v)
{
	//gives range from 0 to 2pi
	if( pos<6.28){
		pos += 0.09;
	}
	else 
		pos = 0;
	
	//if statement to change colors
		col += dc;
	if( col >= 1 || col <= 0){
		dc *= -1;
	}
	glutPostRedisplay(); // trigger display function by sending redraw into message queue
	glutTimerFunc(1000/nFPS,timer,v);
	
}

void reshape (int w, int h)
{
	// reset viewport ( drawing screen ) size
	glViewport(0, 0, w, h);
	float fAspect = ((float)w)/h; 
	// reset OpenGL projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.f,fAspect,0.001f,30.f); 
}

void keyboard(unsigned char key, int x, int y)
{
	// put your keyboard control here
	if (key == 27) 
	{
		// ESC hit, so quit
		printf("demonstration finished.\n");
		exit(0);
	}

	//if h is hit, mode changes to line-mode
	if( key == 'h'){
		dipMode = 1-dipMode;
	}
}

void DoDisplay()
{//glColor3f(0,0,0);

	 //gluLookAt(0.f,0.f,3.f,0.f,0.f,0.f,0.f,1.f,0.f);
	if(dipMode==1)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	

	curF++;
	// put your OpenGL display commands here
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// reset OpenGL transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // reset transformation matrix to identity

	// setup look at transformation so that 
	// eye is at : (0,0,3)
	// look at center is at : (0,0,0)
	// up direction is +y axis
	gluLookAt(0.f,0.f,3.f,0.f,0.f,0.f,0.f,1.f,0.f);

	glClear(GL_COLOR_BUFFER_BIT);
	
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.1,col,-col);
		glVertex2f(0.0+sin(pos)/6,1.0-cos(pos)/5);	 // #1 vertex
		glColor3f(0.1,col,-col);
		
		glVertex2f(-0.6+sin(pos)/6,1.0+sin(pos)/6);	 // #2 vertex
		glColor3f(0.2,col,-col);
		
		glVertex2f(-0.6+sin(pos)/6,0.6+cos(pos)/6);	 // #3 vertex
		glColor3f(0.4,col,-col);
		glVertex2f(-0.2+sin(pos)/20,0.6-sin(pos)/20);	 // #4 vertex
		glColor3f(0.4,col,-col);

		glVertex2f(-0.2+cos(pos)/6,-0.6+sin(pos)/6);	 // #5 vertex
		glColor3f(0.5,col,-col);
		
		glVertex2f(0.2+cos(pos)/6,-0.6+sin(pos)/6);	 // #6 vertex
		glColor3f(0.4,col,-col);

		glVertex2f(0.2+sin(pos)/20,0.6-sin(pos)/20);	 // #7 vertex
		glColor3f(0.4,col,-col);

		glVertex2f(0.6+sin(pos)/6,0.6+cos(pos)/6);	 // #8 vertex
		glColor3f(0.5,col,-col);

		glVertex2f(0.6+sin(pos)/6,1.0+sin(pos)/6);	 // #9 vertex

	glEnd();
	
		glBegin(GL_TRIANGLE_STRIP );
		glColor3f(0.3,col,-col);
		glVertex2f(-0.6+sin(pos)/6,-0.6+cos(pos)/6);// #10 vertex
		glColor3f(0.4,col,-col);
		glVertex2f(-0.6+sin(pos)/6,-1+cos(pos)/6);//#11 vertex
		glColor3f(0.4,col,-col);
		glVertex2f(-0.2+cos(pos)/6,-0.6+sin(pos)/6);// #5 vertex
		glColor3f(0.7,col,-col);
		glVertex2f(0.6+sin(pos)/6,-1-sin(pos)/6); // #12 vertex
	    glColor3f(0.5,col,-col);
		glVertex2f(0.2+cos(pos)/6,-0.6+sin(pos)/6);// #6 vertex
		glColor3f(0.6,col,-col);
		glVertex2f(0.6+sin(pos)/6, -0.6-sin(pos)/6);// #13 vertex
	
    glEnd();
	
     glFlush();
	 glutSwapBuffers();	// swap front/back framebuffer to avoid flickering 

	 curClock=clock();
	float elapsed=(curClock-startClock)/(float)CLOCKS_PER_SEC;
	if(elapsed>1.0f){
		float fps=(float)(curF-prevF)/elapsed;
		printf("fps:%f\n",fps);
		prevF=curF;
		startClock=curClock;
	}
	
}
 

void main()
{
	//glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
     glutCreateWindow("OpenGL");

	 init();
     glutDisplayFunc(DoDisplay);//call DoDisplay, the image
	 glutReshapeFunc(reshape);//called when window size is changed
	 glutKeyboardFunc(keyboard);//recieves keyboard inputs
	 glutTimerFunc(100,timer,nFPS);//periodic timer to update animation

	 startClock=clock();
     glutMainLoop();//main message loop
   //  return 0;
}