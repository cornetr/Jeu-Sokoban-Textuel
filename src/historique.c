#include "main.h"


//on fait une copie du niveau donne pour pouvoir manipuler la copie par la suite comme historique
//on le renvoie
niveau_t* copie_du_niveau (niveau_t* niveau){
	niveau_t* cp_niveau ;
	cp_niveau= nouveau_niveau(niveau->nb_colonnes, niveau->nb_lignes);

	for (int i = 0; i < niveau->nb_colonnes*niveau->nb_lignes; ++i){
		cp_niveau->terrain[i] = niveau->terrain[i];
	}

	cp_niveau->nb_de_pas = niveau->nb_de_pas;
	cp_niveau->perso = malloc(sizeof(point_t));
	cp_niveau->perso->colonne = niveau->perso->colonne;
	cp_niveau->perso->ligne = niveau->perso->ligne;

	return cp_niveau;
}

//on initialise la notre historique dans la memoire avec ses elements, avec un nombre de coups donne
//on le renvoie
historique_t* new_historique(int size){
	historique_t* historique = malloc(sizeof(historique_t));
	historique->tableau = malloc(sizeof(niveau_t*)*size);
	historique->sommet = 0;
	return historique;
}

//on libere la memoire occupee par l'historique
void liberation_hist(historique_t* historique){
	free(historique);
}

//on prend en compte le coup effectue, il est sauvegarde dans l'historique
void sauvegarde_un_coup (historique_t* historique, niveau_t* niveau){
	historique->tableau[historique->sommet] = copie_du_niveau(niveau);
	historique->sommet++;
}

//on renvoie le niveau avec un tour en arriere, -1 tour
niveau_t* coup_precedent (historique_t* historique){
	if (historique->sommet == 0){
		return NULL;
	} else {
		niveau_t* precedent = historique->tableau[historique->sommet-1];
		historique->sommet--;
		return precedent;
	}


}
