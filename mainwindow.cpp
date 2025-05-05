#include "mainwindow.h"
#include "partie.h"
#include <QVBoxLayout>
#include <QMessageBox>


// Constructeur de la fenêtre principale, appelé lors de la création de la fenêtre
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    partie = new Partie(4,true); // Crée une nouvelle partie avec une grille de 4x4 et le mode activé
    scoreMax=0;  // Initialise le score maximum à 0
    setFocusPolicy(Qt::StrongFocus);  // Permet de donner le focus à la fenêtre
    // Créer un widget central pour contenir tout le contenu de la fenêtre
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Créer un layout principal vertical pour organiser les widgets
    QVBoxLayout *mainLayout = new QVBoxLayout();
    centralWidget->setLayout(mainLayout);

    // ---- Titre et Score ----
    QHBoxLayout *headerLayout = new QHBoxLayout(); // Layout horizontal pour le titre et les scores

    // Titre
    QLabel *titleLabel = new QLabel("2048");
    titleLabel->setStyleSheet("font: bold 40px; color: #776e65;");
    headerLayout->addWidget(titleLabel);  // Ajouter le titre au layout

    // Score actuel
    QVBoxLayout *scoreLayout = new QVBoxLayout();
    QLabel *scoreLabel = new QLabel("SCORE");
    scoreLabel->setStyleSheet("font: bold 16px; color: #776e65;");
    currentScoreLabel = new QLabel("0");
    currentScoreLabel->setStyleSheet("font: bold 20px; color: #776e65;");
    scoreLayout->addWidget(scoreLabel);  // Ajouter l'étiquette "SCORE"
    scoreLayout->addWidget(currentScoreLabel);  // Ajouter le score actuel
    headerLayout->addLayout(scoreLayout);

    // High Score
    QVBoxLayout *highScoreLayout = new QVBoxLayout();
    QLabel *highScoreLabel = new QLabel("HIGH SCORE");
    highScoreLabel->setStyleSheet("font: bold 16px; color: #776e65;");
    highScoreValueLabel = new QLabel("0");
    highScoreValueLabel->setStyleSheet("font: bold 20px; color: #776e65;");
    highScoreLayout->addWidget(highScoreLabel);  // Ajouter l'étiquette "HIGH SCORE"
    highScoreLayout->addWidget(highScoreValueLabel);  // Ajouter le score maximum
    headerLayout->addLayout(highScoreLayout);

    mainLayout->addLayout(headerLayout);

    // ---- Boutons de contrôle ----
    QHBoxLayout *controlLayout = new QHBoxLayout(); // Layout horizontal pour les boutons de contrôle

    // Bouton Recommencer
    QPushButton *restartButton = new QPushButton("Recommencer");
    restartButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    restartButton->setStyleSheet("font: bold 16px; background: #8f7a66; color: #f9f6f2; border-radius: 5px; padding: 8px;");
    connect(restartButton, &QPushButton::clicked, this, &MainWindow::restart);  // Connecte l'action du bouton à la méthode 'restart'
    controlLayout->addWidget(restartButton);

    // Boutons de difficulté
    facileButton = new QPushButton("4x4", this);
    facileButton->setStyleSheet("font: bold 16px; background: #ffe0a0; color: #f9f6f2; border-radius: 5px; padding: 8px;");
    facileButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    connect(facileButton, &QPushButton::clicked, this, [this]() { changerDifficulte(4); });  // Change la difficulté à 4x4
    controlLayout->addWidget(facileButton);

    moyenneButton = new QPushButton("6x6", this);
    moyenneButton->setStyleSheet("font: bold 16px; background: #ffb65c; color: #f9f6f2; border-radius: 5px; padding: 8px;");
    moyenneButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    connect(moyenneButton, &QPushButton::clicked, this, [this]() { changerDifficulte(6); });  // Change la difficulté à 6x6
    controlLayout->addWidget(moyenneButton);

    difficileButton = new QPushButton("8x8", this);
    difficileButton->setStyleSheet("font: bold 16px; background: #ff654c; color: #f9f6f2; border-radius: 5px; padding: 8px;");
    difficileButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    connect(difficileButton, &QPushButton::clicked, this, [this]() { changerDifficulte(8); });  // Change la difficulté à 8x8
    controlLayout->addWidget(difficileButton);

    mainLayout->addLayout(controlLayout);

    // ---- Grille principale ----
    gridLayout = new QGridLayout();
    grid.resize(partie->getDifficulte(), std::vector<int>(partie->getDifficulte(), 0));  // Redimensionne la grille en fonction de la difficulté
    buttons.resize(partie->getDifficulte(), std::vector<QPushButton*>(partie->getDifficulte(), nullptr));  // Crée un tableau de boutons
    gridLayout->setSpacing(10);  // Espacement entre les tuiles
    gridLayout->setAlignment(Qt::AlignCenter);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addLayout(gridLayout);

    // Initialisation de la grille
    init();  // Initialiser la grille

    // Taille fixe de la fenêtre
    setFixedSize(sizeHint());
}
// Destructeur : nettoie les ressources allouées
MainWindow::~MainWindow(){
    delete facileButton;
    delete moyenneButton;
    delete difficileButton;
    delete currentScoreLabel;
    delete highScoreValueLabel;
    delete partie;
}

