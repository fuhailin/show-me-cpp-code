#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "glog/logging.h"

using namespace std;

//最大联系人数量，1000
const int max_num = 1000;

//定义联系人结构体
struct Contact_person {
    string name;          //姓名
    string address;       //住址
    string gender;        //如何使用枚举类型：男或者女
    int age;              //年龄
    string phone_number;  //联系电话
};

//应该有文件读取操作，将每次程序运行的数据写入文件中，保存联系人信息
//定义通讯录：联系人结构体的数组
struct Contact_person address_book[1000];

//当前联系人数量
int current_num = 0;

//菜单状态位
short int menu_state = 9;

//是否退出主程序变量
bool isRun = true;

//函数声明
void menu();
void show_menu();
void add_person();
void show_person();
void delete_person();
void find_person();
void revise_person();
void clear_person();
void exit_addressBook();
void writePersonArray(char filename[], Contact_person a[], int n);
int readPersonArray(char filename[], Contact_person a[], int nmax);

//主函数入口
int main() {
    char filename[] = "addressBook.txt";
    current_num = readPersonArray(filename, address_book, 1000);  //读入文件中的数据 ,获取联系人数量
    cout << current_num;
    while (isRun) {
        menu();
    }
    writePersonArray(filename, address_book, current_num);  //将数组写入文件
    return 0;
}

//***********************************************************************************//
//***********************************************************************************//
//********************************外部函数部分***************************************//

//显式菜单函数：在主函数中执行，输入相应的函数符号，运行功能程序
void menu() {
    menu_state = 9;  //重新设置状态位为9
    system("cls");   //执行控制台清屏指令
    show_menu();     //打印提示功能
    while (menu_state == 9) {
        LOG(INFO) << "请输入对应的功能键。";
        cin >> menu_state;  //输入相应的状态位，进入对应函数
        switch (menu_state) {
            case 1:
                add_person();
                break;
            case 2:
                show_person();
                break;
            case 3:
                delete_person();
                break;
            case 4:
                find_person();
                break;
            case 5:
                revise_person();
                break;
            case 6:
                clear_person();
                break;
            case 0:
                exit_addressBook();
                break;
            default:
                LOG(INFO) << "输入错误，请重新输入！！！";
                cout << "\n按任意键回到菜单页面";
                system("pause");
        }
    }
}

//打印菜单栏函数
void show_menu() {
    cout << "*****************************\n";
    cout << "*****************************\n";
    cout << "********1  添加联系人********\n";
    cout << "********2  显示联系人********\n";
    cout << "********3  删除联系人********\n";
    cout << "********4  查找联系人********\n";
    cout << "********5  修改联系人********\n";
    cout << "********6  清空联系人********\n";
    cout << "********0  退出通讯录********\n";
    cout << "*****************************\n";
    cout << "*****************************\n";
}

//添加联系人函数：用户输入联系人信息，封装成结构体后，添加至通讯录数组中
void add_person() {
    int n = current_num;                                    //定位需要添加联系人的位置
    current_num += 1;                                       //计数变量加一
    struct Contact_person *p_addPerson = &address_book[n];  //添加位置的结构体指针
    cout << "请输入联系人姓名：";
    cin >> (*p_addPerson).name;
    cout << "请输入联系人住址：";
    cin >> (*p_addPerson).address;
    cout << "请输入联系人性别：";
    cin >> (*p_addPerson).gender;
    cout << "请输入联系人年龄：";
    cin >> (*p_addPerson).age;
    cout << "请输入联系人电话：";
    cin >> (*p_addPerson).phone_number;
    cout << "输入完成，您添加的联系人信息显式如下：\n";
    cout << "姓名：" << (*p_addPerson).name << "  "
         << "住址：" << (*p_addPerson).address;
    cout << "  性别：" << (*p_addPerson).gender << "  "
         << "年龄：" << (*p_addPerson).age;
    cout << "  电话：" << (*p_addPerson).phone_number;
    cout << "\n按任意键退回主菜单。";
    system("pause");
}

//显式联系人函数：输出所有联系人信息，使用列表循环
void show_person() {
    cout << "所有的联系人信息显式如下：\n";
    int i = 0;
    for (i = 0; i < current_num; i++) {
        struct Contact_person *p_addPerson = &address_book[i];  //添加位置的结构体指针
        cout << "姓名：" << (*p_addPerson).name << "  "
             << "住址：" << (*p_addPerson).address;
        cout << "  性别：" << (*p_addPerson).gender << "  "
             << "年龄：" << (*p_addPerson).age;
        cout << "  电话：" << (*p_addPerson).phone_number << endl;
    }
    cout << "\n按任意键退回主菜单。";
    system("pause");
}

