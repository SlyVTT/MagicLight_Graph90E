#include <stdlib.h>
#include <stdio.h>

#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/gint.h>

#include "colors.h"
#include "structs.h"
#include "primitives.h"


#define R_ROUGE 0
#define R_VERT 1
#define R_BLEU 2
#define R_NOIR 3
#define R_ROSE 4
#define R_CYAN 5
#define R_JAUNE 6
#define R_BLANC 7


unsigned int SIZE = 16;
unsigned int OFFSET_X = 12;
unsigned int OFFSET_Y = 12;

unsigned int OFFSET_X_MINIMAP = 312;
unsigned int OFFSET_Y_MINIMAP = 140;
unsigned int SCALE_X_MINIMAP = 8;
unsigned int SCALE_Y_MINIMAP = 6;

unsigned char ALPHA_OPAQUE = 191;
unsigned char ALPHA_TRANSPARENT = 62;
unsigned char ALPHA_BLOQUE = 10;

unsigned int SPEEDUP_RAY = 1;
unsigned int SPEEDUP_WALL = 1;

#define NB_BLOCKS_MAX  4
#define NB_RECEPTORS_MAX  8
#define NB_DOORS_MAX  4
#define NB_TREASURE_MAX 4
#define NB_OBSTACLE_MAX 4

#define NB_LEVELS 4

unsigned char NbReceptorsLevel;
unsigned char NbDoorsLevel;
unsigned char NbBlocksLevel;
unsigned char NbTreasureLevel;
unsigned char NbObstacleLevel;

selection selected = JOUEUR;

#define SIZE_MAP_X 13
#define SIZE_MAP_Y 11

Player joueur;
Light lumiere;
MapItem carte[SIZE_MAP_X][SIZE_MAP_Y];
Wall murs[4];

Blocks BlocRouge;
Blocks BlocVert ;
Blocks BlocBleu;
Blocks BlocNoir;

Obstacle BlocObstacle01;
Obstacle BlocObstacle02;
Obstacle BlocObstacle03;
Obstacle BlocObstacle04;

Receptor CapteurRouge;
Receptor CapteurVert;
Receptor CapteurBleu;
Receptor CapteurNoir;
Receptor CapteurRose;
Receptor CapteurCyan;
Receptor CapteurJaune;
Receptor CapteurBlanc;

Door PorteNord;
Door PorteOuest;
Door PorteEst;
Door PorteSud ;

Treasure TresorA;
Treasure TresorB;
Treasure TresorC;
Treasure TresorD;

Blocks* BlocksCollection[NB_BLOCKS_MAX];
Receptor* ReceptorCollection[NB_RECEPTORS_MAX];
Door* DoorCollection[ NB_DOORS_MAX ];
Treasure* TreasureCollection[ NB_TREASURE_MAX ];
Obstacle* ObstaclesCollection[ NB_OBSTACLE_MAX ];


Minimap Map[ NB_LEVELS ];

unsigned char ALPHA_VALIDE = 255;
unsigned char ALPHA_NON_VALIDE = 100;

unsigned char EPSILON = 16;

extern bopti_image_t mapbackgrd;
extern bopti_image_t leveltiles;
extern bopti_image_t sprites;
extern bopti_image_t player;
extern bopti_image_t light;
extern bopti_image_t cursor;
extern bopti_image_t plop;
extern bopti_image_t parchemin;
extern bopti_image_t treasures;
extern bopti_image_t chests;

extern font_t font_fantasy;
extern font_t font_tiny;

bool done = false;


unsigned int compteur_mouvement = 0;
unsigned int frame_cursor = 0;
unsigned int frame_light = 0;
unsigned int frame=0;
bool mouvement=false;
orientations direction=HAUT;
unsigned int nextLevel;
unsigned int currentLevel;


void initMap( void )
{
       /*
          for( unsigned int x=0; x<SIZE_MAP_X; x++)
          {
                 for( unsigned int y=0; y<SIZE_MAP_Y; y++)
                 {
                        carte[x][y].ID = VIDE;
                        carte[x][y].x = x;
                        carte[x][y].y = y;
                        carte[x][y].direction =  AUCUNE;

                        if (x==0)
                        {
                               if (y!=5) //(y!=4 && y!=5 && y!=6)
                               {
                                      carte[x][y].ID = MUR;
                               }
                               else
                               {
                                      carte[x][y].ID = PORTE;
                                      carte[x][y].direction = DROITE;
                               }
                        }
                        if (x==12)
                        {
                               if (y!=5) //(y!=4 && y!=5 && y!=6)
                               {
                                      carte[x][y].ID = MUR;
                               }
                               else
                               {
                                      carte[x][y].ID = PORTE;
                                      carte[x][y].direction = GAUCHE;
                               }
                        }
                        if (y==0)
                        {
                               if (x!=6) //(x!=5 && x!=6 && x!=7)
                               {
                                      carte[x][y].ID = MUR;
                               }
                               else
                               {
                                      carte[x][y].ID = PORTE;
                                      carte[x][y].direction = BAS;
                               }
                        }
                        if (y==10)
                        {
                               if (x!=6) //(x!=5 && x!=6 && x!=7)
                               {
                                      carte[x][y].ID = MUR;
                               }
                               else
                               {
                                      carte[x][y].ID = PORTE;
                                      carte[x][y].direction = HAUT;
                               }
                        }
                 }
          }
          */
}