// Fonction pour réinitialiser la grille avec une nouvelle taille
void MainWindow::clearGrid(int taille){
    delete partie;  // Supprime l'ancienne partie
    partie = new Partie(taille, true);  // Crée une nouvelle partie avec la taille spécifiée
    init();  // Réinitialiser la grille
}

// Fonction pour initialiser la grille
void MainWindow::init(){
    int d = partie->getDifficulte();  // Récupère la taille de la grille

    // Redimensionner la grille et les boutons
    buttons.clear();
    grid.clear();
    grid.resize(d, std::vector<int>(d, 0));
    buttons.resize(d, std::vector<QPushButton*>(d, nullptr));

    // Supprimer les widgets existants dans le layout
    while(gridLayout->count()) {
        QWidget* widget = gridLayout->itemAt(0)->widget();
        if( widget ) {
            gridLayout->removeWidget(widget);
            delete widget;
        }
    }

    // Créer de nouveaux boutons pour chaque case de la grille
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < d; ++j) {
            buttons[i][j] = new QPushButton(" ");
            buttons[i][j]->setFixedSize(600/d, 600/d);  // Taille des boutons
            buttons[i][j]->setFocusPolicy(Qt::FocusPolicy::NoFocus);
            gridLayout->addWidget(buttons[i][j], i, j);  // Ajouter chaque bouton à la grille
            partie->getGrille()->getMat()[i][j]->setVal(0);  // Initialiser la valeur de la case à 0
        }
    }

    // Initialiser la grille avec un score de 0 et ajouter deux cases
    partie->getGrille()->setScore(0);
    partie->getGrille()->newCase();
    partie->getGrille()->newCase();

    afficher();  // Afficher la grille avec les valeurs initiales
}


// Fonction pour changer la difficulté du jeu
void MainWindow::changerDifficulte(int taille){
    clearGrid(taille);  // Réinitialise la grille avec la nouvelle taille
    init();  // Réinitialiser la grille après avoir changé la taille
}

