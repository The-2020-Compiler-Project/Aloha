#include "head.h"

/*
未完成之事
1.把取消注释整合进识别字符的自动机里面，预处理只保留从文件中读取源码
2.记录每个单词的行数
3.和组员商量各个种类的单词用哪种序列码加以表示
*/

bool checker::IsWord(char c)//检验是否为字母
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return true;
	}
	else
		return false;
}

bool checker::IsNumber(char c)//检验是否为数字
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	else
		return false;
}

bool checker::IsZhibiao(char c)//检验是否为制表符（可视为单词的分界线）
{
	if (c == ' ' || c == '\n' || c == '\t')
	{
		return true;
	}
	else
		return false;
}

bool checker::IsPTOT(char c)//检验是否为界符、算术符的一部分
{
	for (unsigned int i = 0; i < PT.size(); i++)
	{
		if (PT[i].find(c, 0) != string::npos)
		{
			return true;
		}
	}
	for (unsigned int i = 0; i < OT.size(); i++)
	{
		if (OT[i].find(c, 0) != string::npos)
		{
			return true;
		}
	}
	return false;
}

void recognizer::State_1()//初始状态
{
	int& i = source_pt;
	temp.clear();
	while (i < source.size())
	{
		if (checker::IsZhibiao(source[i]) == true)
		{//跳过制表符
			i++;
			continue;
		}
		else if (source[i] == '_' || checker::IsWord(source[i]) == true)
		{//标识符
			recognizer::State_2();
			break;
		}
		else if (checker::IsNumber(source[i]) == true)
		{//常数
			recognizer::State_3();
			break;
		}
		else if (source[i] == 39)//单引号的ASCII码
		{//字符
			recognizer::State_4();
			break;
		}
		else if (source[i] == 34)//双引号的ASCII码
		{//字符串
			recognizer::State_5();
			break;
		}
		else if (checker::IsPTOT(source[i]) == true)
		{//界符或运算符
			recognizer::State_6();
			break;
		}
		else
		{//未知字符
			recognizer::State_7('n');
			break;
		}
	}
	return;
}

void recognizer::State_2()//处理标识符
{
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	while (checker::IsWord(source[i]) == true || checker::IsNumber(source[i]) == true || source[i] == '_')
	{//字母、数字、下划线
		temp.push_back(source[i]);
		i++;
		if (i >= source.size())//防止越界
		{
			break;
		}
	}
	if (i < source.size() && checker::IsPTOT(source[i]) == false && checker::IsZhibiao(source[i]) == false)//最后为非结束标志
	{//错误字符
		recognizer::State_7('i');
		return;
	}
	for(vector<string>::iterator it = KT.begin(); it != KT.end(); it++)
    {
        if(temp == *it)//在关键字表中查找到单词
        {
            Token.tpKT = it;
            Token.line = line;
            return;
        }
    }
    for(list<SYNBL>::iterator it = SYNBL_list.begin(); it != SYNBL_list.end(); it++)
    {
        if(temp == (*it).name)//在符号表找到该标识符，则指向这个标识符所在位置
        {
            Token.tpIT = it;
        }
        else//新出现的标识符，加入到符号表中
        {
            SYNBL newid;
            newid.name = temp;
            SYNBL_list.push_back(newid);
            Token.tpIT = --SYNBL_list.end();//取最后一个元素的迭代器
        }
    }
    Token.line = line;
    return;
}

void recognizer::State_3()//处理常数
{
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	while (checker::IsNumber(source[i]) == true)
	{//数字
		temp.push_back(source[i]);
		i++;
		if (i >= source.size())//防止越界
		{
			int intc;//常数为整数型，字符型转为整数型
			stringstream s;
			s << temp;
			s >> intc;
			Token.tpI = new INT;
			Token.tpI->numi = intc;
			Token.line = line;
			return;
		}
	}
	if (source[i] == '.')
	{//小数点
		temp.push_back(source[i]);
		i++;
		while (checker::IsNumber(source[i]) == true)
		{//数字
			temp.push_back(source[i]);
			i++;
			if (i >= source.size())//防止越界
			{
				float floatc;//常数为实数型，字符型转为浮点型
                stringstream s;
                s << temp;
                s >> floatc;
                Token.tpR = new REAL;
                Token.tpR->numf = floatc;
                Token.line = line;
                return;
			}
		}
		if (checker::IsPTOT(source[i]) == true || checker::IsZhibiao(source[i]) == true)
        {//遇到界符或制表符停止
            float floatc;//常数为实数型，字符型转为浮点型
            stringstream s;
            s << temp;
            s >> floatc;
            Token.tpR = new REAL;
            Token.tpR->numf = floatc;
            Token.line = line;
            return;
        }
        else
        {//错误字符
            recognizer::State_7('R');
            return;
        }
	}
	else if (checker::IsPTOT(source[i]) == true || checker::IsZhibiao(source[i]) == true)
	{//遇到界符或制表符停止
		int intc;//常数为整数型，字符型转为整数型
        stringstream s;
        s << temp;
        s >> intc;
        Token.tpI = new INT;
        Token.tpI->numi = intc;
        Token.line = line;
        return;
	}
	else
	{//错误字符
		recognizer::State_7('Z');
		return;
	}
}

