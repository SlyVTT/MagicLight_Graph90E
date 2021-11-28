#include <gint/display.h>

void _calculateBlendRGBA( unsigned int X, unsigned int Y, unsigned char* R, unsigned char* G, unsigned char* B, unsigned char A );
void _fastPixelRGB( unsigned int X, unsigned int Y, unsigned char R, unsigned char G, unsigned char B );
void _pixelRGBA( unsigned int X, unsigned int Y, unsigned char R, unsigned char G, unsigned char B, unsigned char A );
void _fastGetPixelRGB( unsigned int X, unsigned int Y, unsigned char* R, unsigned char* G, unsigned char* B );
void _getPixelRGB( unsigned int X, unsigned int Y, unsigned char* R, unsigned char* G, unsigned char* B );
void _lineRGBA( unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, unsigned char R, unsigned char G, unsigned char B, unsigned char A );
void _hLineRGBA( unsigned int X1, unsigned int X2, unsigned int Y, unsigned char R, unsigned char G, unsigned char B, unsigned char A );
void _rectangleRGBA( unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, unsigned char R, unsigned char G, unsigned char B, unsigned char A );
void _boxRGBA( unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2, unsigned char R, unsigned char G, unsigned char B, unsigned char A );
void _circleRGBA( unsigned int X1, unsigned int Y1, unsigned int Rad, unsigned char R, unsigned char G, unsigned char B, unsigned char A );
void _filledCircleRGBA( unsigned int X1, unsigned int Y1, unsigned int Rad, unsigned char R, unsigned char G, unsigned char B, unsigned char A );

int _sgn( int x );

int _abs( int x );