void loadLevel( unsigned char numLevel )
{
       if (numLevel==0)
       {
              currentLevel = 0;

              NbReceptorsLevel = 8;
              NbDoorsLevel = 4;
              NbBlocksLevel = 4;
              NbTreasureLevel = 4;
              NbObstacleLevel = 4;

              Map[0].x=0;
              Map[0].y=0;
              Map[0].R=0;
              Map[0].G=0;
              Map[0].B=255;
              Map[0].A=255;
              Map[0].visited=true;

              BlocObstacle01.x=3;
              BlocObstacle01.y=3;
              BlocObstacle01.type=BLOCK_STONE;

              BlocObstacle02.x=3;
              BlocObstacle02.y=5;
              BlocObstacle02.type=BLOCK_SUN;

              BlocObstacle03.x=2;
              BlocObstacle03.y=5;
              BlocObstacle03.type=BLOCK_MOON;

              BlocObstacle04.x=3;
              BlocObstacle04.y=6;
              BlocObstacle04.type=BLOCK_WOOD;

              ObstaclesCollection[0] = &BlocObstacle01;
              ObstaclesCollection[1] = &BlocObstacle02;
              ObstaclesCollection[2] = &BlocObstacle03;
              ObstaclesCollection[3] = &BlocObstacle04;


              joueur = { 7, 9, HAUT };
              lumiere = { 6, 5, {0,0,0,0}, false };

              BlocRouge = { 6, 3, 255, 0, 0, 127, TRANSPARENT };
              BlocVert = { 9, 3, 0, 255, 0, 127, TRANSPARENT };
              BlocBleu = { 7, 7, 0, 0, 255, 127, TRANSPARENT };
              BlocNoir = { 3, 7, 0, 0, 0, 255, OPAQUE };

              CapteurRouge = { 12, 2, GAUCHE, 255, 0, 0, false };
              CapteurVert = { 0, 2, DROITE, 0, 255, 0, false };
              CapteurBleu = { 4, 10, HAUT, 0, 0, 255, false };
              CapteurNoir = { 3, 0, BAS, 0, 0, 0, false };
              CapteurRose = { 8, 0, BAS, 255, 0, 255, false };
              CapteurCyan = { 9, 10, HAUT, 0, 255, 255, false };
              CapteurJaune = { 12, 8, GAUCHE, 255, 255, 0, false };
              CapteurBlanc = { 0, 7, DROITE, 255, 255, 255, false };

              PorteNord = { 6,0, HAUT, false, true, 2, { R_ROUGE, R_VERT, -1 }, 1};
              PorteOuest = { 0, 5, GAUCHE, false, true, 2, { R_BLEU, R_NOIR, -1 }, 2};
              PorteEst = { 12, 5, DROITE, false, false, 0, { -1, -1, -1 }, -1};
              PorteSud = { 6, 10, BAS, false, true, 1, { R_BLANC, -1, -1 }, 3};

              TresorA = {2,2, T_RED, false, PIERRE_BLANCHE, 100 };
              TresorB = {11,9, T_YELLOW, false, PIERRE_BLANCHE, 100 };
              TresorC = {10,4, T_GREEN, false, PIERRE_BLANCHE, 100 };
              TresorD = {1,1, T_BLUE, true, PIERRE_BLANCHE, 100 };

              //BlocksCollection = [ &BlocRouge, &BlocVert, &BlocBleu, &BlocNoir ];
              BlocksCollection[0] = &BlocRouge;
              BlocksCollection[1] = &BlocVert;
              BlocksCollection[2] = &BlocBleu;
              BlocksCollection[3] = &BlocNoir;

              //ReceptorCollection = [  &CapteurRouge, &CapteurVert, &CapteurBleu, &CapteurNoir, &CapteurRose, &CapteurCyan, &CapteurJaune, &CapteurBlanc ];
              ReceptorCollection[0] = &CapteurRouge;
              ReceptorCollection[1] = &CapteurVert;
              ReceptorCollection[2] = &CapteurBleu;
              ReceptorCollection[3] = &CapteurNoir;
              ReceptorCollection[4] = &CapteurRose;
              ReceptorCollection[5] = &CapteurCyan;
              ReceptorCollection[6] = &CapteurJaune;
              ReceptorCollection[7] = &CapteurBlanc;

              //DoorCollection =[  &PorteNord, &PorteOuest, &PorteEst, &PorteSud ];
              DoorCollection[0] = &PorteNord;
              DoorCollection[1] = &PorteOuest;
              DoorCollection[2] = &PorteEst;
              DoorCollection[3] = &PorteSud;

              TreasureCollection[0] = &TresorA;
              TreasureCollection[1] = &TresorB;
              TreasureCollection[2] = &TresorC;
              TreasureCollection[3] = &TresorD;
       }
       else if (numLevel==1)
       {
              currentLevel = 1;

              NbReceptorsLevel = 8;
              NbDoorsLevel = 4;
              NbBlocksLevel = 4;
              NbTreasureLevel = 0;

              Map[1].x=0;
              Map[1].y=-1;
              Map[1].R=0;
              Map[1].G=0;
              Map[1].B=255;
              Map[1].A=255;
              Map[1].visited=true;

              //joueur = { 7, 9, HAUT };
              lumiere = { 6, 5, {0,0,0,0}, false };

              BlocRouge = { 6, 3, 255, 0, 0, 127, TRANSPARENT };
              BlocVert = { 9, 3, 0, 255, 0, 127, TRANSPARENT };
              BlocBleu = { 7, 7, 0, 0, 255, 127, TRANSPARENT };
              BlocNoir = { 3, 7, 0, 0, 0, 255, OPAQUE };

              CapteurRouge = { 12, 2, GAUCHE, 255, 0, 0, false };
              CapteurVert = { 0, 2, DROITE, 0, 255, 0, false };
              CapteurBleu = { 4, 10, HAUT, 0, 0, 255, false };
              CapteurNoir = { 3, 0, BAS, 0, 0, 0, false };
              CapteurRose = { 8, 0, BAS, 255, 0, 255, false };
              CapteurCyan = { 9, 10, HAUT, 0, 255, 255, false };
              CapteurJaune = { 12, 8, GAUCHE, 255, 255, 0, false };
              CapteurBlanc = { 0, 7, DROITE, 255, 255, 255, false };

              PorteNord = { 6,0, HAUT, false, false, 0, { -1, -1, -1 }, -1};
              PorteOuest = { 0, 5, GAUCHE, false, false, 0, { -1, -1, -1 }, -1};
              PorteEst = { 12, 5, DROITE, false, false, 0, { -1, -1, -1 }, -1};
              PorteSud = { 6, 10, BAS, false, true, 1, { R_ROSE, -1, -1 }, 0};

              //BlocksCollection = [ &BlocRouge, &BlocVert, &BlocBleu, &BlocNoir ];
              BlocksCollection[0] = &BlocRouge;
              BlocksCollection[1] = &BlocVert;
              BlocksCollection[2] = &BlocBleu;
              BlocksCollection[3] = &BlocNoir;

              //ReceptorCollection = [  &CapteurRouge, &CapteurVert, &CapteurBleu, &CapteurNoir, &CapteurRose, &CapteurCyan, &CapteurJaune, &CapteurBlanc ];
              ReceptorCollection[0] = &CapteurRouge;
              ReceptorCollection[1] = &CapteurVert;
              ReceptorCollection[2] = &CapteurBleu;
              ReceptorCollection[3] = &CapteurNoir;
              ReceptorCollection[4] = &CapteurRose;
              ReceptorCollection[5] = &CapteurCyan;
              ReceptorCollection[6] = &CapteurJaune;
              ReceptorCollection[7] = &CapteurBlanc;

              //DoorCollection =[  &PorteNord, &PorteOuest, &PorteEst, &PorteSud ];
              DoorCollection[0] = &PorteNord;
              DoorCollection[1] = &PorteOuest;
              DoorCollection[2] = &PorteEst;
              DoorCollection[3] = &PorteSud;
       }
       else if (numLevel==2)
       {
              currentLevel = 2;

              NbReceptorsLevel = 8;
              NbDoorsLevel = 4;
              NbBlocksLevel = 4;
              NbTreasureLevel = 0;

              Map[2].x=-1;
              Map[2].y=0;
              Map[2].R=0;
              Map[2].G=0;
              Map[2].B=255;
              Map[2].A=255;
              Map[2].visited=true;

              //joueur = { 7, 9, HAUT };
              lumiere = { 6, 5, {0,0,0,0}, false };

              BlocRouge = { 6, 3, 255, 0, 0, 127, TRANSPARENT };
              BlocVert = { 9, 3, 0, 255, 0, 127, TRANSPARENT };
              BlocBleu = { 7, 7, 0, 0, 255, 127, TRANSPARENT };
              BlocNoir = { 3, 7, 0, 0, 0, 255, OPAQUE };

              CapteurRouge = { 12, 2, GAUCHE, 255, 0, 0, false };
              CapteurVert = { 0, 2, DROITE, 0, 255, 0, false };
              CapteurBleu = { 4, 10, HAUT, 0, 0, 255, false };
              CapteurNoir = { 3, 0, BAS, 0, 0, 0, false };
              CapteurRose = { 8, 0, BAS, 255, 0, 255, false };
              CapteurCyan = { 9, 10, HAUT, 0, 255, 255, false };
              CapteurJaune = { 12, 8, GAUCHE, 255, 255, 0, false };
              CapteurBlanc = { 0, 7, DROITE, 255, 255, 255, false };

              PorteNord = { 6,0, HAUT, false, false, 0, { -1, -1, -1 }, -1};
              PorteOuest = { 0, 5, GAUCHE, false, false, 0, { -1, -1, -1 }, -1};
              PorteEst = { 12, 5, DROITE, false, true, 1, { R_CYAN, -1, -1 }, 0 };
              PorteSud = { 6, 10, BAS, false, false, 0, { -1, -1, -1 }, -1};

              //BlocksCollection = [ &BlocRouge, &BlocVert, &BlocBleu, &BlocNoir ];
              BlocksCollection[0] = &BlocRouge;
              BlocksCollection[1] = &BlocVert;
              BlocksCollection[2] = &BlocBleu;
              BlocksCollection[3] = &BlocNoir;

              //ReceptorCollection = [  &CapteurRouge, &CapteurVert, &CapteurBleu, &CapteurNoir, &CapteurRose, &CapteurCyan, &CapteurJaune, &CapteurBlanc ];
              ReceptorCollection[0] = &CapteurRouge;
              ReceptorCollection[1] = &CapteurVert;
              ReceptorCollection[2] = &CapteurBleu;
              ReceptorCollection[3] = &CapteurNoir;
              ReceptorCollection[4] = &CapteurRose;
              ReceptorCollection[5] = &CapteurCyan;
              ReceptorCollection[6] = &CapteurJaune;
              ReceptorCollection[7] = &CapteurBlanc;

              //DoorCollection =[  &PorteNord, &PorteOuest, &PorteEst, &PorteSud ];
              DoorCollection[0] = &PorteNord;
              DoorCollection[1] = &PorteOuest;
              DoorCollection[2] = &PorteEst;
              DoorCollection[3] = &PorteSud;
       }
       else if (numLevel==3)
       {
              currentLevel = 3;

              NbReceptorsLevel = 8;
              NbDoorsLevel = 4;
              NbBlocksLevel = 4;
              NbTreasureLevel = 0;


              Map[3].x=0;
              Map[3].y=1;
              Map[3].R=0;
              Map[3].G=0;
              Map[3].B=255;
              Map[3].A=255;
              Map[3].visited=true;

              //joueur = { 7, 9, HAUT };
              lumiere = { 6, 5, {0,0,0,0}, false };

              BlocRouge = { 6, 3, 255, 0, 0, 127, TRANSPARENT };
              BlocVert = { 9, 3, 0, 255, 0, 127, TRANSPARENT };
              BlocBleu = { 7, 7, 0, 0, 255, 127, TRANSPARENT };
              BlocNoir = { 3, 7, 0, 0, 0, 255, OPAQUE };

              CapteurRouge = { 12, 2, GAUCHE, 255, 0, 0, false };
              CapteurVert = { 0, 2, DROITE, 0, 255, 0, false };
              CapteurBleu = { 4, 10, HAUT, 0, 0, 255, false };
              CapteurNoir = { 3, 0, BAS, 0, 0, 0, false };
              CapteurRose = { 8, 0, BAS, 255, 0, 255, false };
              CapteurCyan = { 9, 10, HAUT, 0, 255, 255, false };
              CapteurJaune = { 12, 8, GAUCHE, 255, 255, 0, false };
              CapteurBlanc = { 0, 7, DROITE, 255, 255, 255, false };

              PorteNord = { 6,0, HAUT, false, true, 1, { R_JAUNE, -1, -1 }, 0};
              PorteOuest = { 0, 5, GAUCHE, false, false, 0, { -1, -1, -1 }, -1};
              PorteEst = { 12, 5, DROITE, false, false, 0, { -1, -1, -1 }, -1 };
              PorteSud = { 6, 10, BAS, false, false, 0, { -1, -1, -1 }, -1};

              //BlocksCollection = [ &BlocRouge, &BlocVert, &BlocBleu, &BlocNoir ];
              BlocksCollection[0] = &BlocRouge;
              BlocksCollection[1] = &BlocVert;
              BlocksCollection[2] = &BlocBleu;
              BlocksCollection[3] = &BlocNoir;

              //ReceptorCollection = [  &CapteurRouge, &CapteurVert, &CapteurBleu, &CapteurNoir, &CapteurRose, &CapteurCyan, &CapteurJaune, &CapteurBlanc ];
              ReceptorCollection[0] = &CapteurRouge;
              ReceptorCollection[1] = &CapteurVert;
              ReceptorCollection[2] = &CapteurBleu;
              ReceptorCollection[3] = &CapteurNoir;
              ReceptorCollection[4] = &CapteurRose;
              ReceptorCollection[5] = &CapteurCyan;
              ReceptorCollection[6] = &CapteurJaune;
              ReceptorCollection[7] = &CapteurBlanc;

              //DoorCollection =[  &PorteNord, &PorteOuest, &PorteEst, &PorteSud ];
              DoorCollection[0] = &PorteNord;
              DoorCollection[1] = &PorteOuest;
              DoorCollection[2] = &PorteEst;
              DoorCollection[3] = &PorteSud;
       }
}

