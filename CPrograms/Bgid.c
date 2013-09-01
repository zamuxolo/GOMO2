
#ifdef __TINY__
#error BGIDEMO will not run in the tiny model.
#endif

#include <dos.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <graphics.h>

#define ESC	0x1b
#define TRUE	1
#define FALSE	0
#define PI	3.14159
#define ON	1
#define OFF	0

#define NFONTS 11
int ch,snd=1,trans=0;
char *Fonts[NFONTS] = {
  "DefaultFont",   "TriplexFont",   "SmallFont",
  "SansSerifFont", "GothicFont", "ScriptFont", "SimplexFont", "TriplexScriptFont",
  "ComplexFont", "EuropeanFont", "BoldFont"
};

char *LineStyles[] = {
  "SolidLn",  "DottedLn",  "CenterLn",  "DashedLn",  "UserBitLn"
};

char *FillStyles[] = {
  "EmptyFill",  "SolidFill",      "LineFill",      "LtSlashFill",
  "SlashFill",  "BkSlashFill",    "LtBkSlashFill", "HatchFill",
  "XHatchFill", "InterleaveFill", "WideDotFill",   "CloseDotFill"
};

char *TextDirect[] = {
  "HorizDir",  "VertDir"
};

char *HorizJust[] = {
  "LeftText",   "CenterText",   "RightText"
};

char *VertJust[] = {
  "BottomText",  "CenterText",  "TopText"
};

struct PTS {
  int x, y;
};	/* Structure to hold vertex points	*/

int    GraphDriver;		/* The Graphics device driver		*/
int errorcodeg;
int    GraphMode;		/* The Graphics mode value		*/
double AspectRatio;		/* Aspect ratio of a pixel on the screen*/
int    MaxX, MaxY;		/* The maximum resolution of the screen */
int    MaxColors;		/* The maximum # of colors available	*/
int    ErrorCode;		/* Reports any graphics errors		*/
struct palettetype palette;		/* Used to read palette info	*/

void Initialize(void);
void PutPixelDemo(void);
void PutImageDemo(void);
void Pause(void);
void MainWindow(char *header);
void StatusLine(char *msg);
void DrawBorder(void);
void changetextstyle(int font, int direction, int charsize);


int main()
{

  Initialize();
  if( GraphDriver==EGA || GraphDriver==EGALO || GraphDriver==VGA )
  PutPixelDemo();
  PutImageDemo();
  closegraph();
  return(0);
}

