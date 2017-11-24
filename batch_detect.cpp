//�ú��������Ǵ����֤ͼƬ�����������������ο�,�ٸ��ݾ��ο���½�ͼƬ�ٳ���
//===========================================================
#include "opencv_lib.h"
#include <iostream>
#include <io.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
using namespace cv;

const float ratio_h1 = 0.55;  //����������߽�Ҫ����ı���
const float ratio_h2 = 1.0;
const float ratio_w1 = 2.75;
const float ratio_w2 = 0.5;

CascadeClassifier faceCascade;

//�����ļ����е�ͼƬ�����������⣺��һ���ļ��޷�ѹ��
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
//��ȡһ��ͼƬ�е�һ�����߶������
//===============================================================================================
int face_detect(string path , string save_path)
{
	//Mat face_rect; //��Ž�ȡ��õľ��ο�
	Mat imgGray;
	Mat src = imread(path);
	vector<Rect> faces;  //Ĭ��ֻ��һ������

	if (src.empty())
	{
		cout << "ͼƬ·��������";
	}

	if (src.channels() == 3)
	{
		cvtColor(src, imgGray, CV_RGB2GRAY);
	}
	else
	{
		imgGray = src;
	}
	//ʹ��detectMultiScale���������������
	faceCascade.detectMultiScale(imgGray, faces, 1.2, 6, 0, Size(0, 0));   //�������

	if (faces.size() == 0)
	{
		cout << "δ��⵽����" << path << endl;
	}
	if (faces.size() > 0)  //�������������֤ͼƬ������Ĭ��ֻ��һ������
	{
		if (faces.size() > 1)
			cout << "��⵽��������" << endl;
		for (int i = 0; i < faces.size(); i++)
			rectangle(src, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),Scalar(255, 0, 0), 1, 8);
	}
	imwrite(save_path, src);
	return 0;
}

//�����������
//============================================================================================
int batch_face_detect(char src_path[30], string save_path)
{
	faceCascade.load("D:/opencv/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");   //���ط�������ע���ļ�·��
	int pic_num;  //ͼƬ����
	string pic_path;  //ÿ�μ��������ͼƬ·��
	Rect face_part;  //������λͼƬ
	Mat result_img;  //ǰ��ͼƬ
	vector<string> filenames;  //�ļ����е�����ͼƬ��
	Mat src;  //ԭʼͼƬ
	string path;

	filenames = get_pic_names(src_path);

	pic_num = filenames.size();  //ͼƬ����
	for (int i = 0; i < pic_num + 1; i++)
	{
		pic_path = src_path + filenames[i];
		path = save_path + filenames[i];
		face_detect(pic_path, path);
		cout << pic_path << endl;
	}
	return 0;
}