void initWalls( void )
{
       murs[0] = { HORIZONTAL, OFFSET_X+SIZE*1, OFFSET_X+SIZE*(SIZE_MAP_X-1), OFFSET_Y+SIZE };
       murs[1] = { VERTICAL, OFFSET_Y+SIZE*1, OFFSET_Y+SIZE*(SIZE_MAP_Y-1), OFFSET_X+SIZE*(SIZE_MAP_X-1) };
       murs[2] = { HORIZONTAL, OFFSET_X+SIZE*1, OFFSET_X+SIZE*(SIZE_MAP_X-1), OFFSET_Y+SIZE*(SIZE_MAP_Y-1) };
       murs[3] = { VERTICAL, OFFSET_Y+SIZE*1, OFFSET_Y+SIZE*(SIZE_MAP_Y-1), OFFSET_X+SIZE };

       for(int k=0; k<SIZE_MAP_X; k++)
              dprint_opt( OFFSET_X+SIZE*k+SIZE/2, OFFSET_Y-SIZE/2, C_WHITE, C_NONE, DTEXT_CENTER, DTEXT_MIDDLE, "%d", k );

       for( int k=1; k<SIZE_MAP_Y; k++)
              dprint_opt( OFFSET_X-SIZE/2, OFFSET_Y+k*SIZE+SIZE/2, C_WHITE, C_NONE, DTEXT_CENTER, DTEXT_MIDDLE, "%d", k );
}

void renderMap( void )
{
       //dimage(OFFSET_X, OFFSET_Y, &mapbackgrd);

       for(int x=0; x<SIZE_MAP_X; x++)
              for( int y=0; y<SIZE_MAP_Y; y++)
              {
                     unsigned int lX=OFFSET_X+x*SIZE;
                     unsigned int lY=OFFSET_Y+y*SIZE;

                     if(y==0)
                     {
                            if (x==0)
                                   dsubimage( lX, lY, &leveltiles, 0,0,16,16,  DIMAGE_NONE);
                            else if (x==SIZE_MAP_X-1)
                                   dsubimage( lX, lY, &leveltiles, 16,0,16,16,  DIMAGE_NONE);
                            else
                                   dsubimage( lX, lY, &leveltiles, 32,0,16,16,  DIMAGE_NONE);
                     }
                     else if(y==SIZE_MAP_Y-1)
                     {
                            if (x==0)
                                   dsubimage( lX, lY, &leveltiles, 0,16,16,16,  DIMAGE_NONE);
                            else if (x==SIZE_MAP_X-1)
                                   dsubimage( lX, lY, &leveltiles, 16,16,16,16,  DIMAGE_NONE);
                            else
                                   dsubimage( lX, lY, &leveltiles, 48,16,16,16,  DIMAGE_NONE);
                     }
                     else
                     {
                            if (x==0)
                                   dsubimage( lX, lY, &leveltiles, 48,0,16,16,  DIMAGE_NONE);
                            else if (x==SIZE_MAP_X-1)
                                   dsubimage( lX, lY, &leveltiles, 32,16,16,16,  DIMAGE_NONE);
                            else if ((x+y)%2==0)
                                   dsubimage( lX, lY, &leveltiles, 0,32,16,16,  DIMAGE_NONE);
                            else
                                   dsubimage( lX, lY, &leveltiles, 16,32,16,16,  DIMAGE_NONE);
                     }
              }
}

void computeLightModification( unsigned int currentCellX, unsigned int currentCellY, unsigned char* R, unsigned char* G, unsigned char* B, unsigned char* A )
{
       if (*A!=ALPHA_BLOQUE)
       {

              for( unsigned int k=0; k<NbBlocksLevel; k++ )
              {
                     if (BlocksCollection[k]->x == currentCellX)
                            if (BlocksCollection[k]->y == currentCellY)
                            {
                                   if (*R!=BlocNoir.R || *G!=BlocNoir.G || *B!=BlocNoir.B || *A!=ALPHA_OPAQUE )
                                   {
                                          if (BlocksCollection[k]->type == OPAQUE)
                                          {
                                                 *R = *R & BlocksCollection[k]->R;
                                                 *G = *G & BlocksCollection[k]->G;
                                                 *B = *B & BlocksCollection[k]->B;
                                                 *A = ALPHA_OPAQUE;
                                          }
                                          if (BlocksCollection[k]->type == TRANSPARENT)
                                          {
                                                 *R = *R | BlocksCollection[k]->R;
                                                 *G = *G | BlocksCollection[k]->G;
                                                 *B = *B | BlocksCollection[k]->B;
                                                 *A = ALPHA_TRANSPARENT;
                                          }
                                   }
                            }
              }

              for( unsigned int k=0; k<NbObstacleLevel; k++ )
              {
                     if (ObstaclesCollection[k]->x == currentCellX)
                            if (ObstaclesCollection[k]->y == currentCellY)
                            {
                                   *A = ALPHA_BLOQUE;
                            }
              }

       }
}

