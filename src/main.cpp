//  __/\\\\\\\\\\\\\\\__________________________/\\\________/\\\\\\\_______________/\\\____        
//   _\////////////\\\_________________________/\\\\\______/\\\/////\\\___________/\\\\\____       
//    ___________/\\\/________________________/\\\/\\\_____/\\\____\//\\\________/\\\/\\\____      
//     _________/\\\/______/\\\\\\\\\\\______/\\\/\/\\\____\/\\\_____\/\\\______/\\\/\/\\\____     
//      _______/\\\/_______\///////////_____/\\\/__\/\\\____\/\\\_____\/\\\____/\\\/__\/\\\____    
//       _____/\\\/________________________/\\\\\\\\\\\\\\\\_\/\\\_____\/\\\__/\\\\\\\\\\\\\\\\_   
//        ___/\\\/_________________________\///////////\\\//__\//\\\____/\\\__\///////////\\\//__  
//         __/\\\\\\\\\\\\\\\_________________________\/\\\_____\///\\\\\\\/_____________\/\\\____ 
//          _\///////////////__________________________\///________\///////_______________\///_____

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

const int INF=65535;	//����ֵ
const int MAX_CITY_NUM=23;	//����������

int Order = 1;//����ѡ���ʶ

//UDN****************************************************************************************
typedef struct {
	int time;	//��ʱ��
	int cost;	//�𳵷���
}Arc;//��

class UDN {
public:
	void Floyd(int);//Floyd
	void printPath(int, int);//��ӡ·��
	Arc sumPath(int, int);//�����ܻ���
	UDN();//��ʼ�������б���ڽӾ���
	void outputCityList();//��������б�
	
	
	vector<string> city;//�����б�
	Arc arcs[MAX_CITY_NUM][MAX_CITY_NUM];//��Ȩ�ڽӾ���
	Arc sum;//���������ܻ��ѵ�ֵ
	int path[MAX_CITY_NUM][MAX_CITY_NUM];//Path����
	int cityNum;//��������
};//������

UDN::UDN() :cityNum(12)
{
	city = { "�ɶ�", "ʯ��ׯ", "֣��", "�人", "����", "��ɳ", "����", "����", "����", "����", "���", "�Ϻ�" };//��ʼ�������б�
	for (int i = 0; i < MAX_CITY_NUM; i++)//��ʼ����Ȩ�ڽӾ���
	{
		for (int j = 0; j < MAX_CITY_NUM; j++)
		{
			if (i == j)
			{
				arcs[i][j].time = 0;
				arcs[i][j].cost = 0;
			}
			else
			{
				arcs[i][j].time = INF;
				arcs[i][j].cost = INF;
			}			
		}
	}

	//���ô�Ȩ�ڽӾ���
	arcs[0][4].time = arcs[4][0].time = 3;
	arcs[0][9].time = arcs[9][0].time = 8;
	arcs[1][2].time = arcs[2][1].time = 5;
	arcs[1][4].time = arcs[4][1].time = 24;
	arcs[1][9].time = arcs[9][1].time = 2;
	arcs[2][3].time = arcs[3][2].time = 5;
	arcs[2][4].time = arcs[4][2].time = 21;
	arcs[3][4].time = arcs[4][3].time = 16;
	arcs[3][5].time = arcs[5][3].time = 4;
	arcs[3][8].time = arcs[8][3].time = 6;
	arcs[3][9].time = arcs[9][3].time = 11;
	arcs[3][10].time = arcs[10][3].time = 15;
	arcs[3][11].time = arcs[11][3].time = 5;
	arcs[4][5].time = arcs[5][4].time = 12;
	arcs[4][7].time = arcs[7][4].time = 5;
	arcs[4][9].time = arcs[9][4].time = 27;
	arcs[5][6].time = arcs[6][5].time = 8;
	arcs[5][7].time = arcs[7][5].time = 6;
	arcs[5][11].time = arcs[11][5].time = 5;
	arcs[6][7].time = arcs[7][6].time = 13;
	arcs[6][11].time = arcs[11][6].time = 20;
	arcs[8][10].time = arcs[10][8].time = 5;
	arcs[8][11].time = arcs[11][8].time = 10;
	arcs[9][10].time = arcs[10][9].time = 2;
	arcs[10][11].time = arcs[11][10].time = 17;

	arcs[0][4].cost = arcs[4][0].cost = 268;
	arcs[0][9].cost = arcs[9][0].cost = 800;
	arcs[1][2].cost = arcs[2][1].cost = 60;
	arcs[1][4].cost = arcs[4][1].cost = 250;
	arcs[1][9].cost = arcs[9][1].cost = 20;
	arcs[2][3].cost = arcs[3][2].cost = 75;
	arcs[2][4].cost = arcs[4][2].cost = 220;
	arcs[3][4].cost = arcs[4][3].cost = 170;
	arcs[3][5].cost = arcs[5][3].cost = 50;
	arcs[3][8].cost = arcs[8][3].cost = 520;
	arcs[3][9].cost = arcs[9][3].cost = 160;
	arcs[3][10].cost = arcs[10][3].cost = 160;
	arcs[3][11].cost = arcs[11][3].cost = 300;
	arcs[4][5].cost = arcs[5][4].cost = 120;
	arcs[4][7].cost = arcs[7][4].cost = 300;
	arcs[4][9].cost = arcs[9][4].cost = 270;
	arcs[5][6].cost = arcs[6][5].cost = 100;
	arcs[5][7].cost = arcs[7][5].cost = 300;
	arcs[5][11].cost = arcs[11][5].cost = 500;
	arcs[6][7].cost = arcs[7][6].cost = 100;
	arcs[6][11].cost = arcs[11][6].cost = 200;
	arcs[8][10].cost = arcs[10][8].cost = 50;
	arcs[8][11].cost = arcs[11][8].cost = 124;
	arcs[9][10].cost = arcs[10][9].cost = 20;
	arcs[10][11].cost = arcs[11][10].cost = 170;
}//UDN::UDN

