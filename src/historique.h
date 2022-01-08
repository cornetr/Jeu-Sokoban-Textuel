
niveau_t* copie_du_niveau (niveau_t* niveau);
historique_t* new_historique(int size);
void liberation_hist(historique_t* hist);
void sauvegarde_un_coup (historique_t* hist, niveau_t* niveau);
niveau_t* coup_precedent (historique_t* hist);
void affichage_hist(historique_t* hist, int niveau_precedent);
