#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>
#include <string>
#include <windows.h>

using namespace std;

struct student
{
    string name;
    int xuehao;
    int sorce;    //分数
    int cishu;    //被点的次数
    int queqin;   //缺勤的次数
};

enum banaji { J1 = 1, J2,J3, J4, J5, C1 ,MAX};     //方便记录有几个班级

//可以用结构体封装
student check[110][110] = 
{ 
    {{"李某",2000112471},{"王某",2000112472},{"刘某",2000112473},{"郭某",2000112474},{"何某",2000112475},{"吴某",2000112476},{"赵某",2000112477}},         //可汗大点兵
   {{"李某",2000112471},{"王某",2000112472},{"刘某",2000112473},{"郭某",2000112474},{"何某",2000112475},{"吴某",2000112476},{"赵某",2000112477}},
   { {"李某",2000112471},{"王某",2000112472},{"刘某",2000112473},{"郭某",2000112474},{"何某",2000112475},{"吴某",2000112476},{"赵某",2000112477}},   //可汗大点兵
{ {"李某",2000112471},{"王某",2000112472},{"刘某",2000112473},{"郭某",2000112474},{"何某",2000112475},{"吴某",2000112476},{"赵某",2000112477}},
{ {"李某",2000112471},{"王某",2000112472},{"刘某",2000112473},{"郭某",2000112474},{"何某",2000112475},{"吴某",2000112476},{"赵某",2000112477}},
{ {"李某",2000112471},{"王某",2000112472},{"刘某",2000112473},{"郭某",2000112474},{"何某",2000112475},{"吴某",2000112476},{"赵某",2000112477}},
{ {"李某",2000112471},{"王某",2000112472},{"刘某",2000112473},{"郭某",2000112474},{"何某",2000112475},{"吴某",2000112476},{"赵某",2000112477}},
{ {"李某",2000112471},{"王某",2000112472},{"刘某",2000112473},{"郭某",2000112474},{"何某",2000112475},{"吴某",2000112476},{"赵某",2000112477}}
};
int num[110] = { 7,7,7,7,7,7 };
string name[110] = { "计一","计二","计三","计四","计五","智一","智二"};
string classbh[110] = { " ","Ox3F12","Ox3F13","Ox3F14","Ox3F15","Ox3F16" ,"Ox3F17" ,"Ox3F18" };     //每个下标一一对应               //班级对应的编码                 

map<int, string> classbh_name;     //从编号下标找到名字
map<string, int> name_classbh;     //从名字找到编号下标                                                        //从老师指向班级


const int N = 13;
int year, week;                                                                      //打表打出学期
int lesson[N][N];    //存课表
bool checkclass[110];     //检查班级是否以及进入课表
bool checkstudent[110][110];

void start()
{
    int x;
    printf("此作业为课堂点名系统\n");
    printf("制作人员郭智超 李佩泽 王昕烨 刘永聪\n");
    printf("接下来我们以李佩泽，李老师为例子看看这个屎山代码如何运行,输入一开始\n");
    printf("////////////////////////////////////////////////////////////////////\n");
    printf("//                          _ooOoo_                               //\n");
    printf("//                         o8888888o                              //\n");
    printf("//                         88' . '88                              //\n");
    printf("//                         (| ^_^ |)                              //\n");
    printf("//                         O\\  =  /O                              //\n");
    printf("//                      ____/`---'\\____                           //\n");
    printf("//                    .'  \\|     |//  `.                         //\n");
    printf("//                   /  \\|||  :  |||//  \\                        //\n");
    printf("//                  /  _||||| -:- |||||-  \\                       //\n");
    printf("//                  |   | \\\\  -  /// |   |                       //\n");
    printf("//                  | \\_|  ''\\---/''  |   |                       //\n");
    printf("//                  \\  .-\\__  `-`  ___/-. /                       //\n");
    printf("//                ___`. .'  /--.--\\  `. . ___                     //\n");
    printf("//              .\"\" '<  `.___\\<|>/___.'  >'\".                  //\n");
    printf("//            | | :  `- \\\`.;`\\ _ /`;.`/ - ` : | |                 //\n");
    printf("//            \\  \\ `-.   \\_ __\\ /__ _/   .-` /  /                 //\n");
    printf("//      ========`-.____`-.___\\_____/___.-`____.-'========         //\n");
    printf("//                           `=---='                              //\n");
    printf("//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //\n");
    printf("//             佛祖保佑       永不宕机      永无BUG               //\n");
    printf("////////////////////////////////////////////////////////////////////\n");


    scanf("%d", &x);
    system("cls");
}


