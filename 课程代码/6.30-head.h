#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

//*********头文件**********
#include<iostream>
#include<string>
#include<vector>
#include<list>
using namespace std;


//**********宏定义**********
#define OK 1
#define ERROR 0


//**********关键字与界符**********
vector<string> KT = {"auto","short","int","long","real",
"double","char","struct","union","enum","typedef",
"const","unsigned","signed","extern","register","static",
"volatile","void","if","else","switch","case","for",
"do","while","goto","continue","break","default",
"sizeof","return","bool","cout"
};//关键字表


vector<string> PT = {"{","}","(",")","[","]",
"\"","\'",";",",",".","->","?","#"
};//界符表


vector<string> OT = {"+","-","*","/","%","++","--","=",
">",">=","<","<=","==","!=",
"&&","||","!",
"&","|","^","~",">>","<<"
};//运算符表


//**********结构体**********
typedef struct SYNBL{//标识符表节点
    string name;//标识符名字
    char cat;//种类，目前有：f(函数),a(数组),d(结构),v(变量),n(换名形参),g(赋值形参)
    char L;//活跃信息
    struct TYPEL* type;//类型表指针
    struct PFINFL* pfinfl;//函数表指针
    struct LENL* lenl;//长度表指针
    struct VALL* vall;//活动记录表指针
}SYNBL;

typedef struct AINFL{//数组表
    int low;//数组下界
    int up;//数组上界
    int clen;//成分类型的长度，成分类型数据所占值单元的个数
    struct TYPEL* ctp;//成分类型指针，指向该维数组成分的类型的指针
}AINFL;

typedef struct RINFL{//结构表
    string id;//结构域名
    int off;//(区距)—是idk的值单元首址相对于所在记录值区区头位置
    struct TYPEL* tp;//指针，指向idk域成分类型(在类型表中的信息)
}RINFL;

typedef struct TYPEL{//类型表
    char tval;//类码，类型代码，决定下列指针选择，现有类码为：i(整型),r(实型),c(字符型),a(数组),d(结构体)
    list<AINFL> ainfl;//数组表迭代器
    list<RINFL>::iterator rinfl;//结构体表迭代器
}TYPEL;

typedef struct PFINFL{//函数表
    string level;//层次号，该过函静态层次嵌套号
    int off;//该过函自身数据区起始单元相对该过函值区区头位置
    int fn;//该过函的形式参数的个数
    string entry;//该函数目标程序首地址(运行时填写)
    SYNBL* param;//指针，指向形参表
}PFINFL;

typedef struct INT{//整数型表
    int numi;
}INT;

typedef struct REAL{//实数型表
    float numf;
}REAL;

typedef struct CHAR{//字符型表
    char numc;
}CHAR;

typedef struct LENL{//长度表
    int length;//长度信息
}LENL;

typedef struct VALL{//活动记录表

}VALL;

typedef struct ERRORL{//错误记录表
    int line;//错误行数
    char type;//错误类型，
    string name;//错误内容
}ERRORL;

typedef struct TOKEN{//TOKEN记录
    string token;//token码
    int line;//行数记录，系统编码标记
    INT* tpI;//整型指针
    REAL* tpR;//实型指针
    CHAR* tpC;//字符指针
    list<SYNBL>::iterator tpIT;//标识符表迭代器
    vector<string>::iterator tpKT;//关键字表迭代器
    vector<string>::iterator tpPT;//界符表迭代器
    vector<string>::iterator tpOT;//运算符表迭代器
}TOKEN;

typedef struct SEM{//语义栈
    list<TOKEN>::iterator tpToken;
}SEM;

typedef struct Operand{//操作数
    list<TOKEN>::iterator tpToken;
}Operand;

typedef struct Quaternary{//四元式
    vector<string>::iterator Operator;//操作符表迭代器
    vector<Operand> operand;//操作数数组，存放操作符后面的三个操作数
}Quaternary;


//**********全局变量**********
list<SYNBL> SYNBL_list;//标识符表
list<AINFL> AINFL_list;//数组表总表
list<RINFL> RINFL_list;//结构体总表
list<ERRORL> ERRORL_list;//错误记录表
list<TOKEN> TOKEN_list;//Token流
list<SEM> SEM_stack;//语义栈
list<Quaternary> Q_list;//四元式序列


//**********类声明**********










#endif // HEAD_H_INCLUDED
