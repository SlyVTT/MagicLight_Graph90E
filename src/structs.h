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
    unsigned int x;
    unsigned int y;
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
    unsigned int x;
    unsigned int y;
    unsigned char R,G,B,A;
    kind type;
};

struct Player
{
    unsigned int x;
    unsigned int y;
    orientations direction;
};

struct MapItem
{
    unsigned int ID;
    unsigned int x;
    unsigned int y;
    orientations direction;
};

struct Light
{
    unsigned int x;
    unsigned int y;
    Color couleur;
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
    unsigned int x, y;
    orientations direction;
    bool isopen;
    bool isdoor;
    unsigned char nbreceptor;
    int receptors[NB_RECEPTORS_PER_DOOR_MAX];
    int nextLevelNumber;
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
    LINGOT_PLATINE
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
    BLOCK_SUN
};

struct Obstacle
{
    unsigned int x, y;
    nonmovable type;
};

struct Treasure
{
    unsigned int x, y;
    chest type;
    bool isopen;
    content  inside;
    unsigned int scoreboost;
};

struct Minimap
{
    int x, y;
    unsigned char R,G,B,A;
    bool visited;
};
