//2017.11.19����������λ��������ȡǰ��ͼƬ  
//=====================================================================
#include <string>
#include <iostream>

using namespace std;

extern int batch_face_detect(char src_path[30], string save_path);

int main(void)  //path��Ҫ���в�����ͼƬ�ļ��е�·��
{
	string save_path;
	char src_path[30];
	cout << "������Ҫ���в�����ͼƬ�ļ���·����";
	cin.getline(src_path, 30);
	cout << "������Ҫ���浽��ͼƬ�ļ���·����";
	cin >> save_path;
	batch_face_detect(src_path, save_path);
	while (1);
}
