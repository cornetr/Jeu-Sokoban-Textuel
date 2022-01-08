typedef struct {
  int colonne;
  int ligne;
}point_t;

typedef struct {
  char * terrain;
  int nb_colonnes;
  int nb_lignes;
  point_t * perso;
  int nb_de_pas;
}niveau_t;

typedef struct{
	int score;
	char* pseudo;
}ligne_t;

typedef struct {
    niveau_t** tableau;
    int sommet;
}historique_t;

niveau_t* nouveau_niveau(int nb_colonnes, int nb_lignes);
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car);
char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne);
void initialise_le_terrain (niveau_t* niveau);
void affichage_niveau (niveau_t* niveau);
niveau_t* lecture_du_niveau(int quel_niveau);
void liberation_du_niveau (niveau_t* niveau);
char entree_du_joueur (void);
void deplacement (niveau_t* niveau, char direction);
int niveau_termine (niveau_t* niveau);
int demande_quel_niveau();