void rayCast( unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned char* Rs, unsigned char* Gs, unsigned char* Bs, unsigned char* As )
{
       // Cette fonction est un algo type BRESENHAM qui lance un rayon depuis la lumière jusqu'à chaque pixel des murs
       // Elle analyse la présence de blocs de glace de couleurs qui peuvent changer la couleur de la lumière du départ (Rs, Gs, Bs)
       // Elle dessine le point sur le mur de la bonne couleur

       // ATTENTION : toujours mettre x1 et y1 comme étant en premier et correspondant à la source de lumière !!!!

       unsigned int currentCellX = -1;
       unsigned int currentCellY = -1;

       /*
           int R = Rs;
           int G = Gs;
           int B = Bs;
           int A = As;
       */

       unsigned int x,y;
       int dx,dy,swp,temp,s1,s2,p,i;

       x=x1;
       y=y1;
       dx=_abs(x2-x1);
       dy=_abs(y2-y1);
       s1=_sgn(x2-x1);
       s2=_sgn(y2-y1);
       swp=0;

       //_pixelRGBA(  x1, y1, 255, 255, 255, 255 );

       if(dy>dx)
       {
              temp=dx;
              dx=dy;
              dy=temp;
              swp=1;
       }
       p=2*dy-dx;
       for(i=0; i<dx; i+=SPEEDUP_RAY)
       {
              currentCellX = (x-OFFSET_X)/SIZE;
              currentCellY = (y-OFFSET_Y)/SIZE;
              computeLightModification( currentCellX, currentCellY, Rs, Gs, Bs, As );

              // TODO : will need a rectangle instead of a pixel
              _pixelRGBA(  x, y, *Rs, *Gs, *Bs, *As );
              //_boxRGBA( x, y, x+SPEEDUP_WALL, y+SPEEDUP_RAY-1,  *Rs, *Gs, *Bs, *As );

              while(p>=0)
              {
                     p=p-2*dx;
                     if(swp)
                            x+=s1*SPEEDUP_RAY;
                     else
                            y+=s2*SPEEDUP_RAY;
              }
              p=p+2*dy;
              if(swp)
                     y+=s2*SPEEDUP_RAY;
              else
                     x+=s1*SPEEDUP_RAY;
       }
}

void renderWalls( void )
{
       unsigned char lR = lumiere.couleur.R;
       unsigned char lG = lumiere.couleur.G;
       unsigned char lB = lumiere.couleur.B;
       unsigned char lA = lumiere.couleur.A;

       unsigned int lX = SIZE*lumiere.x+OFFSET_X+SIZE/2;
       unsigned int lY = SIZE*lumiere.y+OFFSET_Y+SIZE/2;

       for( int k=0; k<4; k++ )
       {
              if (murs[k].direction == HORIZONTAL)
                     for( unsigned int z=murs[k].mini; z<=murs[k].maxi; z+=SPEEDUP_WALL)
                     {
                            lR = lumiere.couleur.R;
                            lG = lumiere.couleur.G;
                            lB = lumiere.couleur.B;
                            lA = lumiere.couleur.A;

                            rayCast( lX, lY, z, murs[k].fixe,  &lR,&lG,&lB,&lA );

                            if (lR!=lumiere.couleur.R || lG!=lumiere.couleur.G || lB!=lumiere.couleur.B || lA!=lumiere.couleur.A )
                            {
                                   if(lA!=ALPHA_BLOQUE)
                                   {
                                          _pixelRGBA(  z, murs[k].fixe+1,  lR,lG,lB, 255 );
                                          _pixelRGBA(  z, murs[k].fixe,  lR,lG,lB, 255 );
                                          _pixelRGBA(  z, murs[k].fixe-1,  lR,lG,lB, 255 );
                                   }
                            }
                     }

              if (murs[k].direction == VERTICAL)
                     for( unsigned int z=murs[k].mini; z<=murs[k].maxi; z+=SPEEDUP_WALL)
                     {
                            lR = lumiere.couleur.R;
                            lG = lumiere.couleur.G;
                            lB = lumiere.couleur.B;
                            lA = lumiere.couleur.A;

                            rayCast(  lX, lY, murs[k].fixe, z, &lR,&lG,&lB,&lA );

                            if (lR!=lumiere.couleur.R || lG!=lumiere.couleur.G || lB!=lumiere.couleur.B || lA!=lumiere.couleur.A )
                            {
                                   if (lA!=ALPHA_BLOQUE)
                                   {
                                          _pixelRGBA(  murs[k].fixe+1, z, lR,lG,lB,255 );
                                          _pixelRGBA(  murs[k].fixe, z, lR,lG,lB,255 );
                                          _pixelRGBA(  murs[k].fixe-1, z, lR,lG,lB,255 );
                                   }
                            }
                     }

       }
}

void renderObstacles( void )
{
       for( int k=0; k<NbObstacleLevel; k++ )
       {
              unsigned int Xb = ObstaclesCollection[k]->x;
              unsigned int Yb = ObstaclesCollection[k]->y;
              unsigned char Tb = ObstaclesCollection[k]->type;

              unsigned int lX = SIZE*Xb+OFFSET_X;
              unsigned int lY = SIZE*Yb+OFFSET_Y;

              if (Tb==BLOCK_STONE) dsubimage( lX, lY, &sprites, 0,64,16,16,  DIMAGE_NONE);
              else if (Tb==BLOCK_MOON) dsubimage( lX, lY, &sprites, 16,64,16,16,  DIMAGE_NONE);
              else if (Tb==BLOCK_WOOD) dsubimage( lX, lY, &sprites, 32,64,16,16,  DIMAGE_NONE);
              else if (Tb==BLOCK_SUN) dsubimage( lX, lY, &sprites, 48,64,16,16,  DIMAGE_NONE);
       }
}

void renderTreasures( void )
{
       for( int k=0; k<NbTreasureLevel; k++ )
       {
              unsigned int Xb = TreasureCollection[k]->x;
              unsigned int Yb = TreasureCollection[k]->y;
              chest Tb = TreasureCollection[k]->type;
              bool Ob = TreasureCollection[k]->isopen;

              unsigned int lX = SIZE*Xb+OFFSET_X;
              unsigned int lY = SIZE*Yb+OFFSET_Y;

              if (Tb==T_RED)
              {
                     if (Ob==false)
                     {
                            dsubimage( lX, lY, &chests, 0,0,16,16,  DIMAGE_NONE);
                     }
                     else
                     {
                            dsubimage( lX, lY, &chests, 0,48,16,16,  DIMAGE_NONE);
                     }
              }
              else if (Tb==T_YELLOW)
              {
                     if (Ob==false)
                     {
                            dsubimage( lX, lY, &chests, 16,0,16,16,  DIMAGE_NONE);
                     }
                     else
                     {
                            dsubimage( lX, lY, &chests, 16,48,16,16,  DIMAGE_NONE);
                     }
              }
              else if (Tb==T_GREEN)
              {
                     if (Ob==false)
                     {
                            dsubimage( lX, lY, &chests, 32,0,16,16,  DIMAGE_NONE);
                     }
                     else
                     {
                            dsubimage( lX, lY, &chests, 32,48,16,16,  DIMAGE_NONE);
                     }
              }
              else if (Tb==T_BLUE)
              {
                     if (Ob==false)
                     {
                            dsubimage( lX, lY, &chests, 48,0,16,16,  DIMAGE_NONE);
                     }
                     else
                     {
                            dsubimage( lX, lY, &chests, 48,48,16,16,  DIMAGE_NONE);
                     }
              }
       }

}

void renderMovable( void )
{
       for( int k=0; k<NbBlocksLevel; k++ )
       {
              unsigned int Xb = BlocksCollection[k]->x;
              unsigned int Yb = BlocksCollection[k]->y;
              unsigned char Rb = BlocksCollection[k]->R;
              unsigned char Gb = BlocksCollection[k]->G;
              unsigned char Bb = BlocksCollection[k]->B;
              unsigned char Ab = BlocksCollection[k]->A;

              /*
                           unsigned int xmin = OFFSET_X + Xb*SIZE;
                           unsigned int xmax = xmin + SIZE;
                           unsigned int ymin = OFFSET_Y + Yb*SIZE;
                           unsigned int ymax = ymin + SIZE;

                           _boxRGBA(  xmin, ymin, xmax, ymax, Rb, Gb, Bb, Ab );
                           _rectangleRGBA( xmin, ymin, xmax, ymax, 0, 0, 0, 255 );

                           unsigned int lX = SIZE*Xb+OFFSET_X+SIZE/2;
                           unsigned int lY = SIZE*Yb+OFFSET_Y+SIZE/2;

                           _filledCircleRGBA(  lX, lY, 4, 150, 150, 150, 255 );
                           _circleRGBA(  lX, lY, 4, 0, 0, 0, 255 );
              */

              unsigned int lX = SIZE*Xb+OFFSET_X;
              unsigned int lY = SIZE*Yb+OFFSET_Y;

              if (Rb==255 && Gb==0 && Bb==0) dsubimage( lX, lY, &sprites, 16,0,16,16,  DIMAGE_NONE);
              else if (Rb==0 && Gb==0 && Bb==255) dsubimage( lX, lY, &sprites, 32,0,16,16,  DIMAGE_NONE);
              else if (Rb==0 && Gb==255 && Bb==0) dsubimage( lX, lY, &sprites, 48,0,16,16,  DIMAGE_NONE);
              else if (Rb==0 && Gb==0 && Bb==0) dsubimage( lX, lY, &sprites, 64,0,16,16,  DIMAGE_NONE);
              else if (Rb==255 && Gb==255 && Bb==255) dsubimage( lX, lY, &sprites, 0,0,16,16,  DIMAGE_NONE);
       }

}

