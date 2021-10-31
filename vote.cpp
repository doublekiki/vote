#include <bits/stdc++.h>
#define awards 10  //投票项目个数
#define student_num  40  //学生总数
using namespace std;
map<string,int> student_name_num;
map<int,string> student_num_name;
int vote_result_voted[awards+1][student_num+1];
int vote_result_number[awards+1][student_num+1];
void swap(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
}
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
    }
}
void vote()
{
    int filein_num;
    cout<<"请选择数据输入方式\n";
    cin>>filein_num;
    ifstream putin_vote("votein.txt");
    for(int i=1;i<=filein_num;i++)
    {
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
    for(int j=1;j<=awards;j++)
    {
        for(int i=1;i<=student_num;i++)
        {
            vote_result_voted[j][i]=student[i].voted_num[j];
            vote_result_number[j][i]=i;
        }
    }
}
void sort_vote()
{
    for(int i=1;i<=awards;i++)
    {
        for(int j=1;j<=student_num;j++)
        {
            bool ki=true;
            for(int k=2;k<=student_num;k++)
            {
                if(vote_result_voted[i][k-1]<=vote_result_voted[i][k])
                {
                    swap(vote_result_voted[i][k-1],vote_result_voted[i][k]);
                    swap(vote_result_number[i][k-1],vote_result_number[i][k]);
                    ki=false;
                }
            }
        }
    }
}
void put_out()
{
    ofstream putout("putout.txt");
    for(int j=1;j<=awards;j++)
    {
        putout<<"这是第"<<j<<"个投票项目\n";
        for(int i=1;i<=student_num;i++)
        {
            putout<<"第"<<i<<"名是";
            putout<<student_num_name[vote_result_number[j][i]]<<"，被投了"<<vote_result_voted[j][i]<<"票   ";
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