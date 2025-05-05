#ifndef CASE_H
#define CASE_H

// Définition de la classe Case qui représente une case de la grille de jeu
class Case
{
private:
    int m_val; // Valeur stockée dans la case (par exemple, 0, 2, 4, etc.)
    int m_x;   // Position de la case sur l'axe des abscisses (x)
    int m_y;   // Position de la case sur l'axe des ordonnées (y)

public:
    // Constructeur de la classe Case
    Case(int val, int x, int y);

    // Accesseur pour obtenir la valeur de la case
    int getVal();

    // Accesseur pour obtenir la position de la case sur l'axe des abscisses (x)
    int getx();

    // Accesseur pour obtenir la position de la case sur l'axe des ordonnées (y)
    int gety();

    // Modificateur pour définir la valeur de la case
    void setVal(int val);

    // Modificateur pour définir la position de la case sur l'axe des abscisses (x)
    void setx(int x);

    // Modificateur pour définir la position de la case sur l'axe des ordonnées (y)
    void sety(int y);
};

#endif // CASE_H
