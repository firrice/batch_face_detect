//该函数功能是从身份证图片中批量检测出人脸矩形框,再根据矩形框大致将图片抠出来
//===========================================================
#include "opencv_lib.h"
#include <iostream>
#include <io.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
using namespace cv;

const float ratio_h1 = 0.55;  //人脸坐标各边将要增添的比例
const float ratio_h2 = 1.0;
const float ratio_w1 = 2.75;
const float ratio_w2 = 0.5;

CascadeClassifier faceCascade;

//遍历文件夹中的图片名，存在问题：第一个文件无法压入
vector<string> get_pic_names(char origin_path[30])
{
	vector<string> pic_names;
	char path[30];
	strcpy_s(path, 30, origin_path);
	char* appended_path = "*.jpg";
	strcat_s(path, 30, appended_path);
	char* filename = path;

	struct _finddata_t fileinfo;
	long handle;
	handle = _findfirst(filename, &fileinfo);
	cout << handle << endl;
	if (handle == -1) cout << "fail..." << endl;

	while (!_findnext(handle, &fileinfo))
	{
		pic_names.push_back(fileinfo.name);
	}
	_findclose(handle);
	return pic_names;
}
//获取一张图片中的一个或者多个人脸
//===============================================================================================
int face_detect(string path , string save_path)
{
	//Mat face_rect; //存放截取获得的矩形框
	Mat imgGray;
	Mat src = imread(path);
	vector<Rect> faces;  //默认只有一张人脸

	if (src.empty())
	{
		cout << "图片路径不存在";
	}

	if (src.channels() == 3)
	{
		cvtColor(src, imgGray, CV_RGB2GRAY);
	}
	else
	{
		imgGray = src;
	}
	//使用detectMultiScale函数进行人脸检测
	faceCascade.detectMultiScale(imgGray, faces, 1.2, 6, 0, Size(0, 0));   //检测人脸

	if (faces.size() == 0)
	{
		cout << "未检测到人脸" << path << endl;
	}
	if (faces.size() > 0)  //这里由于是身份证图片，所以默认只有一个人脸
	{
		if (faces.size() > 1)
			cout << "检测到多张人脸" << endl;
		for (int i = 0; i < faces.size(); i++)
			rectangle(src, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),Scalar(255, 0, 0), 1, 8);
	}
	imwrite(save_path, src);
	return 0;
}

//批量框出人脸
//============================================================================================
int batch_face_detect(char src_path[30], string save_path)
{
	faceCascade.load("D:/opencv/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");   //加载分类器，注意文件路径
	int pic_num;  //图片数量
	string pic_path;  //每次检测人脸的图片路径
	Rect face_part;  //人脸部位图片
	Mat result_img;  //前景图片
	vector<string> filenames;  //文件夹中的所有图片名
	Mat src;  //原始图片
	string path;

	filenames = get_pic_names(src_path);

	pic_num = filenames.size();  //图片数量
	for (int i = 0; i < pic_num + 1; i++)
	{
		pic_path = src_path + filenames[i];
		path = save_path + filenames[i];
		face_detect(pic_path, path);
		cout << pic_path << endl;
	}
	return 0;
}