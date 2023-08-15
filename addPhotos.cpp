#include <opencv2/opencv.hpp>

int main() {
    std::vector<cv::Mat> images;

    for (int i = 1179; i <= 1188; ++i) {
        cv::Mat image = cv::imread("IMG_" + std::to_string(i) + ".png");
        if (image.empty()) {
            std::cerr << "Nie udało się wczytać obrazu." << std::endl;
            return 1;
        }
        images.push_back(image);
    }

    for (size_t i = 1; i < images.size(); ++i) {
        if (images[i].size() != images[0].size()) {
            std::cerr << "Obrazy mają różne rozmiary!" << std::endl;
            return 1;
        }
    }

    cv::Mat row1 = images[0];
    cv::Mat row2 = images[5];

    for (size_t i = 1; i < 5; ++i) {
        cv::Mat borderedImage;
        cv::copyMakeBorder(images[i], borderedImage, 0, 0, 10, 0, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
        cv::hconcat(row1, borderedImage, row1); 
    }

    for (size_t i = 6; i < 10; ++i) {
        cv::Mat borderedImage;
        cv::copyMakeBorder(images[i], borderedImage, 0, 0, 10, 0, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
        cv::hconcat(row2, borderedImage, row2);
    }

    cv::Mat borderBetweenRows(10, row1.cols, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat mergedImage;
    cv::vconcat(row1, borderBetweenRows, mergedImage);
    cv::vconcat(mergedImage, row2, mergedImage);

    cv::imwrite("merged_images_grid_with_borders.jpg", mergedImage);

    return 0;
}
