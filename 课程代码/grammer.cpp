#include "head.h"

class GrammaticalAnalysis{
private:
    //语法部分
    list<TOKEN>::iterator ch;//当前词的迭代器
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
    //语义部分
    int d; //结构体标记
    list<TOKEN>::iterator type;//类型标记
    list<TOKEN>::iterator ch_sem;//入语义栈的词
    list<TOKEN>::iterator ch_function;//函数名标记
    list<TOKEN>::iterator ch_struct;//struct 的标记
    list<TOKEN>::iterator operand_now;//当前操作数
    list<SEM>::iterator top;
    list<SEM>::iterator base;
    list<Quaternary>::iterator quater_now;//当前四元式指针
    int mark;//标明运算符位置
    int counter;//系统变量计数器
    void Bi_oper_qua();//双目算符的操作数生成
    void Unary_oper_qua();//单目算符的操作数生成
    void Assign_oper_qua();//赋值操作数生成
    void If_While_qua();//IF条件,WHILE循环操作数生成
    //void GetMark(list<TOKEN>::iterator ch_ope);//获取运算符
    void GetMark_front(list<TOKEN>::iterator ch_ope);//获取前置运算符
    int FindSynbl();//查重
    void PushSynbl();//添加进符号表
    int CoutSynbl();//输出符号表
    void CheckSynbl();//检查标识符是否被定义，未定义则记录到错误表中
    void PushRinfl();//添加进结构表
    void CoutRinfl();//输出结构表

public:
    void Grammar();
    //语法部分
    int result;
    int end;
    int begin;
    list<SYNBL>::iterator id;//用户定义标识符
    list<SYNBL>::iterator id_now;//当前标识符指针
    list<SYNBL>::iterator id_struct;//结构体名标识符指针
    list<RINFL>::iterator rinfl_now;//结构表当前指针
    //语义部分
    list<TOKEN>::iterator ch_ope;//操作符 
    void CoutQuaternary();
};

void GrammaticalAnalysis::Grammar()//语法分析初始化部分
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
    result=Start();//执行语法和语义动作
    CheckSynbl();//检查四元式中用户定义的标识符是否在符号表中存在
    CoutSynbl();//输出符号表信息
    CoutQuaternary();
}

void GrammaticalAnalysis::nextW()//读取下一个单词
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

void GrammaticalAnalysis::CheckSynbl()//检查表示标识符是否被定义
{
    int m;
    list<Quaternary>::iterator q=Q_list.begin();
    for(q;q!=Q_list.end();q++)
    //vector<Operand> operand
    //操作数数组，存放操作符后面的三个操作数
    {
        for(int i=0;i<3;i++)
        {
            if((*q).operand[i].tpToken->token=="IT")  //如果操作符的类型为标识符
            //(*ch).token.find("IT")!=string::npos
            //list<SYNBL> SYNBL_list;//标识符表
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
		            //cout<<"变量未被定义"<<endl;
		            TOKEN Token;
		            Token.token = "ERROR";
		            ERRORL newerr;
		            newerr.name = (*((*((*q).operand[i].tpToken)).tpIT)).name;
		            newerr.type = 'u'; //表示变量未定义
		            ERRORL_list.push_back(newerr);
		        }
        	}
        }
    }
}


int GrammaticalAnalysis::CoutSynbl()//输出符号表
{
    cout<<"SYNBL"<<endl;
    for(list<SYNBL>::iterator it=SYNBL_list.begin();it!=SYNBL_list.end();it++)
    {
        cout<<"变量名:"<<(*it).name<<"  类型:"<<((*it).type)->tval<<"  种类:"<<(*it).cat<<"  长度:"<<(*it).lenl->length<<endl;
    }
}

void GrammaticalAnalysis::CoutRinfl()//输出结构表
{
    cout<<" RINFL:"<<endl;
    cout<<"域名"<<"   区距"<<"   种类"<<endl;
    for(list<RINFL>::iterator it=RINFL_list.begin();it!=RINFL_list.end();it++)
            cout<<"  "<<(*it).id<<"      "<<(*it).off<<"      "<<((*it).tp)->tval<<endl;
}

//缺少输出数组表 有待补充

