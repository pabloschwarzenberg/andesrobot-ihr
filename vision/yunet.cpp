#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

int main() {
    // Load the YuNet model
    // You need to download the 'face_detection_yunet_2021sep.onnx' model
    // from the OpenCV Zoo (https://github.com/opencv/opencv_zoo/tree/master/models/face_detection_yunet)
    // and place it in the same directory as your executable or provide the full path.
    std::string modelPath = "face_detection_yunet_2023mar.onnx";
    cv::Ptr<cv::FaceDetectorYN> detector = cv::FaceDetectorYN::create(modelPath, "", cv::Size(320, 240));

    if (detector.empty()) {
        std::cerr << "Failed to load YuNet model." << std::endl;
        return -1;
    }

    // Load an image
    cv::Mat image = cv::imread("frame.jpg"); // Replace with your image path
    if (image.empty()) {
        std::cerr << "Failed to load image." << std::endl;
        return -1;
    }

    // Set input size for the detector (can be adjusted for performance/accuracy)
    detector->setInputSize(image.size());

    // Detect faces
    cv::Mat faces;
    detector->detect(image, faces);

    // Draw bounding boxes and landmarks
    for (int i = 0; i < faces.rows; i++) {
        // Bounding box
        int x = static_cast<int>(faces.at<float>(i, 0));
        int y = static_cast<int>(faces.at<float>(i, 1));
        int width = static_cast<int>(faces.at<float>(i, 2));
        int height = static_cast<int>(faces.at<float>(i, 3));
        cv::rectangle(image, cv::Rect(x, y, width, height), cv::Scalar(0, 255, 0), 2);

        // Landmarks (optional, YuNet provides 5 facial landmarks)
        for (int j = 0; j < 5; j++) {
            int lx = static_cast<int>(faces.at<float>(i, 4 + j * 2));
            int ly = static_cast<int>(faces.at<float>(i, 4 + j * 2 + 1));
            cv::circle(image, cv::Point(lx, ly), 2, cv::Scalar(0, 0, 255), -1);
        }
    }

    // Display the result
    cv::imshow("Face Detection with YuNet", image);
    cv::waitKey(0);

    return 0;
}

