#ifndef HEAD_H
#define HEAD_H


//*********ͷ�ļ�**********
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<list>
using namespace std;


//**********�궨��**********
#define OK 1
#define ERROR 0


//**********�ؼ�������**********
vector<string> KT = {"auto","short","int","long","real",
"double","char","struct","union","enum","typedef",
"const","unsigned","signed","extern","register","static",
"volatile","void","if","else","switch","case","for",
"do","while","goto","continue","break","default",
"sizeof","return","bool","cout","main"
};//�ؼ��ֱ�


vector<string> PT = {"{","}","(",")","[","]",
"\"","\'",";",",",".","->","?","#"
};//�����


vector<string> OT = {"+","-","*","/","%","++","--","=",
">",">=","<","<=","==","!=",
"&&","||","!",
"&","|","^","~",">>","<<"
};//�������


//**********�ṹ��**********
typedef struct SYNBL{//��ʶ����ڵ�
    string name;//��ʶ������
    char cat;//���࣬Ŀǰ�У�f(����),a(����),d(�ṹ),v(����),n(�����β�),g(��ֵ�β�)
    char L;//��Ծ��Ϣ
    struct TYPEL* type;//���ͱ�ָ��
    struct PFINFL* pfinfl;//������ָ��
    struct LENL* lenl;//���ȱ�ָ��
    struct VALL* vall;//���¼��ָ��
}SYNBL;

typedef struct AINFL{//�����
    int low;//�����½�
    int up;//�����Ͻ�
    int clen;//�ɷ����͵ĳ��ȣ��ɷ�����������ռֵ��Ԫ�ĸ���
    struct TYPEL* ctp;//�ɷ�����ָ�룬ָ���ά����ɷֵ����͵�ָ��
}AINFL;

typedef struct RINFL{//�ṹ��
    string id;//�ṹ����
    int off;//(����)����idk��ֵ��Ԫ��ַ��������ڼ�¼ֵ����ͷλ��
    struct TYPEL* tp;//ָ�룬ָ��idk��ɷ�����(�����ͱ��е���Ϣ)
}RINFL;

typedef struct TYPEL{//���ͱ�
    char tval;//���룬���ʹ��룬��������ָ��ѡ����������Ϊ��i(����),r(ʵ��),c(�ַ���),a(����),d(�ṹ��)
    list<AINFL>::iterator ainfl;//����������
    list<RINFL>::iterator rinfl;//�ṹ��������
}TYPEL;

typedef struct PFINFL{//������
    string level;//��κţ��ù�����̬���Ƕ�׺�
    int off;//�ù���������������ʼ��Ԫ��Ըù���ֵ����ͷλ��
    int fn;//�ù�������ʽ�����ĸ���
    string entry;//�ú���Ŀ������׵�ַ(����ʱ��д)
    list<SYNBL>::iterator param;//�βα������
}PFINFL;

typedef struct INT{//�����ͱ�
    int numi;
}INT;

typedef struct REAL{//ʵ���ͱ�
    float numf;
}REAL;

typedef struct CHAR{//�ַ��ͱ�
    char numc;
}CHAR;

typedef struct LENL{//���ȱ�
    int length;//������Ϣ
}LENL;

typedef struct VALL{//���¼��

}VALL;

typedef struct ERRORL{//�����¼��
    int line;//��������
    char type;//�������ͣ�
    string name;//��������
}ERRORL;

typedef struct TOKEN{//TOKEN��¼
    string token;//token��
    int line;//������¼��ϵͳ������
    INT* tpI;//����ָ��
    REAL* tpR;//ʵ��ָ��
    CHAR* tpC;//�ַ�ָ��
    string tps;//�ַ�������
    list<ERRORL>::iterator tpER;//������Ϣ�������
    list<SYNBL>::iterator tpIT;//��ʶ���������
    vector<string>::iterator tpKT;//�ؼ��ֱ������
    vector<string>::iterator tpPT;//����������
    vector<string>::iterator tpOT;//������������
}TOKEN;

typedef struct SEM{//����ջ
    list<TOKEN>::iterator tpToken;
}SEM;

typedef struct Operand{//������
    list<TOKEN>::iterator tpToken;
}Operand;

typedef struct Quaternary{//��Ԫʽ
    vector<string>::iterator Operator;//�������������
    vector<Operand> operand;//���������飬��Ų��������������������
}Quaternary;


//**********ȫ�ֱ���**********
list<SYNBL> SYNBL_list;//��ʶ����
list<AINFL> AINFL_list;//������ܱ�
list<RINFL> RINFL_list;//�ṹ���ܱ�
list<ERRORL> ERRORL_list;//�����¼��
list<TOKEN> TOKEN_list;//Token��
list<SEM> SEM_stack;//����ջ
list<Quaternary> Q_list;//��Ԫʽ����
string source;//Դ����
ifstream testfile;//Դ�����ļ�
int source_pt;//ɨ��Դ�����ɨ��λ��
int line;//����Դ���������
string temp;//ʶ�𵥴�ʱ����ʱ����

//**********������**********
class checker//����������ڼ����ַ��Ĺ���
{
public:
	checker() {};
	~checker() {};
	static bool IsWord(char c);//�����Ƿ�Ϊ��ĸ
	static bool IsNumber(char c);//�����Ƿ�Ϊ����
	static bool IsZhibiao(char c);//�����Ƿ�Ϊ�Ʊ��������Ϊ���ʵķֽ��ߣ�
	static bool IsPTOT(char c);//�����Ƿ���������һ����
};

class recognizer//����ʶ�����Զ���
{
public:
	recognizer() {};
	~recognizer() {};
	static void State_1();//��ʼ״̬
	static void State_1_2();//ȥ��ע��
	static void State_2();//�����ʶ��
	static void State_3();//������
	static void State_4();//�����ַ�
	static void State_5();//�����ַ���
	static void State_6();//������
	static void State_7(char mode);//��������ַ�
};


//**********��������**********
void SCANNER();//�ʷ���������
void Token_clear(TOKEN& Token);//��һ��TOKEN���������
void preprocessor();//����Ԥ����Դ���룬ȥ��ע��
void testprint();

#endif // HEAD_H