void GrammaticalAnalysis::CoutQuaternary()//输出四元式
{
    for(list<Quaternary>::iterator p=Q_list.begin();p!=Q_list.end();p++)
    {//输出队列中的全部四元式
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
            //注意这里临时变量的考虑 后续还需要进行修改
        }
        cout<<")"<<endl;
    }
}

void GrammaticalAnalysis::Unary_oper_qua()//单目算符操作数生成
{
    Quaternary quat;
    quat.Operator=(*ch_ope).tpOT;  //生成操作符
    cout << "单目运算符:" << *((*ch_ope).tpOT) << endl;
    Operand q;
    q.tpToken=(*(--SEM_stack.end())).tpToken;
    quat.operand.push_back(q);//第一个第一个操作数
    SEM_stack.erase(--SEM_stack.end());//将其从语义栈中释放
    Operand p;
    p.tpToken=tt.begin();
    quat.operand.push_back(p);//生成第二个操作数 为空
    TOKEN temp;     //生成临时变量
    temp.token="99";
    temp.line=counter;
    counter++;
    TEMP_var.push_back(temp);
    Operand m;
    m.tpToken=(--TEMP_var.end());
    quat.operand.push_back(m);  //第三个操作数为临时变量
    Q_list.push_back(quat);
    SEM sem;
    sem.tpToken=(--TEMP_var.end());  //临时变量入语义栈
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
//	    //注意这里临时变量的考虑 后续还需要进行修改
//	}
//	cout<<")"<<endl;
}

void GrammaticalAnalysis::Assign_oper_qua()//赋值操作数生成
{
    Quaternary quat;
    quat.Operator=(*ch_ope).tpOT;  //生成操作符
    Operand q;
    q.tpToken=(*(--(SEM_stack.end()))).tpToken;
    quat.operand.push_back(q);//第一个操作数
    SEM_stack.pop_back();//将其从语义栈中释放
    Operand p;
    p.tpToken=tt.begin();
    quat.operand.push_back(p);//生成第二个操作数为空
    Operand m;
    m.tpToken=(*(--(SEM_stack.end()))).tpToken;
    quat.operand.push_back(m);//第三个操作数
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
//	    //注意这里临时变量的考虑 后续还需要进行修改
//	}
//	cout<<")"<<endl;
}

void GrammaticalAnalysis::Bi_oper_qua()//双目算符操作数生成
{
    Quaternary quat;
    quat.Operator=(*ch_ope).tpOT;  //生成操作符
    Operand q;
    q.tpToken=(*(--SEM_stack.end())).tpToken;
    quat.operand.push_back(q);//第一个操作数
    SEM_stack.erase(--SEM_stack.end());//将其从语义栈中释放
    Operand p;
    p.tpToken=(*(--SEM_stack.end())).tpToken;
    quat.operand.push_back(p);//第二个操作数
    SEM_stack.erase(--SEM_stack.end());//将其从语义栈中释放

    TOKEN temp;     //生成临时变量
    temp.token="99";
    temp.line=counter;
    counter++;
    TEMP_var.push_back(temp);
    Operand m;
    m.tpToken=(--TEMP_var.end());
    quat.operand.push_back(m);  //第三个操作数为临时变量
    Q_list.push_back(quat);
    SEM sem;
    sem.tpToken=(--TEMP_var.end());  //临时变量入语义栈
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
//	    //注意这里临时变量的考虑 后续还需要进行修改
//	}
//	cout<<")"<<endl;
}

void GrammaticalAnalysis::If_While_qua()//IF,WHILE,COUT结构操作数生成
{
    Quaternary quat;
    quat.Operator=(*ch_ope).tpOT;  //生成操作符

    if(*((*ch_ope).tpOT)=="if"||*((*ch_ope).tpOT)=="do"||*((*ch_ope).tpOT)=="co")
    {//if do cout
        Operand q;
        q.tpToken=(*(--SEM_stack.end())).tpToken;
        quat.operand.push_back(q);//第一个第一个操作数
        SEM_stack.erase(--SEM_stack.end());//将其从语义栈中释放
    }
    else
    {
        Operand p;
        p.tpToken=tt.begin();
        quat.operand.push_back(p);//生成第一个操作数 为空
    }
    Operand p;
    p.tpToken=tt.begin();
    quat.operand.push_back(p);//生成第二、三个操作数 为空
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
//	    //注意这里临时变量的考虑 后续还需要进行修改
//	}
//	cout<<")"<<endl;
}