void againstart()
{
    int numa = 0;
    for (auto x:name)
    {
        if (x[0])
        {
            numa++;
            name_classbh[x] = numa;
            cout << numa << "班级名字" << " " << x << " " << "班级对应的课程编号" << classbh[numa] << "\n";

            cout << "学生的名字以及学号\n";
            int numaa = -1;
            for (auto a : check[numa])
            {
                numaa++;
                if (checkstudent[numa][numaa] == false) continue;
                if (a.name[0])
                    cout << "学生名字" << a.name << " " << "学号" << a.xuehao << '\n';
                else break; 
            }
        
               
            cout << "\n";
        }
        else break;
    }
    
}

void Print()
{
    printf("你现在看到的是第%d年%d周的课表\n\n",year,week);
    printf("         星期一 星期二 星期三 星期四 星期五 星期六 星期日\n");
    for (int i = 0; i < 13; i++)
    {
        printf("第%-2d节     ", i+1);
        for (int j = 0; j < 7; j++)
        {
            if (lesson[i][j] != 0)  cout << name[lesson[i][j] - 1] << "   ";
            else cout << "无课   ";
        }
        printf("\n");
        printf("课程编号    ");
        for (int j = 0; j < 7; j++)
        {  
            if (lesson[i][j] != 0)  cout << classbh[lesson[i][j]]<<' ';
            else cout << "       ";
        }
        printf("\n");
        printf("\n");
    }
}

void Inint()
{
   // printf("因为李老师在1——19周的课是一样的，因此只输出一周的课表\n");
    memset(lesson, 0, sizeof lesson);
    memset(checkclass, false, sizeof checkclass);
    int go=0;
    int num = rand();
    while(1)
    {
        bool checka = false;
        int arr = 0;
        arr++;
        int r = (num + go*(num%4+arr)) % 13 + 1;
        int c = ((num % 7) + 1+go)%7;
        for (int i = 0; i < 3; i++)
        {
            if (lesson[r + i][c] == 0 && r + i <= 13)
            {
                lesson[r + i][c] = go;
                checkclass[go] = true;
            }
           else if(lesson[r + i][c] == 1)
           {
               checka = true;
               break;
           }
        }
        if (checka) continue;
        go++;
        if (go == MAX) break;
    }
    
    Print();

    int x;
    printf("查看完毕请输入一\n");
    scanf("%d", &x);
    system("cls");
}



void classyear()
{
    printf("请输入你要查询的学期,还有周\n");
    scanf("%d %d", &year,&week);  
}

int classweek()
{
    int x;
    while (1)
    {
        printf("请输入你要查询的周1-19\n");
        scanf("%d", &x);
        if (x >= 1 && x <= 19)
        {
            break;
        }
        else printf("读入错误的周，只有1到19周读入\n");
    }
    return x;
}


void add()   
{
    printf("原课表\n");
    Print();

    string cname;  //班级的名字
    while (1)
    {
        printf("因为李老师讨厌加课因此你添加的课只能在其中一周上😡\n");
        printf("为了李老师方便我们添加课的标准是在其他课的末尾查上一节\n");
        printf("请分别输入输入你要添加的班级名字\n");
        cin >> cname;      
        cout << cname<< name_classbh[cname]<<'\n';
        if (checkclass[name_classbh[cname]])
        {
            Print();
            printf("该班级以及存在，请重新输入\n");
            continue;
        }
        else break;
    }
   
    printf("现在的课表\n");
    int go = 0;
    for (int i = 0;i < 13; i++)
    {

        for (int j = 0; j < 7; j++)
        {

            if (lesson[i][j] && lesson[i + 1][j] == 0 && i + 1 != 13)
            {
                lesson[i + 1][j] = name_classbh[cname];
                go++;
            }
            if (go == 3) break;
        }
        if (i == 122 && go < 3)
        {
            for (int z = go; z <= 3; z++)
                lesson[1 + z][1] = name_classbh[cname];
        }
        if (go == 3) break;
    }

    Print();
}

void delet()
{
     string cname;  //班级的名字
     printf("原课表\n");
     Print();
     printf("因为李老师喜欢不加课因此你可以多删几次（滑稽当然我没有设置这个功能）\n");
     printf("请分别输入输入你要删掉的班级名字\n");
     cin >> cname;
     cout << cname << name_classbh[cname] << '\n';
     checkclass[name_classbh[cname]] = false;

     printf("现在的课表\n");
    
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (checkclass[lesson[i][j]] == false) lesson[i][j] = 0;
        } 
    }

    Print();
}

void change()
{
    int x;
    printf("李老师很头疼有的班级想要李老师给他讲课，或者有的班级不想上了你能帮帮他吗\n");
    printf("输入0为删除一个班，输入1为插入一个班,输入其他为退出\n");
    scanf("%d", &x);
    if (x != 0 && x != 1) return;
    if (x == 1) add();
    else delet();
}

