#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
using namespace std;
const int DestinationType_Max = 9 + 1;
const int DestinationNumber_Max = 66 + 1;
const int SumOfDestination = 181;
const int StationNumber_Max = 103 + 1;


class Coordinate
{
	friend void dataInput(Coordinate place[][DestinationNumber_Max]);
	friend void dataInput(Coordinate station[]);
private:
	double x;
	double y;
public:
	int Nearest (const Coordinate Station[]);
};

int Coordinate::Nearest(const Coordinate Station[]){
	int temp;
	int smallest = 1000000;
	for(int i = 0; i < StationNumber_Max; i++){
		if (sqrt(pow(this->x - Station[i].x , 2) + pow(this->y - Station[i].y , 2)) < smallest){
			temp = i;
		}
	}
	return temp;
}

string* BuildingName  = new string [DestinationType_Max];
Coordinate station[StationNumber_Max];
Coordinate place[DestinationType_Max][DestinationNumber_Max];

struct StationLocation
{
	string x;
	string y;
};

//global function
void dataInput(Coordinate place[][DestinationNumber_Max]);
void dataInput(Coordinate station[]);
void dataInput(StationLocation Location[]);


int main()
{
	Coordinate PlaceName[DestinationType_Max][DestinationNumber_Max];//存建築物經緯 
	dataInput(PlaceName);
	Coordinate Station[StationNumber_Max];//存站點經緯 
	dataInput(Station);
	StationLocation Location[StationNumber_Max];//存站點經緯度(for網址) 
	dataInput(Location);
	bool CorrectInput1 = false;//總共輸入四次數字
	bool CorrectInput2 = false;
	bool CorrectInput3 = false;
	bool CorrectInput4 = false;
	int FirstChoose = 0,SecondChoose = 0,ThirdChoose = 0,FourthChoose = 0;


	while(CorrectInput1 == false){
		cout << "請選擇出發地：" << endl;
			for(int i = 1; i < 10 ; i++){						//輸出建築物選項
				cout << i << "." << BuildingName[i][0] << "     ";
			if (i % 3 == 0) cout << endl;
		}
		cin >> FirstChoose;										//輸入出發地
		if (FirstChoose > DestinationType_Max)
		cout << "此選項不存在"<<endl;
		else{
			CorrectInput1 = true;
			break;
		}
	}
	while(CorrectInput2 == false){
		int temp_Number_Max;
		for(int i = 1; i < DestinationNumber_Max ; i++){
			if(BuildingName[FirstChoose][i] == '\0'){
				temp_Number_Max = i;
				break;
			}
		}
		cout << "請選擇出發地：" << endl;
		for(int j = 1;j < temp_Number_Max ; j++){
			cout << j << "." << BuildingName[FirstChoose][j] << "  ";
			if (j % 5 == 0) cout << endl;
		}
		cin >> SecondChoose;
		if (SecondChoose > temp_Number_Max)
			cout << "此選項不存在"<< endl;
		else {
			CorrectInput2 = true;
			break;
		}
	}
	while(CorrectInput3 == false){
		cout << "請選擇目的地：" << endl;
			for(int i = 1; i < 10 ; i++){						//輸出建築物選項
				cout << i << "." << BuildingName[i][0] << "   ";
			if (i % 3 == 0) cout << endl;
		}
		cin >> ThirdChoose;										//輸入目的地
		if (ThirdChoose > DestinationType_Max)
		cout << "此選項不存在" << endl;
		else {
			CorrectInput3 = true;
			break;
		}
	}
	while(CorrectInput4 == false){
		int temp_Number_Max;
		for(int i = 1; i < DestinationNumber_Max ; i++){
			if(BuildingName[ThirdChoose][i] == '\0'){
				temp_Number_Max = i ;
				break;
			}
		}
		cout << "請選擇目的地：" << endl;
		for(int j = 1;j < temp_Number_Max ; j++){
			cout << j << "." << BuildingName[ThirdChoose][j] <<"  ";
			if (j % 5 == 0) cout << endl;
		}
		cin >> FourthChoose;
		if (FourthChoose > temp_Number_Max)
			cout << "此選項不存在" << endl;
		else{
			 CorrectInput4 = true;
			 break;
		}
	}
	cout << place[FirstChoose][SecondChoose].Nearest( Station);
	cout << place[ThirdChoose][FourthChoose].Nearest( Station);
	return 0;
}


void dataInput(Coordinate place[][DestinationNumber_Max])
{
	fstream fin("Building-adjusted.txt", ios::in);//相對路徑
	int num1 = 0, num2 = 0;
	for(int i = 0; i < SumOfDestination; i++)
	{	
		fin >> num1 >> num2;
		fin >> BuildingName[num1][num2];
		fin >> place[num1][num2].x >> place[num1][num2].y;
		//cout << "(" << num1 << ", " << num2 << ") = (" << place[num1][num2].x << ", " << place[num1][num2].y << ")" << "\n"; 
	}
	fin.close();
}

void dataInput(Coordinate station[])
{
	fstream fin("Ubike-adjusted.txt", ios::in);
	for(int i = 1; i < StationNumber_Max; i++)
	{
		fin >> station[i].x >> station[i].y;
	}
	fin.close();
}

void dataInput(StationLocation location[])
{
	fstream fin("Ubike-original.txt", ios::in);
	for(int i = 1; i < StationNumber_Max; i++)
	{
		fin >> location[i].x >> location[i].y;
	}
	fin.close();
}
