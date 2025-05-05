#include "case.h"

// Constructeur de la classe Case
// Initialise une case avec une valeur (val) et des coordonnées (x, y)
Case::Case(int val, int x, int y){
    m_val = val;  // Initialisation de la valeur de la case
    m_x = x;      // Initialisation de la position x de la case
    m_y = y;      // Initialisation de la position y de la case
}

// Méthode d'accès pour obtenir la valeur de la case
// Retourne la valeur de la case
int Case::getVal(){
    return m_val;
}

// Méthode d'accès pour obtenir la position x de la case
// Retourne la position x de la case
int Case::getx(){
    return m_x;
}

// Méthode d'accès pour obtenir la position y de la case
// Retourne la position y de la case
int Case::gety(){
    return m_y;
}

// Méthode de modification pour définir la valeur de la case
// Modifie la valeur de la case
void Case::setVal(int val){
    m_val = val;
}

// Méthode de modification pour définir la position x de la case
// Modifie la position x de la case
void Case::setx(int x){
    m_x = x;
}

// Méthode de modification pour définir la position y de la case
// Modifie la position y de la case
void Case::sety(int y){
    m_y = y;
}