//��������б�
void UDN::outputCityList()
{
	cout << "���м������" << endl;
	cout << "*********************************************************" << endl;
	for (int i = 0; i < cityNum; i++)
	{
		cout << i + 1 << '.' << city[i] << "    ";
	}
	cout << endl<<"*********************************************************" << endl;
}//UDN::outputCityList

//Floyd
//����ÿ������v������һ�����(i,j)��i��j��v��i, v��j
//��� A[i][j] > A[i][v]+A[v][j]���� A[i][j] ����Ϊ A[i][v]+A[v][j] ��ֵ
//���ҽ�Path[i][j]��Ϊv
void UDN::Floyd(int flag)//flag�������ݹ���ѡ����Ӧ�ľ�����Path
{
	int A[MAX_CITY_NUM][MAX_CITY_NUM];
	for (int i = 0; i < cityNum; i++) {
		for (int j = 0; j < cityNum; j++) {
			//��ʼ������A��path
			if (flag == 2)
			{
				A[i][j] = arcs[i][j].time;
			}
			else if (flag == 3)
			{
				A[i][j] = arcs[i][j].cost;
			}
			path[i][j] = -1;	//��ʼ������p,��-1.
		}
	}//for

	for (int v = 0; v < cityNum; v++) //vΪ��ѡ����м���
	{ 
		for (int i = 0; i < cityNum; i++) //
		{ 
			for (int j = 0; j < cityNum; j++)
			{

				if (A[i][j] > A[i][v] + A[v][j])
				{
					A[i][j] = A[i][v] + A[v][j];
					path[i][j] = v;//��i����v��j��iֱ��j������̣�����A[i][j]=A[i][v]+A[v][j]
				}//if
			}			
		}
	}//for
}//ShortestPath_ Floyd

//��ӡ·��
void UDN::printPath(int beginV, int endV)
{
	if (path[beginV][endV] == -1) 
	{
		cout << city[endV] << "    ";//���·�����������׶���
	}
	else
	{
		int mid = path[beginV][endV];//midΪ�м�ڵ�
		printPath(beginV, mid);
		printPath(mid, endV);
	}
}//UDN::printPath

//����·��Ȩֵ
Arc UDN::sumPath(int beginV, int endV)
{
	if (path[beginV][endV] == -1) {
		sum.time += arcs[beginV][endV].time;
		sum.cost += arcs[beginV][endV].cost;
	}
	else
	{
		int mid = path[beginV][endV];
		sumPath(beginV, mid);
		sumPath(mid, endV);
	}
	return sum;
}//UDN::sumPath

