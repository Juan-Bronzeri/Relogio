
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 
#include <math.h>
#define PI 3.142
#include <winsock.h>
#include <unistd.h>

void init(void);
void desenha(void);
void teclado(unsigned char key, int x, int y);
static void SpecialKey(int key, int x, int y);
void MouseClick(int button, int state, int x, int y);
void movimentarRight(void);
void movimentarUp(void);
void movimentarDowm(void);
void movimentarLeft(void);
void ponteiroSeg(int s);
void relogio(void);
void MouseClick (int button, int state, int x, int y);
// assinatura da funçao que recebe um texto e imprime.
void DesenhaTextoStroke(void *font, char *string);

int px = 100, py = 100;
int p1x = 100, p1y = 139;
int p2x = 100, p2y = 128;
int p3x = 100, p3y = 144;
float angulo;
int raio = 50;
int raioP1 = 40;
int raioP2 = 30;
int raioP3 = 45;
int i1 = 0;
int i2 = 0;
int i3 = 0;
int aux = 0;
int s = 0, m = 0, h = 0, is = 0, im = 0, ih = 0;
time_t start, delta, endwait;

int main(int argc, char** argv) 
{
	start=time(NULL);

  	glutInit(&argc, argv);
  	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize (600, 600); 
  	glutInitWindowPosition (50, 50); 
  	glutCreateWindow ("Relogio");
  
  	init();
  	glutDisplayFunc(desenha); 
  	glutKeyboardFunc(teclado);
  	glutSpecialFunc(SpecialKey);
  	// Click em um botão
  	glutMouseFunc(MouseClick);
  	glutMainLoop();
}
	
void init(void)
{
  	glClearColor(1.0, 1.0, 1.0, 1.0);
  	glOrtho (0, 256, 0, 256, -1 ,1);
}

void desenha(void)
{
  	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(0.8f, 0.8f, 0.8f);
  	glLineWidth(1.5); 

  	int i;
  	float angulo;
  
  	glBegin(GL_POLYGON);
    	for (i = 0; i < 1440; i++) 
		{
    		angulo = i * PI / 180;
    		glVertex2f(100 + raio * cos(angulo), 100 + raio * sin(angulo));
		}
  	glEnd();
  
  	//numero 1
    glBegin(GL_LINE_STRIP);
    	glColor3f(1.0f, 0.0f, 0.0f);
    	glLineWidth(100.0f);
    	glVertex2f(90, 140);
    	glVertex2f(95, 145);
    	glVertex2f(95, 135);
    glEnd();
    
    //numero 2
    glBegin(GL_LINE_STRIP);
    	glColor3f(1.0f, 0.0f, 0.0f);
    	glLineWidth(100.0f);
    	glVertex2f(100, 145);
    	glVertex2f(105, 145);
    	glVertex2f(105, 140);
    	glVertex2f(100, 140);
    	glVertex2f(100, 135);
    	glVertex2f(105, 135);
    glEnd();
    
    //numero 3
    glBegin(GL_LINE_STRIP);
    	glColor3f(1.0f, 0.0f, 0.0f);
    	glLineWidth(100.0f);
    	glVertex2f(140, 105);
    	glVertex2f(145, 105);
    	glVertex2f(145, 100);
    	glVertex2f(140, 100);
    	glVertex2f(145, 100);
    	glVertex2f(145, 95);
    	glVertex2f(140, 95);
    glEnd();
    
    //numero 6
    glBegin(GL_LINE_STRIP);
    	glColor3f(1.0f, 0.0f, 0.0f);
    	glLineWidth(100.0f);
    	glVertex2f(100, 65);
    	glVertex2f(95, 65);
    	glVertex2f(95, 55);
    	glVertex2f(100, 55);
    	glVertex2f(100, 60);
    	glVertex2f(95, 60);
    glEnd();
    
    //numero 9
    glBegin(GL_LINE_STRIP);
    	glColor3f(1.0f, 0.0f, 0.0f);
    	glLineWidth(100.0f);
    	glVertex2f(60, 100);
    	glVertex2f(55, 100);
    	glVertex2f(55, 105);
    	glVertex2f(60, 105);
    	glVertex2f(60, 95);
    	glVertex2f(55, 95);
    glEnd();
  	
  	glLineWidth(2.0f);
  	//ponteiro minutos
  	glBegin(GL_LINES);
  		glColor3f(0.0f, 0.0f, 0.0f);
    	glVertex2i(px, py);
    	glVertex2i(p1x, p1y);
  	glEnd();
  
  	glLineWidth(2.5f);
	  //ponteiro horas
	glBegin(GL_LINES);
  		glColor3f(0.0f, 0.0f, 0.0f);
    	glVertex2i(px, py);
    	glVertex2i(p2x, p2y);
  	glEnd();
  	
  	glLineWidth(1.0f);
  	//ponteiro segundos
  	glBegin(GL_LINES); 
  		glColor3f(0.0f, 0.0f, 0.0f);
    	glVertex2i(px, py);
    	glVertex2i(p3x, p3y);
  	glEnd();
  	
  	//botão
  	glBegin(GL_QUADS);
  		glColor3f(0.5f, 0.5f, 0.7f);
        glVertex2i(50,45);
        glVertex2i(50,25);  
        glVertex2i(90,25);
        glVertex2i(90,45);               
     glEnd();
     
    glPushMatrix();	
    	glColor3f(1.0f, 1.0f, 1.0f);
  		glTranslatef(54, 30, 0);      // altera a origem do sistema de coordenadas para (x, y, z) 0, 0, 0
  		glScalef(0.1, 0.1, 0.1); // diminui o tamanho da fonte do texto através de uma tranformação de escala
  		//glRotatef(15, 0, 0, 1);   // rotaciona o texto
  		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"PLAY");
  		// função glPopMatrix devole os parametros inciais lembrados pela funcao glPushMatrix 
  	glPopMatrix();
     
      	//botão
  	glBegin(GL_QUADS);
  		glColor3f(0.5f, 0.5f, 0.7f);
        glVertex2i(109,45);
        glVertex2i(109,25);  
        glVertex2i(150,25);
        glVertex2i(150,45);               
     glEnd();
     
     glPushMatrix();	
    	glColor3f(1.0f, 1.0f, 1.0f);
  		glTranslatef(111, 30, 0);      // altera a origem do sistema de coordenadas para (x, y, z) 0, 0, 0
  		glScalef(0.09, 0.09, 0.09); // diminui o tamanho da fonte do texto através de uma tranformação de escala
  		//glRotatef(15, 0, 0, 1);   // rotaciona o texto
  		DesenhaTextoStroke(GLUT_STROKE_ROMAN,"PAUSE");
  		// função glPopMatrix devole os parametros inciais lembrados pela funcao glPushMatrix 
  	glPopMatrix();
  	
  glFlush();
}


