#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include<iostream>
#include<vector>

using namespace std;
using namespace cv;

void display(int center_x, int center_y, int corner_x, int corner_y, int align_h, int count, int spoilt);
int main()
{
	Mat image, image_gray,image_blur,image_thre, 
		image_dilate,image_erode,
		add_output;
	//image = imread("num.jpg");
	image = imread("word.png");
	
	if (image.empty())
	{
		cerr << "Invalid Image" << endl;
		return -1;
	}
	
	//imshow("image", image);
	//Rect r0 = selectROI("input", image, true, false);
	//image = image(r0);
#pragma region text
	// 1 change gray
	cvtColor(image, image_gray, COLOR_BGR2GRAY);
	imshow("Gray", image_gray);

	// 2 Threshold 
	//GaussianBlur(image_gray, image_blur, Size(5, 5), 1);
	medianBlur(image_gray, image_blur, 5);
	threshold(image_blur, image_thre, 0, 255, THRESH_OTSU);
	//imshow("Thre", image_blur);
	imshow("Thre", image_thre);

	// 3 DILATE, ERODE
	//erode(image_thre, image_erode, 1);
	//dilate(image_erode, image_dilate, 1);
	//dilate(image_erode, image_dilate, 2);
	//image_dilate = image_erode;
	erode(image_thre, image_erode, Mat(), Point(-1, -1), 1, 1, 1);
	dilate(image_erode, image_dilate, Mat(), Point(-1, -1), 1, 1, 1);
	//dilate(image_erode, image_dilate, Mat(), Point(-1, -1), 1, 1, 1);

	imshow("dilate", image_dilate);

#pragma region find text
	// 4 Find text
//vector<vector<Point>> contours_roi;
//vector<Vec4i> hierarchy_roi;
//findContours(image_dilate, contours_roi, hierarchy_roi, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//add_output = Mat::zeros(image_dilate.size(), CV_8UC3);
//drawContours(add_output, contours_roi, -1, Scalar(255, 255, 0), 1);
//for (int i = 0; i < (int)contours_roi.size(); i++) {
//	Rect r = boundingRect(contours_roi[i]);
//	//if (r.height > r.width * 1.2) continue;
//	rectangle(add_output, r, Scalar(255, 0, 0), 2);

//}
//float epsilon = 0.001 * arcLength(contours_roi[0], true);
//Mat approx;
//approxPolyDP(contours_roi[0], approx, epsilon, true);

//RotatedRect rect = minAreaRect(contours_roi[0]);

//Mat box;
//boxPoints(rect, box);

//float r1 = box.at<float>(Point(0, 0));
//float r2 = box.at<float>(Point(1, 0));
//float r3 = box.at<float>(Point(0, 1));
//float r4 = box.at<float>(Point(1, 1));
//float r5 = box.at<float>(Point(0, 2));
//float r6 = box.at<float>(Point(1, 2));
//float r7 = box.at<float>(Point(0, 3));
//float r8 = box.at<float>(Point(1, 3));

//line(add_output, Point(r1, r2), Point(r3, r4), Scalar(0, 255, 255), 2);
//line(add_output, Point(r3, r4), Point(r5, r6), Scalar(0, 255, 255), 2);
//line(add_output, Point(r7, r8), Point(r5, r6), Scalar(0, 255, 255), 2);
//line(add_output, Point(r7, r8), Point(r1, r2), Scalar(0, 255, 255), 2);

		//imshow("out", add_output);

#pragma endregion

#pragma endregion

	char* outText;

	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init("C:\\tesseract-include\\tessdata", "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}
	
	api->SetImage((uchar*)image_dilate.data, image_dilate.cols, image_dilate.rows,1, image_dilate.cols);
	// Get OCR result
	outText = api->GetUTF8Text();
	if (outText == nullptr)
		cout << "Can't Detect..." << endl;
	else
		
		cout << "OCR output: " << outText;

	// Destroy used object and release memory
	api->End();
	delete api;
	delete[] outText;

	waitKey();

	return 0;
}


void display(int center_x, int center_y,int corner_x,int corner_y,int align_h ,int count,int spoilt) {
	cout << "***************" << endl;
	cout << "Test CHIP XXX" << endl;
	cout << "Focus Point X:" << center_x << " Y: " << center_y << endl;
	cout <<"Left Top Corner X: " << corner_x << " Y: " << corner_y << endl;
	cout << "Align Height: " << align_h << endl;
	cout << "Count: " << count << endl;
	cout << "Spoilt: " << spoilt << endl;

}
