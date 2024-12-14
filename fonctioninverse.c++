#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

// Fonction pour reconstruire une image à partir d'une liste 1 colonne
cv::Mat reconstruireImage(const std::vector<int>& pixelValues, int width, int height) {
    if (pixelValues.size() != width * height * 3) {
        std::cerr << "Erreur : Taille invalide du tableau de pixels." << std::endl;
        return cv::Mat(); // Retourner une image vide en cas d'erreur
    }

    // Transformer le vecteur pixelValues en une matrice colonne unique
    cv::Mat colonneUnique(static_cast<int>(pixelValues.size()), 1, CV_8UC1);
    for (size_t i = 0; i < pixelValues.size(); i++) {
        colonneUnique.at<uchar>(i, 0) = static_cast<uchar>(pixelValues[i]);
    }

    // Découper la matrice colonne en trois canaux
    int totalPixels = width * height;
    cv::Mat blueColumn = colonneUnique.rowRange(0, totalPixels);
    cv::Mat greenColumn = colonneUnique.rowRange(totalPixels, 2 * totalPixels);
    cv::Mat redColumn = colonneUnique.rowRange(2 * totalPixels, 3 * totalPixels);

    // Reformater chaque canal en matrice 2D
    cv::Mat blueChannel = blueColumn.reshape(1, height);
    cv::Mat greenChannel = greenColumn.reshape(1, height);
    cv::Mat redChannel = redColumn.reshape(1, height);

    // Combiner les trois canaux pour reconstruire l'image couleur
    cv::Mat reconstitutedImage;
    cv::merge({blueChannel, greenChannel, redChannel}, reconstitutedImage);
    return reconstitutedImage;
}

int main() {
    // Exemple d'utilisation
    cv::Mat image = cv::imread("IMAGE BMP.jpg");
    if (image.empty()) {
        std::cerr << "Erreur : Impossible de charger l'image." << std::endl;
        return -1;
    }

    // Extraire les pixels de l'image originale en une liste 1 colonne
    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    cv::Mat blueColumn = channels[0].reshape(1, channels[0].rows * channels[0].cols);
    cv::Mat greenColumn = channels[1].reshape(1, channels[1].rows * channels[1].cols);
    cv::Mat redColumn = channels[2].reshape(1, channels[2].rows * channels[2].cols);

    cv::Mat colonneUnique;
    cv::vconcat(blueColumn, greenColumn, colonneUnique);
    cv::vconcat(colonneUnique, redColumn, colonneUnique);

    // Convertir la matrice colonne en vecteur
    std::vector<int> pixelValues(colonneUnique.rows);
    for (int i = 0; i < colonneUnique.rows; i++) {
        pixelValues[i] = colonneUnique.at<uchar>(i, 0);
    }

    // Reconstruire l'image
    cv::Mat reconstitutedImage = reconstruireImage(pixelValues, image.cols, image.rows);
    if (!reconstitutedImage.empty()) {
        cv::imshow("Image Reconstituée", reconstitutedImage); // Afficher l'image reconstruite
        cv::waitKey(0); // Attendre une entrée utilisateur avant de fermer
    }

    return 0;
}
