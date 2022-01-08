#include "main.h"

int main(){
	while(1){
		niveau_t* niveau;
		int quel_niveau=demande_quel_niveau();
		niveau=lecture_du_niveau(quel_niveau);
		historique_t* hist = new_historique(500);
	
		affichage_niveau(niveau);
		niveau->nb_de_pas=0;

		while(niveau_termine(niveau)==0){
			char direction=entree_du_joueur();
			if (direction == 'a'){
           		if (niveau->nb_de_pas>0){
              	  niveau = coup_precedent(hist);
              	  affichage_niveau(niveau);
            	} else {
            		affichage_niveau(niveau);
              	  	printf("Impossible de revenir en arrière ! ");
            	}
     	    } else {
	            sauvegarde_un_coup(hist, niveau);
	            deplacement(niveau,direction);
	            affichage_niveau(niveau);
	            
        	}
			
			
			printf("\e[93mNombre de pa(s):\e[0m %d  \n",niveau->nb_de_pas );
		}

		printf("\e[92mNiveau terminé en %d pas. Bravo !\e[0m\n\n",niveau->nb_de_pas);

		char * pseudo;
		pseudo=nom_du_joueur();
		printf("\e[92mBien joué %s !\e[0m\n\n",pseudo);
		
		ecriture_du_score_multi(quel_niveau,pseudo,niveau->nb_de_pas);
		affiche_scores(quel_niveau);
		free(pseudo);
		liberation_du_niveau(niveau);
	
	}


	return 0;
}
