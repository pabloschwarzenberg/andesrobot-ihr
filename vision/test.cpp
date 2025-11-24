#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
int main()
{
	cv::VideoCapture cap(0);

	if(!cap.isOpened())
	{
		std::cerr << "Error: could not open camera" << endl;
		return -1;
	}

	cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    	cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    	cv::namedWindow("Camera Feed", cv::WINDOW_AUTOSIZE);

	cv::Mat frame; // Matrix to store each frame

    	while (true) {
        	cap >> frame;

        	if (frame.empty()) {
            		std::cerr << "Error: Blank frame grabbed." << std::endl;
            		break;
        	}

        	cv::imshow("Camera Feed", frame);
		cv::imwrite("frame.jpg",frame);

        	if (cv::waitKey(1) == 'q') {
            		break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
