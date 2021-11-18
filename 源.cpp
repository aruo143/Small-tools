#include<iostream>
using namespace std;
#include<string>
#include<io.h>
#include<vector>
#include<fstream>

//string filePath = "D:\\先放在这里安装包\\计科11905班健康码41人";
//string qian = "D:\\VS创建的项目\\项目练手\\excel对比查询\\qian.txt";
//string hou = "D:\\VS创建的项目\\项目练手\\excel对比查询\\hou.txt";
void getFiles(string path, vector<string>& files)
{
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int  shuju(string position,string *a)
{
	ifstream ifs;
	ifs.open(position, ios::in);
	int num = 0;
	while (ifs >> a[num])
	{
		num++;
	}
	ifs.close();
	return num;
}

void duibi(string* a, int num, string* b, int num2)
{
	int ren = 0;
	for (int i = 0;i < num;i++)
	{
		int flag = 1;
		for (int j = 0;j < num2;j++)
		{
			if (b[j].find(a[i]) != 4294967295)//找到了
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			cout << a[i] << endl;
			ren++;
		}
	}
	cout << "未交人数为：" << ren << endl;
}


void duibi(string* a, int num, vector<string> b, int num2)
{
	int ren=0;
	for (int i = 0;i < num;i++)
	{
		int flag = 1;//没找到
		for (int j = 0;j < num2;j++)
		{
			if (b[j].find(a[i]) != 4294967295)//找到了
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			cout << a[i] << endl;
			ren++;
		}
	}
	cout << "未交人数为：" << ren<<endl;
}

//单斜杠转双斜杠
void pathConvert_Single2Double(string& s) {
	string::size_type pos = 0;
	while ((pos = s.find('\\', pos)) != string::npos) {
		s.insert(pos, "\\");
		pos = pos + 2;
	}
}

void huoqulujin(string& qian, string& hou)
{
	int num = 0;
	cout << "是否使用默认名单？(按1)";
	cin >> num;
	if(num==1) qian = "D:\\VS创建的项目\\项目练手\\excel对比查询\\qian.txt";
	else
	{
		cout << "请输入完整名单的文件路径" << endl;
		cin >> qian;
		pathConvert_Single2Double(qian);
	}
	
	cout << "请输入已交名单的文件路径" << endl;
	cin >> hou;
	pathConvert_Single2Double(hou);
}


int main()
{
	cout << "请问你是选择两个文本文件数据对比，还是文本文件与文件夹里的文件名？" << endl
		<< "1.选择两个文本文件数据对比" << endl
		<< "2.文本文件与文件夹里的文件名" << endl
		<< "请输入您的选择：";
	int select;
	while (1)
	{
		cin >> select;
		if (select == 1)
		{
			string qian, hou;
			huoqulujin(qian,hou);

			string a[100];
			int num;
			num = shuju(qian, a);  //存放数据
			string b[100];
			int num2;
			num2 = shuju(hou, b);

			duibi(a, num, b, num2);  //进行对比
			system("pause");
			exit(1);

		}
		else if (select == 2)
		{
			string qian, hou;
			huoqulujin(qian, hou);
			string a[100];
			int num;
			num = shuju(qian, a);  //存放数据
			vector<string> files;
			//获取该路径下的所有文件
			getFiles(hou, files);
			int size = files.size();

			duibi(a, num, files, size);
			system("pause");
			exit(0);
		}
		else
		{
			cout << "输入有误，请重新输入" << endl;
		}
	}
	

}