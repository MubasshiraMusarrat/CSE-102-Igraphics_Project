# include "iGraphics.h"
# include<stdio.h>
# include<conio.h>
# include<math.h>
# include "gl.h"


# define screenHeight 650
# define screenWidth 1024


//curve properties
double x, y[5], z;
double a[5] = {75, 60, 87, 102, 73}, angle[5] = {1, 2, .5, 1.33, .7}, phase = 0;

//ball position & increament
double ball_x = 0, ball_y[5] = {0}, ball_z, dx = 4.0;

//text gapping
double text_x = 10, text_y = 630;

//toggle a single curve
int count[5] = {1, 1, 1, 0, 0}, mode[5]= {0}, newBall[2] = {0};

//kite position
double pic_x = screenWidth, pic_y;

int showCurve = 1, showBall = 1, homepage = 1, showText = 0;


/*
	function iDraw() is called again and again by the system.
*/
void text(); //function to write the instruction.

void curve() //function to draw the curves.
{
    for( x=0; x<=screenWidth; x++)
    {
        y[0] = a[0]* sin( angle[0]* (phase+ x*3.1416/180));
        if( count[0] )
        {
            glColor4ub(255, 127, 39, .7*255);   //filling the curve & controlling transperency
            iLine(x, screenHeight/2, x, screenHeight/2+y[0]);
            iSetColor(255, 127, 39);
            iPoint(x, screenHeight/2+y[0], .5);
        }

        y[1]=a[1]*cos(angle[1]*(phase+x*3.1416/180));
        if(count[1])
        {
            glColor4ub(0,255,0,.45*255);
            iLine(x,screenHeight/2,x,screenHeight/2+y[1]);
            iSetColor(0,255,0);
            iPoint(x,screenHeight/2+y[1],1);
        }

        y[2]=a[2]*sin(angle[2]*(phase+x*3.1416/180));
        if(count[2])
        {
            glColor4ub(0,0,255,.3*255);
            iLine(x,screenHeight/2,x,screenHeight/2+y[2]);
            iSetColor(0,0,255);
            iPoint(x,screenHeight/2+y[2],1);
        }

        if(newBall[0]) //plotting new curves
        {
            y[3]=a[3]*cos(angle[3]*(phase+x*3.1416/180));
            if(count[3])
            {
                glColor4ub(0,255,255,.4*255);
                iLine(x,screenHeight/2,x,screenHeight/2+y[3]);
                iSetColor(0,255,255);
                iPoint(x,screenHeight/2+y[3],1);
            }
        }

        if(newBall[1])
        {
            y[4]=a[4]*sin(angle[4]*(phase+x*3.1416/180));
            if(count[4])
            {
                glColor4ub(255,255,0,.4*255);
                iLine(x,screenHeight/2,x,screenHeight/2+y[4]);
                iSetColor(255,255,0);
                iPoint(x,screenHeight/2+y[4],1);
            }
        }

        z=y[0]+y[1]+y[2]+y[3]+y[4]; //summation of the curves
        glColor4ub(206,86,241,.35*255);
        iLine(x,screenHeight/2,x,screenHeight/2+z);
        iSetColor(206,86,241);
        iPoint(x,screenHeight/2+z,1);
    }
}


