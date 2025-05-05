#ifndef PARTIE_H
#define PARTIE_H

#include "grille.h"
#include <QKeyEvent>
#include <QPainter>

class Partie
{
private:
    Grille* m_grille; // Pointeur vers un objet Grille qui gère l'état de la grille de jeu
    int m_difficulte; // Stocke la difficulté du jeu (par exemple, taille de la grille)
    bool m_encours; // Indicateur qui détermine si la partie est en cours ou non
    int m_valMax; // Valeur maximale du jeu (par exemple, 2048)

public:
    // Constructeur de la classe Partie.
    // d : difficulté du jeu, c : état de la partie (en cours ou non), val : valeur maximale à atteindre.
    Partie(int d, bool c, int val=2048);

    // Constructeur de copie, utilisé pour créer une nouvelle instance de Partie avec les mêmes valeurs qu'une autre.
    Partie(const Partie& e);

    // Destructeur, qui nettoie les ressources allouées dynamiquement.
    ~Partie();

    // Retourne la valeur maximale du jeu (par défaut 2048).
    int getvalMax();

    // Définit la valeur maximale du jeu (par exemple, pour un mode de jeu avec une autre valeur).
    void setvalMax(int val);

    // Retourne la difficulté actuelle du jeu.
    int getDifficulte();

    // Retourne un booléen qui indique si la partie est encore en cours.
    bool getEnCours();

    // Définit la difficulté du jeu.
    void setDifficulte(int d);

    // Modifie l'état de la partie (en cours ou non).
    void setEnCours(bool c);

    // Retourne un pointeur vers l'objet Grille qui gère l'état du jeu.
    Grille* getGrille();

    // Teste si le joueur a gagné (a atteint la valeur maximale).
    bool testGagne();

    // Teste si la partie est perdue (aucun mouvement possible).
    bool perdu();

#endif // PARTIE_H
