#include "main.h"

//fonction de deplacement en 4 directions et qui gere toutes les exceptions du terrain
void deplacement (niveau_t* niveau, char direction){
	int lignePerso=niveau->perso->ligne;	
	int colonnePerso=niveau->perso->colonne;
	int stock=0;
	
	// 4 directions possibles donc 4 if avec les coordonnees qui different
	if(direction=='z'){
		//3 variables qui definissent le contenu des cases du jeu
		char estUn=lecture_du_terrain(niveau,colonnePerso,lignePerso);
		char seraUn=lecture_du_terrain(niveau,colonnePerso,lignePerso-1);
		char seraEnsuiteUn=lecture_du_terrain(niveau,colonnePerso,lignePerso-2);
		//si le perso est un + alors je suis sur un stock, un rangement
		if(estUn=='+'){
			stock=1;
		}
		//si je m'avance vers une case libre
		if(seraUn==' '){
			//si j'etais sur un stock alors je remets un stock
			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');
			//et j'avance mon joueur
			place_sur_terrain(niveau,colonnePerso,lignePerso-1,'@');
			//maj de ses coordonnees
			niveau->perso->ligne--;
		
		//sinon si je m'avance vers une case de rangement	
		}else if(seraUn=='.'){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			place_sur_terrain(niveau,colonnePerso,lignePerso-1,'+');
			niveau->perso->ligne--;
		
		//sinon si je dois pousser une caisse	
		}else if((seraUn=='$'||seraUn=='X')&& (seraEnsuiteUn==' '|| seraEnsuiteUn=='.')){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			//si ma caisse est sur un rangement alors je serai sur un rangement si je la suis au tout suivant
			if(seraUn=='X'){
				place_sur_terrain(niveau,colonnePerso,lignePerso-1,'+');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso-1,'@');

			//si la case apres ma caisse est un rangement alors elle sera bien rangee 
			if(seraEnsuiteUn=='.'){
				place_sur_terrain(niveau,colonnePerso,lignePerso-2,'X');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso-2,'$');
			niveau->perso->ligne--;
		}
	}

	if(direction=='q'){
		char estUn=lecture_du_terrain(niveau,colonnePerso,lignePerso);
		char seraUn=lecture_du_terrain(niveau,colonnePerso-1,lignePerso);
		char seraEnsuiteUn=lecture_du_terrain(niveau,colonnePerso-2,lignePerso);

		if(estUn=='+'){
			stock=1;
		}

		if(seraUn==' '){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			place_sur_terrain(niveau,colonnePerso-1,lignePerso,'@');
			niveau->perso->colonne--;
			
		}else if(seraUn=='.'){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			place_sur_terrain(niveau,colonnePerso-1,lignePerso,'+');
			niveau->perso->colonne--;
			
		}else if((seraUn=='$'||seraUn=='X')&& (seraEnsuiteUn==' '|| seraEnsuiteUn=='.')){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			if(seraUn=='X'){
				place_sur_terrain(niveau,colonnePerso-1,lignePerso,'+');
			}else place_sur_terrain(niveau,colonnePerso-1,lignePerso,'@');

			if(seraEnsuiteUn=='.'){
				place_sur_terrain(niveau,colonnePerso-2,lignePerso,'X');
			}else place_sur_terrain(niveau,colonnePerso-2,lignePerso,'$');
			niveau->perso->colonne--;
		}
	}

	if(direction=='s'){
		char estUn=lecture_du_terrain(niveau,colonnePerso,lignePerso);
		char seraUn=lecture_du_terrain(niveau,colonnePerso,lignePerso+1);
		char seraEnsuiteUn=lecture_du_terrain(niveau,colonnePerso,lignePerso+2);

		if(estUn=='+'){
			stock=1;
		}

		if(seraUn==' '){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			place_sur_terrain(niveau,colonnePerso,lignePerso+1,'@');
			niveau->perso->ligne++;
			
		}else if(seraUn=='.'){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			place_sur_terrain(niveau,colonnePerso,lignePerso+1,'+');
			niveau->perso->ligne++;
			
		}else if((seraUn=='$'||seraUn=='X')&& (seraEnsuiteUn==' '|| seraEnsuiteUn=='.')){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			if(seraUn=='X'){
				place_sur_terrain(niveau,colonnePerso,lignePerso+1,'+');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso+1,'@');

			if(seraEnsuiteUn=='.'){
				place_sur_terrain(niveau,colonnePerso,lignePerso+2,'X');

			}else place_sur_terrain(niveau,colonnePerso,lignePerso+2,'$');
			niveau->perso->ligne++;

			
		}

	}

	if(direction=='d'){
		char estUn=lecture_du_terrain(niveau,colonnePerso,lignePerso);
		char seraUn=lecture_du_terrain(niveau,colonnePerso+1,lignePerso);
		char seraEnsuiteUn=lecture_du_terrain(niveau,colonnePerso+2,lignePerso);
		
		if(estUn=='+'){
			stock=1;
		}

		if(seraUn==' '){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			place_sur_terrain(niveau,colonnePerso+1,lignePerso,'@');
			niveau->perso->colonne++;
			
			
			
		}else if(seraUn=='.'){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			place_sur_terrain(niveau,colonnePerso+1,lignePerso,'+');
			niveau->perso->colonne++;
			

		}else if((seraUn=='$'||seraUn=='X')&& (seraEnsuiteUn==' '|| seraEnsuiteUn=='.') ){

			if(stock==0){
				place_sur_terrain(niveau,colonnePerso,lignePerso,' ');
			}else place_sur_terrain(niveau,colonnePerso,lignePerso,'.');

			
			if(seraUn=='X'){
				place_sur_terrain(niveau,colonnePerso+1,lignePerso,'+');
			}else place_sur_terrain(niveau,colonnePerso+1,lignePerso,'@');

			if(seraEnsuiteUn=='.'){
				place_sur_terrain(niveau,colonnePerso+2,lignePerso,'X');
				
			}else place_sur_terrain(niveau,colonnePerso+2,lignePerso,'$');
			niveau->perso->colonne++;
		}
	}
	//incremente meme si le joueur fonce dans le mur, je prefere comme ça
	niveau->nb_de_pas++;


}