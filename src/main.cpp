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

const int INF=65535;	//极大值
const int MAX_CITY_NUM=23;	//最大城市数量

int Order = 1;//功能选择标识

//UDN****************************************************************************************
typedef struct {
	int time;	//火车时间
	int cost;	//火车费用
}Arc;//弧

class UDN {
public:
	void Floyd(int);//Floyd
	void printPath(int, int);//打印路径
	Arc sumPath(int, int);//计算总花费
	UDN();//初始化城市列表和邻接矩阵
	void outputCityList();//输出城市列表
	
	
	vector<string> city;//城市列表
	Arc arcs[MAX_CITY_NUM][MAX_CITY_NUM];//带权邻接矩阵
	Arc sum;//用来返回总花费的值
	int path[MAX_CITY_NUM][MAX_CITY_NUM];//Path矩阵
	int cityNum;//城市总数
};//无向网

UDN::UDN() :cityNum(12)
{
	city = { "成都", "石家庄", "郑州", "武汉", "贵阳", "长沙", "广州", "南宁", "济南", "北京", "天津", "上海" };//初始化城市列表
	for (int i = 0; i < MAX_CITY_NUM; i++)//初始化带权邻接矩阵
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

	//设置带权邻接矩阵
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

//输出城市列表
void UDN::outputCityList()
{
	cout << "城市及其代码" << endl;
	cout << "*********************************************************" << endl;
	for (int i = 0; i < cityNum; i++)
	{
		cout << i + 1 << '.' << city[i] << "    ";
	}
	cout << endl<<"*********************************************************" << endl;
}//UDN::outputCityList

//Floyd
//对于每个顶点v，和任一顶点对(i,j)，i≠j，v≠i, v≠j
//如果 A[i][j] > A[i][v]+A[v][j]，则将 A[i][j] 更新为 A[i][v]+A[v][j] 的值
//并且将Path[i][j]改为v
void UDN::Floyd(int flag)//flag用来根据功能选择相应的矩阵建立Path
{
	int A[MAX_CITY_NUM][MAX_CITY_NUM];
	for (int i = 0; i < cityNum; i++) {
		for (int j = 0; j < cityNum; j++) {
			//初始化矩阵A和path
			if (flag == 2)
			{
				A[i][j] = arcs[i][j].time;
			}
			else if (flag == 3)
			{
				A[i][j] = arcs[i][j].cost;
			}
			path[i][j] = -1;	//初始化矩阵p,置-1.
		}
	}//for

	for (int v = 0; v < cityNum; v++) //v为逐步选择的中间结点
	{ 
		for (int i = 0; i < cityNum; i++) //
		{ 
			for (int j = 0; j < cityNum; j++)
			{

				if (A[i][j] > A[i][v] + A[v][j])
				{
					A[i][j] = A[i][v] + A[v][j];
					path[i][j] = v;//若i经过v到j比i直达j距离更短，则令A[i][j]=A[i][v]+A[v][j]
				}//if
			}			
		}
	}//for
}//ShortestPath_ Floyd

//打印路径
void UDN::printPath(int beginV, int endV)
{
	if (path[beginV][endV] == -1) 
	{
		cout << city[endV] << "    ";//输出路径，不包含首顶点
	}
	else
	{
		int mid = path[beginV][endV];//mid为中间节点
		printPath(beginV, mid);
		printPath(mid, endV);
	}
}//UDN::printPath

//计算路径权值
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

//网*********************************************************************************************************************
void menu();				//主菜单
void action(UDN&);			//功能选择
void chooseTime(UDN&);		//选择时间最短路线
void chooseCost(UDN&);		//选择消费最少路线
void administrator(UDN&);	//编辑和修改交通网
void add_city(UDN&);
void edit_cost(UDN&);
void edit_time(UDN&);

void menu()
{
	cout << "**********************交通咨询系统**********************" << endl;
	cout << "*                         主菜单                       *" << endl;
	cout << "*                1.查看城市                            *" << endl;
	cout << "*                2.选择最短时间路线                    *" << endl;
	cout << "*                3.选择最节约费用路线                  *" << endl;
	cout << "*                4.管理员程序                          *" << endl;
	cout << "*                0.退出程序                            *" << endl;
	cout << "********************************************************" << endl;
	cout << endl;	
}//menu

//选择功能执行
void action(UDN& cityNet)
{
	cout << "请选择（0-4）.....  ";//输入选择菜单
	cin >> Order;
	switch (Order) {
	case 1:
		cityNet.outputCityList();//输出交通网中的城市列表
		break;
	case 2:
		chooseTime(cityNet);//选择时间最短路线
		break;
	case 3:
		chooseCost(cityNet);//选择消费最少路线
		break;
	case 4:
		administrator(cityNet);//编辑和修改交通网
		break;
	case 0:
		system("pause");
		break;
	default: 
		cout << endl << "输入有误!!!请在0-4之间选择!!" << endl;   //输入出错
	}
}//action

//选择时间最短路线
void chooseTime(UDN& cityNet)
{
	int beginCity, endCity;//起始成市号码和终点城市号码
	cityNet.outputCityList();//输出城市列表
	cout << "请输入起始城市和目的城市的数字代码，中间以空格隔开，范围(1--" << cityNet.cityNum << "):";
	cin >> beginCity >> endCity;//输入起始城市和终点城市的代码
	beginCity--; endCity--;//处理输入

	if (!((0 <= beginCity && beginCity < cityNet.cityNum) && (0 <= endCity && endCity < cityNet.cityNum) && beginCity != endCity))
	{
		cout << "错误!!!输入城市数字号码请在1-" << cityNet.cityNum << "之间，且两城市不能相等!!" << endl << endl;
	}
	else 
	{
		cityNet.Floyd(Order);//调用Floyed函数
		cout << cityNet.city[beginCity] << "    ";//显示起始城市
		cityNet.printPath(beginCity, endCity);//调用printPath函数，显示最短路径经过的城市
		cout << endl;

		cityNet.sum = { 0,0 };//计算总花费
		Arc sum = cityNet.sumPath(beginCity, endCity);
		if (sum.time == INF)
		{
			cout << "两地间还没有线路通过" << endl;
		}
		else
		{
			cout << "坐火车花费的金额是" << sum.cost << "元" << endl;
			cout << "坐火车需要的时间是" << sum.time << "小时" << endl;
		}
	}
}//chooseTime

//选择消费最少路线
void chooseCost(UDN& cityNet)
{
	int beginCity, endCity;//起始成市号码和终点城市号码
	cityNet.outputCityList();//输出城市列表
	cout << "请输入起始城市和目的城市的数字代码，中间以空格隔开，范围(1--" << cityNet.cityNum << "):";
	cin >> beginCity >> endCity;//输入起始城市和终点城市的代码。
	beginCity--; endCity--;//处理输入

	if (!((0 <= beginCity && beginCity < cityNet.cityNum) && (0 <= endCity && endCity < cityNet.cityNum) && beginCity != endCity))
	{
		cout << "出错啦!!!  输入城市数字号码请在1-" << cityNet.cityNum << "之间，且两城市不能相等!!" << endl << endl;
	}
	else 
	{
		cityNet.Floyd(Order);//调用Floyed函数
		cout << cityNet.city[beginCity] << "    ";//显示起始城市
		cityNet.printPath(beginCity, endCity);//调用printPath函数，显示最短路径经过的城市
		cout << endl;

		cityNet.sum = { 0,0 };//计算总花费
		Arc sum = cityNet.sumPath(beginCity, endCity);
		if (sum.time == INF)
		{
			cout << "两地间还没有线路通过" << endl;
		}
		else
		{
			cout << "坐火车花费的金额是" << sum.cost << "元" << endl;
			cout << "坐火车需要的时间是" << sum.time << "小时" << endl;
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
		cout << "1:增加城市" << endl;
		cout << "2:添加或编辑火车费用" << endl;
		cout << "3:添加或编辑火车时间" << endl;
		cout << "0:返回主菜单" << endl;
		cout << "************************************************************" << endl;
		cout << "请选择:" << endl;
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
			cout << "选择出错！" << endl;
		}
	}	
}//administrator

void add_city(UDN& cityNet)
{
	string cityName;
	int flag=1;
	cout << "请输入你要增加的城市名：";
	cin >> cityName;
	for (auto& iter : cityNet.city)
	{
		if (cityName == iter)
		{
			cout << "添加失败！该城市已存在！" << endl;
			flag = 0;
			system("pause");
		}
	}
	if (flag)
	{
		cityNet.city.push_back(cityName);//添加到城市列表
		cityNet.cityNum++;//城市总数+1
	}
}//add_city

void edit_cost(UDN& cityNet)
{
	int beginCity, endCity;//起始成市号码和终点城市号码
	int cost;//路费
	cityNet.outputCityList();//输出城市列表
	cout << "请输入起始城市和目的城市的数字代码，中间以空格隔开，范围(1--" << cityNet.cityNum << "):";
	cin >> beginCity >> endCity;//输入起始城市和终点城市的代码。
	beginCity--; endCity--;//处理输入

	if (!((0 <= beginCity && beginCity < cityNet.cityNum) && (0 <= endCity && endCity < cityNet.cityNum) && beginCity != endCity))
	{
		cout << "出错啦!!!  输入城市数字号码请在1-" << cityNet.cityNum << "之间，且两城市不能相等!!" << endl;
	}
	else
	{
		cout << "请输入两地间所需路费：";
		cin >> cost;
		cityNet.arcs[beginCity][endCity].cost = cityNet.arcs[endCity][beginCity].cost = cost;
	}	
}//edit_cost

void edit_time(UDN& cityNet)
{
	int beginCity, endCity;//起始成市号码和终点城市号码
	int time;//时间
	cityNet.outputCityList();//输出城市列表
	cout << "请输入起始城市和目的城市的数字代码，中间以空格隔开，范围(1--" << cityNet.cityNum << "):";
	cin >> beginCity >> endCity;//输入起始城市和终点城市的代码。
	beginCity--; endCity--;//处理输入

	if (!((0 <= beginCity && beginCity < cityNet.cityNum) && (0 <= endCity && endCity < cityNet.cityNum) && beginCity != endCity))
	{
		cout << "出错啦!!!  输入城市数字号码请在1-" << cityNet.cityNum << "之间，且两城市不能相等!!" << endl;
	}
	else
	{
		cout << "请输入两地间所需时间：";
		cin >> time;
		cityNet.arcs[beginCity][endCity].time = cityNet.arcs[endCity][beginCity].time = time;
	}
}//edit_time

int main()
{
	UDN cityNet;//创建交通网
	while (Order)
	{
		menu();
		action(cityNet);
	}
}