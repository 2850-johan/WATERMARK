#include <opencv2/opencv.hpp>  // Inclusion de la bibliothèque OpenCV
#include <iostream>            // Inclusion de la bibliothèque pour les entrées/sorties standard
#include <vector>              // Pour utiliser std::vector

int main() {
    // Charger l'image couleur d'origine
    cv::Mat image = cv::imread("IMAGE BMP.jpg"); // "image.jpg" est le fichier d'entrée
    if (image.empty()) {                     // Vérification si l'image a été chargée
        std::cerr << "Erreur : Impossible de charger l'image." << std::endl;
        return -1;                           // Si l'image ne peut être chargée, afficher un message d'erreur
    }

    // Diviser l'image en trois canaux (B, G, R)
    std::vector<cv::Mat> channels;           // Déclarer un vecteur pour stocker les trois canaux
    cv::split(image, channels);              // Diviser l'image en canaux B, G, R (dans cet ordre)

    // Vérifier que l'image a bien trois canaux
    if (channels.size() != 3) {
        std::cerr << "Erreur : L'image n'est pas au format BGR." << std::endl;
        return -1;
    }

    // Convertir les pixels de chaque canal en colonnes de valeurs décimales
    std::vector<int> blue_column, green_column, red_column; // Vecteurs pour stocker les valeurs décimales

    // Parcourir chaque pixel pour extraire les valeurs décimales de chaque canal
    for (int row = 0; row < image.rows; row++) {
        for (int col = 0; col < image.cols; col++) {
            // Extraire la valeur du pixel pour chaque canal
            int blue = channels[0].at<uchar>(row, col);  // Canal Bleu
            int green = channels[1].at<uchar>(row, col); // Canal Vert
            int red = channels[2].at<uchar>(row, col);   // Canal Rouge

            // Ajouter chaque valeur à la colonne correspondante
            blue_column.push_back(blue);
            green_column.push_back(green);
            red_column.push_back(red);
        }
    }

    // Affichage des premières valeurs de chaque canal pour vérification
    std::cout << "Premières valeurs décimales du canal Bleu : ";
    for (int i = 0; i < std::min(10, (int)blue_column.size()); i++) {
        std::cout << blue_column[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Premières valeurs décimales du canal Vert : ";
    for (int i = 0; i < std::min(10, (int)green_column.size()); i++) {
        std::cout << green_column[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Premières valeurs décimales du canal Rouge : ";
    for (int i = 0; i < std::min(10, (int)red_column.size()); i++) {
        std::cout << red_column[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

    