void Initialize(void)
{
  int xasp, yasp;			/* Used to read the aspect ratio*/
errorcodeg = registerbgidriver(EGAVGA_driver);
if (errorcodeg <= 0)   exit(0);

  initgraph( &GraphDriver, &GraphMode, "" );
  ErrorCode = graphresult();		/* Read result of initialization*/
  if( ErrorCode != grOk ){		/* Error occured during init	*/
    printf(" Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );
    exit( 1 );
  }

  getpalette( &palette );		/* Read the palette from board	*/
  MaxColors = getmaxcolor() + 1;	/* Read maximum number of colors*/

  MaxX = getmaxx();
  MaxY = getmaxy();			/* Read size of screen		*/

  getaspectratio( &xasp, &yasp );	/* read the hardware aspect	*/
  AspectRatio = (double)xasp / (double)yasp; /* Get correction factor	*/

}

void PutPixelDemo(void)
{
  int seed = 1958;
  int i, x, y, h, w, color;
  struct viewporttype vp;

  MainWindow( "ScreenSaver By Mr. Sameer Potdar   " );

  getviewsettings( &vp );
  h = vp.bottom - vp.top;
  w = vp.right	- vp.left;

  srand( seed );			/* Restart random # function	*/

  for( i=0 ; i<5000 ; ++i ){		/* Put 5000 pixels on screen	*/
    x = 1 + random( w - 1 );		/* Generate a random location	*/
    y = 1 + random( h - 1 );
    color = random( MaxColors );
    putpixel( x, y, color );
  }

  srand( seed );			/* Restart Random # at same #	*/

  for( i=0 ; i<5000 ; ++i ){		/* Take the 5000 pixels off	*/
    x = 1 + random( w - 1 );		/* Generate a random location	*/
    y = 1 + random( h - 1 );
    color = getpixel( x, y );		/* Read the color pixel 	*/
    if( color == random( MaxColors ) )	/* Used to keep RANDOM in sync	*/
      putpixel( x, y, 0 );		/* Write pixel to BLACK 	*/
  }
}
void PutImageDemo(void)
{
  static int r	    = 20;
  static int StartX = 100;
  static int StartY = 50;

  struct viewporttype vp;
  int PauseTime, x, y, ulx, uly, lrx, lry, size, i, width, height, step;
  void *Saucer;
  void *Saucer1;
  MainWindow( "ScreenSaver By Mr. Sameer Potdar   " );
  getviewsettings( &vp );
  /* Draw Saucer */
  setfillstyle(9,12);
  fillellipse(StartX, StartY, r, (r/3)+2);
  setfillstyle(5,12);
  fillellipse(StartX, StartY-10, r-10, (r/3)+1);
  setfillstyle(1,14);
  fillellipse(StartX, StartY-4, r, r/3);
  line(StartX+7, StartY-6, StartX+10, StartY-12);
  circle(StartX+10, StartY-12, 2);
  line(StartX-7, StartY-6, StartX-10, StartY-12);
  circle(StartX-10, StartY-12, 2);


  /* Read saucer image */
  ulx = StartX-(r+1);
  uly = StartY-14;
  lrx = StartX+(r+1);
  lry = StartY+(r/3)+3;
  width = lrx - ulx + 1;
  height = lry - uly + 1;
  size = imagesize(ulx, uly-10, lrx, lry);

  Saucer = malloc( size );
  getimage(ulx, uly-10, lrx, lry, Saucer);
  putimage(ulx, uly-10, Saucer, XOR_PUT);

/* Plot some "stars"  */
  for ( i=0 ; i<1000; ++i )
    putpixel(random(MaxX), random(MaxY), random( MaxColors-1 )+1);
  x = MaxX / 2;
  y = MaxY / 2;
  PauseTime = 100;

  /* until a key is hit */
  do
   {
       /* Draw the Saucer */
    if(trans==1)  putpixel(random(MaxX), random(MaxY), random( MaxColors-1 )+1);
    sound(snd*(x+y+10));
    putimage(x, y, Saucer, XOR_PUT);		     /*  draw image  */
    delay(PauseTime);
    putimage(x, y, Saucer, XOR_PUT);		     /* erase image  */
     /* Move Saucer */
     step = random( 2*r );
    if ((step/2) % 2 != 0 )
      step = -1 * step;
    x = x + step;
    step = random( r );
    if ((step/2) % 2 != 0 )
      step = -1 * step;
    y = y + step;

    if (vp.left + x + width - 1 > vp.right)
      x = vp.right-vp.left-width + 1;
    else
      if (x < 0)
	x = 0;
    if (vp.top + y + height - 1 > vp.bottom)
      y = vp.bottom-vp.top-height + 1;
    else
      if (y < 0)
	y = 0;
      if(kbhit()) {ch=getch();
      switch(ch)
     { case 48:
	       PauseTime=100;
	       sound(snd*500);delay(30);nosound();
	       break;

       case 49:
	       PauseTime=60;
	       sound(snd*600);delay(20);nosound();
	       break;
       case 50:
	       PauseTime=50;
	       sound(snd*700);delay(20);nosound();

	       break;
       case 51:PauseTime=40;sound(snd*800);delay(20);nosound();break;
       case 52:PauseTime=30;sound(snd*900);delay(20);nosound();break;
       case 53:PauseTime=20;sound(snd*1000);delay(20);nosound();break;
       case 54:PauseTime=15;sound(snd*1100);delay(20);nosound();break;
       case 55:PauseTime=10;sound(snd*1200);delay(30);nosound();break;
       case 56:PauseTime=5;sound(snd*1300);delay(40);nosound();break;
       case 57:PauseTime=1;sound(snd*1500);delay(50);nosound();;break;
       case 110:snd=0;
		sound(600);delay(20);nosound();
		setviewport( 0, 0, MaxX, MaxY, 1 );
		setcolor(0);
		outtextxy( MaxX/2-250,2,"лллллллллллллл");
		outtextxy( MaxX/2-250,1,"лллллллллллллл");
		outtextxy( MaxX/2-250,0,"лллллллллллллл");
		setcolor(14);
		outtextxy( MaxX/2-295,2,"S ");
		setcolor(12);
		outtextxy( MaxX/2-245,2," For   Sound");
		setviewport( 10, 15, MaxX, MaxY, 1 );
		getviewsettings( &vp );
		break;
       case 78:snd=0;
		sound(600);delay(20);nosound();
		setviewport( 0, 0, MaxX, MaxY, 1 );
		setcolor(0);
		outtextxy( MaxX/2-250,2,"лллллллллллллл");
		outtextxy( MaxX/2-250,1,"лллллллллллллл");
		outtextxy( MaxX/2-250,0,"лллллллллллллл");
		setcolor(14);
		outtextxy( MaxX/2-295,2,"S ");
		setcolor(12);
		outtextxy( MaxX/2-245,2," For   Sound");
		setviewport( 10, 15, MaxX, MaxY, 1 );
		getviewsettings( &vp );
		break;
       case 83:snd=1;
		sound(600);delay(20);nosound();
		setviewport( 0, 0, MaxX, MaxY, 1 );
		setcolor(0);
		outtextxy( MaxX/2-250,2,"лллллллллллллл");
		outtextxy( MaxX/2-250,1,"лллллллллллллл");
		outtextxy( MaxX/2-250,0,"лллллллллллллл");
		setcolor(14);
		outtextxy( MaxX/2-295,2,"N ");
		setcolor(12);
		outtextxy( MaxX/2-245,2," For NoSound");
		setviewport( 10, 15, MaxX, MaxY, 1 );
		getviewsettings( &vp );
		break;
       case 115:snd=1;
		sound(600);delay(20);nosound();
		setviewport( 0, 0, MaxX, MaxY, 1 );
		setcolor(0);
		outtextxy( MaxX/2-250,2,"лллллллллллллл");
		outtextxy( MaxX/2-250,1,"лллллллллллллл");
		outtextxy( MaxX/2-250,0,"лллллллллллллл");
		setcolor(14);
		outtextxy( MaxX/2-295,2,"N ");
		setcolor(12);
		outtextxy( MaxX/2-245,2," For NoSound");
		setviewport( 10, 15, MaxX, MaxY, 1 );
		getviewsettings( &vp );
		break;
       case 32 :if(trans==1)
		{ settextstyle(2,0,5);
		  settextjustify( 0, TOP_TEXT );
		  setcolor(0);
		  outtextxy(MaxX/2+40,-4,"лллллллллллллллллллллллллл");
		  setcolor(12);
		  outtextxy(MaxX/2+45,-4,"<  O F F  >");
		  changetextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );
		  settextjustify( CENTER_TEXT, TOP_TEXT );
		  trans=0;
		 }
		  else
		 if(trans==0)
		{ settextstyle(2,0,5);
		  settextjustify( 0, TOP_TEXT );
		  setcolor(0);
		  outtextxy(MaxX/2+40,-4,"лллллллллллллллллллллллллл");
		  setcolor(12);
		  outtextxy(MaxX/2+45,-4,"<  O   N  > ");
		  changetextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );
		  settextjustify( CENTER_TEXT, TOP_TEXT );
		  trans=1;
		}
       default:if(ch!=32) PauseTime=100;
     }
     }
  }
   while (ch!=27);
   nosound();
  free( Saucer );
  free(Saucer1);
}
void MainWindow( char *header )
{
  int height;

  cleardevice();			/* Clear graphics screen	*/
  setcolor( MaxColors - 1 );		/* Set current color to white	*/
  setviewport( 0, 0, MaxX, MaxY, 1 );	/* Open port to full screen	*/

  height = textheight( "H" );           /* Get basic text height        */

  changetextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );
  settextjustify( CENTER_TEXT, TOP_TEXT );
  settextstyle(2,0,5);
  setcolor(11);
  outtextxy( MaxX/2, -4, header );
  outtextxy( MaxX/2+1, -4, header );
  settextstyle(2,0,5);
  setcolor(9);
  outtextxy(MaxX/2-25,10,"SPACE For Transition ");
  setcolor(12);
  outtextxy(MaxX/2+97,11,"<  O F F  >");
  settextstyle(2,0,5);
  setcolor(10);
  outtextxy( MaxX/2+250,-4,"Esc To Exit");
  setcolor(14);
  outtextxy( MaxX/2-295,-4,"N ");
  setcolor(12);
  outtextxy( MaxX/2-245,-4," For  NoSound");
  setcolor(14);
  outtextxy( 35,MaxY-13,"Press 0:");
  setcolor(10);
  outtextxy( 120,MaxY-13,"Normal Speed");
  outtextxy( 121,MaxY-13,"Normal Speed");
  setcolor(13);
  outtextxy( 180,MaxY-13,"<");
  outtextxy( 181,MaxY-13,"<");
  outtextxy( 182,MaxY-13,"<");
  setcolor(10);
  outtextxy( 200,MaxY-13," 1");
  outtextxy( 230,MaxY-13," 2");
  outtextxy( 260,MaxY-13," 3");
  outtextxy( 290,MaxY-13," 4");
  outtextxy( 320,MaxY-13," 5");
  outtextxy( 350,MaxY-13," 6");
  outtextxy( 380,MaxY-13," 7");
  outtextxy( 410,MaxY-13," 8");
  outtextxy( 440,MaxY-13," 9");
  setcolor(13);
  outtextxy( 467,MaxY-13,">");
  outtextxy( 468,MaxY-13,">");
  outtextxy( 469,MaxY-13,">");
  setcolor(12);
  outtextxy( 552,MaxY-13," To INCREASE UFO Speed");
  outtextxy( 553,MaxY-13," To INCREASE UFO Speed");
  settextstyle(5,0,9);
  setcolor(12);
  outtextxy( MaxX/2+5,MaxY/2,"A Sams Art");
  setcolor(9);
  outtextxy( MaxX/2+6,MaxY/2,"A Sams Art");
  setcolor(12);
  outtextxy( MaxX/2+7,MaxY/2,"A Sams Art");
  setcolor(10);
  outtextxy( MaxX/2+8,MaxY/2,"A Sams Art");
  setcolor(14);
  outtextxy( MaxX/2+10,MaxY/2,"A Sams Art");
  changetextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );
  settextjustify( CENTER_TEXT, TOP_TEXT );
  setviewport( 0, height+4, MaxX, MaxY-(height+4), 1 );
  DrawBorder();
  setviewport( 1, height+5, MaxX-1, MaxY-(height+5), 1 );

}
void changetextstyle(int font, int direction, int charsize)
{
  int ErrorCode;

  graphresult();			/* clear error code		*/
  settextstyle(font, direction, charsize);
  ErrorCode = graphresult();		/* check result 		*/
  if( ErrorCode != grOk ){		/* if error occured		*/
    closegraph();
    printf(" Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );
    exit( 1 );
  }
}

void StatusLine( char *msg )
{
  int height;

  setviewport( 0, 0, MaxX, MaxY, 1 );	/* Open port to full screen	*/
  setcolor( MaxColors - 1 );		/* Set current color to white	*/

  changetextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );
  settextjustify( CENTER_TEXT, TOP_TEXT );
  setlinestyle( SOLID_LINE, 0, NORM_WIDTH );
  setfillstyle( EMPTY_FILL, 0 );

  height = textheight( "H" );           /* Detemine current height      */
  bar( 0, MaxY-(height+4), MaxX, MaxY );
  rectangle( 0, MaxY-(height+4), MaxX, MaxY );
  outtextxy( MaxX/2, MaxY-(height+2), msg );
  setviewport( 1, height+5, MaxX-1, MaxY-(height+5), 1 );

}
void DrawBorder(void)
{
  struct viewporttype vp;

  setcolor( 14 );		/* Set current color to white	*/

  setlinestyle( SOLID_LINE, 0, NORM_WIDTH );

  getviewsettings( &vp );
}