void renderPlayer( void )
{
       unsigned int lX = SIZE*joueur.x+OFFSET_X;
       unsigned int lY = SIZE*joueur.y+OFFSET_Y;

       if (direction==BAS)
       {
              if (mouvement==true)
              {
                     if (frame==0) dsubimage( lX, lY-11, &player, 0,0,16,16,  DIMAGE_NONE);
                     else if (frame==1) dsubimage( lX, lY-6, &player, 16,0,16,16,  DIMAGE_NONE);
                     else if (frame==2) dsubimage( lX, lY, &player, 32,0,16,16,  DIMAGE_NONE);

                     frame++;
                     if  (frame==3) mouvement = false;
              }
              else
              {
                     dsubimage( lX, lY, &player, 0,0,16,16,  DIMAGE_NONE);
                     frame = 0;
              }
       }
       else if (direction==DROITE)
       {
              if (mouvement==true)
              {
                     if (frame==0) dsubimage( lX-11, lY, &player, 0,16,16,16,  DIMAGE_NONE);
                     else if (frame==1) dsubimage( lX-6, lY, &player, 16,16,16,16,  DIMAGE_NONE);
                     else if (frame==2) dsubimage( lX, lY, &player, 32,16,16,16,  DIMAGE_NONE);

                     frame++;
                     if  (frame==3) mouvement = false;
              }
              else
              {
                     dsubimage( lX, lY, &player, 0,16,16,16,  DIMAGE_NONE);
                     frame = 0;
              }
       }
       else if (direction==HAUT)
       {
              if (mouvement==true)
              {
                     if (frame==0) dsubimage( lX, lY+11, &player, 0,32,16,16,  DIMAGE_NONE);
                     else if (frame==1) dsubimage( lX, lY+6, &player, 16,32,16,16,  DIMAGE_NONE);
                     else if (frame==2) dsubimage( lX, lY, &player, 32,32,16,16,  DIMAGE_NONE);

                     frame++;
                     if  (frame==3) mouvement = false;
              }
              else
              {
                     dsubimage( lX, lY, &player, 0,32,16,16,  DIMAGE_NONE);
                     frame = 0;
              }
       }
       else if (direction==GAUCHE)
       {
              if (mouvement==true)
              {
                     if (frame==0) dsubimage( lX+11, lY, &player, 0,48,16,16,  DIMAGE_NONE);
                     else if (frame==1) dsubimage( lX+6, lY, &player, 16,48,16,16,  DIMAGE_NONE);
                     else if (frame==2) dsubimage( lX, lY, &player, 32,48,16,16,  DIMAGE_NONE);

                     frame++;
                     if  (frame==3) mouvement = false;
              }
              else
              {
                     dsubimage( lX, lY, &player, 0,48,16,16,  DIMAGE_NONE);
                     frame = 0;
              }
       }
}

void renderLight( void )
{
       /*
       unsigned int lX = SIZE*lumiere.x+OFFSET_X+SIZE/2;
       unsigned int lY = SIZE*lumiere.y+OFFSET_Y+SIZE/2;

       _filledCircleRGBA(  lX, lY, 4, 255, 255, 255, 255 );
       _circleRGBA(  lX, lY, 4, 0, 0, 0, 255 );
       */

       unsigned int lX = SIZE*lumiere.x+OFFSET_X;
       unsigned int lY = SIZE*lumiere.y+OFFSET_Y;

       frame_light%=6;
       dsubimage( lX, lY, &light, 16*frame_light,0,16,16,  DIMAGE_NONE);
       frame_light++;

}

void drawMinimap( void )
{
       for( int k=0; k< NB_LEVELS; k++ )
       {
              if (Map[k].visited==true)
              {
                     unsigned char R= Map[k].R;
                     unsigned char G= Map[k].G;
                     unsigned char B= Map[k].B;
                     unsigned char A= Map[k].A;

                     unsigned int lX = OFFSET_X_MINIMAP + Map[k].x*(SCALE_X_MINIMAP+2);
                     unsigned int lY = OFFSET_Y_MINIMAP + Map[k].y*(SCALE_Y_MINIMAP+2);

                     if (k==currentLevel)
                            _boxRGBA( lX-4, lY-3, lX+4, lY+3, 0, 255, 0, 100);

                     _rectangleRGBA( lX-4, lY-3, lX+4, lY+3, R, G, B, 255);
              }
       }

}


void drawInterface( void )
{
       unsigned int midX, midY;

       //_boxRGBA( 232, 0, 396, 199, 150, 150, 150, 255);
       dsubimage( 232, 0, &parchemin, 0,0, 164, 210,  DIMAGE_NONE);

       dfont( &font_fantasy );

       dprint( 256, 36, C_RGB(150,150,150), "MAGIC Light v0.1B");
       dprint( 255, 35, C_BLACK, "MAGIC Light v0.1B");

       dfont( &font_tiny );

       dprint( 251, 56, C_RGB(150,150,150), "Score : " );
       dprint( 250, 55, C_BLACK, "Score : " );

       dprint( 251, 66, C_RGB(150,150,150), "Level : %d", currentLevel );
       dprint( 250, 65, C_BLACK, "Level : %d",  currentLevel );




       //_boxRGBA(  0, 200, 396, 224, 150, 150, 150, 255);

       midY=(200+224)/2;

       midX=(66)/2;
       dsubimage( midX-8, midY-8, &player, 0,0,16,16,  DIMAGE_NONE);

       midX+=66;
       dsubimage( midX-8, midY-8, &light, 0,0,16,16,  DIMAGE_NONE);

       midX+=66;
       dsubimage( midX-8, midY-8, &sprites, 16,0,16,16,  DIMAGE_NONE);

       midX+=66;
       dsubimage( midX-8, midY-8, &sprites, 48,0,16,16,  DIMAGE_NONE);

       midX+=66;
       dsubimage( midX-8, midY-8, &sprites, 32,0,16,16,  DIMAGE_NONE);

       midX+=66;
       dsubimage( midX-8, midY-8, &sprites, 64,0,16,16,  DIMAGE_NONE);

       if (selected >=1 && selected <=6)
       {

              if (frame_cursor==0) dsubimage( 66*(selected)-33-11, midY-11, &cursor, 0,0,22,22,  DIMAGE_NONE);
              else if (frame_cursor==1) dsubimage( 66*(selected)-33-11, midY-11, &cursor, 22,0,22,22,  DIMAGE_NONE);
              else if (frame_cursor==2) dsubimage( 66*(selected)-33-11, midY-11, &cursor, 44,0,22,22,  DIMAGE_NONE);
              else if (frame_cursor==3) dsubimage( 66*(selected)-33-11, midY-11, &cursor, 22,0,22,22,  DIMAGE_NONE);
       }
}

