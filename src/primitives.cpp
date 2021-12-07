#include <gint/display.h>
#include <math.h>
#include "primitives.h"


/* return the sign of the number given in parameter*/
/* -1 if x<0   0 if x=0 and +1 if x>0 */
int _sgn( int x )
{
       if(x>=0)
              return 1;
       else if(x<0)
              return -1;
       else
              return 0;
}

/* return the absolute value of the number given in parameter*/
int _abs( int x )
{
       if(x>=0)
              return x;
       else
              return -1*x;
}

/* draw a pixel at coordinates (X,Y) of color (R,G,B) */
/* all color values (R,G,B) to be in the range 0..255 */
inline void _fastPixelRGB( unsigned int X, unsigned int Y, unsigned char R, unsigned char G, unsigned char B )
{
       if ( X<DWIDTH && Y<DHEIGHT)
       {
              //dpixel( X, Y, C_RGB(R,G,B)  );
              unsigned int color = (((R>>3) << 11) | ((G>>2) << 5 ) | (B>>3));
              gint_vram[ Y*DWIDTH + X ] = color;
       }
}

inline void  _fastGetPixelRGB( unsigned int X, unsigned int Y, unsigned char *R, unsigned char *G, unsigned char *B )
{
       unsigned int color =  gint_vram[ Y*DWIDTH + X ];
       *R = (((color >> 11 ) & 0b11111 ) << 3);
       *G = (((color >> 5) & 0b111111) << 2);
       *B = ((color & 0b11111) << 3);
}

/* return the color of the pixel at coordinates (X,Y) */
/* modifies R,G,B given as parameters */
/* all returns R,G,B are in range 0..255 */
void _getPixelRGB( unsigned int X, unsigned int Y, unsigned char *R, unsigned char *G, unsigned char *B )
{
       if (X<DWIDTH && Y<DHEIGHT)
       {
              unsigned int color =  gint_vram[ Y*DWIDTH + X ];
              *R = (((color >> 11 ) & 0b11111 ) << 3);
              *G = (((color >> 5) & 0b111111) << 2);
              *B = ((color & 0b11111) << 3);
       }
}

inline void _calculateBlendRGBA( unsigned int X, unsigned int Y, unsigned char *R, unsigned char *G, unsigned char *B, unsigned char A )
{
       unsigned char Ro, Go, Bo;
       _fastGetPixelRGB( X, Y, &Ro, &Go, &Bo );
       *R = Ro + (((*R-Ro)*A) >> 8);
       *G = Go + (((*G-Go)*A) >> 8);
       *B = Bo + (((*B-Bo)*A) >> 8);
}

void _pixelRGBA( unsigned int X, unsigned int Y, unsigned char R, unsigned char G, unsigned char B, unsigned char A )
{
       if (X<DWIDTH && Y<DHEIGHT)
       {
              if (A==0) return;
              else if (A==255) _fastPixelRGB( X, Y, R, G, B );
              else
              {
                     unsigned char Rf = R;
                     unsigned char Gf = G;
                     unsigned char Bf = B;
                     _calculateBlendRGBA( X, Y, &Rf, &Gf, &Bf, A );
                     _fastPixelRGB( X, Y, Rf, Gf, Bf );
              }
       }
}

void _lineRGBA( unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, unsigned char R, unsigned char G, unsigned char B, unsigned char A )
{
       int x,y,dx,dy,swp,temp,s1,s2,p,i;

       x=X1;
       y=Y1;
       dx=_abs(X2-X1);
       dy=_abs(Y2-Y1);
       s1=_sgn(X2-X1);
       s2=_sgn(Y2-Y1);
       swp=0;

       _pixelRGBA( X1, Y1, R, G, B, A );

       if(dy>dx)
       {
              temp=dx;
              dx=dy;
              dy=temp;
              swp=1;
       }
       p=2*dy-dx;
       for(i=0; i<=dx; i++)
       {
              _pixelRGBA( x, y, R, G, B, A );

              while(p>=0)
              {
                     p=p-2*dx;
                     if(swp)
                            x+=s1;
                     else
                            y+=s2;
              }
              p=p+2*dy;
              if(swp)
                     y+=s2;
              else
                     x+=s1;
       }
}