void menu()
{
    printf("########################################\n");
    printf("###1.修改课表#####2.录入班级信息########\n");
    printf("###3.打印课表#####4.点名################\n");
    printf("###5.成绩汇总#####0.退出################\n");
    printf("########################################\n");
    printf("########################################\n");
}

void menu3()
{
    printf("李老师很生气，为什么我教课还要自己录入课堂人的资料，不过谁让李老师是个小牛马呢\n");
    printf("########################\n");
    printf("###1.增加学生信息#######\n");
    printf("###2.删除学生信息#######\n");
    printf("########################\n");
    printf("########################\n");
    printf("########################\n");


}

void addStudent()
{
    struct student New;
    printf("李老师听说有个学生很聪明想要把他加到自己的班上\n");
    printf("请选择你要添加的班，以及该学生的姓名，学号\n");
    string cname;
    cin >> cname >> New.name >> New.xuehao;
    if (name_classbh[cname] == 0)
    {
        printf("没有这个班级，李老师生气了所以不让你改了，怒怒怒\n");
        return;
    }
    check[ name_classbh[cname] ][ num[name_classbh[cname]-1]++ ] = New;
}

void deletstudent()
{
    printf("李老师感觉这个学生天天玩二字游戏已经废了想要把他踢出去\n");
    printf("请选择你要删除的班的名字以及学生的姓名\n");
    string cname,stname;
    cin >> cname >> stname;   //可以复杂度，但是空间复杂度增长有点多
    int x = name_classbh[cname];
    cout << x;
    for (int i = 0; i < num[x - 1]; i++)   //可以设置一个bool变量，看看我之后懒不懒吧
    { 
        if (check[x][i].name == stname)
        {
            printf("傻逼的版本\n");
            cout << x << i;
            checkstudent[x][i] = false;
            break;
        }
        
    }
}

void readIn()
{
    againstart();
    menu3();
    int x;
    scanf("%d", &x);
    if (x == 1) addStudent();
    else deletstudent();
    againstart();
}


void Readstudent(int x)
{
    cout << name[x] << '\n';
    int numa = 1;
    for (auto a:check[x])
    {
        if (a.name[0]) cout << numa << a.name << " " << a.xuehao<<' '<<"分数:"<< a.sorce << '\n';
        else break;

            numa++;
    }
}

void menu4()
{
    printf("现在是课堂时间李老师可以一直看的这个课表，有人表现好李老师可以给他加分\n");
    printf("######1.随机点名######################\n");
    printf("######2.主动回答#####################\n");
    printf("######3.课堂结束退出#######################\n");
}

void Solve(int c)
{
    for (int i = 1; i < num[c]; i++)
    {
        check[c][i].queqin = check[c][i].cishu / 2;
    }
}

void sjdm(int c)
{
    printf("\n别看李老师说是随机点名，其实李老师也有自己的小九九，李老师希望雨露均沾，因此通过点名次数的多少来随机点名\n");
    check[c][2].cishu = 2;
    for (int i = 1; i < num[c]; i++)          //用下标的坏处来了，只能用冒泡
    {
        for (int j = i; j < num[c]; j++)
        {
            if (check[c][i].cishu > check[c][j].cishu)
            {
                swap(check[c][i],check[c][j]);
                swap(checkstudent[c][i], checkstudent[c][j]);
            }
        }
    }
    printf("点名前的次数情况\n");
    for (int i=0;i<num[c];i++)
    {
        if (checkstudent[c][i]) cout << check[c][i].name <<check[c][i].cishu << " ";
    }
    printf("\n输入你要点的人数\n");
    int x;
    scanf("%d", &x);
    for (int i = 0; i < x; i++)
    {
        if (checkstudent[c][i])
        {
            cout << check[c][i].name << check[c][i].cishu << " ";
            check[c][i].cishu++;
        }
    }
    printf("\n");
    printf("点名后的情况\n");
    for (int i = 0; i < num[c]; i++)
    {
        if (checkstudent[c][i]) cout << check[c][i].name << check[c][i].cishu << " ";
    }
    printf("\n");
    Solve(c);
    return;
}

void jl(int c)     //c代表当前班的
{
    printf("因为李老师的记性不好因此我们先打印一下学生的名字\n");
    Readstudent(c);
    printf("李老师的课居然真的有人听，现在有一个爱学习的童鞋回答了问题，李老师专门为他设置了奖励程序\n");
    printf("请你输入爱学习的同学的学号\n");
    int x;
    scanf("%d", &x);
    int weizhi=-1;

    for (int i = 0; i < num[c]; i++)
    {
        if (checkstudent[c][i])
        {
            if (check[c][i].xuehao == x)
            {
                weizhi = i;
                break;
            }
        }
    }
    if (weizhi == -1) printf("查无此人\n");
    else
    {
        check[c][weizhi].sorce++;
    }
    Readstudent(c);
}

