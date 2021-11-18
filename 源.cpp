#include<iostream>
using namespace std;
#include<string>
#include<io.h>
#include<vector>
#include<fstream>

//string filePath = "D:\\�ȷ������ﰲװ��\\�ƿ�11905�ཡ����41��";
//string qian = "D:\\VS��������Ŀ\\��Ŀ����\\excel�ԱȲ�ѯ\\qian.txt";
//string hou = "D:\\VS��������Ŀ\\��Ŀ����\\excel�ԱȲ�ѯ\\hou.txt";
void getFiles(string path, vector<string>& files)
{
	//�ļ����
	long   hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮
			//�������,�����б�
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
			if (b[j].find(a[i]) != 4294967295)//�ҵ���
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
	cout << "δ������Ϊ��" << ren << endl;
}


void duibi(string* a, int num, vector<string> b, int num2)
{
	int ren=0;
	for (int i = 0;i < num;i++)
	{
		int flag = 1;//û�ҵ�
		for (int j = 0;j < num2;j++)
		{
			if (b[j].find(a[i]) != 4294967295)//�ҵ���
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
	cout << "δ������Ϊ��" << ren<<endl;
}

//��б��ת˫б��
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
	cout << "�Ƿ�ʹ��Ĭ��������(��1)";
	cin >> num;
	if(num==1) qian = "D:\\VS��������Ŀ\\��Ŀ����\\excel�ԱȲ�ѯ\\qian.txt";
	else
	{
		cout << "�����������������ļ�·��" << endl;
		cin >> qian;
		pathConvert_Single2Double(qian);
	}
	
	cout << "�������ѽ��������ļ�·��" << endl;
	cin >> hou;
	pathConvert_Single2Double(hou);
}


int main()
{
	cout << "��������ѡ�������ı��ļ����ݶԱȣ������ı��ļ����ļ�������ļ�����" << endl
		<< "1.ѡ�������ı��ļ����ݶԱ�" << endl
		<< "2.�ı��ļ����ļ�������ļ���" << endl
		<< "����������ѡ��";
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
			num = shuju(qian, a);  //�������
			string b[100];
			int num2;
			num2 = shuju(hou, b);

			duibi(a, num, b, num2);  //���жԱ�
			system("pause");
			exit(1);

		}
		else if (select == 2)
		{
			string qian, hou;
			huoqulujin(qian, hou);
			string a[100];
			int num;
			num = shuju(qian, a);  //�������
			vector<string> files;
			//��ȡ��·���µ������ļ�
			getFiles(hou, files);
			int size = files.size();

			duibi(a, num, files, size);
			system("pause");
			exit(0);
		}
		else
		{
			cout << "������������������" << endl;
		}
	}
	

}