#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
int main()
{
	std::string modelPath = "face_detection_yunet_2023mar.onnx";
    cv::Ptr<cv::FaceDetectorYN> detector = cv::FaceDetectorYN::create(modelPath, "", cv::Size(320, 240));
    if (detector.empty()) {
        std::cerr << "Failed to load YuNet model." << std::endl;
        return -1;
    }
	cv::VideoCapture cap(0);
	if(!cap.isOpened())
	{
		std::cerr << "Error: could not open camera" << endl;
		return -1;
	}

	cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
	cv::Mat frame;
    cv::Mat faces;

	while(true)
	{
		cap >> frame;
		if (frame.empty()) {
				std::cerr << "Error: Blank frame grabbed." << std::endl;
				break;
		}	
		detector->setInputSize(frame.size());
		detector->detect(frame, faces);
		if(faces.rows!=0)
		{
			cv::namedWindow("Camera Feed", cv::WINDOW_AUTOSIZE);
			cv::imshow("Camera Feed", frame);
			if (cv::waitKey(1) == 'q')
				break;
		}
		else
			std::cout << "no faces" << std::endl;
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}