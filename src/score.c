#include "main.h"

//on lit le score efectue pour ce niveau dans le fichier correspondant
int lecture_du_score (int quel_niveau){
	char chemin[50];
	sprintf(chemin,"./score_%d",quel_niveau);
	FILE * fichier;
	fichier = fopen(chemin,"r");
	if(!fichier){
		return 0;
	}else{
		int score;
		fscanf(fichier,"%d",&score);
		printf("Meilleur score enregistré : %d pas !\n", score);
		fclose(fichier);
		return score;
	}
}

//on ecrit le score effectue par le joueur dans le fichier du niveau correspondant si il n'existe pas on le creer 
void ecriture_du_score (int quel_niveau, int score){
	char chemin[50];
	sprintf(chemin,"./score_%d",quel_niveau);
	FILE * fichier;
	int test=lecture_du_score(quel_niveau);
	if(test==0){
		fichier = fopen(chemin,"w");
		fprintf(fichier,"%d",score);
		printf("Tu es le premier à jouer sur ce niveau !\n");
		fclose(fichier);
	}
	if(score<test){
		fichier = fopen(chemin,"w");
		fprintf(fichier,"%d\n",score);
		printf("Nouveau meilleur score ! Seulement %d pas !\n",score );
		fclose(fichier);
	}else printf("Tu feras mieux la prochaine fois !\n\n");
	
}

//on lit le meilleur score effectue par les joueur tout au debut du fichier si il n'existe pas on le creer 
int lecture_du_score_multi (int quel_niveau){
	char chemin[50];
	sprintf(chemin,"./score_multi_%d",quel_niveau);
	FILE * fichier;
	fichier = fopen(chemin,"r");

	if(!fichier){
		fichier=fopen(chemin,"w");
		fclose(fichier);
		printf("Tu es le premier à jouer sur ce niveau !\n");
		return 0;
	}else{
		int score;
		fscanf(fichier,"%d",&score);
		printf("Le meilleur score enregistré est %d pas !\n", score);
		fclose(fichier);
		return score;
	}
}

//on ecrit le score du joeur a la suite des autres si il y a moins de 5 scores, sinon on garde les 5 meilleurs scores
//pour ce faire, on ajoute le score, on trie les score, on ecrit les 5 meilleurs dans un fichier qui devient le nouveau fichier score du niveau 
void ecriture_du_score_multi (int quel_niveau, char * pseudo, int score){
	char chemin[50];
	sprintf(chemin,"score_multi_%d",quel_niveau);
	FILE * fichier;

	lecture_du_score_multi(quel_niveau);

	if(test_du_top(quel_niveau)==0){
		fichier = fopen(chemin,"a");
		fprintf(fichier,"%d %s\n",score,pseudo);
		fclose(fichier);
		tri_des_lignes(quel_niveau);

	}else{
		fichier = fopen(chemin,"a");
		fprintf(fichier,"%d %s\n",score,pseudo);
		fclose(fichier);
		tri_des_lignes(quel_niveau);

		char tab[250];
    	int idx=0;
    	// on recupere les 5 premieres lignes des scores dans tab
		int nb_score=0;
		fichier=fopen(chemin,"r");
		while(nb_score!=5){
			tab[idx]=getc(fichier);
			if(tab[idx]=='\n'||tab[idx]==EOF){
				nb_score++;
			}
			idx++;
		}
		fclose(fichier);
		//transfere de tab dans fichier tmp
		fichier=fopen("score.txt","w");
		for(int cpt=0;cpt<idx;cpt++){
			fprintf(fichier,"%c",tab[cpt]);
		}
		fclose(fichier);

		remove(chemin);

		rename("score.txt",chemin);

	}
	
}

//on demande au joeur de saisir un pseudo qui fait au maximum 8 caracteres
char * nom_du_joueur (void){
	char * pseudo=malloc(sizeof(char)*8);
	printf("\e[4mQuel est ton pseudo\e[0m ? (8 caractères max.) ");
	scanf ("%s", pseudo);

	if (strlen(pseudo)>8||strlen(pseudo)==0){	
   	 	printf ("\e[91mTa saisie est invalide !\e[0m\n\n");
    	free(pseudo);
    	return pseudo=nom_du_joueur();
	}else return pseudo;

}

//on compte le nombres de scores dans le fichier du niveau au numero donne
int nb_de_scores(int quel_niveau){
	char chemin[50];
    sprintf(chemin,"./score_multi_%d",quel_niveau);
    FILE *fichier;
    fichier = fopen(chemin,"r");


    int nb_score = 0;
    char c;
    while ((c=getc(fichier))!=EOF){
        if(c=='\n'){
            nb_score++;
        }
    }
    fclose(fichier);
    return nb_score;
}

//on stock les lignes composees d'un score et d'un pseudo dans un tableau pour 
//pouvoir les trier et enfin les reecrire dans l'ordre dans le fichier score du niveau
void tri_des_lignes(int quel_niveau){

    int nb_score = nb_de_scores(quel_niveau);


    char chemin[50];
    sprintf(chemin,"./score_multi_%d",quel_niveau);
    FILE *fichier;
    fichier = fopen(chemin,"r");
    ligne_t** tab_ligne_t = malloc(sizeof(ligne_t*)*15);
    ligne_t* volante = malloc(sizeof(ligne_t));


    for (int i = 0; i < nb_score; i++){
        ligne_t* ligne = malloc(sizeof(ligne_t));
        ligne->pseudo = malloc(sizeof(char)*8);

        fscanf(fichier,"%d %s",&(ligne->score),(ligne->pseudo));

        tab_ligne_t[i]=ligne;
    }


    for(int cpt=0;cpt<nb_score;cpt++){
        for (int i = 0; i <nb_score-1; i++){
            if(tab_ligne_t[i+1]->score<tab_ligne_t[i]->score){
                volante=tab_ligne_t[i+1];
                tab_ligne_t[i+1]=tab_ligne_t[i];
                tab_ligne_t[i]=volante;
            }     
        }     
    }
    fclose(fichier);


    fopen(chemin,"w");
    for (int cpt2 = 0; cpt2 <nb_score; cpt2++){
        //printf("- %d %s\n",tab_ligne_t[cpt2]->score,tab_ligne_t[cpt2]->pseudo);
        
        fprintf(fichier,"%d %s\n",tab_ligne_t[cpt2]->score,tab_ligne_t[cpt2]->pseudo);
        free(tab_ligne_t[cpt2]->pseudo);
        free(tab_ligne_t[cpt2]);
    }
    printf("\n");
    free(tab_ligne_t);
    fclose(fichier);
}

//on test si le fichier plus ou moins de 5 scores pour un top de 5 scores maximum
int test_du_top(int quel_niveau){

	int nb_score=nb_de_scores(quel_niveau);
    char chemin[50];

    sprintf(chemin,"./score_multi_%d",quel_niveau);
    FILE *fichier;

    fichier = fopen(chemin,"r");

	if(nb_score>=5){
		fclose(fichier);		
		return 1;

	}else{
		fclose(fichier);
		return 0;
	}
}

//on affiche le top des 5 meilleurs scores du niveau
int affiche_scores(int quel_niveau){
	char chemin[50];
    sprintf(chemin,"./score_multi_%d",quel_niveau);
    FILE *fichier;
    fichier = fopen(chemin,"r");

    char c;
    printf("\e[93m\e[4mTOP 5 des scores\e[0m\e[93m :\e[0m\n  ");
    while ((c=getc(fichier))!=EOF){
    	if(c=='\n'){
    		printf("%c  ",c );
    	}else printf("%c",c);
    }
    printf("\n");
    return 1;

}