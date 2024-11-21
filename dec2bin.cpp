#include <iostream>
using namespace std;

// Fonction pour convertir un nombre décimal en binaire

void decimalToBinary(int arr [nbre_lignes][1]) 
{
     /*int size = 4;*/ // Taille du tableau

    int array_binary[nbre_lignes][8]; // Tableau pour stocker le résultat binaire.

        for (int i =0; i< nbre_lignes; i++)
        {
            int index = 7 ; // etant donné on commence à 0 donc {0,1,2,3,4,5,6,7}
            int num = arr[i][0]; // on initialise la premiere valeur du tableau pris en paramètre.

            while (num > 0)
            {
                array_binary [i][index] = num % 2 ;
                num /= 2;
                index --; 
            }

        }
        // affichage

        for (int i = 0; i < nbre_lignes; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << array_binary[i][j] ;
            }
            cout << endl ;
        }

            /*// Conversion de chaque valeur décimale en binaire
            for (int i = 0; i < nbre_lignes; i++) {
                int num = arr[i][0]; // Nombre actuel à convertir
                int index = 0;

                // Conversion en binaire
                while (num > 0) {
                    array_binary[index] = num % 2; // Récupérer le bit de poids faible
                    num /= 2;                      // Diviser par 2
                    index++;
                }


                // Affichage du résultat en ordre inverse
                //cout << "Valeur " << arr[i] << " en binaire : ";
                for (int j = index - 1; j >= 0; j--) {
                    cout << array_binary[i][j];
                }
                cout << endl;*/
    
}



/*int main() 
{
    int nbre_lignes= 4
    int 
     decimalToBinary(arr);
    return 0;
}*/
