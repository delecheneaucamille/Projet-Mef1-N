#define MAX_PLAYERS 4
#define HAND_SIZE 5
#define DECK_SIZE 50

 typedef struct {
int value;
int state;
} Card;

typedef struct {
    Card* pile;      // Tableau dynamique pour la défausse
    int count;       // Nombre de cartes actuellement dans la défausse
    int capacity;    // Taille maximale allouée
} Defausse;

typedef struct {
    Card* hand;      // Tableau dynamique pour la main du joueur
    int count;       // Nombre de cartes actuellement dans la main
    int capacity;    // Taille maximale allouée
} PlayerHand;

typedef struct {
    PlayerHand* players; // Tableau dynamique pour les mains des joueurs
    int playerCount;     // Nombre de joueurs
    int currentPlayer;   // Indice du joueur courant
    Defausse defausse;   // Pile de défausse
} GameState;

