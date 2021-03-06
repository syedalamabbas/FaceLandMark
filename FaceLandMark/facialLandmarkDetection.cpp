#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include "drawLandmarks.hpp"


using namespace std;
using namespace cv;
using namespace cv::face;


int main(int argc,char** argv)
{
    // Load Face Detector
    CascadeClassifier faceDetector("haarcascade_frontalface_alt2.xml");

    // Create an instance of Facemark
    Ptr<Facemark> facemark = FacemarkLBF::create();

    // Load landmark detector
    facemark->loadModel("lbfmodel.yaml");

    // Set up webcam for video capture
    VideoCapture cam("Trevor.mp4");
    
    // Variable to store a video frame and its grayscale 
    Mat frame, gray;
    
    // Read a frame
    while(cam.read(frame))
    {
      // Find face
      vector<Rect> faces;
      // Convert frame to grayscale because
      // faceDetector requires grayscale image.
      cvtColor(frame, gray, COLOR_BGR2GRAY);

	  // Simple conversions to check some stuff 
	  uchar* new_array =  new uchar(gray.rows*gray.cols);
	  new_array = gray.data;
	  Mat M(gray.rows, gray.cols, CV_8U, new_array);
	  imshow("Simple gray image", M);
      
	  // Color conversion setting 

	  Mat colorFrame(gray.rows, gray.cols, CV_8UC4, cv::Scalar(0, 0, 0, 1));

	  for (int i = 0; i < frame.rows*frame.cols; i++)
	  {
		  colorFrame.data[i*4 + 0] = frame.data[i * 3 + 0];
		  colorFrame.data[i * 4 + 1] = frame.data[i * 3 + 1];
		  colorFrame.data[i * 4 + 2] = frame.data[i * 3 + 2];
	  
	  }

	  imshow("Full color image BGRA", colorFrame);

	  // Detect faces
      faceDetector.detectMultiScale(gray, faces);
      
      // Variable for landmarks. 
      // Landmarks for one face is a vector of points
      // There can be more than one face in the image. Hence, we 
      // use a vector of vector of points. 
      vector< vector<Point2f> > landmarks;
      
      // Run landmark detector
      bool success = facemark->fit(frame,faces,landmarks);
      
      if(success)
      {
        // If successful, render the landmarks on the face
        for(int i = 0; i < landmarks.size(); i++)
        {
          drawLandmarks(frame, landmarks[i]);
        }
      }

      // Display results 
      imshow("Facial Landmark Detection", frame);
      // Exit loop if ESC is pressed
      if (waitKey(1) == 27) break;
      
    }
    return 0;
}