void iDraw()
{
    //place your drawing codes here
    int i;
    iClear();

    iShowBMP( 0, 0, "sky.bmp"); //background

    iShowBMP2(pic_x,pic_y,"kite.bmp",0);

    if(showText) //show instruction
    {
        text();
    }

    iSetColor(255,0,0); //x-axis line
    iLine(0,screenHeight/2,screenWidth,screenHeight/2);

    if(showCurve) //toggle all the curves altogther
    {
        curve();
    }

    if(showBall) //toggle the balls
    {
        for(i=0; i<3; i++)
        {
            if(count[i]) //toggle balls with the curve
            {
                iSetColor(255, 255, 255);
                iFilledCircle(ball_x,screenHeight/2+ball_y[i], 6);
            }
        }
        for(i=3; i<5; i++)
        {
            if(count[i] && newBall[i-3]) //show balls with newly plotted curves & toogle
            {
                iSetColor(100, 50, 255);
                iFilledCircle(ball_x,screenHeight/2+ball_y[i], 6);
            }
        }

        iSetColor(150, 0, 150); //ball at the sum curve
        iFilledCircle(ball_x,ball_z,6);
    }

    iSetColor(0, 0, 0);
    iText(20, 20, "Left click on the curve & drag the mouse to change the amplitude of a particular curve.",GLUT_BITMAP_TIMES_ROMAN_24);

    if(homepage) //view homepage
    {
        iShowBMP(0, 0, "help.bmp");
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouseMove(int mx, int my)
{
    //place your codes here
    int j; //
    for(j=0; j<5; j++) //change the amplitude of the clicked curve
     {
        if(mode[j])
        {
            a[j] =my-screenHeight/2;
        }
    }

}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouse(int button, int state, int mx, int my)
{
    int i;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //activate a curve
        if(my>=(screenHeight/2+a[0]*sin(angle[0]*(phase+mx*3.1416/180))-2) && my<=(screenHeight/2+a[0]*sin(angle[0]*(phase+mx*3.1416/180))+2))
        {
            for(i=0; i<5; i++) //deactivate all the curves at first
            {
                mode[i]=0;
            }
            mode[0]=1;
        }

        if(my>=(screenHeight/2+a[1]*cos(angle[1]*(phase+mx*3.1416/180))-2) && my<=(screenHeight/2+a[1]*cos(angle[1]*(phase+mx*3.1416/180))+2))
        {
            for(i=0; i<5; i++)
            {
                mode[i]=0;
            }
            mode[1]=1;
        }

        if(my>=(screenHeight/2+a[2]*sin(angle[2]*(phase+mx*3.1416/180))-2) && my<=(screenHeight/2+a[2]*sin(angle[2]*(phase+mx*3.1416/180))+2))
        {
            for(i=0; i<5; i++)
            {
                mode[i]=0;
            }
            mode[2]=1;
        }

        if(my>=(screenHeight/2+a[3]*cos(angle[3]*(phase+mx*3.1416/180))-2) && my<=(screenHeight/2+a[3]*cos(angle[3]*(phase+mx*3.1416/180))+2))
        {
            for(i=0; i<5; i++)
            {
                mode[i]=0;
            }
            mode[3]=1;
        }

        if(my>=(screenHeight/2+a[4]*sin(angle[4]*(phase+mx*3.1416/180))-2) && my<=(screenHeight/2+a[4]*sin(angle[4]*(phase+mx*3.1416/180))+2))
        {
            for(i=0; i<5; i++)
            {
                mode[i]=0;
            }
            mode[4]=1;
        }

    }
    //if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    //place your codes here.
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/

void iKeyboard(unsigned char key)
{
    int i;

    if(key=='p'||key=='P') //pause balls
    {
        iPauseTimer(0);
    }

    if(key=='r'||key=='R') //resume balls
    {
        iResumeTimer(0);
    }

    if(key=='a') //increase amplitude of the curves
    {
        for(i=0; i<5; i++)
        {
            if(a[i]<=screenHeight/4)
            {
                a[i]+=3;
            }
        }
    }

    if(key=='A') //decrease amplitude
    {
        for(i=0; i<5; i++)
        {
            if(a[i]>0)
            {
                a[i]-=3;
            }
        }
    }

    if(key=='f') //increase or decrease frequency of the curves
    {
        for(i=0; i<5; i++)
        {
            if(angle[i]<screenWidth/100)
            {
                angle[i]++;
            }
        }
    }

    if(key=='F')
    {
        for(i=0; i<5; i++)
        {
            if(angle[i]>0)
            {
                angle[i]--;
            }
        }
    }

    if(key== '+' ) //change speed of the balls
    {
        if(dx>=0)
        {
          dx+=2;
        }
        else
            dx-=2;

    }

    if(key== '-' )
    {
        if(dx>0)
        {
            dx-=2;
        }
       if(dx<0)
       {
           dx+=2;
       }

    }

    if(key =='s' || key =='S') //toggle all curve
    {
        showCurve=!showCurve;
    }

    if(key =='j' || key =='J') //toggle all ball
    {
        showBall=!showBall;
    }

    if(key=='o'||key=='O') //toggle single curves
    {
        count[0]=!count[0];
    }

    if(key=='g'||key=='G')
    {
        count[1]=!count[1];
    }

    if(key=='b'||key=='B')
    {
        count[2]=!count[2];
    }

    if(key=='c'||key=='C')
    {
        newBall[0]=1;
        count[3]=!count[3];
    }

    if(key=='y'|| key=='Y')
    {
        newBall[1]=1;
        count[4]=!count[4];
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

void iSpecialKeyboard(unsigned char key)
{
    switch(key)
    {
    case GLUT_KEY_END:
        exit(0);
        break;
    case GLUT_KEY_LEFT: //change the curves to left or right
        phase++;
        break;
    case GLUT_KEY_RIGHT: //
        phase--;
        break;
    case GLUT_KEY_F1:
        homepage=0;
        break;
    case GLUT_KEY_F2: //toggle instruction
        showText=!showText;
        break;

    }
    //place your codes for other keys here
}


void ballChange()
{
    ball_x += dx;
    ball_y[0] = a[0]*sin(angle[0]*(phase+ball_x*3.1416/180));
    ball_y[1] = a[1]*cos(angle[1]*(phase+ball_x*3.1416/180));
    ball_y[2] = a[2]*sin(angle[2]*(phase+ball_x*3.1416/180));

    if(newBall[0]) //show balls with new curves
    {
        ball_y[3] = a[3]*cos(angle[3]*(phase+ball_x*3.1416/180));
    }

    if(newBall[1])
    {
        ball_y[4] = a[4]*sin(angle[4]*(phase+ball_x*3.1416/180));
    }

    ball_z=screenHeight/2+ball_y[0]+ball_y[1]+ball_y[2]+ball_y[3]+ball_y[4];

    if(ball_x>screenWidth || ball_x<0) dx*=-1;
}


void pictureChange() //kite animation
{
    pic_x-=4;
    pic_y=4*.0001*pic_x*pic_x;
    if(pic_x==0)
    {
        pic_x=screenWidth;

    }
}


void text() //instructions
{
    double j=20.0; //gap between each line

    iSetColor(255,255,255);
    iText(text_x,text_y,"Toogle Curves: s/S" );
    iText(text_x,text_y-j,"Toggle Balls Show/Hide: j/J");
    iText(text_x,text_y-2*j,"Pause Animation: p/P");
    iText(text_x,text_y-3*j,"Resume Animation: r/R");
    iText(text_x,text_y-4*j,"Increase Amplitude: a");
    iText(text_x,text_y-5*j,"Decrease Amplitude: A");
    iText(text_x,text_y-6*j,"Increase Frequency: f");
    iText(text_x,text_y-7*j,"Decrease Frequency: F");
    iText(text_x,text_y-8*j,"Increase Speed: '+' ");
    iText(text_x,text_y-9*j,"Decrease Speed: '-' ");
    iText(text_x,text_y-10*j,"Change Curves To Right: 'Right Arrow Key' ");
    iText(text_x,text_y-11*j,"Change Curves To Right: 'Left Arrow Key' ");



    iSetColor(0,0,0);
    iText(text_x,text_y-20*j,"Toggle A Specific Curve Pressing The First Letter Of Its Color");
    iText(text_x,text_y-21*j,"o/O For Orange",GLUT_BITMAP_HELVETICA_10);
    iText(text_x,text_y-22*j,"y/Y For Yellow",GLUT_BITMAP_HELVETICA_10);
    iText(text_x,text_y-23*j,"g/G For Green",GLUT_BITMAP_HELVETICA_10);
    iText(text_x,text_y-24*j,"c/C For Cyan/Light Blue",GLUT_BITMAP_HELVETICA_10);
    iText(text_x,text_y-25*j,"b/B For Blue",GLUT_BITMAP_HELVETICA_10);
}


int main()
{
    //place your own initialization codes here.
    iSetTimer(15, ballChange);
    iSetTimer(16,pictureChange);

    iInitialize(screenWidth,screenHeight, "iGraphics");


    return 0;
}

