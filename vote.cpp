#include <bits/stdc++.h>
#define awards 10  //投票项目个数
#define student_num  40  //学生总数
using namespace std;
map<string,int> student_name_num;
map<int,string> student_num_name;
struct student_information
{
    int rank[awards+1];
    string name;   //学生姓名
    int number;  //学生学号
    int vote_person[awards+1]={};   //每个奖项分别投的谁
    int voted_num[awards+1]={};    //每个奖项被投的数目
}student[student_num+1];
void init()
{
    ifstream putin_student_information("studentinformation.txt");
    for(int i=1;i<=student_num;i++)
    {
        putin_student_information>>student[i].number;
        putin_student_information>>student[i].name;
        student_num_name[student[i].number]=student[i].name;
        student_name_num[student[i].name]=student[i].number;   //用map型将学生姓名与学号进行对应
        for(int j=1;j<=awards;j++)
        {
            student[i].rank[j]=student[i].number;
        }
    }
}
void vote()
{
    int filein_num;
    cout<<"请选择数据输入方式\n";
    cin>>filein_num;
    for(int i=1;i<=filein_num;i++)
    {
        ifstream putin_vote("voteinformation.txt");
        for(int j=1;j<=awards;j++)
        {
            int temporary;
            putin_vote>>temporary;
            if(temporary==-1)
            {
                break;
            }
            else
            {
                student[i].vote_person[j]=temporary;
                student[temporary].voted_num[j]++;
            }
        }
    }
    for(int i=filein_num+1;i<=student_num;i++)
    {
        printf("这是第%d组数据",i);
        for(int j=1;j<=awards;j++)
        {
            int temporary;
            printf("这是第%d个要投票的项目",j);
            cin>>temporary;
            if(temporary==-1)
            {
                cout<<"这组数据已经弃权！\n";
                break;
            }
            else
            {
                student[i].vote_person[j]=temporary;
                student[temporary].voted_num[j]++;
            }
        }
    }
}
void sort_vote()
{
    for(int i=1;i<=student_num;i++)
    {
        for(int j=1;j<=awards;j++)
        {
            bool ki=true;
            for(int k=2;k<=awards;j++)
            {
                if(student[i].voted_num[k]>=student[i].voted_num[k-1])
                {
                    swap(student[i].voted_num[k],student[i].voted_num[k-1]);
                    swap(student[i].rank[k],student[i].rank[k-1]);
                    ki=false;
                }
            }
            if(ki)
            {
                break;
            }
        }
    }
}
void put_out()
{
    ofstream putout("putout.txt");
    for(int j=1;j<=awards;j++)
    {
        for(int i=1;i<=student_num;i++)
        {
            putout<<student[i].rank[j]<<" "<<student[i].voted_num[j]<<"     ";
        }
        putout<<endl;
    }
}
int main()
{
    init();
    vote();
    sort_vote();
    put_out();
}