void teclado(unsigned char key, int x, int y)
{
  switch (key) 
  {  	  
  	case 27:
		exit(0);
		break;
  }    
}

void movimentarUp(void) 
{
	if(i1 == 0)
	{
		i1 = 6;
		angulo = i1 * PI / 180;
    	p1x = 100 + raioP1 * sin(angulo);
		p1y = 100 + raioP1 * cos(angulo);
	}
	else
	{
		i1 += 6;
		angulo = i1 * PI / 180;
    	p1x = 100 + raioP1 * sin(angulo);
		p1y = 100 + raioP1 * cos(angulo);
	}
	if(im == 59)
	{
		im = 0;
		movimentarRight();
	}	
	else
		im++;
	
}

void movimentarDowm(void) 
{
	if(i1 == 0)
	{
		i1 = -6;
		angulo = i1 * PI / 180;
    	p1x = 100 + raioP1 * sin(angulo);
		p1y = 100 + raioP1 * cos(angulo);
	}
	else
	{
		i1 -= 6;
		angulo = i1 * PI / 180;
    	p1x = 100 + raioP1 * sin(angulo);
		p1y = 100 + raioP1 * cos(angulo);
	}
	if(im == 0)
		im = 59;
	else	
		im--;
}

void movimentarRight(void) 
{
	if(i2 == 0)
	{
		i2 = 15;
		angulo = i2 * PI / 180;
    	p2x = 100 + raioP2 * sin(angulo);
		p2y = 100 + raioP2 * cos(angulo);
	}
	else
	{
		i2 += 15;
		angulo = i2 * PI / 180;
    	p2x = 100 + raioP2 * sin(angulo);
		p2y = 100 + raioP2 * cos(angulo);
	}
	if(ih == 59)
		ih = 0;
	else
		ih++;
}

void movimentarLeft(void) 
{
	if(i2 == 0)
	{
		i2 = -15;
		angulo = i2 * PI / 180;
    	p2x = 100 + raioP2 * sin(angulo);
		p2y = 100 + raioP2 * cos(angulo);
	}
	else
	{
		i2 -= 15;
		angulo = i2 * PI / 180;
    	p2x = 100 + raioP2 * sin(angulo);
		p2y = 100 + raioP2 * cos(angulo);
	}
	if(ih == 0)
		ih = 59;
	else
		ih--;
}

void ponteiroSeg(int s) 
{
	while(s > is)
	{
		if(i3 == 0)
		{
			i3 = 6;
			angulo = i3 * PI / 180;
    		p3x = 100 + raioP3 * sin(angulo);
			p3y = 100 + raioP3 * cos(angulo);
		}
		else
		{
			i3 += 6;
			angulo = i3 * PI / 180;
    		p3x = 100 + raioP3 * sin(angulo);
			p3y = 100 + raioP3 * cos(angulo);
		}
		if(is == 60)
			is = 0;
		else
			is++;
	}
}

static void SpecialKey(int key, int x, int y)
{
  switch (key) 
  {
  case GLUT_KEY_UP:
	movimentarUp();
	desenha();
    break;
  case GLUT_KEY_DOWN:
  	movimentarDowm();
  	desenha();
    break;
  case GLUT_KEY_LEFT:
  	movimentarLeft();
  	desenha();
    break;
  case GLUT_KEY_RIGHT:
   	movimentarRight();
   	desenha();
    break;
  }
}

void relogio(void)
{
	if(aux != 0)
	{
		delta=time(NULL)-start;
	
    	s=delta%60;
    	if(is != s)
    	{
    		ponteiroSeg(s);
			desenha();
		}
 	   	m=(delta/60)%60;
 	   	if(is == 60)
  	  	{
   	 		movimentarUp();
			desenha();
    		is = 0;
		}
    	h=(delta/3600)%24;
    	if(im == 60)
    	{
    		movimentarRight();
			desenha();
    		im = 0;
		}
		glutTimerFunc(1000, relogio, 0);
	}
	else
		delta = s*60;
	printf("%i", s);
}

void MouseClick (int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON: 
    		if(x < 210 && x > 117 && y < 540 && y > 495)
    		{
    			aux = 1;
    			glutTimerFunc(1000, relogio, 0);
			}
			else if(x < 350 && x > 255 && y < 540 && y > 495) aux = 0;
            break;     
    }
}

void DesenhaTextoStroke(void *font, char *string) 
{  
	// Exibe caractere a caractere
	while(*string) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++); 
	}
		
}
