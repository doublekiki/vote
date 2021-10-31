#include <bits/stdc++.h>
#define awards 10  //ͶƱ��Ŀ����
#define student_num  40  //ѧ������
using namespace std;
map<string,int> student_name_num;
map<int,string> student_num_name;
struct student_information
{
    int rank[awards+1];
    string name;   //ѧ������
    int number;  //ѧ��ѧ��
    int vote_person[awards+1]={};   //ÿ������ֱ�Ͷ��˭
    int voted_num[awards+1]={};    //ÿ�����Ͷ����Ŀ
}student[student_num+1];
void init()
{
    ifstream putin_student_information("studentinformation.txt");
    for(int i=1;i<=student_num;i++)
    {
        putin_student_information>>student[i].number;
        putin_student_information>>student[i].name;
        student_num_name[student[i].number]=student[i].name;
        student_name_num[student[i].name]=student[i].number;   //��map�ͽ�ѧ��������ѧ�Ž��ж�Ӧ
        for(int j=1;j<=awards;j++)
        {
            student[i].rank[j]=student[i].number;
        }
    }
}
void vote()
{
    int filein_num;
    cout<<"��ѡ���������뷽ʽ\n";
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
        printf("���ǵ�%d������",i);
        for(int j=1;j<=awards;j++)
        {
            int temporary;
            printf("���ǵ�%d��ҪͶƱ����Ŀ",j);
            cin>>temporary;
            if(temporary==-1)
            {
                cout<<"���������Ѿ���Ȩ��\n";
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