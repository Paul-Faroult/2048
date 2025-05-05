#include "grille.h"
#include <stdlib.h>
#include <QDateTime>

// Constructeur de la classe Grille
Grille::Grille(int taille, int score) {
    srand(QDateTime::currentMSecsSinceEpoch() % UINT_MAX); // Initialisation du générateur de nombres aléatoires avec la date actuelle
    m_taille = taille; // Initialisation de la taille de la grille
    m_score = score; // Initialisation du score du jeu
    m_mat = new Case**[taille]; // Allocation dynamique d'un tableau 2D de pointeurs de cases
    for (int i = 0; i < taille; i++) { // Parcours des lignes
        m_mat[i] = new Case*[taille]; // Allocation dynamique pour chaque ligne
        for (int j = 0; j < taille; j++) { // Parcours des colonnes
            m_mat[i][j] = new Case(0, i, j); // Initialisation de chaque case à la valeur 0
        }
    }
}

// Constructeur de recopie pour dupliquer une grille existante
Grille::Grille(const Grille& e) {
    m_taille = e.m_taille; // Copie de la taille de la grille
    m_score = e.m_score; // Copie du score
    m_mat = new Case**[m_taille]; // Allocation dynamique pour la nouvelle grille
    for (int i = 0; i < m_taille; i++) { // Parcours des lignes
        m_mat[i] = new Case*[m_taille]; // Allocation dynamique pour chaque ligne
        for (int j = 0; j < m_taille; j++) { // Parcours des colonnes
            m_mat[i][j] = e.m_mat[i][j]; // Copie des cases de l'ancienne grille
        }
    }
}

// Destructeur pour libérer la mémoire allouée dynamiquement
Grille::~Grille() {
    for (int i = 0; i < m_taille; i++) { // Parcours des lignes
        for (int j = 0; j < m_taille; j++) { // Parcours des colonnes
            delete[] m_mat[i][j]; // Libération de chaque case
        }
        delete[] m_mat[i]; // Libération de chaque ligne
    }
    delete[] m_mat; // Libération de la grille elle-même
}

// Accesseurs et modificateurs pour la taille de la grille
int Grille::getTaille() {
    return m_taille; // Retourne la taille de la grille
}
void Grille::setTaille(int taille) {
    // Libère l'ancienne grille avant de redimensionner
    for (int i = 0; i < m_taille; i++) {
        for (int j = 0; j < m_taille; j++) {
            delete m_mat[i][j]; // Libère les cases
        }
        delete[] m_mat[i]; // Libère chaque ligne
    }
    delete[] m_mat; // Libère la grille

    m_taille = taille; // Mise à jour de la taille
    m_mat = new Case**[taille]; // Allocation d'une nouvelle grille
    for (int i = 0; i < taille; i++) { // Parcours des lignes
        m_mat[i] = new Case*[taille]; // Allocation d'une nouvelle ligne
        for (int j = 0; j < taille; j++) { // Parcours des colonnes
            m_mat[i][j] = new Case(0, i, j); // Initialisation de chaque case à 0
        }
    }
}

// Accesseurs et modificateurs pour le score du jeu
int Grille::getScore() {
    return m_score; // Retourne le score actuel
}
void Grille::setScore(int score) {
    m_score = score; // Met à jour le score
}

// Retourne le tableau de la grille
Case*** Grille::getMat() {
    return m_mat; // Retourne la grille (matrice de cases)
}

// Méthode pour générer une nouvelle case avec une valeur 2 ou 4 à une position vide aléatoire
void Grille::newCase() {
    int nb = 0; // Compteur de cases vides
    int caseVide[m_taille * m_taille]; // Tableau pour stocker les indices des cases vides
    for (int i = 0; i < m_taille; i++) { // Parcours des lignes
        for (int j = 0; j < m_taille; j++) { // Parcours des colonnes
            if (m_mat[i][j]->getVal() == 0) { // Si la case est vide
                caseVide[nb] = i * m_taille + j; // Enregistrer la position de la case vide
                nb++;
            }
        }
    }
    int nouv = rand() % nb; // Choisir une case vide au hasard
    int val = (rand() % 10 == 0) ? 4 : 2; // Déterminer la valeur de la nouvelle case (10% de chance pour 4)
    m_mat[caseVide[nouv] / m_taille][caseVide[nouv] % m_taille]->setVal(val); // Affecter la valeur à la case choisie
}