//��*********************************************************************************************************************
void menu();				//���˵�
void action(UDN&);			//����ѡ��
void chooseTime(UDN&);		//ѡ��ʱ�����·��
void chooseCost(UDN&);		//ѡ����������·��
void administrator(UDN&);	//�༭���޸Ľ�ͨ��
void add_city(UDN&);
void edit_cost(UDN&);
void edit_time(UDN&);

void menu()
{
	cout << "**********************��ͨ��ѯϵͳ**********************" << endl;
	cout << "*                         ���˵�                       *" << endl;
	cout << "*                1.�鿴����                            *" << endl;
	cout << "*                2.ѡ�����ʱ��·��                    *" << endl;
	cout << "*                3.ѡ�����Լ����·��                  *" << endl;
	cout << "*                4.����Ա����                          *" << endl;
	cout << "*                0.�˳�����                            *" << endl;
	cout << "********************************************************" << endl;
	cout << endl;	
}//menu

//ѡ����ִ��
void action(UDN& cityNet)
{
	cout << "��ѡ��0-4��.....  ";//����ѡ��˵�
	cin >> Order;
	switch (Order) {
	case 1:
		cityNet.outputCityList();//�����ͨ���еĳ����б�
		break;
	case 2:
		chooseTime(cityNet);//ѡ��ʱ�����·��
		break;
	case 3:
		chooseCost(cityNet);//ѡ����������·��
		break;
	case 4:
		administrator(cityNet);//�༭���޸Ľ�ͨ��
		break;
	case 0:
		system("pause");
		break;
	default: 
		cout << endl << "��������!!!����0-4֮��ѡ��!!" << endl;   //�������
	}
}//action

//ѡ��ʱ�����·��
void chooseTime(UDN& cityNet)
{
	int beginCity, endCity;//��ʼ���к�����յ���к���
	cityNet.outputCityList();//��������б�
	cout << "��������ʼ���к�Ŀ�ĳ��е����ִ��룬�м��Կո��������Χ(1--" << cityNet.cityNum << "):";
	cin >> beginCity >> endCity;//������ʼ���к��յ���еĴ���
	beginCity--; endCity--;//��������

	if (!((0 <= beginCity && beginCity < cityNet.cityNum) && (0 <= endCity && endCity < cityNet.cityNum) && beginCity != endCity))
	{
		cout << "����!!!����������ֺ�������1-" << cityNet.cityNum << "֮�䣬�������в������!!" << endl << endl;
	}
	else 
	{
		cityNet.Floyd(Order);//����Floyed����
		cout << cityNet.city[beginCity] << "    ";//��ʾ��ʼ����
		cityNet.printPath(beginCity, endCity);//����printPath��������ʾ���·�������ĳ���
		cout << endl;

		cityNet.sum = { 0,0 };//�����ܻ���
		Arc sum = cityNet.sumPath(beginCity, endCity);
		if (sum.time == INF)
		{
			cout << "���ؼ仹û����·ͨ��" << endl;
		}
		else
		{
			cout << "���𳵻��ѵĽ����" << sum.cost << "Ԫ" << endl;
			cout << "������Ҫ��ʱ����" << sum.time << "Сʱ" << endl;
		}
	}
}//chooseTime

//ѡ����������·��
void chooseCost(UDN& cityNet)
{
	int beginCity, endCity;//��ʼ���к�����յ���к���
	cityNet.outputCityList();//��������б�
	cout << "��������ʼ���к�Ŀ�ĳ��е����ִ��룬�м��Կո��������Χ(1--" << cityNet.cityNum << "):";
	cin >> beginCity >> endCity;//������ʼ���к��յ���еĴ��롣
	beginCity--; endCity--;//��������

	if (!((0 <= beginCity && beginCity < cityNet.cityNum) && (0 <= endCity && endCity < cityNet.cityNum) && beginCity != endCity))
	{
		cout << "������!!!  ����������ֺ�������1-" << cityNet.cityNum << "֮�䣬�������в������!!" << endl << endl;
	}
	else 
	{
		cityNet.Floyd(Order);//����Floyed����
		cout << cityNet.city[beginCity] << "    ";//��ʾ��ʼ����
		cityNet.printPath(beginCity, endCity);//����printPath��������ʾ���·�������ĳ���
		cout << endl;

		cityNet.sum = { 0,0 };//�����ܻ���
		Arc sum = cityNet.sumPath(beginCity, endCity);
		if (sum.time == INF)
		{
			cout << "���ؼ仹û����·ͨ��" << endl;
		}
		else
		{
			cout << "���𳵻��ѵĽ����" << sum.cost << "Ԫ" << endl;
			cout << "������Ҫ��ʱ����" << sum.time << "Сʱ" << endl;
		}		
	}
}//chooseCost