void recognizer::State_4()//处理字符
{
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	i++;//跳过第一个单引号
	if (i >= source.size())
	{//防止越界
		for(vector<string>::iterator it = PT.begin(); it != PT.end(); it++)
        {//'作为程序结尾则按一个界符算
            if(*it == "\'")
            {
                Token.tpPT = it;
            }
        }
		Token.line = line;
		return;
	}
	while (source[i] != 39)
	{
		if (source[i] == '\n' || i >= source.size())
		{//越界尚未匹配到下一个'，或出现了换行符
			Token.line = line;
            Token.token = 'c';
            ERRORL newerr;
            newerr.name = temp;
            newerr.line = line;
            newerr.type = 'c';
            ERRORL_list.push_back(newerr);
			return;
		}
		temp.push_back(source[i]);
		i++;
	}
	if(temp.size() == 0)
    {//空白字符，按错误处理
        Token.line = line;
        Token.token = 'c';
        ERRORL newerr;
        newerr.name = "\'\'";
        newerr.line = line;
        newerr.type = 'c';
        ERRORL_list.push_back(newerr);
        return;
    }
    Token.tpC = new CHAR;
    Token.tpC->numc = temp[0];//只保留第一个字符
    Token.line = line;
	i++;
	return;
}

void recognizer::State_5()//处理字符串
{
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	i++;
	if (i >= source.size())
	{//防止越界
		for(vector<string>::iterator it = PT.begin(); it != PT.end(); it++)
        {//'作为程序结尾则按一个界符算
            if(*it == "\"")
            {
                Token.tpPT = it;
            }
        }
		Token.line = line;
		return;
	}
	while (source[i] != 34)
	{
		if (source[i] == '\n' || i >= source.size())
		{//越界尚未匹配到下一个'，或出现了换行符
			Token.line = line;
            Token.token = 's';
            ERRORL newerr;
            newerr.name = temp;
            newerr.line = line;
            newerr.type = 's';
            ERRORL_list.push_back(newerr);
            return;
		}
		temp.push_back(source[i]);
		i++;
	}
    Token.tps = temp;
    Token.line = line;
	i++;
	return;
}

void recognizer::State_6()//处理界符和算术符
{
	/*"[", "]", "(", ")", ".", "->", "-", "++", "--", "*", "&", "!",
	"/", "%", "+", ">", "<", ">=", "<=", "==", "!=", "&&", "||", "=",
	"+=", "-=", "*=", "/=", "%=", ",", ";", "|"*/
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	char c = source[i];
	i++;
	temp.push_back(c);
	if (i == source.size())
	{//若为源程序的最后一个字符，直接处理
	    for(vector<string>::iterator it = PT.begin(); it != PT.end(); it++)
        {
            if(*it == temp)
            {
                Token.tpPT = it;
            }
        }
        for(vector<string>::iterator it = OT.begin(); it != OT.end(); it++)
        {
            if(*it == temp)
            {
                Token.tpOT = it;
            }
        }
        Token.line = line;
		return;
	}
	switch (c)
	{//考虑双目界符或运算符
	case '+':
		if (source[i] == '+' || source[i] == '=')
		{
			temp.push_back(source[i]);
			i++;
		}
		break;
	case '-':
		if (source[i] == '-' || source[i] == '=' || source[i] == '>')
		{
			temp.push_back(source[i]);
			i++;
		}
		break;
	case '&':
		if (source[i] == '&')
		{
			temp.push_back(source[i]);
			i++;
		}
		break;
	case '|':
		if (source[i] == '|')
		{
			temp.push_back(source[i]);
			i++;
		}
		break;
	case '*':
	case '/':
	case '%':
	case '=':
	case '>':
	case '<':
	case '!':
		if (source[i] == '=')
		{
			temp.push_back(source[i]);
			i++;
		}
		break;
	default:
		break;
	}
	for(vector<string>::iterator it = PT.begin(); it != PT.end(); it++)
    {
        if(*it == temp)
        {
            Token.tpPT = it;
        }
    }
    for(vector<string>::iterator it = OT.begin(); it != OT.end(); it++)
    {
        if(*it == temp)
        {
            Token.tpOT = it;
        }
    }
    Token.line = line;
	return;
}

void recognizer::State_7(char mode)//处理错误字符
{
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	while (i < source.size() && checker::IsPTOT(source[i]) == false && checker::IsZhibiao(source[i]) == false)
	{//将下一个界符或制表符前的字符都归为该错误单词
		temp.push_back(source[i]);
		i++;
	}
	Token.line = line;
	Token.token = mode;
	ERRORL newerr;
	newerr.name = temp;
	newerr.line = line;
	newerr.type = mode;
	ERRORL_list.push_back(newerr);
	return;
}

void preprocessor()//接收预处理源代码，去除注释
{
	testfile.open("testfile.txt");
	source_pt = 0;
	char ch;
	while ((ch = testfile.get()) != EOF)
	{
		source.push_back(ch);
	}
	for (unsigned int i = 0; i < source.size(); i++)
	{
		int begin = i, length = 0;
		if (i != source.size() - 1 && source[i] == '/' && source[i + 1] == '/')
		{//去除单行注释
			while (i != source.size() && source[i] != '\n')
			{
				i++;
				length++;
			}
			source.erase(begin, length);
			i = begin - 1;//重置i的位置
			continue;
		}
		if (i != source.size() - 1 && source[i] == '/' && source[i + 1] == '*')
		{//去除多行注释
			while (i != source.size() - 1 && (source[i] != '*' || source[i + 1] != '/'))
			{
				i++;
				length++;
			}
			if (i == source.size() - 1)//已检查到末尾
			{
				source.erase(begin);
				break;
			}
			length += 2;//加上*/的长度
			source.erase(begin, length);
			i = begin - 1;//重置i的位置
			continue;
		}
	}
}

void Token_clear(TOKEN& Token)//将一个TOKEN的内容清空
{
    Token.token.clear();
    Token.line = 0;
    Token.tpI = NULL;
    Token.tpR = NULL;
    Token.tpC = NULL;
}

void SCANNER()//词法分析
{
    recognizer::State_1();//调用单词识别器，识别的结果保存在TOKEN中
}
