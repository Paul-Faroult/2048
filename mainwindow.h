#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <vector>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "partie.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Partie* partie; // Objet Partie qui gère la logique du jeu
    int scoreMax; // Stocke le score maximal atteint
    QPushButton* facileButton; // Bouton pour la difficulté 4x4
    QPushButton* moyenneButton; // Bouton pour la difficulté 6x6
    QPushButton* difficileButton; // Bouton pour la difficulté 8x8
    QVBoxLayout *mainLayout; // Disposition verticale pour la fenêtre principale
    QGridLayout *gridLayout; // Disposition en grille pour la grille de jeu
    QLabel *currentScoreLabel; // Label pour afficher le score actuel
    QLabel *highScoreValueLabel; // Label pour afficher le score maximal
    std::vector<std::vector<int>> grid; // Grille de jeu en 2D
    std::vector<std::vector<QPushButton*>> buttons; // Boutons associés à chaque case de la grille

public:
    // Constructeur de la classe MainWindow
    // Initialise les composants de la fenêtre, les boutons, les labels et l'objet Partie.
    MainWindow(QWidget *parent = nullptr);

    // Destructeur de la classe MainWindow
    // Libère la mémoire allouée pour les boutons et l'objet Partie.
    ~MainWindow();

    // Initialise la grille de jeu et les boutons associés.
    // Remplit la grille avec des valeurs par défaut et l'affiche.
    void init();

    // Efface et réinitialise la grille de jeu avec une taille donnée.
    // Taille : nouvelle taille de la grille (ex : 4x4, 6x6, etc.)
    void clearGrid(int taille);

    // Change la difficulté du jeu et réinitialise la grille en fonction de la nouvelle taille.
    // Taille : nouvelle taille de la grille (ex : 4x4, 6x6, etc.)
    void changerDifficulte(int taille);

    // Met à jour l'affichage de la grille et du score sur l'interface.
    void afficher();

    // Gère les événements de touche. Selon la touche pressée (haut, bas, gauche, droite),
    // effectue un mouvement sur la grille de jeu.
    // event : l'événement de la touche pressée.
    void keyPressEvent(QKeyEvent *event);

    // Redémarre la partie en réinitialisant la grille et le score.
    void restart();
};

#endif // MAINWINDOW_H