//void GrammaticalAnalysis::GetMark(list<TOKEN>::iterator ch_ope)//获取运算符
//{	
//	cout<<"运算符:"<<*((*ch_ope).tpOT)<<endl;
//}

void GrammaticalAnalysis::GetMark_front(list<TOKEN>::iterator ch_ope)//获取前置运算符
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

int GrammaticalAnalysis::Start()//语法分析开始
{
    while(!end)
	{//Function()
        if(!Function()){return 0;}
    }
    return 1;
}

int GrammaticalAnalysis::Function()//函数
{
    if(!FType())
    {//FType 返回值为0 则 Function返回值为0
        return 0;
    }
    if(!end&&(*ch).token.find("IT")!=string::npos)
    {//IT 判断是否是IT，是则读入下一个词，不是则返回值为0
        ch_function=ch;
        ch_sem=ch_function;
        if ((*(*ch_sem).tpIT).name=="main")
            {nextW();}
        else
        {
            if(!FindSynbl())//查重
            {
                PushSynbl();//添加进符号表
                TYPEL* p=new TYPEL;//定义新的类型表，并初始化
                (*id_now).type=p;
                ((*id_now).type)->tval='f';
                (*id_now).lenl=new LENL;//定义新的长度表
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
            {//出现语法错误，重复定义
                ERRORL e;//定义错误表
                e.name = (*((*ch_sem).tpIT)).name;
                e.line = (*ch_sem).line;
                e.type='m';//错误类型
                ERRORL_list.push_back(e);
            }
        nextW();
        }
    }
    else{return 0;}
    if(!end && (*ch).token == "PT2")
    {//(   判断是否是(，是则读入下一个词，不是则返回值为0
        nextW();
    }
    else{return 0;}
    if(!Parameter())
    {// Parameter()返回值为0，则Function返回值为0
        return 0;
    }
    if(!end &&(*ch).token == "PT3")
    {//)  判断是否是)，是则读入下一个词，不是则返回值为0
        nextW();
    }
    else{return 0;}
    if(!end &&(*ch).token == "PT0")
    {//{  判断是否是{，是则读入下一个词，不是则返回值为0
        nextW();
    }
    else{return 0;}
    if(!Declaration()){return 0;}//Declaration() 进入Declaration子程序，返回值为0，则Function返回值为0
    if(!Content()){return 0;}//Content()  进入Content子程序，返回值为0，则Function返回值为0
    if(!end &&(*ch).token == "PT1")
    {//}  判断是否是}，是则读入下一个词，不是则返回值为0
        nextW();
    }
    else{return 0;}
    return 1;
}

int GrammaticalAnalysis::Parameter()//函数参数
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

int GrammaticalAnalysis::FType()//函数类型
{
    if(!end &&(*ch).token == "KT18")
    {//void
        nextW();
        return 1;
    }
    if(!Type()){return 0;}//Type()
    return 1;
}

int GrammaticalAnalysis::Type()//基本数据类型
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

int GrammaticalAnalysis::Declaration()//声明
{
    while(!end &&((*ch).token == "KT2"||(*ch).token == "KT4"||(*ch).token == "KT6"||(*ch).token == "KT7"))
    {
        if(!end &&(*ch).token == "KT7")
        {//struct 不能生成结构体四元式
            ch_struct=ch;
            nextW();
            if(!end&&(*ch).token.find("IT")!=string::npos)
            {//Identifier
                ch_sem=ch;
                nextW();
                d=1;//结构体
                if(!end &&(*ch).token == "PT0")
                {//{
                    if(!FindSynbl())
                    {//查重
                        PushSynbl();
                        TYPEL* p=new TYPEL;
                        (*(id_now)).type=p;
                        rinfl_now=(*(id_now)).type->rinfl;
                        (*(id_now)).type->tval='t';
                        (*(id_now)).lenl=new LENL;//定义新的长度表
                        (*(id_now)).lenl->length=0;
                        (*(id_now)).cat='d';
                        id_struct=id_now;
                }
                else
                {//出现语法错误，重复定义
                    ERRORL e;//定义错误表
                    e.name = (*((*ch_sem).tpIT)).name;
                    e.line = (*ch_sem).line;
                    e.type='m';//错误类型
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
            {//结构体定义
                type=ch_struct;
                d=0;
                if(Id())
                {//IT
                    (*(id_now)).type->rinfl=(*(id_struct)).type->rinfl;//定义新的长度表
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

int GrammaticalAnalysis::Base_declaration()//基本类型声明
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
                    if(!FindSynbl())//查重
                    {
                        PushSynbl();//添加进符号表
                        TYPEL* p=new TYPEL;//定义新的类型表，并初始化
                        if(d){p->tval='d';}//结构体类型
                        else {p->tval='a';}//数组型
                        AINFL newa;//定义新的数组表，并初始化
                        newa.low = 0;//数组下界为0
                        newa.up = ((*num_temp).tpI)->numi-1;//数组上界为integer-1
                        newa.ctp = new TYPEL;//成分类型指针，指向对应的成分类型
                        if((*type).token == "KT2")//int
                            {(*id_now).cat ='i';}
                        else if((*type).token == "KT4")//real
                            {(*id_now).cat ='r';}
                        else if((*type).token == "KT6")//char
                            {(*id_now).cat ='c';}
                        newa.clen=(newa.up + 1) * 2;//成分类型的长度，默认为数组长度乘2
                        AINFL_list.push_back(newa);
                        p->ainfl = --(AINFL_list.end());
                        (*id_now).lenl = new LENL;//定义新的长度表，并初始化
                        (*id_now).lenl->length=newa.clen;//将长度信息存入长度表中
                        (*id_now).type = p;
                        if (d)
                        {
                            PushRinfl();
                        }
                    }
	                else{//出现语法错误，重复定义
                        ERRORL e;//定义错误表
						e.name = (*((*ch_sem).tpIT)).name;
                        e.line = (*ch_sem).line;
                        e.type='m';//错误类型
                        ERRORL_list.push_back(e);
                    }
                    nextW();
                    return 1;//数组类型
                }
                else {return 0;}
            }
            else {return 0;}
        }
        else //整型
        {
            if(!FindSynbl())
            {//查重
                PushSynbl();//添加进符号表
                TYPEL* p=new TYPEL;
                AINFL newa;
                RINFL newr;
				(*id_now).type = p;
                if(d){((*id_now).type)->tval='d';}//域名
                else {((*id_now).type)->tval='v';}//变量
                if((*type).token == "KT2")//int
	                {(*id_now).cat ='i';}
	            else if((*type).token == "KT4")//real
	                {(*id_now).cat ='r';}
	            else if((*type).token == "KT6")//char
	                {(*id_now).cat ='c';}
	            else if((*type).token == "KT7")//struct
	                {(*id_now).cat ='d';}
                (*id_now).lenl=new LENL;//定义新的长度表
                ((*id_now).lenl)->length=2;//默认设置int,char,real长度均为2
                if (d)
                {
                    PushRinfl();
                }
            }
            else
            {//出现语法错误，重复定义
            	ERRORL e;//定义错误表
				e.name = (*((*ch_sem).tpIT)).name;
                e.line = (*ch_sem).line;
                e.type='m';//错误类型
                ERRORL_list.push_back(e);
            }
            return 1;
        }//基本类型标识符
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
            SEM_stack.push_back(sem);//基本类型标识符入栈
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
                    SEM_stack.push_back(sem);//基本类型标识符入栈
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
                    return 1;//数组类型
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
                SEM_stack.push_back(sem);//基本类型标识符入栈
            }
            return 1;
        }//基本类型标识符
    }
    return 0;
}

int GrammaticalAnalysis::Content(){//内容
    while(!end )
    {
        if(!Structure())
        {//Structure()
            return 0;
        }
        else
        {
            if(!end &&(*ch).token == "PT1"){return 1;}//若下一个词为'}',则说明结束，跳出
        }
    }
    return 1;
}

int GrammaticalAnalysis::Structure()//内容结构选择
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
                        if(!end &&(*ch).token == "PT1"){return 1;}//若下一个词为'}',则说明结束，跳出,此处不读词
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

int GrammaticalAnalysis::Cout()//输出函数
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

int GrammaticalAnalysis::Fun()//函数表达式
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
                {//Assignment(),无参数
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
                {//有参数
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
            {//若不是函数表达式，则返回记录位置
                ch=ch_temp;
                return 0;
            }
        }
    }
    else {return 0;}
}

int GrammaticalAnalysis::Expression()//表达式
{
    if(!Assignment()){return 0;}//Assignment()
    while(!end&&(*ch).token=="PT9")
    {//,
        ch_ope=ch;
        nextW();
        if(!Assignment()){return 0;}//Assignment()
        //GetMark(ch_ope);//用来获取运算符
        Unary_oper_qua();//单目算符的操作数生成
    }
    return 1;
}

int GrammaticalAnalysis::Assignment()//赋值
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
            SEM_stack.push_back(sem);//基本类型标识符入栈
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
                        //GetMark(ch_ope);//获取运算符
                        Assign_oper_qua();//赋值操作数生成
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
                        Assign_oper_qua();//赋值操作数生成
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

int GrammaticalAnalysis::Logical_or()//逻辑或
{
    if(!Logical_and()){return 0;}
    while(!end&&(*ch).token=="OT15")
    {
        ch_ope=ch;
        nextW();
        if(!Logical_and()){return 0;}
		//GetMark(ch_ope);//用来获取运算符
        Bi_oper_qua();//双目算符的操作数生成
    }
    return 1;
}

int GrammaticalAnalysis::Logical_and()//逻辑与
{
    if(!Inclusive_or()){return 0;}
    while(!end&&(*ch).token=="OT14")
    {
        ch_ope=ch;
        nextW();
        if(!Inclusive_or()){return 0;}
        //GetMark(ch_ope);//用来获取运算符
        Bi_oper_qua();//用来双目算符的操作数生成
    }
    return 1;
}

int GrammaticalAnalysis::Inclusive_or()//或运算
{
    if(!Exclusive_or()){return 0;}
    while(!end&&(*ch).token=="OT18")
    {
        ch_ope=ch;
        nextW();
        if(!Exclusive_or()){return 0;}
        //GetMark(ch_ope);//用来获取运算符
        Bi_oper_qua();//用来双目算符的操作数生成
    }
    return 1;
}

int GrammaticalAnalysis::Exclusive_or()//异或运算
{
    if(!And()){return 0;}
    while(!end&&(*ch).token=="OT19")
    {
        ch_ope=ch;
        nextW();
        if(!And()){return 0;}
        //GetMark(ch_ope);//用来获取运算符
        Bi_oper_qua();//用来双目算符的操作数生成
    }
    return 1;
}

int GrammaticalAnalysis::And()//与运算
{
    if(!Equality()){return 0;}
    while(!end&&(*ch).token=="OT17")
    {
        ch_ope=ch;
        nextW();
        if(!Equality()){return 0;}
        //GetMark(ch_ope);//用来获取运算符
        Bi_oper_qua();//用来双目算符的操作数生成
    }
    return 1;
}

int GrammaticalAnalysis::Equality()//等值判断，==或者!=
{
    if(!Relational()){return 0;}
    while(!end&&((*ch).token=="OT12"||(*ch).token=="OT13"))
    {//==,!=
        ch_ope=ch;
        nextW();
        if(!Relational()){return 0;}
        //GetMark(ch_ope);//用来获取运算符
        Bi_oper_qua();//用来双目算符的操作数生成

    }
    return 1;
}

int GrammaticalAnalysis::Relational()//关系运算，>,>=,<,<=
{
    if(!Shift()){return 0;}
    while(!end&&((*ch).token=="OT8"||(*ch).token=="OT9"||(*ch).token=="OT10"||(*ch).token=="OT11"))
    {
        ch_ope=ch;
        nextW();
        if(!Shift()){return 0;}
        //GetMark(ch_ope);//用来获取运算符
        Bi_oper_qua();//用来双目算符的操作数生成

    }
    return 1;
}

int GrammaticalAnalysis::Shift()//移位运算，>>,<<
{
    if(!Additive()){return 0;}
    while(!end&&((*ch).token=="OT21"||(*ch).token=="OT22"))
    {
        ch_ope=ch;
        nextW();
        if(!Additive()){return 0;}
        //GetMark(ch_ope);//用来获取运算符
        Bi_oper_qua();//用来双目算符的操作数生成
    }
    return 1;
}

int GrammaticalAnalysis::Additive()//加法，减法，+,-
{
    if(!Multiplicative()){return 0;}
    while(!end&&((*ch).token=="OT0"||(*ch).token=="OT1"))
    {
        ch_ope=ch;
        nextW();
        if(!Multiplicative()){return 0;}
        //GetMark(ch_ope);//用来获取运算符
        Bi_oper_qua();//用来双目算符的操作数生成
    }
    return 1;
}

int GrammaticalAnalysis::Multiplicative()//乘法，除法，取模，*,/,%
{
    if(!Unary()){return 0;}
    while(!end&&((*ch).token=="OT2"||(*ch).token=="OT3"||(*ch).token=="OT4"))
    {
        ch_ope=ch;
        nextW();
        if(!Unary()){return 0;}
        //GetMark(ch_ope);//用来获取运算符
        Bi_oper_qua();//用来双目算符的操作数生成

    }
    return 1;
}

int GrammaticalAnalysis::Unary()//前置算符，非，取补，自增，自减，求大小,!,~,INC,DEC,sizeof
{
    if(!end&&((*ch).token=="OT16"||(*ch).token=="OT20"||(*ch).token=="OT5"||(*ch).token=="OT6"||(*ch).token=="KT30"))
    {
        ch_ope=ch;
        nextW();
        if(!Postfix()){return 0;}
        GetMark_front(ch_ope);//用来获取运算符
        Unary_oper_qua();//用来单目算符的操作数生成
    }
    else
    {
        if(!Postfix()){return 0;}
    }
    return 1;
}

int GrammaticalAnalysis::Postfix()//后置算符，[Expression],++,--,.
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
                    Bi_oper_qua();//用来双目算符的操作数生成
                }
                else {return 0;}
            }
        }
        else if((*ch).token=="PT10")
        {//.
            nextW();
            if(!end&&(*ch).token.find("IT")!=string::npos)
            {//Identifier
                ch_sem=ch;/*语义分析*/
                SEM sem;
                sem.tpToken=ch_sem;
                SEM_stack.push_back(sem);//基本类型标识符入栈
                for(vector<string>::iterator it =  OperatorL.begin(); it != OperatorL.end(); it++)
		       {
					if(*it == ".")
					{
						(*ch_ope).tpOT = it;
						break;
					}
			   }
                Bi_oper_qua();//用来双目算符的操作数生成
                nextW();
            }
            else {return 0;}
        }
        else
        {//若为++，--，直接读取下一个字符

            //GetMark(ch);//用来获取运算符
            Unary_oper_qua();//单目算符的操作数生成
            nextW();
        }
    }
    return 1;
}

