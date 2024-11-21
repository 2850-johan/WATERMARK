#include <opencv2/opencv.hpp> //Permet d'accéder à toutes les fonctionnalités principakes d'OpenCV y compris la manipulation d'images
#include <iostream>//Import de la bibliothèque iostream nécessaire pour les entrées /sorties standard comme l'affichage avec std:cout
using namespace cv;
using namespace std;



Mat  lsbreplace(Mat& imagehideuc ,Mat&imagehidein) {


//Cibler la dernière colonne,la colonne des lsb de l'image hôte
Mat lsbcol=imagehidein.col(imagehidein.cols-1);


//Créer une matrice qui servira pour le stockage de la dernière colonne de l'image 
Mat matricelsb=Mat::zeros(lsbcol.rows,1,CV_8UC1);


//Cette boucle permet en fait d'insérer les valeurs de la colonne unique des lsb dans la matricelsb
for (int i=0;i<lsbcol.rows;i++) {
	uchar valeur=lsbcol.at<uchar>(i,0);
	matricelsb.at<uchar>(i,0)=valeur



};

//Ici on vérifie si le nombre de lignes de la matrice à colonne
//unique de l'image à cacher est supérieur ou pas à celle de matricelsb
//Si oui on effectue le remplacement de la partie correspondante à la taille de 
//imagehideuc dans matricels
 if (imagehideuc.rows > matricelsb.rows) {
        cout << "Erreur : La colonne unique de l'image à cacher est trop grande pour remplacer une portion de la matrice LSB." << endl;
       return Mat();
    }
else {


           for (int i=0;i<imagehideuc.rows;++i) {

 		matricelsb.at<uchar>(i,0)=imagehideuc.at<uchar>(i,0)


 	};

} ;	
// Remplacement de la colonne des lsb de l'image hôte par matricelsb qui contient l'image cachée



 if (imagehidein.rows == matricelsb.rows)


 {
 	
 	matricelsb.copyTo(imagehidein.col(imagehidein.cols - 1));

 };

else {
	cout<<"Les matrices n\'ont pas le même nombre de ligne"<<endl;
};


return imagehidein;
};
