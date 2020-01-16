#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>	//highgui模块头文件
#include <opencv2/imgproc/imgproc.hpp>	//图像处理头文件

#include<iostream>

using namespace cv;
using namespace std;

/*
int main(int argc, char** argv) {

	Mat image = imread("1234.jpg");

	if (image.empty()) {

		printf("could not load image...\n");

		return -1;

	}

	namedWindow("test_opencv_setup", 0);

	imshow("test_opencv_srtup", image);

	waitKey(0);

	return 0;

}*/

//图像腐蚀
void test1()
{
	Mat srcImage = imread("tlp.jpg", 1);
	imshow("原图", srcImage);

	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat destImage;
	erode(srcImage, destImage, element);
	imshow("腐蚀图", destImage);
	waitKey(0);
}

//调用摄像头采集图像
void test2()
{
	//Sleep(3000);
	VideoCapture capture;
	capture.open(0);
	if (!capture.isOpened()) {
		cout << "摄像头打开失败" << endl;
		return ;
	}
	while (1) {
		Mat frame;
		capture >> frame;
		if (frame.empty()) {
			break;
		}
		imshow("读取摄像头", frame);
		waitKey(30);
	}
}

//生成PNG图片
void createAlphaMat(Mat& mat) {
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.cols; j++) {
			Vec4b& rgba = mat.at<Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
			rgba[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.cols) * UCHAR_MAX);
			rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
		}
	}
}

void test3() {
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	vector<int> compression_params;
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try {
		imwrite("透明Alpha值图.png", mat, compression_params);
		imshow("生成PNG图", mat);
		fprintf(stdout, "PNG图片保存完成\r\n可以在工程目录下查看\r\n");
		waitKey(0);
	}
	catch (runtime_error& er) {
		fprintf(stderr, "图片转换为PNG格式发生错误:%s\r\n", er.what());
		return ;
	}
}



int main() {
	
	//test1();
	//test2();
	//test3();

	return EXIT_SUCCESS;
}