// Fonction pour recommencer la partie
void MainWindow::restart(){
    partie->setEnCours(true);  // Indiquer que la partie est en cours
    int d = partie->getDifficulte();
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < d; ++j) {
            partie->getGrille()->getMat()[i][j]->setVal(0);  // Réinitialiser toutes les cases
        }
    }
    partie->getGrille()->setScore(0);  // Réinitialiser le score
    partie->getGrille()->newCase();  // Ajouter deux nouvelles cases
    partie->getGrille()->newCase();
    afficher();  // Afficher la grille mise à jour
}
// Fonction pour afficher la grille et les scores
void MainWindow::afficher(){
    int d = partie->getDifficulte();
    for(int i=0;i<d;i++){
        for(int j=0;j<d;j++){
            QString style = QString("font-size: %1px; border: 0px;").arg(280/d);
            if(partie->getGrille()->getMat()[i][j]->getVal() == 0){
                buttons[i][j]->setText("");
                buttons[i][j]->setStyleSheet("background-color: lightgray;" "border: 0px");
            }
            else if(partie->getGrille()->getMat()[i][j]->getVal() == 2){
                buttons[i][j]->setText(QString::number(partie->getGrille()->getMat()[i][j]->getVal()));
                buttons[i][j]->setStyleSheet(style + "background-color: white;");
            }
            else if(partie->getGrille()->getMat()[i][j]->getVal() == 4){
                buttons[i][j]->setText(QString::number(partie->getGrille()->getMat()[i][j]->getVal()));
                buttons[i][j]->setStyleSheet(style + "background-color: #fdf4d1;");
            }
            else if(partie->getGrille()->getMat()[i][j]->getVal() == 8){
                buttons[i][j]->setText(QString::number(partie->getGrille()->getMat()[i][j]->getVal()));
                buttons[i][j]->setStyleSheet(style + "background-color: #ffc96a;");
            }
            else if(partie->getGrille()->getMat()[i][j]->getVal() == 16){
                buttons[i][j]->setText(QString::number(partie->getGrille()->getMat()[i][j]->getVal()));
                buttons[i][j]->setStyleSheet(style + "background-color: #ffaf69;");
            }
            else if(partie->getGrille()->getMat()[i][j]->getVal() == 32){
                buttons[i][j]->setText(QString::number(partie->getGrille()->getMat()[i][j]->getVal()));
                buttons[i][j]->setStyleSheet(style + "background-color: #ff8e1d;");
            }
            else if(partie->getGrille()->getMat()[i][j]->getVal() == 64){
                buttons[i][j]->setText(QString::number(partie->getGrille()->getMat()[i][j]->getVal()));
                buttons[i][j]->setStyleSheet(style + "background-color: #ff6e25;");
            }
            else if(partie->getGrille()->getMat()[i][j]->getVal() == 128){
                buttons[i][j]->setText(QString::number(partie->getGrille()->getMat()[i][j]->getVal()));
                buttons[i][j]->setStyleSheet(style + "background-color: #ffe061;");
            }
            else if(partie->getGrille()->getMat()[i][j]->getVal() == 256){
                buttons[i][j]->setText(QString::number(partie->getGrille()->getMat()[i][j]->getVal()));
                buttons[i][j]->setStyleSheet(style + "background-color: #ffd426;");
            }
            else{
                buttons[i][j]->setText(QString::number(partie->getGrille()->getMat()[i][j]->getVal()));
                buttons[i][j]->setStyleSheet(style + "background-color: #f9c802;");
            }
        }
    }
    // Mettre à jour les scores
    if(partie->getGrille()->getScore()>scoreMax){
        scoreMax=partie->getGrille()->getScore();  // Mettre à jour le score maximum
        highScoreValueLabel->setText(QString::number(scoreMax));  // Afficher le nouveau score maximum
    }
    currentScoreLabel->setText(QString::number(partie->getGrille()->getScore()));  // Afficher le score actuel
    currentScoreLabel->update();
}

// Fonction pour gérer les pressions de touches pour déplacer les cases
void MainWindow::keyPressEvent(QKeyEvent * event){
    if(!partie->getEnCours()) return;// Si la partie n'est pas en cours, rien ne se passe

    // Gestion des touches pour déplacer les cases (haut, bas, gauche, droite)
    if (event->key() == Qt::Key_Up && partie->getGrille()->hautPossible()){
        partie->getGrille()->haut();// Déplacer les cases vers le haut
        partie->getGrille()->newCase();// Ajouter une nouvelle case
        afficher();// Afficher la grille mise à jour
    }
    // Similaire pour les autres directions
    else if (event->key() == Qt::Key_Left && partie->getGrille()->gauchePossible()){
        partie->getGrille()->gauche();
        partie->getGrille()->newCase();
        afficher();
    }
    else if (event->key() == Qt::Key_Right && partie->getGrille()->droitePossible()){
        partie->getGrille()->droite();
        partie->getGrille()->newCase();
        afficher();
    }
    else if (event->key() == Qt::Key_Down && partie->getGrille()->basPossible()){
        partie->getGrille()->bas();
        partie->getGrille()->newCase();
        afficher();
    }
    // Vérifier si le joueur a gagné ou perdu
    if(partie->testGagne()){
        QMainWindow::setStyleSheet("QMessageBox { background-color: #f4f4f4; font-size: 14px; color: #333; border-radius: 10px; }");
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Gagné", "Voulez-vous continuer ?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if(reply==QMessageBox::No){
            partie->setEnCours(false);  // Fin de la partie
        }
        else{
            partie->setvalMax(partie->getvalMax()*2);  // Doubler la valeur maximale
        }
    }
    if(partie->perdu()){
        // Message de fin de jeu si le joueur a perdu
        QMainWindow::setStyleSheet("QMessageBox { background-color: #f4f4f4; font-size: 14px; color: #333; border-radius: 10px; }");
        QMessageBox::StandardButton fin = QMessageBox::information(this, "Perdu", "Voulez-vous rejouer ?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(fin==QMessageBox::No){
            partie->setEnCours(false);  // Fin de la partie
        }
        else{
            highScoreValueLabel->setText(QString::number(partie->getGrille()->getScore()));  // Mettre à jour le score
            partie->setvalMax(2048);  // Réinitialiser la valeur maximale
            restart();  // Recommencer la partie
        }
    }
}