void _hLineRGBA( unsigned int X1, unsigned int X2, unsigned int Y, unsigned char R, unsigned char G, unsigned char B, unsigned char A )
{
       if( X1<=X2 )
       {
              for(int k=X1; k<=X2; k++)
              {
                     _pixelRGBA(k,Y,R,G,B,A);
              }
       }
       else
       {
              for(int k=X2; k<=X1; k++)
              {
                     _pixelRGBA(k,Y,R,G,B,A);
              }
       }

}


void _rectangleRGBA( unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, unsigned char R, unsigned char G, unsigned char B, unsigned char A )
{

       _lineRGBA( X1, Y1, X1, Y2, R, G, B, A ) ;
       _lineRGBA( X1, Y2, X2, Y2, R, G, B, A ) ;
       _lineRGBA( X2, Y2, X2, Y1, R, G, B, A ) ;
       _lineRGBA( X2, Y1, X1, Y1, R, G, B, A ) ;

}

void _boxRGBA( unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, unsigned char R, unsigned char G, unsigned char B, unsigned char A )
{
       if (Y1<=Y2)
       {
              for( unsigned int k=Y1; k<=Y2; k++)
                     _lineRGBA( X1, k, X2, k, R, G, B, A ) ;
       }
       else
       {
              for( unsigned int k=Y2; k<=Y1; k++)
                     _lineRGBA( X1, k, X2, k, R, G, B, A ) ;
       }

}

void _circleRGBA( unsigned int X1, unsigned int Y1, unsigned int Rad, unsigned char R, unsigned char G, unsigned char B, unsigned char A )
{

       int x,y,p;

       x=0;
       y=Rad;
       p=3-2*Rad;

       _pixelRGBA(X1+x,Y1+y,R,G,B,A);
       _pixelRGBA(X1+x,Y1-y,R,G,B,A);
       _pixelRGBA(X1-x,Y1+y,R,G,B,A);
       _pixelRGBA(X1-x,Y1-y,R,G,B,A);
       _pixelRGBA(X1+y,Y1+x,R,G,B,A);
       _pixelRGBA(X1+y,Y1-x,R,G,B,A);
       _pixelRGBA(X1-y,Y1+x,R,G,B,A);
       _pixelRGBA(X1-y,Y1-x,R,G,B,A);

       while(x<y)
       {
              if(p<0)
              {
                     x++;
                     p=p+4*x+6;
              }
              else
              {
                     x++;
                     y--;
                     p=p+4*(x-y)+10;
              }
              _pixelRGBA(X1+x,Y1+y,R,G,B,A);
              _pixelRGBA(X1+x,Y1-y,R,G,B,A);
              _pixelRGBA(X1-x,Y1+y,R,G,B,A);
              _pixelRGBA(X1-x,Y1-y,R,G,B,A);
              _pixelRGBA(X1+y,Y1+x,R,G,B,A);
              _pixelRGBA(X1+y,Y1-x,R,G,B,A);
              _pixelRGBA(X1-y,Y1+x,R,G,B,A);
              _pixelRGBA(X1-y,Y1-x,R,G,B,A);
       }

}

void _filledCircleRGBA( unsigned int X1, unsigned int Y1, unsigned int Rad, unsigned char R, unsigned char G, unsigned char B, unsigned char A )
{

       int x,y,p;

       x=0;
       y=Rad;
       p=3-2*Rad;

       _hLineRGBA(X1+x,X1-x,Y1+y,R,G,B,A);
       _hLineRGBA(X1+x,X1-x,Y1-y,R,G,B,A);
       _hLineRGBA(X1+y,X1-y,Y1+x,R,G,B,A);
       _hLineRGBA(X1+y,X1-y,Y1-x,R,G,B,A);

       while(x<y)
       {
              if(p<0)
              {
                     x++;
                     p=p+4*x+6;
              }
              else
              {
                     x++;
                     y--;
                     p=p+4*(x-y)+10;
              }

              _hLineRGBA(X1+x,X1-x,Y1+y,R,G,B,A);
              _hLineRGBA(X1+x,X1-x,Y1-y,R,G,B,A);
              _hLineRGBA(X1+y,X1-y,Y1+x,R,G,B,A);
              _hLineRGBA(X1+y,X1-y,Y1-x,R,G,B,A);
       }

}
