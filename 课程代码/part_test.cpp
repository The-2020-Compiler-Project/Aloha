#include "head.h"

class Optimization:public GrammaticalAnalysis
{
private:
    list<Quaternary>::iterator optimize_now;//��ǰ�Ż���Ԫʽ
    list<Quaternary>::iterator optimize_block_now;//�Ż���ĵ�ǰ��
    //list<Quaternary>::iterator block_now;//��ǰ��ָ��
    list<Quaternary>::iterator qua;//��Ԫʽ
    list<DAG>::iterator dag_head;//DAGͷָ��
    list<DAG>::iterator dag_tail;//DAGβָ��
    list<DAG>::iterator dag_now;//DAG��ǰָ��

    list<Operand>::iterator find_now_num1;//��ǰ���Ҵ�
    list<Operand>::iterator find_now_num2;//��ǰ���Ҵ� 

    string find_now_ope;//��ǰ���������
    list<Operand>::iterator add_now;//��ǰ��Ҫ����Ľ��
    string op_now;//��ǰ�����
    list<DAG>::iterator find_begin;//���ҿ�ʼ��
    list<DAG>::iterator pos;//�ҵ���λ��

    list<Mark>::iterator mark_pos;//�ҵ��ı��λ��
    list<DAG>::iterator temp_dag;//������������ڵ�dag���

    list<Mark>::iterator temp1;//���������1
    list<Mark>::iterator temp2;//���������2

    void CreateOptimize();//����һ���Ż�����Ԫʽͷ��
    void CreateOptimize_Block();//����һ���Ż����ͷ��
    void DivideBlock();//�黮�ֺ���
    void CoutBlock();//�������������Ԫʽ
    void CreateDAG();//����һ��DAG
    void DeleteDAG();//ɾ��DAG
    void AddDAG();//����һ��DAG��
    int FindDAG();//����ظ�DAG���
    int FindDAG_unary();//��鵥Ŀ������ظ�DAG���
    int FindDAG_Bi();//���˫Ŀ������ظ�DAG���
    int MainMark();//���ñ���ǲ��������
    void SwopMark();//�����������
    void DeleteMark();//ɾ��һ�����
    void GetDAG();//�õ�DAG���ɽ��
    void CoutOptimize();//����Ż������Ԫʽ

public:
    list<Quaternary>::iterator optimize;//�Ż���Ԫʽ
    list<Quaternary>::iterator optimize_block;//�Ż���Ŀ�
    list<Quaternary>::iterator block;//��ָ��
    list<Quaternary>::iterator quater;//��Ԫʽ 
    void Optimize();
    Optimization(){}    //���캯������ִ���κβ���
};

void Optimization::Optimize(){
    quater = Q_list.begin();
	qua=quater;           //quater����Q_list.begin()
    DivideBlock();//���ֻ�����
    CoutBlock();//�����������
}

void Optimization::DivideBlock()//���ֿ�
{
    Block_list.clear();
	Block_list.resize(Block_list.size() + 1);//���������� 
    list<list<Quaternary> >::iterator block_now = --(Block_list.end());//���������������һ���� 
    list<Quaternary>::iterator p = qua;//��Ԫʽ 
    while(p!=Q_list.end())
    {
        if((*((*p).Operator)=="if")||(*((*p).Operator)=="el")||(*((*p).Operator)=="wh")||
            (*((*p).Operator)=="do")||(*((*p).Operator)=="we")||(*((*p).Operator)=="gt"))
        {
            (*block_now).push_back((*p));
			Block_list.resize(Block_list.size() + 1);//��һ��������������½�һ�������� 
			block_now = --(Block_list.end());
			p++;
        }
        else if((*((*p).Operator)=="ie")||(*((*p).Operator)=="lb"))
        {
            Block_list.resize(Block_list.size() + 1);//��һ��������������½�һ�������� 
			block_now = --(Block_list.end());
			(*block_now).push_back((*p));
			p++; 
        }
        else
        {
            (*block_now).push_back((*p));
            p++;
        }
    }
    if((*block_now).size() == 0)
    {
    	Block_list.pop_back();
	}
}

void Optimization::CoutBlock()//�����������
{
    list<list<Quaternary> >::iterator block_now;
    list<Quaternary>::iterator p;
    int i = 0;
    cout << "�Ż�ǰ����Ԫʽ" << endl;
	for(block_now = Block_list.begin(); block_now != Block_list.end(); block_now++)
    {
    	cout << "������" << ++i << ":" << endl;
    	for(p = (*block_now).begin(); p != (*block_now).end(); p++)
	    {//��������е�ȫ����Ԫʽ
	        cout<<"("<<*((*p).Operator);
	        for(vector<Operand>::iterator it=(*p).operand.begin();it!=(*p).operand.end();it++)
	        {
	            if(  ((*(*it).tpToken).token)=="ZT" )       {cout<<","<<(*(*((*it).tpToken)).tpI).numi;}
	            else if(((*(*it).tpToken).token)=="RT")     {cout<<","<<(*(*((*it).tpToken)).tpR).numf;}
	            else if(((*(*it).tpToken).token)=="CT")     {cout<<","<<(*(*((*it).tpToken)).tpC).numc;}
	            else if(((*(*it).tpToken).token)=="IT")     {cout<<","<<(*(*((*it).tpToken)).tpIT).name;}
	            else if(((*(*it).tpToken).token)=="99")     {cout<<",t"<<(*((*it).tpToken)).line;}
	            else if(((*(*it).tpToken).token)=="NULL")     cout<<",_";
	            //ע��������ʱ�����Ŀ��� ��������Ҫ�����޸�
	        }
	        cout<<")"<<endl;
	    }
	}
}
