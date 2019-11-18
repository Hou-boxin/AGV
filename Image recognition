#include "stdafx.h"
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0); //capture the video from web cam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 100;
	int iHighH = 140;

	int iLowS = 90;
	int iHighS = 255;

	int iLowV = 90;
	int iHighV = 255;

	//轮廓检测
	vector<vector<Point>> contours;
	vector<Vec4i> hireachy;
	Rect rect;
	Point2f center;
	float radius = 5;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;
		vector<Mat> hsvSplit;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		//因为我们读取的是彩色图，直方图均衡化需要在HSV空间做
		split(imgHSV, hsvSplit);
		equalizeHist(hsvSplit[2], hsvSplit[2]);
		merge(hsvSplit, imgHSV);
		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
		
																									  //开操作 (去除一些噪点)
		Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);

		//闭操作 (连接一些连通域)
		morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

		//获取边界	
		findContours(imgThresholded, contours, hireachy, RETR_EXTERNAL, CV_CHAIN_APPROX_NONE, Point(0, 0));

		/// 多边形逼近轮廓 +获取矩形和圆形边界框
		vector<vector<Point>> contours_poly(contours.size());//近似后的轮廓点集
		vector<Rect>boundRect(contours.size());//包围点集的最小矩形vector
		vector<Point2f>center(contours.size());//包围点集的最小圆形vector
		vector<float>radius(contours.size());//包围点集的最小圆形半径vector

		double maxArea = 0;
		int max = -1;
		for (int i = 0; i < contours.size(); i++)
		{
			double area = contourArea(contours[static_cast<int>(i)]);
			approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);//对多边形曲线做适当近似，contours_poly[i]是输出的近似点集
			boundRect[i] = boundingRect(Mat(contours_poly[i]));//计算并返回包围轮廓点集的最小矩形
			minEnclosingCircle(contours_poly[i], center[i], radius[i]);//计算并返回包围轮廓点集的最小圆形及其半径
			if (area > maxArea)
			{
				maxArea = area;
				max = i;
			}
		}

		// 画多边形轮廓 + 包围的矩形框 + 圆形框
		if (max != -1)
		{
			Scalar color = Scalar(255, 255, 255);
			drawContours(imgThresholded, contours_poly, max, color, 1, 8, hireachy, 0, Point());//根据轮廓点集contours_poly和轮廓结构hierarchy画出轮廓
			rectangle(imgThresholded, boundRect[max].tl(), boundRect[max].br(), color, 2, 8, 0);//画矩形，tl矩形左上角，br右上角
			circle(imgThresholded, center[max], (int)radius[max], color, 2, 8, 0);//画圆形
		}
	

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", imgOriginal); //show the original image

		char key = (char)waitKey(30);
		if (key == 27)
			break;
	}

	return 0;
}