bool isValidMove( selection selected, unsigned int x, unsigned int y, orientations sens )
{
       for(int k=0; k<NbDoorsLevel; k++)
       {
              if ( x==DoorCollection[k]->x && y==DoorCollection[k]->y)
              {
                     if (DoorCollection[k]->isdoor && DoorCollection[k]->isopen)
                     {
                            loadLevel(  DoorCollection[k]->nextLevelNumber );
                            joueur = { 11-10*x/12, 9-8*y/10, sens };
                            return false;
                     }
              }
       }

       if (x<1 || x>11 || y<1 || y>9)
       {
              return false;
       }
       else if (selected == JOUEUR)
       {
              if (x==lumiere.x && y==lumiere.y) return false;
              else if (x==BlocRouge.x && y==BlocRouge.y) return false;
              else if (x==BlocVert.x && y==BlocVert.y) return false;
              else if (x==BlocBleu.x && y==BlocBleu.y) return false;
              else if (x==BlocNoir.x && y==BlocNoir.y) return false;
              else
              {
                     for (int k =0; k<NbObstacleLevel; k++)
                            if (ObstaclesCollection[k]->x==x && ObstaclesCollection[k]->y==y)
                                   return false;
                     return true;
              }
       }
       else if (selected == LUMIERE)
       {
              if (x==joueur.x && y==joueur.y) return false;
              else
              {
                     for (int k =0; k<NbObstacleLevel; k++)
                            if (ObstaclesCollection[k]->x==x && ObstaclesCollection[k]->y==y)
                                   return false;
                     return true;
              }
       }
       else if (selected == ROUGE)
       {
              if (x==joueur.x && y==joueur.y) return false;
              else if (x==BlocVert.x && y==BlocVert.y) return false;
              else if (x==BlocBleu.x && y==BlocBleu.y) return false;
              else if (x==BlocNoir.x && y==BlocNoir.y) return false;
              else
              {
                     for (int k =0; k<NbObstacleLevel; k++)
                            if (ObstaclesCollection[k]->x==x && ObstaclesCollection[k]->y==y)
                                   return false;
                     return true;
              }
       }
       else if (selected == VERT)
       {
              if (x==joueur.x && y==joueur.y) return false;
              else if (x==BlocRouge.x && y==BlocRouge.y) return false;
              else if (x==BlocBleu.x && y==BlocBleu.y) return false;
              else if (x==BlocNoir.x && y==BlocNoir.y) return false;
              else
              {
                     for (int k =0; k<NbObstacleLevel; k++)
                            if (ObstaclesCollection[k]->x==x && ObstaclesCollection[k]->y==y)
                                   return false;
                     return true;
              }
       }
       else if (selected == BLEU)
       {
              if (x==joueur.x && y==joueur.y) return false;
              else if (x==BlocRouge.x && y==BlocRouge.y) return false;
              else if (x==BlocVert.x && y==BlocVert.y) return false;
              else if (x==BlocNoir.x && y==BlocNoir.y) return false;
              else
              {
                     for (int k =0; k<NbObstacleLevel; k++)
                            if (ObstaclesCollection[k]->x==x && ObstaclesCollection[k]->y==y)
                                   return false;
                     return true;
              }
       }
       else if (selected == NOIR)
       {
              if (x==joueur.x && y==joueur.y) return false;
              else if (x==BlocRouge.x && y==BlocRouge.y) return false;
              else if (x==BlocVert.x && y==BlocVert.y) return false;
              else if (x==BlocBleu.x && y==BlocBleu.y) return false;
              else
              {
                     for (int k =0; k<NbObstacleLevel; k++)
                            if (ObstaclesCollection[k]->x==x && ObstaclesCollection[k]->y==y)
                                   return false;
                     return true;
              }
       }
}

void gameMechanics(  selection what, orientations touche )
{
       if (touche==GAUCHE)
       {
              if (what==JOUEUR && isValidMove(JOUEUR, joueur.x-1, joueur.y, touche ))
              {
                     joueur.x--;
                     frame=0;
                     direction=GAUCHE;
                     mouvement=true;
              }
              else if (what==JOUEUR && !isValidMove(JOUEUR, joueur.x-1, joueur.y, touche))
              {
                     frame=0;
                     direction=GAUCHE;
              }
              else if (what==LUMIERE && isValidMove(LUMIERE, lumiere.x-1, lumiere.y, touche))     lumiere.x--;
              else if (what==ROUGE && isValidMove(ROUGE, BlocRouge.x-1, BlocRouge.y, touche ))     BlocRouge.x--;
              else if (what==VERT && isValidMove(VERT, BlocVert.x-1, BlocVert.y, touche))     BlocVert.x--;
              else if (what==BLEU && isValidMove(BLEU, BlocBleu.x-1, BlocBleu.y, touche))     BlocBleu.x--;
              else if (what==NOIR && isValidMove(NOIR, BlocNoir.x-1, BlocNoir.y, touche))     BlocNoir.x--;
       }
       if (touche==DROITE)
       {
              if (what==JOUEUR && isValidMove(JOUEUR, joueur.x+1, joueur.y, touche))
              {
                     joueur.x++;
                     frame=0;
                     direction=DROITE;
                     mouvement=true;
              }
              else if (what==JOUEUR && !isValidMove(JOUEUR, joueur.x+1, joueur.y, touche))
              {
                     frame=0;
                     direction=DROITE;
              }
              else if (what==LUMIERE && isValidMove(LUMIERE, lumiere.x+1, lumiere.y, touche))     lumiere.x++;
              else if (what==ROUGE && isValidMove(ROUGE, BlocRouge.x+1, BlocRouge.y, touche))     BlocRouge.x++;
              else if (what==VERT && isValidMove(VERT, BlocVert.x+1, BlocVert.y, touche))     BlocVert.x++;
              else if (what==BLEU && isValidMove(BLEU, BlocBleu.x+1, BlocBleu.y, touche))     BlocBleu.x++;
              else if (what==NOIR && isValidMove(NOIR, BlocNoir.x+1, BlocNoir.y, touche))     BlocNoir.x++;
       }

       if (touche==HAUT)
       {
              if (what==JOUEUR && isValidMove(JOUEUR, joueur.x, joueur.y-1, touche))
              {
                     joueur.y--;
                     frame=0;
                     direction=HAUT;
                     mouvement=true;
              }
              else if (what==JOUEUR && !isValidMove(JOUEUR, joueur.x, joueur.y-1, touche))
              {
                     frame=0;
                     direction=HAUT;
              }
              else if (what==LUMIERE && isValidMove(LUMIERE, lumiere.x, lumiere.y-1, touche))     lumiere.y--;
              else if (what==ROUGE && isValidMove(ROUGE, BlocRouge.x, BlocRouge.y-1, touche))     BlocRouge.y--;
              else if (what==VERT && isValidMove(VERT, BlocVert.x, BlocVert.y-1, touche))     BlocVert.y--;
              else if (what==BLEU && isValidMove(BLEU, BlocBleu.x, BlocBleu.y-1, touche))     BlocBleu.y--;
              else if (what==NOIR && isValidMove(NOIR, BlocNoir.x, BlocNoir.y-1, touche))     BlocNoir.y--;
       }
       if (touche==BAS)
       {
              if (what==JOUEUR && isValidMove(JOUEUR, joueur.x, joueur.y+1, touche))
              {
                     joueur.y++;
                     frame=0;
                     direction=BAS;
                     mouvement=true;
              }
              else if (what==JOUEUR && !isValidMove(JOUEUR, joueur.x, joueur.y+1, touche))
              {
                     frame=0;
                     direction=BAS;
              }
              else if (what==LUMIERE && isValidMove(LUMIERE, lumiere.x, lumiere.y+1, touche))     lumiere.y++;
              else if (what==ROUGE && isValidMove(ROUGE, BlocRouge.x, BlocRouge.y+1, touche))     BlocRouge.y++;
              else if (what==VERT && isValidMove(VERT, BlocVert.x, BlocVert.y+1, touche))     BlocVert.y++;
              else if (what==BLEU && isValidMove(BLEU, BlocBleu.x, BlocBleu.y+1, touche))     BlocBleu.y++;
              else if (what==NOIR && isValidMove(NOIR, BlocNoir.x, BlocNoir.y+1, touche))     BlocNoir.y++;
       }


}

