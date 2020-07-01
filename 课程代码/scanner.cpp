#include "head.h"

/*
δ���֮��
1.��ȡ��ע�����Ͻ�ʶ���ַ����Զ������棬Ԥ����ֻ�������ļ��ж�ȡԴ��
2.��¼ÿ�����ʵ�����
3.����Ա������������ĵ�����������������Ա�ʾ
*/

bool checker::IsWord(char c)//�����Ƿ�Ϊ��ĸ
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return true;
	}
	else
		return false;
}

bool checker::IsNumber(char c)//�����Ƿ�Ϊ����
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	else
		return false;
}

bool checker::IsZhibiao(char c)//�����Ƿ�Ϊ�Ʊ��������Ϊ���ʵķֽ��ߣ�
{
	if (c == ' ' || c == '\n' || c == '\t')
	{
		return true;
	}
	else
		return false;
}

bool checker::IsPTOT(char c)//�����Ƿ�Ϊ�������������һ����
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

void recognizer::State_1()//��ʼ״̬
{
	int& i = source_pt;
	temp.clear();
	while (i < source.size())
	{
		if (checker::IsZhibiao(source[i]) == true)
		{//�����Ʊ��
			i++;
			continue;
		}
		else if (source[i] == '_' || checker::IsWord(source[i]) == true)
		{//��ʶ��
			recognizer::State_2();
			break;
		}
		else if (checker::IsNumber(source[i]) == true)
		{//����
			recognizer::State_3();
			break;
		}
		else if (source[i] == 39)//�����ŵ�ASCII��
		{//�ַ�
			recognizer::State_4();
			break;
		}
		else if (source[i] == 34)//˫���ŵ�ASCII��
		{//�ַ���
			recognizer::State_5();
			break;
		}
		else if (checker::IsPTOT(source[i]) == true)
		{//����������
			recognizer::State_6();
			break;
		}
		else
		{//δ֪�ַ�
			recognizer::State_7('n');
			break;
		}
	}
	return;
}

void recognizer::State_2()//�����ʶ��
{
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	while (checker::IsWord(source[i]) == true || checker::IsNumber(source[i]) == true || source[i] == '_')
	{//��ĸ�����֡��»���
		temp.push_back(source[i]);
		i++;
		if (i >= source.size())//��ֹԽ��
		{
			break;
		}
	}
	if (i < source.size() && checker::IsPTOT(source[i]) == false && checker::IsZhibiao(source[i]) == false)//���Ϊ�ǽ�����־
	{//�����ַ�
		recognizer::State_7('i');
		return;
	}
	for(vector<string>::iterator it = KT.begin(); it != KT.end(); it++)
    {
        if(temp == *it)//�ڹؼ��ֱ��в��ҵ�����
        {
            Token.tpKT = it;
            Token.line = line;
            return;
        }
    }
    for(list<SYNBL>::iterator it = SYNBL_list.begin(); it != SYNBL_list.end(); it++)
    {
        if(temp == (*it).name)//�ڷ��ű��ҵ��ñ�ʶ������ָ�������ʶ������λ��
        {
            Token.tpIT = it;
        }
        else//�³��ֵı�ʶ�������뵽���ű���
        {
            SYNBL newid;
            newid.name = temp;
            SYNBL_list.push_back(newid);
            Token.tpIT = --SYNBL_list.end();//ȡ���һ��Ԫ�صĵ�����
        }
    }
    Token.line = line;
    return;
}

void recognizer::State_3()//������
{
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	while (checker::IsNumber(source[i]) == true)
	{//����
		temp.push_back(source[i]);
		i++;
		if (i >= source.size())//��ֹԽ��
		{
			int intc;//����Ϊ�����ͣ��ַ���תΪ������
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
	{//С����
		temp.push_back(source[i]);
		i++;
		while (checker::IsNumber(source[i]) == true)
		{//����
			temp.push_back(source[i]);
			i++;
			if (i >= source.size())//��ֹԽ��
			{
				float floatc;//����Ϊʵ���ͣ��ַ���תΪ������
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
        {//����������Ʊ��ֹͣ
            float floatc;//����Ϊʵ���ͣ��ַ���תΪ������
            stringstream s;
            s << temp;
            s >> floatc;
            Token.tpR = new REAL;
            Token.tpR->numf = floatc;
            Token.line = line;
            return;
        }
        else
        {//�����ַ�
            recognizer::State_7('R');
            return;
        }
	}
	else if (checker::IsPTOT(source[i]) == true || checker::IsZhibiao(source[i]) == true)
	{//����������Ʊ��ֹͣ
		int intc;//����Ϊ�����ͣ��ַ���תΪ������
        stringstream s;
        s << temp;
        s >> intc;
        Token.tpI = new INT;
        Token.tpI->numi = intc;
        Token.line = line;
        return;
	}
	else
	{//�����ַ�
		recognizer::State_7('Z');
		return;
	}
}

void recognizer::State_4()//�����ַ�
{
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	i++;//������һ��������
	if (i >= source.size())
	{//��ֹԽ��
		for(vector<string>::iterator it = PT.begin(); it != PT.end(); it++)
        {//'��Ϊ�����β��һ�������
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
		{//Խ����δƥ�䵽��һ��'��������˻��з�
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
    {//�հ��ַ�����������
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
    Token.tpC->numc = temp[0];//ֻ������һ���ַ�
    Token.line = line;
	i++;
	return;
}

void recognizer::State_5()//�����ַ���
{
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	i++;
	if (i >= source.size())
	{//��ֹԽ��
		for(vector<string>::iterator it = PT.begin(); it != PT.end(); it++)
        {//'��Ϊ�����β��һ�������
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
		{//Խ����δƥ�䵽��һ��'��������˻��з�
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

void recognizer::State_6()//��������������
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
	{//��ΪԴ��������һ���ַ���ֱ�Ӵ���
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
	{//����˫Ŀ����������
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

void recognizer::State_7(char mode)//��������ַ�
{
	int& i = source_pt;
	TOKEN Token;
	Token_clear(Token);
	while (i < source.size() && checker::IsPTOT(source[i]) == false && checker::IsZhibiao(source[i]) == false)
	{//����һ��������Ʊ��ǰ���ַ�����Ϊ�ô��󵥴�
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

void preprocessor()//����Ԥ����Դ���룬ȥ��ע��
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
		{//ȥ������ע��
			while (i != source.size() && source[i] != '\n')
			{
				i++;
				length++;
			}
			source.erase(begin, length);
			i = begin - 1;//����i��λ��
			continue;
		}
		if (i != source.size() - 1 && source[i] == '/' && source[i + 1] == '*')
		{//ȥ������ע��
			while (i != source.size() - 1 && (source[i] != '*' || source[i + 1] != '/'))
			{
				i++;
				length++;
			}
			if (i == source.size() - 1)//�Ѽ�鵽ĩβ
			{
				source.erase(begin);
				break;
			}
			length += 2;//����*/�ĳ���
			source.erase(begin, length);
			i = begin - 1;//����i��λ��
			continue;
		}
	}
}

void Token_clear(TOKEN& Token)//��һ��TOKEN���������
{
    Token.token.clear();
    Token.line = 0;
    Token.tpI = NULL;
    Token.tpR = NULL;
    Token.tpC = NULL;
}

void SCANNER()//�ʷ�����
{
    recognizer::State_1();//���õ���ʶ������ʶ��Ľ��������TOKEN��
}
