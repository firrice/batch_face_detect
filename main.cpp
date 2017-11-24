//2017.11.19：根据人脸位置批量获取前景图片  
//=====================================================================
#include <string>
#include <iostream>

using namespace std;

extern int batch_face_detect(char src_path[30], string save_path);

int main(void)  //path是要进行操作的图片文件夹的路径
{
	string save_path;
	char src_path[30];
	cout << "请输入要进行操作的图片文件夹路径：";
	cin.getline(src_path, 30);
	cout << "请输入要保存到的图片文件夹路径：";
	cin >> save_path;
	batch_face_detect(src_path, save_path);
	while (1);
}