void renderReceptors( void )
{
       for( unsigned int k=0; k<NbReceptorsLevel; k++ )
       {
              unsigned int lX = SIZE*ReceptorCollection[k]->x+OFFSET_X+SIZE/2;
              unsigned int lY = SIZE*ReceptorCollection[k]->y+OFFSET_Y+SIZE/2;
              unsigned char Rr = ReceptorCollection[k]->R;
              unsigned char Gr = ReceptorCollection[k]->G;
              unsigned char Br = ReceptorCollection[k]->B;
              unsigned int direction = ReceptorCollection[k]->direction;
              bool valide = ReceptorCollection[k]->isvalide;

              unsigned char Rc,Gc,Bc;

              if (valide==false)
              {
                     Rc=0;
                     Gc=0;
                     Bc=0;
              }
              else
              {
                     Rc=255;
                     Gc=255;
                     Bc=255;
              }

              _boxRGBA(  lX-4, lY-4, lX+4, lY+4, Rc, Gc, Bc, 255 );
              _boxRGBA(  lX-2, lY-2, lX+2, lY+2, Rr, Gr, Br, 255 );


              if (direction==GAUCHE)
              {
                     _lineRGBA(  lX-4, lY-1, lX-8, lY-1, Rc, Gc, Bc, 255 );
                     _lineRGBA(  lX-4, lY, lX-8, lY, Rc, Gc, Bc, 255 );
                     _lineRGBA(  lX-4, lY+1, lX-8, lY+1, Rc, Gc, Bc, 255 );
              }
              else if (direction==DROITE)
              {
                     _lineRGBA(  lX+4, lY-1, lX+8, lY-1, Rc, Gc, Bc, 255 );
                     _lineRGBA(  lX+4, lY, lX+8, lY, Rc, Gc, Bc, 255 );
                     _lineRGBA(  lX+4, lY+1, lX+8, lY+1, Rc, Gc, Bc, 255 );
              }
              else if (direction==HAUT)
              {
                     _lineRGBA(  lX-1, lY-4, lX-1, lY-8, Rc, Gc, Bc, 255 );
                     _lineRGBA(  lX, lY-4, lX, lY-8, Rc, Gc, Bc, 255 );
                     _lineRGBA(  lX+1, lY-4, lX+1, lY-8, Rc, Gc, Bc, 255 );
              }
              else if (direction==BAS)
              {
                     _lineRGBA(  lX-1, lY+4, lX-1, lY+8, Rc, Gc, Bc, 255 );
                     _lineRGBA(  lX, lY+4, lX, lY+8, Rc, Gc, Bc, 255 );
                     _lineRGBA(  lX+1, lY+4, lX+1, lY+8, Rc, Gc, Bc, 255 );
              }

       }
}

void checkReceptors( void  )
{
       for( unsigned int k=0; k<NbReceptorsLevel; k++ )
       {
              unsigned int lX1, lX2, lX3;
              unsigned int lY1, lY2, lY3;

              unsigned int lX = SIZE*ReceptorCollection[k]->x+OFFSET_X+SIZE/2;
              unsigned int lY = SIZE*ReceptorCollection[k]->y+OFFSET_Y+SIZE/2;
              unsigned char Rr = ReceptorCollection[k]->R;
              unsigned char Gr = ReceptorCollection[k]->G;
              unsigned char Br = ReceptorCollection[k]->B;
              unsigned int direction = ReceptorCollection[k]->direction;

              if (direction==GAUCHE)
              {
                     // all 7 changed to 8
                     lX1=lX-7;
                     lX2=lX-7;
                     lX3=lX-7;
                     lY1=lY-1;
                     lY2=lY;
                     lY3=lY+1;
              }
              else if (direction==DROITE)
              {
                     lX1=lX+7;
                     lX2=lX+7;
                     lX3=lX+7;
                     lY1=lY-1;
                     lY2=lY;
                     lY3=lY+1;
              }
              else if (direction==HAUT)
              {
                     lX1=lX-1;
                     lX2=lX;
                     lX3=lX+1;
                     lY1=lY-7;
                     lY2=lY-7;
                     lY3=lY-7;
              }
              else if (direction==BAS)
              {
                     lX1=lX-1;
                     lX2=lX;
                     lX3=lX+1;
                     lY1=lY+7;
                     lY2=lY+7;
                     lY3=lY+7;
              }

              unsigned char R1, G1, B1;
              unsigned char R2, G2, B2;
              unsigned char R3, G3, B3;
              unsigned char Rm, Gm, Bm;

              _getPixelRGB(  lX1, lY1, &R1, &G1, &B1 );
              _getPixelRGB(  lX2, lY2, &R2, &G2, &B2 );
              _getPixelRGB(  lX3, lY3, &R3, &G3, &B3 );

              Rm = (R1+R2+R3)/3;
              Gm = (G1+G2+G3)/3;
              Bm = (B1+B2+B3)/3;

//              _boxRGBA( 310, 10+k*30, 330, 30+k*30, Rm, Gm, Bm, 255 );
//              _rectangleRGBA( 310, 10+k*30, 330, 30+k*30, 0, 0, 0, 255 );

//              _boxRGBA( 340, 10+k*30, 360, 30+k*30, Rr, Gr, Br, 255 );
//              _rectangleRGBA( 340, 10+k*30, 360, 30+k*30, 0, 0, 0, 255 );


              if (Rm>=Rr-EPSILON && Rm<=Rr+EPSILON && Gm>=Gr-EPSILON && Gm<=Gr+EPSILON && Bm>=Br-EPSILON && Bm<=Br+EPSILON)
              {
                     ReceptorCollection[k]->isvalide = true;
              }
              else
              {
                     ReceptorCollection[k]->isvalide = false;
              }
       }
}

void renderDoors( void )
{
       for( int k=0; k<NbDoorsLevel; k++ )
       {
              unsigned int lX = SIZE*DoorCollection[k]->x+OFFSET_X;
              unsigned int lY = SIZE*DoorCollection[k]->y+OFFSET_Y;

              if (DoorCollection[k]->isdoor==false) // check if it is a door or a wall (draw walls)
              {
                     if (DoorCollection[k]->direction == HAUT)
                     {
                            dsubimage( lX, lY, &sprites, 0,16,16,16,  DIMAGE_NONE);
                     }
                     else if (DoorCollection[k]->direction == GAUCHE)
                     {
                            dsubimage( lX, lY, &sprites, 16,16,16,16,  DIMAGE_NONE);
                     }
                     else if (DoorCollection[k]->direction == BAS)
                     {
                            dsubimage( lX, lY, &sprites, 32,16,16,16,  DIMAGE_NONE);
                     }
                     else if (DoorCollection[k]->direction == DROITE)
                     {
                            dsubimage( lX, lY, &sprites, 48,16,16,16,  DIMAGE_NONE);
                     }
              }
              else if (DoorCollection[k]->isopen==false) // check if the door is open (draw stairs)
              {
                     if (DoorCollection[k]->direction == HAUT)
                     {
                            dsubimage( lX, lY, &sprites, 0,32,16,16,  DIMAGE_NONE);
                     }
                     else if (DoorCollection[k]->direction == GAUCHE)
                     {
                            dsubimage( lX, lY, &sprites, 16,32,16,16,  DIMAGE_NONE);
                     }
                     else if (DoorCollection[k]->direction == BAS)
                     {
                            dsubimage( lX, lY, &sprites, 32,32,16,16,  DIMAGE_NONE);
                     }
                     else if (DoorCollection[k]->direction == DROITE)
                     {
                            dsubimage( lX, lY, &sprites, 48,32,16,16,  DIMAGE_NONE);
                     }
              }
              else  // check if the door is open (draw doors)
              {
                     if (DoorCollection[k]->direction == HAUT)
                     {
                            dsubimage( lX, lY, &sprites, 0,48,16,16,  DIMAGE_NONE);
                     }
                     else if (DoorCollection[k]->direction == GAUCHE)
                     {
                            dsubimage( lX, lY, &sprites, 16,48,16,16,  DIMAGE_NONE);
                     }
                     else if (DoorCollection[k]->direction == BAS)
                     {
                            dsubimage( lX, lY, &sprites, 32,48,16,16,  DIMAGE_NONE);
                     }
                     else if (DoorCollection[k]->direction == DROITE)
                     {
                            dsubimage( lX, lY, &sprites, 48,48,16,16,  DIMAGE_NONE);
                     }
              }
       }

}