int GrammaticalAnalysis::Primary()//主表达式,标识符，常量，继续循环：i,constant,(Expression)
{
    if(!end&&(*ch).token.find("IT")!=string::npos)
    {//Identifier
        ch_sem=ch;
        SEM sem;
        sem.tpToken=ch_sem;
        SEM_stack.push_back(sem);//基本类型标识符入栈
        nextW();
        return 1;
    }
    if(!end&&(*ch).token.find("ZT")!=string::npos)
    {//Integer
        ch_sem=ch;
        SEM sem;
        sem.tpToken=ch_sem;
        SEM_stack.push_back(sem);//基本类型标识符入栈
        nextW();
        return 1;
    }
    if(!end&&(*ch).token.find("RT")!=string::npos)
    {//Real
        ch_sem=ch;
        SEM sem;
        sem.tpToken=ch_sem;
        SEM_stack.push_back(sem);//基本类型标识符入栈
        nextW();
        return 1;
    }
    if(!end&&(*ch).token.find("CT")!=string::npos)
    {//Char
        ch_sem=ch;
        SEM sem;
        sem.tpToken=ch_sem;
        SEM_stack.push_back(sem);//基本类型标识符入栈
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
                                else {return 1;}//无else
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

int GrammaticalAnalysis::FindSynbl()//查重
{
    list<SYNBL>::iterator it;
    for(it = SYNBL_list.begin(); it != SYNBL_list.end(); it++)
    {
    	if((*it).name == (*((*ch_sem).tpIT)).name)
    		return 1;
	}
	return 0;
}

void GrammaticalAnalysis::PushSynbl()//添加进符号表
{
    SYNBL newid = *((*ch_sem).tpIT);
    SYNBL_list.push_back(newid);
    id_now = --(SYNBL_list.end());
}

void GrammaticalAnalysis::PushRinfl()//添加进结构表
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