void rollCall()
{
   
    printf("终于到了李老师的上课时间，李老师年轻的时候特别喜欢翘课因此他成为了小牛马，所以他不想让他的学生翘课也成为小牛马，所以他要点名！\n");
    printf("请输入点名的日期（既要输入年还要输入周）\n");
    scanf("%d %d", &year,&week);
    Print();
    int x, y;
    while (1)
    {
        printf("输入李老师在上课的是那一节课！！！（如输入1 1）\n");
        scanf("%d %d", &x, &y);
        if (lesson[x - 1][y - 1]-1>=0) break;
        else    printf("这节课没有人李老师不需要点名\n");
    }

    Readstudent(lesson[x - 1][y - 1]-1);
    
    menu4();
    int a;
    scanf("%d", &a);
    while (a != 3)
    {
        if (a == 1) sjdm(lesson[x-1][y-1]-1);         //随机点名
        if (a == 2) jl(lesson[x-1][y-1]-1);           //记录
        menu4();
        scanf("%d", &a);
    }
    
}

void menu2()
{
    printf("李老师很辛苦想看看一年什么时候才能规划一次说走就走的旅行你能帮他看看吗?\n");
    printf("########################\n");
    printf("###1.打印整年的课表#####\n");
    printf("###2.打印一周的课表#####\n");
    printf("########################\n");
    printf("########################\n");
    printf("########################\n");  
}

void allPrint()
{
    menu2();

    int x;
    scanf("%d", &x);

    if (x == 1)
    {
        printf("请输入你想打印的年\n");
        scanf("%d", &year);
        for (int i = 1; i <= 12; i++)
        {
            week = i;
            Inint();
        }
    }
    else
    {
        printf("请输入你想打印的年以及周\n");
        scanf("%d %d", &year, &week);
        Inint();
    }
}

void menu5()
{
    printf("######1.按照缺勤排序###########################\n");
    printf("######2.按照课上回答问题次数排序###############\n");
    printf("######0.退出###################################\n");
}

void recall()
{
    printf("到了登记平时分的时候了，李老师准备看看学生的点名，缺勤以及课上回答问题的情况，来决定捞不捞他们(李老师真是好)\n");
    printf("请输入你要查看的班级名字\n");
    string cname;
    cin >> cname;
    int c=name_classbh[cname]-1;
    printf("总成绩如下\n");
    for (int i = 0; i < num[c]; i++)
    {
     if(checkstudent[c][i])   cout << check[c][i].name << " 被点名次数" << check[c][i].cishu << " 回答问题次数" << check[c][i].sorce << " 缺勤次数" << check[c][i].queqin << '\n';
    }
    printf("\n");
    menu5();
    int x;
    scanf("%d", &x);
    while (x)
    {
        if (x == 1)
        {
            for (int i = 1; i < num[c]; i++)          //用下标的坏处来了，只能用冒泡
            {
                for (int j = i; j < num[c]; j++)
                {
                    if (check[c][i].queqin > check[c][j].queqin)
                    {
                        swap(check[c][i], check[c][j]);
                        swap(checkstudent[c][i], checkstudent[c][j]);
                    }
                }
            }

            for (int i = 0; i < num[c]; i++)
            {
                if (checkstudent[c][i])   cout << check[c][i].name << " 缺勤次数:"<<check[c][i].queqin<< ' ';
            }
        }
        else 
        {
            for (int i = 1; i < num[c]; i++)          //用下标的坏处来了，只能用冒泡
            {
                for (int j = i; j < num[c]; j++)
                {
                    if (check[c][i].sorce < check[c][j].sorce)
                    {
                        swap(check[c][i], check[c][j]);
                        swap(checkstudent[c][i], checkstudent[c][j]);
                    }
                }
            }

            for (int i = 0; i < num[c]; i++)
            {
                if (checkstudent[c][i])   cout << check[c][i].name << " 主动回答问题次数:" << check[c][i].sorce << ' ';
            }
         
        }
        printf("\n");
        menu5();
        scanf("%d", &x);
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    memset(checkstudent, true, sizeof checkstudent);
    start();                                             //介绍人员

    againstart();                                        //介绍班级，以及他对应的课程代码，还有教的课程

   int x;
    printf("查看完毕请输入一\n");
    scanf("%d", &x);
    system("cls");

    classyear();                                          //要查询的课表

    Inint();                                              //初始化  已经确定的一个学期的课表！！！

    
        menu();
        cin >> x;
       
        while (x)
        {
            if (x == 1)      change();
            else if (x == 2) readIn();
            else if (x == 3) allPrint();
            else if (x == 4) rollCall();
            else recall();   //汇总
            menu();
            cin >> x;
        }
        system("cls");
        printf("李老师的点名系统终于结束了和屎一样的代码\n");
        for (int i = 0; i < 20; i++)
            printf("感谢观看\n");
        return 0;
}

