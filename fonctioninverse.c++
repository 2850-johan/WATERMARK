#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

// Fonction pour reconstruire une image à partir d'une liste 1 colonne
cv::Mat reconstruireImage(const std::vector<int>& pixelValues, int width, int height) {
    if (pixelValues.size() != width * height * 3) {
        std::cerr << "Erreur : Taille invalide du tableau de pixels." << std::endl;
        return cv::Mat(); // Retourner une image vide en cas d'erreur
    }

    // Création des trois canaux B, G, R à partir des valeurs
    cv::Mat blueChannel(height, width, CV_8UC1);  // Canal Bleu
    cv::Mat greenChannel(height, width, CV_8UC1); // Canal Vert
    cv::Mat redChannel(height, width, CV_8UC1);   // Canal Rouge

    // Remplissage des canaux avec les valeurs des pixels
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = (i * width + j) * 3; // Calcul de l'index de base pour (i, j)
            blueChannel.at<uchar>(i, j) = static_cast<uchar>(pixelValues[index]);
            greenChannel.at<uchar>(i, j) = static_cast<uchar>(pixelValues[index + 1]);
            redChannel.at<uchar>(i, j) = static_cast<uchar>(pixelValues[index + 2]);
        }
    }

    // Combiner les trois canaux pour reconstruire l'image couleur
    cv::Mat reconstitutedImage;
    cv::merge({blueChannel, greenChannel, redChannel}, reconstitutedImage);
    return reconstitutedImage;
}

int main() {
    // Exemple : Imaginons qu'on reçoive un tableau ou une liste 1 colonne
    cv::Mat image = cv::imread("IMAGE BMP.jpg"); // Charger une image pour l'exemple
    if (image.empty()) {
        std::cerr << "Erreur : Impossible de charger l'image." << std::endl;
        return -1;
    }

    // Diviser l'image en ses trois canaux B, G, R
    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    // Transformer chaque canal en une matrice colonne
    cv::Mat blue_column = channels[0].reshape(1, channels[0].rows * channels[0].cols);
    cv::Mat green_column = channels[1].reshape(1, channels[1].rows * channels[1].cols);
    cv::Mat red_column = channels[2].reshape(1, channels[2].rows * channels[2].cols);

    // Combiner les trois colonnes en une seule
    cv::Mat colonneUnique;
    cv::vconcat(blue_column, green_column, colonneUnique);
    cv::vconcat(colonneUnique, red_column, colonneUnique);

    // *** Conversion : Si une liste/colonne est fournie ***
    std::vector<int> pixelValues;
    colonneUnique.reshape(1, 1).copyTo(pixelValues); // Conversion en vecteur 1D

    // Exemple d'entrée utilisateur : "Une seule colonne avec n lignes"
    // Vous pourriez remplacer pixelValues par un tableau ou une liste utilisateur ici.
    // Exemple de liste d'entrée d'une seule colonne donnée en entrée :
    // pixelValues = {valeurs reçues depuis une autre source}

    // Reconstruire l'image
    cv::Mat reconstitutedImage = reconstruireImage(pixelValues, image.cols, image.rows);
    if (!reconstitutedImage.empty()) {
        cv::imshow("Image Reconstituée", reconstitutedImage); // Afficher l'image reconstruite
        cv::waitKey(0); // Attendre une entrée utilisateur avant de fermer
    }

    return 0;
}