void administrator(UDN& cityNet)
{
	int flag = 1;
	while (flag)
	{
		system("cls");
		cout << "************************************************************" << endl;
		cout << "1:���ӳ���" << endl;
		cout << "2:��ӻ�༭�𳵷���" << endl;
		cout << "3:��ӻ�༭��ʱ��" << endl;
		cout << "0:�������˵�" << endl;
		cout << "************************************************************" << endl;
		cout << "��ѡ��:" << endl;
		cin >> flag;
		switch (flag) {
		case 1:
			add_city(cityNet);
			break;
		case 2:
			edit_cost(cityNet);
			break;
		case 3:
			edit_time(cityNet);
			break;
		case 0:
			system("cls");
			break;
		default: 
			cout << "ѡ�����" << endl;
		}
	}	
}//administrator

void add_city(UDN& cityNet)
{
	string cityName;
	int flag=1;
	cout << "��������Ҫ���ӵĳ�������";
	cin >> cityName;
	for (auto& iter : cityNet.city)
	{
		if (cityName == iter)
		{
			cout << "���ʧ�ܣ��ó����Ѵ��ڣ�" << endl;
			flag = 0;
			system("pause");
		}
	}
	if (flag)
	{
		cityNet.city.push_back(cityName);//��ӵ������б�
		cityNet.cityNum++;//��������+1
	}
}//add_city

void edit_cost(UDN& cityNet)
{
	int beginCity, endCity;//��ʼ���к�����յ���к���
	int cost;//·��
	cityNet.outputCityList();//��������б�
	cout << "��������ʼ���к�Ŀ�ĳ��е����ִ��룬�м��Կո��������Χ(1--" << cityNet.cityNum << "):";
	cin >> beginCity >> endCity;//������ʼ���к��յ���еĴ��롣
	beginCity--; endCity--;//��������

	if (!((0 <= beginCity && beginCity < cityNet.cityNum) && (0 <= endCity && endCity < cityNet.cityNum) && beginCity != endCity))
	{
		cout << "������!!!  ����������ֺ�������1-" << cityNet.cityNum << "֮�䣬�������в������!!" << endl;
	}
	else
	{
		cout << "���������ؼ�����·�ѣ�";
		cin >> cost;
		cityNet.arcs[beginCity][endCity].cost = cityNet.arcs[endCity][beginCity].cost = cost;
	}	
}//edit_cost

void edit_time(UDN& cityNet)
{
	int beginCity, endCity;//��ʼ���к�����յ���к���
	int time;//ʱ��
	cityNet.outputCityList();//��������б�
	cout << "��������ʼ���к�Ŀ�ĳ��е����ִ��룬�м��Կո��������Χ(1--" << cityNet.cityNum << "):";
	cin >> beginCity >> endCity;//������ʼ���к��յ���еĴ��롣
	beginCity--; endCity--;//��������

	if (!((0 <= beginCity && beginCity < cityNet.cityNum) && (0 <= endCity && endCity < cityNet.cityNum) && beginCity != endCity))
	{
		cout << "������!!!  ����������ֺ�������1-" << cityNet.cityNum << "֮�䣬�������в������!!" << endl;
	}
	else
	{
		cout << "���������ؼ�����ʱ�䣺";
		cin >> time;
		cityNet.arcs[beginCity][endCity].time = cityNet.arcs[endCity][beginCity].time = time;
	}
}//edit_time

int main()
{
	UDN cityNet;//������ͨ��
	while (Order)
	{
		menu();
		action(cityNet);
	}
}