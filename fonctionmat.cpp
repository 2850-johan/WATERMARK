#include <opencv2/opencv.hpp>  // Inclusion de la bibliothèque OpenCV
#include <iostream>            // Inclusion de la bibliothèque pour les entrées/sorties standard
#include <vector>              // Pour utiliser std::vector

// Déclaration de la fonction
std::vector<int> extrairePixelValues(const std::string& cheminImage) {
    // Charger l'image couleur d'origine
    cv::Mat image = cv::imread(cheminImage); // cheminImage est le fichier d'entrée
    if (image.empty()) {  // Vérification si l'image a été chargée
        std::cerr << "Erreur : Impossible de charger l'image." << std::endl;
        return {};        // Si l'image ne peut être chargée, renvoyer un tableau vide
    }

    // Diviser l'image en trois canaux (B, G, R)
    std::vector<cv::Mat> channels;  // Déclarer un vecteur pour stocker les trois canaux
    cv::split(image, channels);     // Diviser l'image en canaux B, G, R (dans cet ordre)

    // Vérifier que l'image a bien trois canaux
    if (channels.size() != 3) {
        std::cerr << "Erreur : L'image n'est pas au format BGR." << std::endl;
        return {}; // Retourner un tableau vide en cas d'erreur
    }

    // Transformer chaque canal en une seule colonne
    cv::Mat blue_column = channels[0].reshape(1, channels[0].rows * channels[0].cols);
    cv::Mat green_column = channels[1].reshape(1, channels[1].rows * channels[1].cols);
    cv::Mat red_column = channels[2].reshape(1, channels[2].rows * channels[2].cols);

    // Combiner les trois colonnes en une seule
    cv::Mat colonneUnique;
    cv::vconcat(blue_column, green_column, colonneUnique);  // Ajouter le canal bleu puis vert
    cv::vconcat(colonneUnique, red_column, colonneUnique);  // Ajouter le canal rouge

    // Stocker les valeurs de colonneUnique dans un std::vector<int>
    std::vector<int> pixelValues(colonneUnique.rows);
    for (int i = 0; i < colonneUnique.rows; i++) {
        pixelValues[i] = colonneUnique.at<uchar>(i, 0);  // Copier chaque valeur dans le tableau
    }

    return pixelValues; // Retourner les valeurs de pixels
}

int main() {
    // Appel de la fonction avec le chemin de l'image
    std::vector<int> pixels = extrairePixelValues("IMAGE BMP.jpg");

    // Vérifier si la fonction a réussi
    if (pixels.empty()) {
        std::cerr << "Erreur lors de l'extraction des pixels." << std::endl;
        return -1;
    }

    // Afficher les premières valeurs pour vérification
    for (size_t i = 0; i < 10 && i < pixels.size(); i++) {
        std::cout << "Pixel " << i << ": " << pixels[i] << std::endl;
    }

    return 0;
}
