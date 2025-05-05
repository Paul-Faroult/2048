#include "partie.h"

// Constructeur de la classe Partie.
// d : difficulté du jeu (probablement la taille de la grille)
// c : état de la partie (en cours ou non)
// val : valeur maximale à atteindre (par défaut 2048)
Partie::Partie(int d, bool c, int val) {
    m_grille = new Grille(d, 0); // Crée une nouvelle grille de jeu avec la difficulté spécifiée (taille de la grille).
    m_valMax = val; // Définit la valeur maximale du jeu (par exemple, 2048).
    m_difficulte = d; // Définit la difficulté du jeu (probablement la taille de la grille).
    m_encours = c; // Définit si la partie est en cours ou non.
}

// Constructeur de copie.
// e : une autre instance de Partie dont on veut copier les valeurs.
Partie::Partie(const Partie& e) {
    m_valMax = e.m_valMax; // Copie la valeur maximale du jeu de l'autre instance.
    m_difficulte = e.m_difficulte; // Copie la difficulté de l'autre instance.
    m_encours = e.m_encours; // Copie l'état de la partie (en cours ou non).
    m_grille = new Grille(m_difficulte, 0); // Crée une nouvelle grille avec la difficulté spécifiée.
}

// Destructeur de la classe Partie.
// Il est utilisé pour libérer la mémoire allouée pour l'objet `Grille`.
Partie::~Partie() {
    delete m_grille; // Libère la mémoire allouée pour la grille.
}

// Retourne la valeur maximale à atteindre pour gagner la partie.
int Partie::getvalMax() {
    return m_valMax;
}

// Modifie la valeur maximale à atteindre dans le jeu.
void Partie::setvalMax(int val) {
    m_valMax = val;
}

// Retourne la difficulté actuelle du jeu.
int Partie::getDifficulte() {
    return m_difficulte;
}

// Retourne un booléen qui indique si la partie est en cours ou non.
bool Partie::getEnCours() {
    return m_encours;
}

// Modifie la difficulté du jeu (par exemple, changer la taille de la grille).
void Partie::setDifficulte(int d) {
    m_difficulte = d;
}

// Modifie l'état de la partie : en cours ou non.
void Partie::setEnCours(bool c) {
    m_encours = c;
}

// Retourne un pointeur vers l'objet `Grille`, permettant d'accéder à la grille de jeu.
Grille* Partie::getGrille() {
    return m_grille;
}

// Vérifie si le joueur a gagné la partie.
// Cela se fait en vérifiant si une case de la grille contient la valeur maximale.
bool Partie::testGagne() {
    for (int i = 0; i < m_grille->getTaille(); i++) {
        for (int j = 0; j < m_grille->getTaille(); j++) {
            if (m_grille->getMat()[i][j]->getVal() == m_valMax) {
                return true; // Si une case contient la valeur maximale, le joueur a gagné.
            }
        }
    }
    return false; // Aucun gain trouvé, le jeu continue.
}

// Vérifie si la partie est perdue.
// Une partie est perdue si aucun mouvement n'est possible dans toutes les directions.
bool Partie::perdu() {
    // Vérifie si un mouvement est possible dans les quatre directions.
    if (m_grille->droitePossible() || m_grille->gauchePossible() || m_grille->hautPossible() || m_grille->basPossible()) {
        return false; // Si un mouvement est possible, la partie n'est pas perdue.
    }
    return true; // Aucun mouvement possible, donc la partie est perdue.
}