void checkDoors( void )
{
       for( int k=0; k<NbDoorsLevel; k++ )
       {
              if (DoorCollection[k]->isdoor==true) // check if it is a door or a wall
              {
                     bool temp = true;
                     for(int j=0; j<DoorCollection[k]->nbreceptor; j++ )
                     {
                            int receptorReference =  DoorCollection[k]->receptors[j];
                            bool currentrecept = ReceptorCollection[receptorReference]->isvalide;
                            Receptor* tempRecept = ReceptorCollection[receptorReference];

                            temp=temp && currentrecept;

                            if (currentrecept)
                            {
                                   if(DoorCollection[k]->direction==HAUT)
                                   {
                                          int X = DoorCollection[k]->x*SIZE+OFFSET_X;
                                          int Y = DoorCollection[k]->y*SIZE-SIZE/2+OFFSET_Y;

                                          if (DoorCollection[k]->nbreceptor==1)
                                          {
                                                 _boxRGBA( X+SIZE/2-1, Y-1, X+SIZE/2+1, Y+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X+SIZE/2-2, Y-2, X+SIZE/2+2, Y+2, 150, 150, 150, 255);
                                          }
                                          else if (DoorCollection[k]->nbreceptor==2)
                                          {
                                                 _boxRGBA( X+SIZE/3*(j+1)-1, Y-1, X+SIZE/3*(j+1)+1, Y+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X+SIZE/3*(j+1)-2, Y-2, X+SIZE/3*(j+1)+2, Y+2, 150, 150, 150, 255);
                                          }
                                          else if (DoorCollection[k]->nbreceptor==3)
                                          {
                                                 _boxRGBA( X+SIZE/3*(j+1)-1, Y-1, X+SIZE/3*(j+1)+1, Y+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X+SIZE/3*(j+1)-2, Y-2, X+SIZE/3*(j+1)+2, Y+2, 150, 150, 150, 255);
                                          }
                                   }
                                   else if(DoorCollection[k]->direction==BAS)
                                   {
                                          int X = DoorCollection[k]->x*SIZE+OFFSET_X;
                                          int Y = DoorCollection[k]->y*SIZE+3*SIZE/2+OFFSET_Y;

                                          if (DoorCollection[k]->nbreceptor==1)
                                          {
                                                 _boxRGBA( X+SIZE/2-1, Y-1, X+SIZE/2+1, Y+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X+SIZE/2-2, Y-2, X+SIZE/2+2, Y+2, 150, 150, 150, 255);
                                          }
                                          else if (DoorCollection[k]->nbreceptor==2)
                                          {
                                                 _boxRGBA( X+SIZE/3*(j+1)-1, Y-1, X+SIZE/3*(j+1)+1, Y+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X+SIZE/3*(j+1)-2, Y-2, X+SIZE/3*(j+1)+2, Y+2, 150, 150, 150, 255);
                                          }
                                          else if (DoorCollection[k]->nbreceptor==3)
                                          {
                                                 _boxRGBA( X+SIZE/3*(j+1)-1, Y-1, X+SIZE/3*(j+1)+1, Y+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X+SIZE/3*(j+1)-2, Y-2, X+SIZE/3*(j+1)+2, Y+2, 150, 150, 150, 255);
                                          }
                                   }
                                   else if(DoorCollection[k]->direction==GAUCHE)
                                   {
                                          int X = DoorCollection[k]->x*SIZE-SIZE/2+OFFSET_X;
                                          int Y = DoorCollection[k]->y*SIZE+OFFSET_Y;

                                          if (DoorCollection[k]->nbreceptor==1)
                                          {
                                                 _boxRGBA( X-1, Y+SIZE/2-1, X+1, Y+SIZE/2+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X-2, Y+SIZE/2-2, X+2, Y+SIZE/2+2, 150, 150, 150, 255);
                                          }
                                          else if (DoorCollection[k]->nbreceptor==2)
                                          {
                                                 _boxRGBA( X-1, Y+SIZE/3*(j+1)-1, X+1, Y+SIZE/3*(j+1)+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X-2, Y+SIZE/3*(j+1)-2, X+2, Y+SIZE/3*(j+1)+2, 150, 150, 150, 255);
                                          }
                                          else if (DoorCollection[k]->nbreceptor==3)
                                          {
                                                 _boxRGBA( X-1, Y+SIZE/4*(j+1)-1, X+1, Y+SIZE/4*(j+1)+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X-2, Y+SIZE/4*(j+1)-2, X+2, Y+SIZE/4*(j+1)+2, 150, 150, 150, 255);
                                          }
                                   }
                                   else if(DoorCollection[k]->direction==DROITE)
                                   {
                                          int X = DoorCollection[k]->x*SIZE+3*SIZE/2+OFFSET_X;
                                          int Y = DoorCollection[k]->y*SIZE+OFFSET_Y;

                                          if (DoorCollection[k]->nbreceptor==1)
                                          {
                                                 _boxRGBA( X-1, Y+SIZE/2-1, X+1, Y+SIZE/2+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X-2, Y+SIZE/2-2, X+2, Y+SIZE/2+2, 150, 150, 150, 255);
                                          }
                                          else if (DoorCollection[k]->nbreceptor==2)
                                          {
                                                 _boxRGBA( X-1, Y+SIZE/3*(j+1)-1, X+1, Y+SIZE/3*(j+1)+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X-2, Y+SIZE/3*(j+1)-2, X+2, Y+SIZE/3*(j+1)+2, 150, 150, 150, 255);
                                          }
                                          else if (DoorCollection[k]->nbreceptor==3)
                                          {
                                                 _boxRGBA( X-1, Y+SIZE/4*(j+1)-1, X+1, Y+SIZE/4*(j+1)+1, tempRecept->R, tempRecept->G, tempRecept->B, 255);
                                                 _rectangleRGBA( X-2, Y+SIZE/4*(j+1)-2, X+2, Y+SIZE/4*(j+1)+2, 150, 150, 150, 255);
                                          }
                                   }
                            }
                     }
                     DoorCollection[k]->isopen=temp;
              }
       }
}

static int get_inputs(void)
{
       int opt = GETKEY_DEFAULT & ~GETKEY_REP_ARROWS;
       int timeout = 1;

       while(1)
       {
              key_event_t ev = getkey_opt(opt, &timeout);
              if(ev.type == KEYEV_NONE) return -1;

              int key = ev.key;

              if (key==KEY_EXIT)
                     done = true;

              if (key==KEY_F1)
              {
                     selected = JOUEUR;
                     ///dprint( 300, 10, C_WHITE, "F1 Pressed");
              }

              if (key==KEY_F2)
              {
                     selected = LUMIERE;
                     //dprint( 300, 10, C_WHITE, "F2 Pressed");
              }

              if (key==KEY_F3)
              {
                     selected = ROUGE;
                     //dprint( 300, 10, C_WHITE, "F3 Pressed");
              }

              if (key==KEY_F4)
              {
                     selected = VERT;
                     //dprint( 300, 10, C_WHITE, "F4 Pressed");
              }

              if (key==KEY_F5)
              {
                     selected = BLEU;
                     //dprint( 300, 10, C_WHITE, "F5 Pressed");
              }

              if (key==KEY_F6)
              {
                     selected = NOIR;
                     //dprint( 300, 10, C_WHITE, "F6 Pressed");
              }

              if (key==KEY_LEFT)
              {
                     gameMechanics( selected, GAUCHE);
              }

              if (key==KEY_RIGHT)
              {
                     gameMechanics( selected, DROITE);
              }

              if (key==KEY_UP)
              {
                     gameMechanics( selected, HAUT);
              }

              if (key==KEY_DOWN)
              {
                     gameMechanics( selected, BAS);
              }
              /*
                            if (key==KEY_7)
                            {
                                   for( int k=0; k<NB_DOORS; k++ )
                                   {
                                          DoorCollection[k]->isdoor=false;
                                   }
                            }

                            if (key==KEY_8)
                            {
                                   for( int k=0; k<NB_DOORS; k++ )
                                   {
                                          DoorCollection[k]->isdoor=true;
                                          DoorCollection[k]->isopen=false;
                                   }
                            }

                            if (key==KEY_9)
                            {
                                   for( int k=0; k<NB_DOORS; k++ )
                                   {
                                          DoorCollection[k]->isdoor=true;
                                          DoorCollection[k]->isopen=true;
                                   }
                            }
              */
       }
}

void drawTitle( void )
{

}

void drawMenu( void )
{

}

int main ( int argc, char** argv )
{
       for( int k=0; k < NB_LEVELS; k++) Map[k].visited = true;

       currentLevel = 0;

       dfont( &font_fantasy );

       drawTitle();

       drawMenu();

       loadLevel( currentLevel );

       initMap();
       initWalls();

       while (!done)
       {
              dclear(C_RGB(0,0,0));

              frame_cursor++;
              frame_cursor = frame_cursor % 4;

              drawInterface(  );
              drawMinimap( );
              renderMap(  );

              renderWalls(  );

              checkReceptors(  );
              renderReceptors(  );

              checkDoors( );
              renderDoors( );

              renderMovable(  );
              renderObstacles(  );
              renderLight(  );
              renderTreasures( );
              renderPlayer(  );

              dupdate();

              get_inputs();
       }
       return 1;
}