// Méthodes pour vérifier si un mouvement est possible dans chaque direction
bool Grille::droitePossible() {
    for (int i = 0; i < m_taille; i++) { // Parcours des lignes
        int precedent = -1; // Variable pour suivre la dernière valeur
        for (int j = 0; j < m_taille; j++) { // Parcours des colonnes
            int valeur = m_mat[i][j]->getVal(); // Valeur de la case actuelle
            if (valeur == precedent) { // Si les valeurs sont identiques, un mouvement est possible
                return true;
            }
            else if (valeur != 0) {
                precedent = valeur; // Met à jour la valeur précédente
            }
            else {
                if (precedent != -1) { // Si une case non vide a été rencontrée précédemment
                    return true; // Un mouvement est possible
                }
            }
        }
    }
    return false; // Aucun mouvement possible
}
// Les méthodes gauchePossible(), hautPossible(), basPossible() suivent une logique similaire
bool Grille::gauchePossible(){
    for(int i=0;i<m_taille;i++){
        int precedent = -1;
        for(int j=m_taille-1;j>-1;j--){
            int valeur = m_mat[i][j]->getVal();
            if(valeur == precedent){
                return true;
            }
            else if(valeur != 0){
                precedent = valeur;
            }
            else{
                if(precedent != -1){
                    return true;
                }
            }
        }
    }
    return false;
}
bool Grille::hautPossible(){
    for(int j=0;j<m_taille;j++){
        int precedent = -1;
        for(int i=m_taille-1;i>-1;i--){
            int valeur = m_mat[i][j]->getVal();
            if(valeur == precedent){
                return true;
            }
            else if(valeur != 0){
                precedent = valeur;
            }
            else{
                if(precedent != -1){
                    return true;
                }
            }
        }
    }
    return false;
}
bool Grille::basPossible(){
    for(int j=0;j<m_taille;j++){
        int precedent = -1;
        for(int i=0;i<m_taille;i++){
            int valeur = m_mat[i][j]->getVal();
            if(valeur == precedent){
                return true;
            }
            else if(valeur != 0){
                precedent = valeur;
            }
            else{
                if(precedent != -1){
                    return true;
                }
            }
        }
    }
    return false;
}

// Méthodes pour effectuer les déplacements dans chaque direction
void Grille::droite() {
    for (int i = 0; i < m_taille; i++) { // Parcours des lignes
        int precedent = -1; // Suivi de la dernière valeur rencontrée
        int ccible = -1; // Position de la case cible
        for (int j = m_taille - 1; j > -1; j--) { // Parcours des colonnes de droite à gauche
            int valeur = m_mat[i][j]->getVal(); // Valeur de la case actuelle
            if (valeur == 0) { // Si la case est vide
                if (ccible == -1) { // Si la case cible n'a pas encore été définie
                    ccible = j;
                }
            }
            else { // Si la case n'est pas vide
                if (precedent == -1) { // Si aucune valeur précédente n'a été rencontrée
                    if (ccible == -1) { // Si la case cible n'a pas encore été définie
                        ccible = j;
                    }
                    if (j != ccible) { // Si la case n'est pas déjà à la position cible
                        m_mat[i][j]->setVal(0); // Déplacer la valeur vers la droite
                    }
                    m_mat[i][ccible]->setVal(valeur); // Mettre la valeur à la position cible
                    precedent = valeur; // Mettre à jour la valeur précédente
                }
                else if (precedent == valeur) { // Si les valeurs sont égales, fusionner les cases
                    fusion(m_mat[i][ccible], m_mat[i][j]);
                    precedent = -1; // Réinitialiser la valeur précédente
                    ccible -= 1; // Déplacer la case cible vers la gauche
                }
                else { // Si les valeurs sont différentes
                    precedent = valeur; // Mettre à jour la valeur précédente
                    if (j != ccible - 1) { // Si la case n'est pas déjà à la bonne position
                        m_mat[i][j]->setVal(0); // Déplacer la valeur vers la droite
                    }
                    m_mat[i][ccible - 1]->setVal(valeur); // Placer la valeur à la nouvelle position
                    ccible -= 1; // Mettre à jour la position de la case cible
                }
            }
        }
    }
}

