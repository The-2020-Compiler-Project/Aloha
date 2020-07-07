#include "head.h"

class GrammaticalAnalysis{
private:
    //�﷨����
    list<TOKEN>::iterator ch;//��ǰ�ʵĵ�����
    int Start();
    int Function();
    int Parameter();
    int FType();
    int Type();
    int Declaration();
    int Base_declaration();
    int Id();
    int Id_Expression();
    int Content();
    int Structure();
    int Expression();
    int Cout();
    int Assignment();
    int Logical_or();
    int Logical_and();
    int Inclusive_or();
    int Exclusive_or();
    int And();
    int Equality();
    int Relational();
    int Shift();
    int Additive();
    int Multiplicative();
    int Unary();
    int Postfix();
    int Primary();
    int IF();
    int While();
    int Fun();
    void nextW();
    //���岿��
    int d; //�ṹ����
    list<TOKEN>::iterator type;//���ͱ��
    list<TOKEN>::iterator ch_sem;//������ջ�Ĵ�
    list<TOKEN>::iterator ch_function;//���������
    list<TOKEN>::iterator ch_struct;//struct �ı��
    list<TOKEN>::iterator operand_now;//��ǰ������
    list<SEM>::iterator top;
    list<SEM>::iterator base;
    list<Quaternary>::iterator quater_now;//��ǰ��Ԫʽָ��
    int mark;//���������λ��
    int counter;//ϵͳ����������
    void Bi_oper_qua();//˫Ŀ����Ĳ���������
    void Unary_oper_qua();//��Ŀ����Ĳ���������
    void Assign_oper_qua();//��ֵ����������
    void If_While_qua();//IF����,WHILEѭ������������
    //void GetMark(list<TOKEN>::iterator ch_ope);//��ȡ�����
    void GetMark_front(list<TOKEN>::iterator ch_ope);//��ȡǰ�������
    int FindSynbl();//����
    void PushSynbl();//��ӽ����ű�
    int CoutSynbl();//������ű�
    void CheckSynbl();//����ʶ���Ƿ񱻶��壬δ�������¼���������
    void PushRinfl();//��ӽ��ṹ��
    void CoutRinfl();//����ṹ��

public:
    void Grammar();
    //�﷨����
    int result;
    int end;
    int begin;
    list<SYNBL>::iterator id;//�û������ʶ��
    list<SYNBL>::iterator id_now;//��ǰ��ʶ��ָ��
    list<SYNBL>::iterator id_struct;//�ṹ������ʶ��ָ��
    list<RINFL>::iterator rinfl_now;//�ṹ��ǰָ��
    //���岿��
    list<TOKEN>::iterator ch_ope;//������ 
    void CoutQuaternary();
};

void GrammaticalAnalysis::Grammar()//�﷨������ʼ������
{
    TOKEN t;
    t.token="NULL";
    tt.push_back(t);
	counter = 1;
    d = 0;
    begin = 1;
    end = 0;
	nextW();
    result=0;
    result=Start();//ִ���﷨�����嶯��
    CheckSynbl();//�����Ԫʽ���û�����ı�ʶ���Ƿ��ڷ��ű��д���
    CoutSynbl();//������ű���Ϣ
    CoutQuaternary();
}

void GrammaticalAnalysis::nextW()//��ȡ��һ������
{
	if(begin)
	{
		ch = TOKEN_list.begin();
		begin = 0;
	}
	else
	{
		ch++;
	}
	//cout << (*ch).token << endl;
	if(ch == --(TOKEN_list.end()))end = 1;
}

void GrammaticalAnalysis::CheckSynbl()//����ʾ��ʶ���Ƿ񱻶���
{
    int m;
    list<Quaternary>::iterator q=Q_list.begin();
    for(q;q!=Q_list.end();q++)
    //vector<Operand> operand
    //���������飬��Ų��������������������
    {
        for(int i=0;i<3;i++)
        {
            if((*q).operand[i].tpToken->token=="IT")  //���������������Ϊ��ʶ��
            //(*ch).token.find("IT")!=string::npos
            //list<SYNBL> SYNBL_list;//��ʶ����
            {
                for(list<SYNBL>::iterator it=SYNBL_list.begin();it!=SYNBL_list.end();it++)
                {
                    if(  ((*it).name)==(*(*((*q).operand[i].tpToken)).tpIT).name )
                    {
                        m=1;
                        break;
                    }
                }
		        if(m==0)
		        {
		            //cout<<"����δ������"<<endl;
		            TOKEN Token;
		            Token.token = "ERROR";
		            ERRORL newerr;
		            newerr.name = (*((*((*q).operand[i].tpToken)).tpIT)).name;
		            newerr.type = 'u'; //��ʾ����δ����
		            ERRORL_list.push_back(newerr);
		        }
        	}
        }
    }
}


int GrammaticalAnalysis::CoutSynbl()//������ű�
{
    cout<<"SYNBL"<<endl;
    for(list<SYNBL>::iterator it=SYNBL_list.begin();it!=SYNBL_list.end();it++)
    {
        cout<<"������:"<<(*it).name<<"  ����:"<<((*it).type)->tval<<"  ����:"<<(*it).cat<<"  ����:"<<(*it).lenl->length<<endl;
    }
}

void GrammaticalAnalysis::CoutRinfl()//����ṹ��
{
    cout<<" RINFL:"<<endl;
    cout<<"����"<<"   ����"<<"   ����"<<endl;
    for(list<RINFL>::iterator it=RINFL_list.begin();it!=RINFL_list.end();it++)
            cout<<"  "<<(*it).id<<"      "<<(*it).off<<"      "<<((*it).tp)->tval<<endl;
}

