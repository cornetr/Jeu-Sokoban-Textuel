#include "main.h"

//on creer un nouveau niveau ainsi que les elements qui le compose
niveau_t* nouveau_niveau(int nb_colonnes, int nb_lignes){
	niveau_t * niveau;
	niveau=malloc(sizeof(niveau_t));
	int taille=nb_lignes*nb_colonnes;
	niveau->terrain=malloc(taille*sizeof(char));
	niveau->nb_colonnes=nb_colonnes;
	niveau->nb_lignes=nb_lignes;
	return niveau;
}

//on place un caractere donné sur le terrain niveau donne, aux coordonnees donnees
void place_sur_terrain (niveau_t* niveau, int colonne, int ligne, char car){
	int indice=(ligne*(niveau->nb_colonnes))+colonne;
	*((niveau->terrain+indice))=car;

}

//on lit le caractere du terrain aux coordonnees donnees
char lecture_du_terrain (niveau_t* niveau, int colonne, int ligne){
	int indice=ligne*niveau->nb_colonnes+colonne;
	return *(niveau->terrain+indice);
}

//on initialise tout le terrain d'un niveau avec des #
void initialise_le_terrain (niveau_t* niveau){
	for(int idx=0;idx<niveau->nb_lignes;idx++){
		for(int idx2=0;idx2<niveau->nb_colonnes+1;idx2++){
			place_sur_terrain(niveau,idx2,idx,'#');
		}
	}
}

//on parcours le terrain du niveau et on affiche chaque caractere (avec des couleurs en plus)
void affichage_niveau(niveau_t* niveau){
	system("clear");
	for(int idx=0;idx<(niveau->nb_lignes);idx++){
		for(int idx2=0;idx2<(niveau->nb_colonnes);idx2++){
			if(lecture_du_terrain(niveau, idx2, idx) == '@'){
                printf("\e[94m%c\e[0m", lecture_du_terrain(niveau, idx2, idx));
            }else if (lecture_du_terrain(niveau, idx2, idx) == 'X'){
                printf("\e[93m%c\e[0m", lecture_du_terrain(niveau, idx2, idx));
            }else if (lecture_du_terrain(niveau, idx2, idx) == '$'){
                printf("\e[92m%c\e[0m", lecture_du_terrain(niveau, idx2, idx));
            }else if (lecture_du_terrain(niveau, idx2, idx) == '+'){
                printf("\e[94m%c\e[0m", lecture_du_terrain(niveau, idx2, idx));
            }else if (lecture_du_terrain(niveau, idx2, idx) == '.'){
                printf("\e[92m%c\e[0m", lecture_du_terrain(niveau, idx2, idx));
            }else {
                printf("\e[2m%c\e[0m", lecture_du_terrain(niveau, idx2, idx));
            }
            
        }
		printf("\n");
	}
}

//on parcours un fichier contenant un terrain afin d'en faire un niveau et de le retourner
niveau_t* lecture_du_niveau(int quel_niveau){
	char chemin[50];
	sprintf(chemin,"./Niveaux/niveau_%d",quel_niveau);
	FILE * fichier;
	fichier = fopen(chemin,"r");
	if(!fichier){
		printf("\e[91mNiveau inexistant !\e[0m\n");
		exit(0);
	}
	int nb_colonnes=0;
	int nb_lignes=0;
	fscanf(fichier,"%d %d",&nb_colonnes,&nb_lignes);
	getc(fichier);

	niveau_t* niveau;
	niveau=nouveau_niveau(nb_colonnes,nb_lignes);
	point_t * point;
	point=malloc(sizeof(point_t));

	char c;	

	for(int idx=0;idx<nb_lignes;idx++){
		for(int idx2=0;idx2<nb_colonnes+1;idx2++){
			c=getc(fichier);
			if(c=='\n'&&idx2<nb_colonnes){
				while(idx2!=nb_colonnes){
					place_sur_terrain(niveau,idx2,idx,' ');
					idx2++;
				}
			}else if(idx2==nb_colonnes && c!='\n'){
				while(c!='\n'&&c!=EOF){
					c=getc(fichier);

				}
			}else if (c!='\n'){
				place_sur_terrain(niveau,idx2,idx,c);
			}
			if(c=='@'){
				point->ligne=idx;
				point->colonne=idx2;
				niveau->perso=point;
			}
			
		}	
	}
 	fclose(fichier);

 	return niveau;
}
//on libere la memoire occupee par le niveau et ses elements
void liberation_du_niveau (niveau_t* niveau){
	free(niveau->terrain);
	free(niveau->perso);
	free(niveau);
}

//on recupere un caractere tape au clavier par le joueur pour avoir une direction 
char entree_du_joueur (void){
	char entree;
	printf("\e[4mDans quelle direction aller\e[0m ? \n\e[4mDéplacements\e[0m: zqsd ou a pour revenir en arrière : ");
	do{
		entree=getchar(); 
	}while(entree!='z' && entree!='q' && entree!='s' && entree!='d' && entree!='a');
	printf("\n");
	return entree;
}

//determine si le niveau est termine a partir du nombre de caisses a ranger restantes
int niveau_termine (niveau_t* niveau){
	for(int idx=0;idx<niveau->nb_lignes;idx++){
		for(int idx2=0;idx2<niveau->nb_colonnes+1;idx2++){
			if(lecture_du_terrain(niveau,idx2,idx)=='$'){
				return 0;
			}
		}
	}
	return 1;
}

//on recupere un entier tape au clavier par le joueur pour un choix de niveau
int demande_quel_niveau(){
	int nombre;
	int test;

	printf("\e[4mChoisi ton niveau\e[0m : ");
	test = scanf ("%d", &nombre);

	if (test != 1){	
   	 	printf ("\e[91mTa saisie est invalide !\e[0m\n");
    	exit (0);
	}else return nombre;
}