//删除联系人函数：删除某一个联系人，联系人数量减一
void delete_person() {
    string person_name = "";
    cout << "请输入联系人姓名：";
    cin >> person_name;
    int i = 0;
    for (i = 0; i < current_num; i++) {
        if (person_name == address_book[i].name) {
            for (int j = i; j < current_num - 1; j++) {
                address_book[j] = address_book[j + 1];
            }
            address_book[current_num] = {};
            current_num -= 1;
            break;
        }
    }
    if (i >= current_num) {
        cout << "查无此人！！！";
    }
    cout << "\n按任意键退回主菜单。";
    system("pause");
}

//查找联系人函数：查找某个联系人，返回信息
void find_person() {
    string person_name = "";
    cout << "请输入联系人姓名：";
    cin >> person_name;
    int i = 0;
    for (i = 0; i < current_num; i++) {
        if (person_name == address_book[i].name) {
            struct Contact_person *p_addPerson = &address_book[i];  //添加位置的结构体指针
            cout << "您查找的联系人信息显式如下：\n";
            cout << "姓名：" << (*p_addPerson).name << "  "
                 << "住址：" << (*p_addPerson).address;
            cout << "  性别：" << (*p_addPerson).gender << "  "
                 << "年龄：" << (*p_addPerson).age;
            cout << "  电话：" << (*p_addPerson).phone_number;
            break;  //默认没有同姓名的联系人
        }
    }
    if (i >= current_num) {
        cout << "查无此人！！！";
    }
    cout << "\n按任意键退回主菜单。";
    system("pause");
}

//修改联系人函数：用户输入信息，修改对应的联系人信息
void revise_person() {
    string person_name = "";
    cout << "请输入联系人姓名：";
    cin >> person_name;
    int i = 0;
    for (i = 0; i < current_num; i++) {
        if (person_name == address_book[i].name) {
            struct Contact_person *p_addPerson = &address_book[i];  //添加位置的结构体指针
            cout << "现在修改联系人信息\n";
            cout << "请输入联系人姓名：";
            cin >> (*p_addPerson).name;
            cout << "请输入联系人住址：";
            cin >> (*p_addPerson).address;
            cout << "请输入联系人性别：";
            cin >> (*p_addPerson).gender;
            cout << "请输入联系人年龄：";
            cin >> (*p_addPerson).age;
            cout << "请输入联系人电话：";
            cin >> (*p_addPerson).phone_number;
            cout << "输入完成，您添加的联系人信息显式如下：\n";
            cout << "姓名：" << (*p_addPerson).name << "  "
                 << "住址：" << (*p_addPerson).address;
            cout << "  性别：" << (*p_addPerson).gender << "  "
                 << "年龄：" << (*p_addPerson).age;
            cout << "  电话：" << (*p_addPerson).phone_number;
            break;
        }
    }
    if (i >= current_num) {
        cout << "查无此人！！！";
    }
    cout << "\n按任意键退回主菜单。";
    system("pause");
}

//清空联系人函数：清空联系人数组，
void clear_person() {
    for (int i = 0; i < current_num; i++) {
        address_book[i] = {};
    }
    current_num = 0;
    cout << "联系人列表已清空。";
    cout << "\n按任意键退回主菜单。";
    system("pause");
}

//退出通讯录函数，退出主程序
void exit_addressBook() {
    isRun = false;
}

//将数组写入txt文件函数
// n 为数组 a 的元素个数，filename 为写入的文件名
void writePersonArray(char filename[], Contact_person a[], int n) {
    int count = 0;
    ofstream out;
    out.open(filename);
    if (!out.is_open()) {
        LOG(ERROR) << "Error:file open fail.";
        exit(1);
    } else {
        for (count = 0; count < n; count++) {
            out << a[count].name << " " << a[count].address << " " << a[count].gender << " "
                << a[count].age << " " << a[count].phone_number << endl;
        }
        out.close();
    }
}

//从txt文件读入数组函数
// 最多从 filename 文件中读取 nmax 条学生信息，并保存到数组 a。该函数返回实际读取的记录的条数。
int readPersonArray(char filename[], Contact_person address_book[], int nmax) {
    ifstream in;
    in.open(filename, fstream::app);
    int count = 0;
    if (!in.is_open()) {
        LOG(ERROR) << "Error: open file fail!!!";
        exit(1);
    }
    while (!in.eof() && count < nmax) {
        in >> address_book[count].name >> address_book[count].address >> address_book[count].gender >> address_book[count].age >> address_book[count].phone_number;
        count++;
    }
    count--;  //eof()方法当读到文件结尾时，还会在进行一次读取操作，除去多计算的元素，暂时没想到更好的解决方案
    in.close();
    return count;
}