//ȱ���������� �д�����

void GrammaticalAnalysis::CoutQuaternary()//�����Ԫʽ
{
    for(list<Quaternary>::iterator p=Q_list.begin();p!=Q_list.end();p++)
    {//��������е�ȫ����Ԫʽ
        cout<<"("<<*((*p).Operator);
        //int num=0;
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

void GrammaticalAnalysis::Unary_oper_qua()//��Ŀ�������������
{
    Quaternary quat;
    quat.Operator=(*ch_ope).tpOT;  //���ɲ�����
    cout << "��Ŀ�����:" << *((*ch_ope).tpOT) << endl;
    Operand q;
    q.tpToken=(*(--SEM_stack.end())).tpToken;
    quat.operand.push_back(q);//��һ����һ��������
    SEM_stack.erase(--SEM_stack.end());//���������ջ���ͷ�
    Operand p;
    p.tpToken=tt.begin();
    quat.operand.push_back(p);//���ɵڶ��������� Ϊ��
    TOKEN temp;     //������ʱ����
    temp.token="99";
    temp.line=counter;
    counter++;
    TEMP_var.push_back(temp);
    Operand m;
    m.tpToken=(--TEMP_var.end());
    quat.operand.push_back(m);  //������������Ϊ��ʱ����
    Q_list.push_back(quat);
    SEM sem;
    sem.tpToken=(--TEMP_var.end());  //��ʱ����������ջ
    SEM_stack.push_back(sem);
    cout<<"danmu"<<endl;
    
//    list<Quaternary>::iterator p1 = --(Q_list.end());
//	cout<<"("<<*((*p1).Operator);
//	for(vector<Operand>::iterator it=(*p1).operand.begin();it!=(*p1).operand.end();it++)
//	{
//	    if(  ((*(*it).tpToken).token)=="ZT" )       {cout<<","<<(*(*((*it).tpToken)).tpI).numi;}
//	    else if(((*(*it).tpToken).token)=="RT")     {cout<<","<<(*(*((*it).tpToken)).tpR).numf;}
//	    else if(((*(*it).tpToken).token)=="CT")     {cout<<","<<(*(*((*it).tpToken)).tpC).numc;}
//	    else if(((*(*it).tpToken).token)=="IT")     {cout<<","<<(*(*((*it).tpToken)).tpIT).name;}
//	    else if(((*(*it).tpToken).token)=="99")     {cout<<",t"<<(*((*it).tpToken)).line;}
//	    else if(((*(*it).tpToken).token)=="NULL")     cout<<",_";
//	    //ע��������ʱ�����Ŀ��� ��������Ҫ�����޸�
//	}
//	cout<<")"<<endl;
}

void GrammaticalAnalysis::Assign_oper_qua()//��ֵ����������
{
    Quaternary quat;
    quat.Operator=(*ch_ope).tpOT;  //���ɲ�����
    Operand q;
    q.tpToken=(*(--(SEM_stack.end()))).tpToken;
    quat.operand.push_back(q);//��һ��������
    SEM_stack.pop_back();//���������ջ���ͷ�
    Operand p;
    p.tpToken=tt.begin();
    quat.operand.push_back(p);//���ɵڶ���������Ϊ��
    Operand m;
    m.tpToken=(*(--(SEM_stack.end()))).tpToken;
    quat.operand.push_back(m);//������������
    Q_list.push_back(quat);
    
    
//    list<Quaternary>::iterator p1 = --(Q_list.end());
//	cout<<"("<<*((*p1).Operator);
//	for(vector<Operand>::iterator it=(*p1).operand.begin();it!=(*p1).operand.end();it++)
//	{
//	    if(  ((*(*it).tpToken).token)=="ZT" )       {cout<<","<<(*(*((*it).tpToken)).tpI).numi;}
//	    else if(((*(*it).tpToken).token)=="RT")     {cout<<","<<(*(*((*it).tpToken)).tpR).numf;}
//	    else if(((*(*it).tpToken).token)=="CT")     {cout<<","<<(*(*((*it).tpToken)).tpC).numc;}
//	    else if(((*(*it).tpToken).token)=="IT")     {cout<<","<<(*(*((*it).tpToken)).tpIT).name;}
//	    else if(((*(*it).tpToken).token)=="99")     {cout<<",t"<<(*((*it).tpToken)).line;}
//	    else if(((*(*it).tpToken).token)=="NULL")     cout<<",_";
//	    //ע��������ʱ�����Ŀ��� ��������Ҫ�����޸�
//	}
//	cout<<")"<<endl;
}

void GrammaticalAnalysis::Bi_oper_qua()//˫Ŀ�������������
{
    Quaternary quat;
    quat.Operator=(*ch_ope).tpOT;  //���ɲ�����
    Operand q;
    q.tpToken=(*(--SEM_stack.end())).tpToken;
    quat.operand.push_back(q);//��һ��������
    SEM_stack.erase(--SEM_stack.end());//���������ջ���ͷ�
    Operand p;
    p.tpToken=(*(--SEM_stack.end())).tpToken;
    quat.operand.push_back(p);//�ڶ���������
    SEM_stack.erase(--SEM_stack.end());//���������ջ���ͷ�

    TOKEN temp;     //������ʱ����
    temp.token="99";
    temp.line=counter;
    counter++;
    TEMP_var.push_back(temp);
    Operand m;
    m.tpToken=(--TEMP_var.end());
    quat.operand.push_back(m);  //������������Ϊ��ʱ����
    Q_list.push_back(quat);
    SEM sem;
    sem.tpToken=(--TEMP_var.end());  //��ʱ����������ջ
    SEM_stack.push_back(sem);
    cout<<"shuangmu"<<endl;
    
//    list<Quaternary>::iterator p1 = --(Q_list.end());
//	cout<<"("<<*((*p1).Operator);
//	for(vector<Operand>::iterator it=(*p1).operand.begin();it!=(*p1).operand.end();it++)
//	{
//	    if(  ((*(*it).tpToken).token)=="ZT" )       {cout<<","<<(*(*((*it).tpToken)).tpI).numi;}
//	    else if(((*(*it).tpToken).token)=="RT")     {cout<<","<<(*(*((*it).tpToken)).tpR).numf;}
//	    else if(((*(*it).tpToken).token)=="CT")     {cout<<","<<(*(*((*it).tpToken)).tpC).numc;}
//	    else if(((*(*it).tpToken).token)=="IT")     {cout<<","<<(*(*((*it).tpToken)).tpIT).name;}
//	    else if(((*(*it).tpToken).token)=="99")     {cout<<",t"<<(*((*it).tpToken)).line;}
//	    else if(((*(*it).tpToken).token)=="NULL")     cout<<",_";
//	    //ע��������ʱ�����Ŀ��� ��������Ҫ�����޸�
//	}
//	cout<<")"<<endl;
}

void GrammaticalAnalysis::If_While_qua()//IF,WHILE,COUT�ṹ����������
{
    Quaternary quat;
    quat.Operator=(*ch_ope).tpOT;  //���ɲ�����

    if(*((*ch_ope).tpOT)=="if"||*((*ch_ope).tpOT)=="do"||*((*ch_ope).tpOT)=="co")
    {//if do cout
        Operand q;
        q.tpToken=(*(--SEM_stack.end())).tpToken;
        quat.operand.push_back(q);//��һ����һ��������
        SEM_stack.erase(--SEM_stack.end());//���������ջ���ͷ�
    }
    else
    {
        Operand p;
        p.tpToken=tt.begin();
        quat.operand.push_back(p);//���ɵ�һ�������� Ϊ��
    }
    Operand p;
    p.tpToken=tt.begin();
    quat.operand.push_back(p);//���ɵڶ������������� Ϊ��
    quat.operand.push_back(p);
    Q_list.push_back(quat);
    cout<<"If...."<<endl;
    
//    list<Quaternary>::iterator p1 = --(Q_list.end());
//	cout<<"("<<*((*p1).Operator);
//	for(vector<Operand>::iterator it=(*p1).operand.begin();it!=(*p1).operand.end();it++)
//	{
//	    if(  ((*(*it).tpToken).token)=="ZT" )       {cout<<","<<(*(*((*it).tpToken)).tpI).numi;}
//	    else if(((*(*it).tpToken).token)=="RT")     {cout<<","<<(*(*((*it).tpToken)).tpR).numf;}
//	    else if(((*(*it).tpToken).token)=="CT")     {cout<<","<<(*(*((*it).tpToken)).tpC).numc;}
//	    else if(((*(*it).tpToken).token)=="IT")     {cout<<","<<(*(*((*it).tpToken)).tpIT).name;}
//	    else if(((*(*it).tpToken).token)=="99")     {cout<<",t"<<(*((*it).tpToken)).line;}
//	    else if(((*(*it).tpToken).token)=="NULL")     cout<<",_";
//	    //ע��������ʱ�����Ŀ��� ��������Ҫ�����޸�
//	}
//	cout<<")"<<endl;
}

//void GrammaticalAnalysis::GetMark(list<TOKEN>::iterator ch_ope)//��ȡ�����
//{	
//	cout<<"�����:"<<*((*ch_ope).tpOT)<<endl;
//}

void GrammaticalAnalysis::GetMark_front(list<TOKEN>::iterator ch_ope)//��ȡǰ�������
{
	if((*ch_ope).token == "OT5")
    {//++
       for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
       {
			if(*it == "inc")
			{
				(*ch_ope).tpOT = it;
				break;
			}
	   }
    }
    else if((*ch_ope).token == "OT6")
    {//--
        for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
       {
			if(*it == "dec")
			{
				(*ch_ope).tpOT = it;
				break;
			}
	   }
    }
    else if((*ch_ope).token == "KT30")
    {//sizeof
       for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
       {
			if(*it == "si")
			{
				(*ch_ope).tpOT = it;
				break;
			}
	   }
    }
}

int GrammaticalAnalysis::Start()//�﷨������ʼ
{
    while(!end)
	{//Function()
        if(!Function()){return 0;}
    }
    return 1;
}

int GrammaticalAnalysis::Function()//����
{
    if(!FType())
    {//FType ����ֵΪ0 �� Function����ֵΪ0
        return 0;
    }
    if(!end&&(*ch).token.find("IT")!=string::npos)
    {//IT �ж��Ƿ���IT�����������һ���ʣ������򷵻�ֵΪ0
        ch_function=ch;
        ch_sem=ch_function;
        if ((*(*ch_sem).tpIT).name=="main")
            {nextW();}
        else
        {
            if(!FindSynbl())//����
            {
                PushSynbl();//��ӽ����ű�
                TYPEL* p=new TYPEL;//�����µ����ͱ�����ʼ��
                (*id_now).type=p;
                ((*id_now).type)->tval='f';
                (*id_now).lenl=new LENL;//�����µĳ��ȱ�
                (*(id_now)).lenl->length=0;
                if((*ch).token == "KT2")//int
                    {(*id_now).cat ='i';}
                else if((*ch).token == "KT4")//real
                    {(*id_now).cat ='r';}
                else if((*ch).token == "KT6")//char
                    {(*id_now).cat ='c';}
                else
                    {(*id_now).cat ='v';}
            }
            else
            {//�����﷨�����ظ�����
                ERRORL e;//��������
                e.name = (*((*ch_sem).tpIT)).name;
                e.line = (*ch_sem).line;
                e.type='m';//��������
                ERRORL_list.push_back(e);
            }
        nextW();
        }
    }
    else{return 0;}
    if(!end && (*ch).token == "PT2")
    {//(   �ж��Ƿ���(�����������һ���ʣ������򷵻�ֵΪ0
        nextW();
    }
    else{return 0;}
    if(!Parameter())
    {// Parameter()����ֵΪ0����Function����ֵΪ0
        return 0;
    }
    if(!end &&(*ch).token == "PT3")
    {//)  �ж��Ƿ���)�����������һ���ʣ������򷵻�ֵΪ0
        nextW();
    }
    else{return 0;}
    if(!end &&(*ch).token == "PT0")
    {//{  �ж��Ƿ���{�����������һ���ʣ������򷵻�ֵΪ0
        nextW();
    }
    else{return 0;}
    if(!Declaration()){return 0;}//Declaration() ����Declaration�ӳ��򣬷���ֵΪ0����Function����ֵΪ0
    if(!Content()){return 0;}//Content()  ����Content�ӳ��򣬷���ֵΪ0����Function����ֵΪ0
    if(!end &&(*ch).token == "PT1")
    {//}  �ж��Ƿ���}�����������һ���ʣ������򷵻�ֵΪ0
        nextW();
    }
    else{return 0;}
    return 1;
}

int GrammaticalAnalysis::Parameter()//��������
{
    if(!Type())
    {//Type()
        if(!end &&(*ch).token == "KT18")
        {//void
            nextW();
            return 1;
        }
        else {return 1;}
    }
    else
    {
        if(!Id())
            {return 0;}//Id()
        else
        {
            while(!end &&(*ch).token == "PT9")
            {//
                nextW();
                if(!Type()){return 0;}//Type()
                else
                {
                    if(!Id()){return 0;}//Id()
                }
            }
        }
    }
    return 1;
}

int GrammaticalAnalysis::FType()//��������
{
    if(!end &&(*ch).token == "KT18")
    {//void
        nextW();
        return 1;
    }
    if(!Type()){return 0;}//Type()
    return 1;
}

int GrammaticalAnalysis::Type()//������������
{
    if(!end && (*ch).token == "KT2"){//int
        type = ch;
        nextW();
        return 1;
    }
    else if(!end && (*ch).token == "KT4"){//real
        type = ch;
        nextW();
        return 1;
    }
    else if(!end && (*ch).token == "KT6"){//char
        type = ch;
        nextW();
        return 1;
    }
    return 0;
}

int GrammaticalAnalysis::Declaration()//����
{
    while(!end &&((*ch).token == "KT2"||(*ch).token == "KT4"||(*ch).token == "KT6"||(*ch).token == "KT7"))
    {
        if(!end &&(*ch).token == "KT7")
        {//struct �������ɽṹ����Ԫʽ
            ch_struct=ch;
            nextW();
            if(!end&&(*ch).token.find("IT")!=string::npos)
            {//Identifier
                ch_sem=ch;
                nextW();
                d=1;//�ṹ��
                if(!end &&(*ch).token == "PT0")
                {//{
                    if(!FindSynbl())
                    {//����
                        PushSynbl();
                        TYPEL* p=new TYPEL;
                        (*(id_now)).type=p;
                        rinfl_now=(*(id_now)).type->rinfl;
                        (*(id_now)).type->tval='t';
                        (*(id_now)).lenl=new LENL;//�����µĳ��ȱ�
                        (*(id_now)).lenl->length=0;
                        (*(id_now)).cat='d';
                        id_struct=id_now;
                }
                else
                {//�����﷨�����ظ�����
                    ERRORL e;//��������
                    e.name = (*((*ch_sem).tpIT)).name;
                    e.line = (*ch_sem).line;
                    e.type='m';//��������
                    ERRORL_list.push_back(e);
                }
                nextW();
                if(!Base_declaration()){return 0;}//Base_declaration()
                else {
                    if(!end &&(*ch).token == "PT1")
                    {//}
                        nextW();
                        if(!end &&(*ch).token == "PT8")
                        {//;
                            nextW();
                            d=0;
                            cout<<(*(id_struct)).name;
                            CoutRinfl();
                        }
                        else {return 0;}
                    }
                    else {return 0;}
                }
            }
            else
            {//�ṹ�嶨��
                type=ch_struct;
                d=0;
                if(Id())
                {//IT
                    (*(id_now)).type->rinfl=(*(id_struct)).type->rinfl;//�����µĳ��ȱ�
                    (*(id_now)).lenl->length=(*(id_struct)).lenl->length;
                    if(!end &&(*ch).token == "PT8")
                    {//;
                        nextW();
                        cout<<(*(id_now)).name;
                        CoutRinfl();
                    }
                    else {return 0;}
                }
                else {return 0;}
            }
        }
        else {return 0;}
        }
        if(!Base_declaration()){return 0;}//Base_declaration()
    }
    return 1;
}

int GrammaticalAnalysis::Base_declaration()//������������
{
    while(Type())
    {//Type()
        if(!Id()){return 0;}//Id()
        else{
            while(!end &&(*ch).token == "PT9")
            {//
                nextW();
                if(!Id()){return 0;}//Id()
            }
        }
        if(!end &&(*ch).token == "PT8")
        {//;
            nextW();
        }
        else {return 0;}
    }
    return 1;
}

int GrammaticalAnalysis::Id()//Id
{
    if(!end&&(*ch).token.find("IT")!=string::npos)
    {//IT
        ch_sem=ch;
        nextW();
        if(!end &&(*ch).token == "PT4")//[
        {
            nextW();
            if(!end&&(*ch).token.find("ZT")!=string::npos)
            {//Integer
                list<TOKEN>::iterator num_temp=ch;
                nextW();
                if(!end &&(*ch).token == "PT5")
                {//]
                    if(!FindSynbl())//����
                    {
                        PushSynbl();//��ӽ����ű�
                        TYPEL* p=new TYPEL;//�����µ����ͱ�����ʼ��
                        if(d){p->tval='d';}//�ṹ������
                        else {p->tval='a';}//������
                        AINFL newa;//�����µ����������ʼ��
                        newa.low = 0;//�����½�Ϊ0
                        newa.up = ((*num_temp).tpI)->numi-1;//�����Ͻ�Ϊinteger-1
                        newa.ctp = new TYPEL;//�ɷ�����ָ�룬ָ���Ӧ�ĳɷ�����
                        if((*type).token == "KT2")//int
                            {(*id_now).cat ='i';}
                        else if((*type).token == "KT4")//real
                            {(*id_now).cat ='r';}
                        else if((*type).token == "KT6")//char
                            {(*id_now).cat ='c';}
                        newa.clen=(newa.up + 1) * 2;//�ɷ����͵ĳ��ȣ�Ĭ��Ϊ���鳤�ȳ�2
                        AINFL_list.push_back(newa);
                        p->ainfl = --(AINFL_list.end());
                        (*id_now).lenl = new LENL;//�����µĳ��ȱ�����ʼ��
                        (*id_now).lenl->length=newa.clen;//��������Ϣ���볤�ȱ���
                        (*id_now).type = p;
                        if (d)
                        {
                            PushRinfl();
                        }
                    }
	                else{//�����﷨�����ظ�����
                        ERRORL e;//��������
						e.name = (*((*ch_sem).tpIT)).name;
                        e.line = (*ch_sem).line;
                        e.type='m';//��������
                        ERRORL_list.push_back(e);
                    }
                    nextW();
                    return 1;//��������
                }
                else {return 0;}
            }
            else {return 0;}
        }
        else //����
        {
            if(!FindSynbl())
            {//����
                PushSynbl();//��ӽ����ű�
                TYPEL* p=new TYPEL;
                AINFL newa;
                RINFL newr;
				(*id_now).type = p;
                if(d){((*id_now).type)->tval='d';}//����
                else {((*id_now).type)->tval='v';}//����
                if((*type).token == "KT2")//int
	                {(*id_now).cat ='i';}
	            else if((*type).token == "KT4")//real
	                {(*id_now).cat ='r';}
	            else if((*type).token == "KT6")//char
	                {(*id_now).cat ='c';}
	            else if((*type).token == "KT7")//struct
	                {(*id_now).cat ='d';}
                (*id_now).lenl=new LENL;//�����µĳ��ȱ�
                ((*id_now).lenl)->length=2;//Ĭ������int,char,real���Ⱦ�Ϊ2
                if (d)
                {
                    PushRinfl();
                }
            }
            else
            {//�����﷨�����ظ�����
            	ERRORL e;//��������
				e.name = (*((*ch_sem).tpIT)).name;
                e.line = (*ch_sem).line;
                e.type='m';//��������
                ERRORL_list.push_back(e);
            }
            return 1;
        }//�������ͱ�ʶ��
    }
    return 0;
}

int GrammaticalAnalysis::Id_Expression()//Id_Expression
{
    if(!end&&(*ch).token.find("IT")!=string::npos)
    {//Identifier
        ch_sem=ch;
        nextW();
        if(!end&&(*ch).token.find("PT4")!=string::npos)
        {//[
            SEM sem;
            sem.tpToken=ch_sem;
            SEM_stack.push_back(sem);//�������ͱ�ʶ����ջ
            //PushStack();
            nextW();
            if(!end&&(*ch).token.find("ZT")!=string::npos)
            {//Integer
                ch_sem=ch;
                nextW();
                if(!end &&(*ch).token == "PT5")
                {//]
                    SEM sem;
                    sem.tpToken=ch_sem;
                    SEM_stack.push_back(sem);//�������ͱ�ʶ����ջ
                    for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
			       {
						if(*it == "arr")
						{
							(*ch_ope).tpOT = it;
							break;
						}
				   }
                    Bi_oper_qua();
                    nextW();
                    return 1;//��������
                }
                else {return 0;}
            }
            else {return 0;}
        }
        else{
            if(!end &&(*ch).token == "OT7")
            {
               SEM sem;
                sem.tpToken=ch_sem;
                SEM_stack.push_back(sem);//�������ͱ�ʶ����ջ
            }
            return 1;
        }//�������ͱ�ʶ��
    }
    return 0;
}

int GrammaticalAnalysis::Content(){//����
    while(!end )
    {
        if(!Structure())
        {//Structure()
            return 0;
        }
        else
        {
            if(!end &&(*ch).token == "PT1"){return 1;}//����һ����Ϊ'}',��˵������������
        }
    }
    return 1;
}

int GrammaticalAnalysis::Structure()//���ݽṹѡ��
{
    if(!Fun())
    {//Fun()
        if(!Expression())
        {//Expression()
            if(!IF())
            {//If()
                if(!While())
                {//While()
                    if(!Cout())
                    {//Cout()
                        if(!end &&(*ch).token == "PT1"){return 1;}//����һ����Ϊ'}',��˵������������,�˴�������
                        else {return 0;}
                    }
                    else {return 1;}
                }
                else {return 1;}
            }
            else {return 1;}
        }
        if(!end &&(*ch).token == "PT8")
        {//;
            nextW();
            return 1;
        }
        else {return 0;}
    }
    else {return 1;}
}

int GrammaticalAnalysis::Cout()//�������
{
    if(!end &&(*ch).token=="KT33")
    {//cout
        nextW();
        if(!Logical_or())
        {return 0;}
        else
        {//Logical_or()
            if(!end&&(*ch).token=="PT8")
            {//;
                for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
		       {
					if(*it == "co")
					{
						(*ch_ope).tpOT = it;
						break;
					}
			   }
                If_While_qua();
                nextW();
                return 1;
            }
            else{return 0;}
        }
    }
    else {return 0;}
}

int GrammaticalAnalysis::Fun()//�������ʽ
{
    list<TOKEN>::iterator ch_temp=ch;
    if(!end&&(*ch).token.find("IT")!=string::npos)
    {//Identifier
        ch_sem=ch;
        nextW();
        if (!FindSynbl()) {return 0;}
        else
        {
            if(!end&&(*ch).token=="PT2")
            {//(
                nextW();
                if(!Assignment())
                {//Assignment(),�޲���
                    if(!end&&(*ch).token=="PT3")
                    {//)
                        nextW();
                        if(!end&&(*ch).token=="PT8")
                        {//;
                            nextW();
                            return 1;
                        }
                        else {return 0;}
                    }
                    else {return 0;}
                }
                else
                {//�в���
                    while(!end&&(*ch).token=="PT9")
                    {//,
                        nextW();
                        if(!Assignment()){return 0;}//Assignment()
                    }
                    if(!end&&(*ch).token=="PT3")
                    {//)
                        nextW();
                        if(!end&&(*ch).token=="PT8")
                        {//;
                            nextW();
                            return 1;
                        }
                        else {return 0;}
                    }
                    else {return 0;}
                }
            }
            else
            {//�����Ǻ������ʽ���򷵻ؼ�¼λ��
                ch=ch_temp;
                return 0;
            }
        }
    }
    else {return 0;}
}

int GrammaticalAnalysis::Expression()//���ʽ
{
    if(!Assignment()){return 0;}//Assignment()
    while(!end&&(*ch).token=="PT9")
    {//,
        ch_ope=ch;
        nextW();
        if(!Assignment()){return 0;}//Assignment()
        //GetMark(ch_ope);//������ȡ�����
        Unary_oper_qua();//��Ŀ����Ĳ���������
    }
    return 1;
}

int GrammaticalAnalysis::Assignment()//��ֵ
{
    list<TOKEN>::iterator ch_temp=ch;
    if(!end&&(*ch).token=="IT")
    {
        ch_sem=ch;
        nextW();
        if(!end&&(*ch).token=="PT10")
        {
            SEM sem;
            sem.tpToken=ch_sem;
            SEM_stack.push_back(sem);//�������ͱ�ʶ����ջ
            //PushStack();
            ch_sem=ch;
            nextW();
            if(!Id_Expression()){return 0;}
            else
            {
                for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
		       {
					if(*it == ".")
					{
						(*ch_ope).tpOT = it;
						break;
					}
			   }
                Bi_oper_qua();
                if(!end&&(*ch).token=="OT7")
                {
                    ch_ope=ch;
                    nextW();
                    if(!Logical_or()){return 0;}
                    else
                    {
                        //GetMark(ch_ope);//��ȡ�����
                        Assign_oper_qua();//��ֵ����������
                        return 1;
                    }
                }
                else {return 0;}
            }
        }
        else
        {
            ch=ch_temp;
            if(!Id_Expression())
            {
                if(!Logical_or()){return 0;}
                else {return 1;}
            }
            else{
                if(!end&&(*ch).token=="OT7")
                {
                    ch_ope=ch;
                    nextW();
                    if(!Logical_or()){return 0;}
                    else
                    {
                        //GetMark(ch_ope);
                        Assign_oper_qua();//��ֵ����������
                        return 1;
                    }
                }
                else
                {
                    ch=ch_temp;
                    if(!Logical_or()){return 0;}
                    else {return 1;}
                }
            }
        }
    }
    else
    {
        if(!Logical_or()){return 0;}
        else {return 1;}
    }
    return 0;
}

int GrammaticalAnalysis::Logical_or()//�߼���
{
    if(!Logical_and()){return 0;}
    while(!end&&(*ch).token=="OT15")
    {
        ch_ope=ch;
        nextW();
        if(!Logical_and()){return 0;}
		//GetMark(ch_ope);//������ȡ�����
        Bi_oper_qua();//˫Ŀ����Ĳ���������
    }
    return 1;
}

int GrammaticalAnalysis::Logical_and()//�߼���
{
    if(!Inclusive_or()){return 0;}
    while(!end&&(*ch).token=="OT14")
    {
        ch_ope=ch;
        nextW();
        if(!Inclusive_or()){return 0;}
        //GetMark(ch_ope);//������ȡ�����
        Bi_oper_qua();//����˫Ŀ����Ĳ���������
    }
    return 1;
}

int GrammaticalAnalysis::Inclusive_or()//������
{
    if(!Exclusive_or()){return 0;}
    while(!end&&(*ch).token=="OT18")
    {
        ch_ope=ch;
        nextW();
        if(!Exclusive_or()){return 0;}
        //GetMark(ch_ope);//������ȡ�����
        Bi_oper_qua();//����˫Ŀ����Ĳ���������
    }
    return 1;
}

int GrammaticalAnalysis::Exclusive_or()//�������
{
    if(!And()){return 0;}
    while(!end&&(*ch).token=="OT19")
    {
        ch_ope=ch;
        nextW();
        if(!And()){return 0;}
        //GetMark(ch_ope);//������ȡ�����
        Bi_oper_qua();//����˫Ŀ����Ĳ���������
    }
    return 1;
}

int GrammaticalAnalysis::And()//������
{
    if(!Equality()){return 0;}
    while(!end&&(*ch).token=="OT17")
    {
        ch_ope=ch;
        nextW();
        if(!Equality()){return 0;}
        //GetMark(ch_ope);//������ȡ�����
        Bi_oper_qua();//����˫Ŀ����Ĳ���������
    }
    return 1;
}

int GrammaticalAnalysis::Equality()//��ֵ�жϣ�==����!=
{
    if(!Relational()){return 0;}
    while(!end&&((*ch).token=="OT12"||(*ch).token=="OT13"))
    {//==,!=
        ch_ope=ch;
        nextW();
        if(!Relational()){return 0;}
        //GetMark(ch_ope);//������ȡ�����
        Bi_oper_qua();//����˫Ŀ����Ĳ���������

    }
    return 1;
}

int GrammaticalAnalysis::Relational()//��ϵ���㣬>,>=,<,<=
{
    if(!Shift()){return 0;}
    while(!end&&((*ch).token=="OT8"||(*ch).token=="OT9"||(*ch).token=="OT10"||(*ch).token=="OT11"))
    {
        ch_ope=ch;
        nextW();
        if(!Shift()){return 0;}
        //GetMark(ch_ope);//������ȡ�����
        Bi_oper_qua();//����˫Ŀ����Ĳ���������

    }
    return 1;
}

int GrammaticalAnalysis::Shift()//��λ���㣬>>,<<
{
    if(!Additive()){return 0;}
    while(!end&&((*ch).token=="OT21"||(*ch).token=="OT22"))
    {
        ch_ope=ch;
        nextW();
        if(!Additive()){return 0;}
        //GetMark(ch_ope);//������ȡ�����
        Bi_oper_qua();//����˫Ŀ����Ĳ���������
    }
    return 1;
}

int GrammaticalAnalysis::Additive()//�ӷ���������+,-
{
    if(!Multiplicative()){return 0;}
    while(!end&&((*ch).token=="OT0"||(*ch).token=="OT1"))
    {
        ch_ope=ch;
        nextW();
        if(!Multiplicative()){return 0;}
        //GetMark(ch_ope);//������ȡ�����
        Bi_oper_qua();//����˫Ŀ����Ĳ���������
    }
    return 1;
}

int GrammaticalAnalysis::Multiplicative()//�˷���������ȡģ��*,/,%
{
    if(!Unary()){return 0;}
    while(!end&&((*ch).token=="OT2"||(*ch).token=="OT3"||(*ch).token=="OT4"))
    {
        ch_ope=ch;
        nextW();
        if(!Unary()){return 0;}
        //GetMark(ch_ope);//������ȡ�����
        Bi_oper_qua();//����˫Ŀ����Ĳ���������

    }
    return 1;
}

int GrammaticalAnalysis::Unary()//ǰ��������ǣ�ȡ�����������Լ������С,!,~,INC,DEC,sizeof
{
    if(!end&&((*ch).token=="OT16"||(*ch).token=="OT20"||(*ch).token=="OT5"||(*ch).token=="OT6"||(*ch).token=="KT30"))
    {
        ch_ope=ch;
        nextW();
        if(!Postfix()){return 0;}
        GetMark_front(ch_ope);//������ȡ�����
        Unary_oper_qua();//������Ŀ����Ĳ���������
    }
    else
    {
        if(!Postfix()){return 0;}
    }
    return 1;
}

int GrammaticalAnalysis::Postfix()//���������[Expression],++,--,.
{
    if(!Primary()){return 0;}
    while(!end&&((*ch).token=="PT4"||(*ch).token=="OT5"||(*ch).token=="OT6"||(*ch).token=="PT10"))
    {
        if((*ch).token=="PT4")
        {//[
            nextW();
            if(!Expression()){return 0;}//Expression()
            else{
                if(!end&&(*ch).token=="PT5")
                {//]
                    nextW();
                    for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
			       {
						if(*it == "arr")
						{
							(*ch_ope).tpOT = it;
							break;
						}
				   }
                    Bi_oper_qua();//����˫Ŀ����Ĳ���������
                }
                else {return 0;}
            }
        }
        else if((*ch).token=="PT10")
        {//.
            nextW();
            if(!end&&(*ch).token.find("IT")!=string::npos)
            {//Identifier
                ch_sem=ch;/*�������*/
                SEM sem;
                sem.tpToken=ch_sem;
                SEM_stack.push_back(sem);//�������ͱ�ʶ����ջ
                for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
		       {
					if(*it == ".")
					{
						(*ch_ope).tpOT = it;
						break;
					}
			   }
                Bi_oper_qua();//����˫Ŀ����Ĳ���������
                nextW();
            }
            else {return 0;}
        }
        else
        {//��Ϊ++��--��ֱ�Ӷ�ȡ��һ���ַ�

            //GetMark(ch);//������ȡ�����
            Unary_oper_qua();//��Ŀ����Ĳ���������
            nextW();
        }
    }
    return 1;
}

int GrammaticalAnalysis::Primary()//�����ʽ,��ʶ��������������ѭ����i,constant,(Expression)
{
    if(!end&&(*ch).token.find("IT")!=string::npos)
    {//Identifier
        ch_sem=ch;
        SEM sem;
        sem.tpToken=ch_sem;
        SEM_stack.push_back(sem);//�������ͱ�ʶ����ջ
        nextW();
        return 1;
    }
    if(!end&&(*ch).token.find("ZT")!=string::npos)
    {//Integer
        ch_sem=ch;
        SEM sem;
        sem.tpToken=ch_sem;
        SEM_stack.push_back(sem);//�������ͱ�ʶ����ջ
        nextW();
        return 1;
    }
    if(!end&&(*ch).token.find("RT")!=string::npos)
    {//Real
        ch_sem=ch;
        SEM sem;
        sem.tpToken=ch_sem;
        SEM_stack.push_back(sem);//�������ͱ�ʶ����ջ
        nextW();
        return 1;
    }
    if(!end&&(*ch).token.find("CT")!=string::npos)
    {//Char
        ch_sem=ch;
        SEM sem;
        sem.tpToken=ch_sem;
        SEM_stack.push_back(sem);//�������ͱ�ʶ����ջ
        nextW();
        return 1;
    }
    if(!end&&(*ch).token=="PT2")
    {//(
        nextW();
        if(!Expression()){return 0;}//Expression()
        else
        {
            if(!end&&(*ch).token=="PT3")
            {//)
                nextW();
                return 1;
            }
            else {return 0;}
        }
    }
    else {return 0;}
}

int GrammaticalAnalysis::IF()//IF
{
    if(!end&&(*ch).token=="KT19")
    {//if
        nextW();
        if(!end&&(*ch).token=="PT2")
        {//(
            nextW();
            if(!Expression()){return 0;}//Expression()
            else
            {
                if(!end&&(*ch).token=="PT3")
                {//)
                    nextW();
                    for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
			       {
						if(*it == "if")
						{
							(*ch_ope).tpOT = it;
							break;
						}
				   }
                    If_While_qua();
                    if(!end&&(*ch).token=="PT0")
                    {//{
                        nextW();
                        if(!Content()){return 0;}//Content()
                        else
                        {
                            if(!end&&(*ch).token=="PT1")
                            {//}
                                nextW();
                                if(!end&&(*ch).token=="KT20")
                                {//else
                                    nextW();
                                    for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
							       {
										if(*it == "el")
										{
											(*ch_ope).tpOT = it;
											break;
										}
								   }
                                    If_While_qua();
                                    if(!end&&(*ch).token=="PT0")
                                    {//{
                                        nextW();
                                        if(!Content()){return 0;}//Content()
                                        else
                                        {
                                            if(!end&&(*ch).token=="PT0")
                                            {//}
                                                nextW();
                                                for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
										       {
													if(*it == "ie")
													{
														(*ch_ope).tpOT = it;
														break;
													}
											   }
                                                If_While_qua();
                                                return 1;
                                            }
                                            else {return 0;}
                                        }
                                    }
                                    else {return 0;}
                                }
                                else {return 1;}//��else
                            }
                            else {return 0;}
                        }
                    }
                    else {return 0;}
                }
                else {return 0;}
            }
        }
        else {return 0;}
    }
    else {return 0;}
}

int GrammaticalAnalysis::While()//WHILE
{
    if(!end&&(*ch).token=="KT25")
    {//while
        nextW();
        for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
       {
			if(*it == "wh")
			{
				(*ch_ope).tpOT = it;
				break;
			}
	   }
        If_While_qua();
        if(!end&&(*ch).token=="PT2")
        {//(
            nextW();
            if(!Expression()){return 0;}//Expression()
            else
            {
                if(!end&&(*ch).token=="PT3")
                {//)
                    nextW();
                    for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
			       {
						if(*it == "do")
						{
							(*ch_ope).tpOT = it;
							break;
						}
				   }
                    If_While_qua();
                    if(!end&&(*ch).token=="PT0")
                    {//{
                        nextW();
                        if(!Content()){return 0;}//Content()
                        else
                        {
                            if(!end&&(*ch).token=="PT1")
                            {//}
                                nextW();
                                for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
						       {
									if(*it == "we")
									{
										(*ch_ope).tpOT = it;
										break;
									}
							   }
                                If_While_qua();
                                return 1;
                            }
                            else {return 0;}
                        }
                    }
                    else {return 0;}
                }
                else {return 0;}
            }
        }
        else {return 0;}
    }
    else {return 0;}
}

int GrammaticalAnalysis::FindSynbl()//����
{
    list<SYNBL>::iterator it;
    for(it = SYNBL_list.begin(); it != SYNBL_list.end(); it++)
    {
    	if((*it).name == (*((*ch_sem).tpIT)).name)
    		return 1;
	}
	return 0;
}

void GrammaticalAnalysis::PushSynbl()//��ӽ����ű�
{
    SYNBL newid = *((*ch_sem).tpIT);
    SYNBL_list.push_back(newid);
    id_now = --(SYNBL_list.end());
}

void GrammaticalAnalysis::PushRinfl()//��ӽ��ṹ��
{
    id_now = --(SYNBL_list.end());
	RINFL newr;
    newr.id = (*id_now).name;
    newr.off = ((*id_struct).lenl)->length;
    ((*id_struct).lenl)->length += ((*id_now).lenl)->length;
	newr.tp = (*id_now).type;
    RINFL_list.push_back(newr);
    rinfl_now = --(RINFL_list.end());
}

