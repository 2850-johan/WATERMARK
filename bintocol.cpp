#include <opencv2/opencv.hpp> //Permet d'accéder à toutes les fonctionnalités principakes d'OpenCV y compris la manipulation d'images
#include <iostream>//Import de la bibliothèque iostream nécessaire pour les entrées /sorties standard comme l'affichage avec std:cout
using namespace cv;
using namespace std;

Mat bintocol (const Mat& tableauBinaire){ 
 


    // Transformer la matrice en une seule colonne avec reshape(1,...)


    Mat colonneUnique = tableauBinaire.reshape(1, tableauBinaire.rows * tableauBinaire.cols);
    

    //L'argument 1 signifie que chaque ligne de l'ancienne matrice sera transformée en une seule colonne
    // Afficher la matrice colonne unique


    
    cout << "Colonne unique (affichée ligne par ligne) : " <<endl;
    for (int i = 0; i < colonneUnique.rows; i++) {
        cout << (int)colonneUnique.at<uchar>(i, 0) << endl; 


cout << "La matrice à colonne unique a " <<colonneUnique.rows <<" lignes "<< et <<colonneUnique.cols<<" colonnes"<<endl;
    //int sert à convertir la valeur pour pas que la valeur ne s'affiche pas en caractère ASCII
    //est un uchar en entier(int) avant de l'afficher ligne par ligne


    // return colonneUnique
    //Afficher la matrice transformée



    };
};