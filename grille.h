#ifndef GRILLE_H
#define GRILLE_H
#include "case.h"

class Grille
{
private:
    int m_taille; // Taille de la grille (ex. 4x4 pour un jeu de type 2048)
    int m_score; // Score actuel du joueur
    Case*** m_mat; // Tableau à 2 dimensions de cases représentant la grille de jeu (pointeur sur un tableau de pointeurs vers des objets `Case`)

public:
    Grille(int taille, int score); // Constructeur
    Grille(const Grille& e); // Constructeur de copie
    ~Grille(); // Destructeur

    int getTaille(); // Retourne la taille de la grille
    void setTaille(int taille); // Modifie la taille de la grille
    int getScore(); // Retourne le score actuel
    void setScore(int score); // Modifie le score actuel

    Case*** getMat(); // Retourne le tableau de cases
    void newCase(); // Crée une nouvelle case à un emplacement vide sur la grille
    bool droitePossible(); // Vérifie si un mouvement vers la droite est possible
    bool gauchePossible(); // Vérifie si un mouvement vers la gauche est possible
    bool hautPossible(); // Vérifie si un mouvement vers le haut est possible
    bool basPossible(); // Vérifie si un mouvement vers le bas est possible

    void droite(); // Déplace toutes les cases vers la droite
    void gauche(); // Déplace toutes les cases vers la gauche
    void haut(); // Déplace toutes les cases vers le haut
    void bas(); // Déplace toutes les cases vers le bas

    void fusion(Case* cible, Case* prec); // Fusionne deux cases adjacentes si elles ont la même valeur
};

#endif // GRILLE_H
