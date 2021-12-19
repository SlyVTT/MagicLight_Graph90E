#define NB_RECEPTORS_PER_DOOR_MAX 3

enum orientations
{
    GAUCHE = 0,
    DROITE = 1,
    HAUT = 2,
    BAS = 3,
    AUCUNE = 4,
    VERTICAL = 5,
    HORIZONTAL = 6
};

struct Receptor
{
    unsigned char x;
    unsigned char y;
    orientations direction;
    unsigned char R, G, B;
    bool isvalide;
};

enum selection
{
    NONE = 0,
    JOUEUR = 1,
    LUMIERE = 2,
    ROUGE = 3,
    VERT = 4,
    BLEU = 5,
    NOIR = 6
};

enum ID
{
    VIDE = 0,
    MUR = 1,
    PORTE = 2
};

enum kind
{
    OPAQUE = 0,
    TRANSPARENT = 1
};

struct Blocks
{
    unsigned char x;
    unsigned char y;
    unsigned char R,G,B,A;
    kind type;
};

struct Player
{
    unsigned char x;
    unsigned char y;
    orientations direction;
};

struct MapItem
{
    unsigned char ID;
    unsigned char x;
    unsigned char y;
    orientations direction;
};

struct Light
{
    unsigned char x;
    unsigned char y;
    unsigned char R,G,B,A;
    bool movable;
};

struct Wall
{
    orientations direction;
    unsigned int mini;
    unsigned int maxi;
    unsigned int fixe;
};

struct Door
{
    unsigned char x, y;
    orientations direction;
    bool isopen;
    bool isdoor;
    unsigned char nbreceptor;
    char receptors[NB_RECEPTORS_PER_DOOR_MAX];
    char nextLevelNumber;
};

enum content
{
    RIEN = 0,
    PIERRE_NOIRE,
    PIERRE_VERTE,
    PIERRE_BLEUE,
    PIERRE_ROUGE,
    PIERRE_BLANCHE,
    LINGOT_FER,
    LINGOT_BRONZE,
    LINGOT_ARGENT,
    LINGOT_OR,
    LINGOT_PLATINE,
    WHITE_FRAGMENT,
    BLACK_FRAGMENT ,
    RED_FRAGMENT,
    GREEN_FRAGMENT,
    BLUE_FRAGMENT
};

enum chest
{
    T_RED = 0,
    T_YELLOW,
    T_GREEN,
    T_BLUE
};

enum nonmovable
{
    BLOCK_STONE = 0,
    BLOCK_MOON,
    BLOCK_WOOD,
    BLOCK_SUN,
    BLOCK_WATER
};

struct Obstacle
{
    unsigned char x, y;
    nonmovable type;
};

struct Treasure
{
    unsigned char x, y;
    chest type;
    bool isopen;
    content  inside;
    unsigned int scoreboost;
    bool isvisible;
};

struct Minimap
{
    char x, y;
    unsigned char R,G,B,A;
    bool visited;
    bool doorNorth;
    bool doorSouth;
    bool doorWest;
    bool doorEast;
};

struct LevelSaveStatus
{
    unsigned char chestStatusSave[8]={0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA};              // max 8 chest per level : status = 0 if chest not touched yet / 1 if open (and then empty) (activated one time) / 2 if not visible (activated 2 times)
    unsigned char doorStatusSave[4]={0xBB,0xBB,0xBB,0xBB};                  // status of the door (0 = closed; 1 = open )
    unsigned char bossStatusSave[8]={0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC};               // max 8 bosses per level (0 = normal; 1 = defeated )
    unsigned char monsterStatusSave[8]={0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD};               // max 8 monsters per level (0 = normal; 1 = defeated )
    unsigned char redBlockSave[2]={0xEE,0xEE};                          // X and Y coordinates
    unsigned char greenBlockSave[2]={0xEE,0xEE};                          // X and Y coordinates
    unsigned char blueBlockSave[2]={0xEE,0xEE};                          // X and Y coordinates
    unsigned char blackBlockSave[2]={0xEE,0xEE};                          // X and Y coordinates
    unsigned char lightSave[2]={0xFF,0xFF};                          // X and Y coordinates
}; // TOTAL 38 bytes per level saved

struct GameSaveStatus
{
    unsigned char currentScore[2];          // Score between 0 and 65535 [byte 1 : score / 256] and [byte 2 : score % 256 ]
    unsigned char currentLevel;
    unsigned char visitedLevels[33];        // Levels 1 to 32 save status as level 0 is always visited (0 = not visited, 1 = visited)
    unsigned char currentDifficulty;
    unsigned char currentLife;
    unsigned char redFrag;                      // 0 = bot collected yet - 1 = collected
    unsigned char greenFrag;                      // 0 = bot collected yet - 1 = collected
    unsigned char blueFrag;                      // 0 = bot collected yet - 1 = collected
    unsigned char blackFrag;                      // 0 = bot collected yet - 1 = collected
    unsigned char whiteFrag;                      // 0 = bot collected yet - 1 = collected
    unsigned char terminator = 0x99;
};  // TOTAL 44 bytes

enum monstertype
{
    BLOB = 0,
    BAT,
    GHOST,
    SPIDER,
    SKELETON
};

struct Monster
{
    unsigned char xcur, ycur;
    unsigned char mini, maxi;
    orientations direction;
    orientations sens;
    monstertype kind;
};

enum bosscolor
{
    B_RED = 0,
    B_GREEN,
    B_BLUE,
    B_BLACK,
    BIGBOSS
};


struct Boss
{
    unsigned char xcur, ycur;
    unsigned char mini, maxi;
    orientations direction;
    orientations sens;
    bosscolor color;
};


struct Bullet
{
    unsigned int xpart;
    unsigned int ypart;
    unsigned int color;
    bool visible;
};
