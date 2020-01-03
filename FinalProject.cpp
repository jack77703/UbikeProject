#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <windows.h>
#include <assert.h>
#include <shellapi.h>
using namespace std;
const int DestinationType_Max = 9 + 1;
const int DestinationNumber_Max = 66 + 1;
const int SumOfDestination = 179;
const int StationNumber_Max = 103 + 1;
const int typeMax[DestinationType_Max] = {0, 6, 22, 58, 2, 3, 3, 10, 2, 64};

class Coordinate
{
    friend void dataInput(Coordinate place[][DestinationNumber_Max]);
    friend void dataInput(Coordinate station[]);
private:
    double x;
    double y;
public:
    string name;
    int Nearest (const Coordinate Station[]);
};

int Coordinate::Nearest(const Coordinate Station[])
{
    int temp = 0;
    double smallest = 100000000;
    for(int i = StationNumber_Max - 1; i > 0; i--)
    {
        double distance = sqrt(pow(this->x - Station[i].x, 2) + pow(this->y - Station[i].y , 2));
        if(distance < smallest)
        {
            smallest = distance;
            temp = i;
        }
    }
    return temp;
}


struct StationLocation
{
    string x;
    string y;
};

//global function
void dataInput(Coordinate place[][DestinationNumber_Max]);
void dataInput(Coordinate station[]);
void dataInput(StationLocation Location[]);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR lpCmd, int nShow)
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
    int FirstChoose = 0, SecondChoose = 0, ThirdChoose = 0, FourthChoose = 0;


    while(CorrectInput1 == false)
    {
        cout << "請選擇出發地：" << endl;//輸出建築物選項
        for(int i = 1; i < 10 ; i++)
        {
            cout << i << "." << PlaceName[i][0].name << "  ";
            if(i % 3 == 0)
                cout << endl;
        }
        cin >> FirstChoose;//輸入出發地
        if(FirstChoose > DestinationType_Max)
            cout << "此選項不存在" << endl;
        else
        {
            CorrectInput1 = true;
        }
    }
    while(CorrectInput2 == false)
    {
        cout << "請選擇出發地：" << endl;
        for(int j = 1; j <= typeMax[FirstChoose]; j++)
        {
            cout << j << "." << PlaceName[FirstChoose][j].name << "  ";
            if (j % 5 == 0) cout << endl;
        }
        cin >> SecondChoose;
        if(SecondChoose > typeMax[FirstChoose])
            cout << "此選項不存在" << endl;
        else
        {
            CorrectInput2 = true;
        }
    }
    while(CorrectInput3 == false)
    {
        cout << "請選擇目的地：" << endl;
        for(int i = 1; i < 10 ; i++)
        {
            cout << i << "." << PlaceName[i][0].name << "  ";
            if(i % 3 == 0)
                cout << endl;
        }
        cin >> ThirdChoose;
        if(ThirdChoose > DestinationType_Max)
            cout << "此選項不存在" << endl;
        else
        {
            CorrectInput3 = true;
        }
    }
    while(CorrectInput4 == false)
    {
        cout << "請選擇目的地：" << endl;
        for(int j = 1; j <= typeMax[ThirdChoose]; j++)
        {
            cout << j << "." << PlaceName[ThirdChoose][j].name << "  ";
            if (j % 5 == 0) cout << endl;
        }
        cin >> FourthChoose;
        if (FourthChoose > typeMax[ThirdChoose])
            cout << "此選項不存在" << endl;
        else
        {
            CorrectInput4 = true;
            break;
        }
    }
    if(FirstChoose == ThirdChoose && SecondChoose == FourthChoose)
	{
        cout << "輸入了相同的地方，請重新查詢。";
        return 0;
    }
        
    /*
    cout << PlaceName[FirstChoose][SecondChoose].Nearest(Station) ;
    cout << PlaceName[ThirdChoose][FourthChoose].Nearest(Station) ;
    */
    int from = PlaceName[FirstChoose][SecondChoose].Nearest(Station), to = PlaceName[ThirdChoose][FourthChoose].Nearest(Station);
    /*
    cout << Location[from].y << ", " << Location[from].x << "\n";
    cout << Location[to].y << ", " << Location[to].x << "\n";
    */
    
    string url = "https://www.google.com.tw/maps/dir/" + Location[from].y + "," + Location[from].x + "/" + Location[to].y + "," + Location[to].x + "/@25.0159828,121.5327861,17z/data=!3m1!4b1!4m10!4m9!1m3!2m2!1d121.53995!2d25.01761!1m3!2m2!1d121.52997!2d25.01411!3e2";

    char URL[url.length()] =  {0};
    for (int i = 0; i < url.length(); i++)
        URL[i] = url[i];
    
    HINSTANCE hRslt = ShellExecute(NULL, "open", URL, NULL, NULL, SW_SHOWNORMAL);
    assert(hRslt > (HINSTANCE)HINSTANCE_ERROR);
 
    return 0;
}

void dataInput(Coordinate place[][DestinationNumber_Max])
{
    fstream fin("Building-adjusted.txt", ios::in);//相對路徑 
    int num1 = 0, num2 = 0;
    for(int i = 0; i < SumOfDestination; i++)
    {
        fin >> num1 >> num2;
        fin >> place[num1][num2].name;
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