// Les méthodes gauche(), haut(), bas() suivent une logique similaire
void Grille::gauche(){
    for(int i=0;i<m_taille;i++){
        int precedent = -1;
        int ccible = -1;
        for(int j=0;j<m_taille;j++){
            int valeur = m_mat[i][j]->getVal();
            if(valeur ==0){
                if(ccible == -1){
                    ccible = j;
                }
            }
            else{
                if(precedent ==-1){
                    if(ccible == -1){
                        ccible = j;
                    }

                    if(j != ccible){
                        m_mat[i][j]->setVal(0);
                    }
                    m_mat[i][ccible]->setVal(valeur);
                    precedent = valeur;
                }
                else if(precedent == valeur){
                    fusion(m_mat[i][ccible], m_mat[i][j]);
                    precedent = -1;
                    ccible += 1;
                }
                else{
                    precedent = valeur;
                    if(j != ccible+1){
                        m_mat[i][j]->setVal(0);
                    }
                    m_mat[i][ccible+1]->setVal(valeur);
                    ccible += 1;
                }
            }
        }
    }
}
void Grille::haut(){
    for(int j=0;j<m_taille;j++){
        int precedent = -1;
        int ccible = -1;
        for(int i=0;i<m_taille;i++){
            int valeur = m_mat[i][j]->getVal();
            if(valeur ==0){
                if(ccible == -1){
                    ccible = i;
                }
            }
            else{
                if(precedent ==-1){
                    if(ccible == -1){
                        ccible = i;
                    }

                    if(i != ccible){
                        m_mat[i][j]->setVal(0);
                    }
                    m_mat[ccible][j]->setVal(valeur);
                    precedent = valeur;
                }
                else if(precedent == valeur){
                    fusion(m_mat[ccible][j], m_mat[i][j]);
                    precedent = -1;
                    ccible += 1;
                }
                else{
                    precedent = valeur;
                    if(i != ccible+1){
                        m_mat[i][j]->setVal(0);
                    }
                    m_mat[ccible+1][j]->setVal(valeur);
                    ccible += 1;
                }
            }
        }
    }
}
void Grille::bas(){
    for(int j=0;j<m_taille;j++){
        int precedent = -1;
        int ccible = -1;
        for(int i=m_taille-1;i>-1;i--){
            int valeur = m_mat[i][j]->getVal();
            if(valeur ==0){
                if(ccible == -1){
                    ccible = i;
                }
            }
            else{
                if(precedent ==-1){
                    if(ccible == -1){
                        ccible = i;
                    }

                    if(i != ccible){
                        m_mat[i][j]->setVal(0);
                    }
                    m_mat[ccible][j]->setVal(valeur);
                    precedent = valeur;
                }
                else if(precedent == valeur){
                    fusion(m_mat[ccible][j], m_mat[i][j]);
                    precedent = -1;
                    ccible -= 1;
                }
                else{
                    precedent = valeur;
                    if(i != ccible-1){
                        m_mat[i][j]->setVal(0);
                    }
                    m_mat[ccible-1][j]->setVal(valeur);
                    ccible -= 1;
                }
            }
        }
    }
}
// Méthode pour fusionner deux cases ayant la même valeur
void Grille::fusion(Case* cible, Case* prec) {
    cible->setVal(cible->getVal() * 2); // Doubler la valeur de la case cible
    prec->setVal(0); // Réinitialiser la valeur de la case précédente
    m_score = m_score + cible->getVal(); // Ajouter la valeur fusionnée au score
}
