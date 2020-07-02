#include "head.h"

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
			if(source[i] == '\n')line++;
			i++;
			continue;
		}
		else if (source[i] == '/')
        {
            recognizer::State_1_2();
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

void recognizer::State_1_2()//ȥ��ע��
{
    int& i = source_pt;
    if (i == source.size() - 1)//б���ǳ��������һ���ַ�
    {
        recognizer::State_6();//ת���������
        return;
    }
    else if (source[i] == '/' && source[i + 1] == '/')
    {//ȥ������ע��
        while (i != source.size() && source[i] != '\n')
        {
            i++;
        }
        return;
    }
    else if (source[i] == '/' && source[i + 1] == '*')
    {//ȥ������ע��
        while (i != source.size() - 1 && (source[i] != '*' || source[i + 1] != '/'))
        {
            i++;
            if(source[i] == '\n')line++;
        }
        if (i == source.size() - 1)//�Ѽ�鵽ĩβ
        {
            i++;
            return;
        }
        else//�ҵ�����ע�ͽ�����־
        {
            i += 2;//����������־
        }
    }
    else//����ע�ͣ���Ϊһ��б�ܷ���
    {
        recognizer::State_6();//ת���������
        return;
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
	int num = 0;
	for(vector<string>::iterator it = KT.begin(); it != KT.end(); it++, num++)
    {
        if(temp == *it)//�ڹؼ��ֱ��в��ҵ�����
        {
            string nums;
            stringstream ss;
            ss << num;
            ss >> nums;
            Token.token = "KT" + nums;
            Token.tpKT = it;
            Token.line = line;
            TOKEN_list.push_back(Token);
            return;
        }
    }
    int isfind = 0;
    for(list<SYNBL>::iterator it = SYNBL_list.begin(); it != SYNBL_list.end(); it++)
    {
        if(temp == (*it).name)//�ڷ��ű��ҵ��ñ�ʶ������ָ�������ʶ������λ��
        {
            Token.tpIT = it;
            isfind = 1;
            break;
        }

    }
    if(!isfind)//�³��ֵı�ʶ�������뵽���ű���
    {
        SYNBL newid;
        newid.name = temp;
        SYNBL_list.push_back(newid);
        Token.tpIT = --SYNBL_list.end();//ȡ���һ��Ԫ�صĵ�����
    }
    Token.token = "IT";
    Token.line = line;
    TOKEN_list.push_back(Token);
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
			Token.token = "ZT";
			TOKEN_list.push_back(Token);
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
                Token.token = "RT";
                TOKEN_list.push_back(Token);
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
            Token.token = "RT";
            TOKEN_list.push_back(Token);
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
        Token.token = "ZT";
        TOKEN_list.push_back(Token);
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
		i--;
		recognizer::State_6();//Խ���򰴽����
		return;
	}
	while (source[i] != 39)
	{
		if (source[i] == '\n' || i >= source.size())
		{//Խ����δƥ�䵽��һ��'��������˻��з�
			Token.line = line;
            Token.token = "ERROR";
            ERRORL newerr;
            newerr.name = temp;
            newerr.line = line;
            newerr.type = 'c';
            ERRORL_list.push_back(newerr);
            Token.tpER = --ERRORL_list.end();
            TOKEN_list.push_back(Token);
			return;
		}
		temp.push_back(source[i]);
		i++;
	}
	if(temp.size() == 0)
    {//�հ��ַ�����������
        Token.line = line;
        Token.token = "ERROR";
        ERRORL newerr;
        newerr.name = "\'\'";
        newerr.line = line;
        newerr.type = 'c';
        ERRORL_list.push_back(newerr);
        Token.tpER = --ERRORL_list.end();
        TOKEN_list.push_back(Token);
        return;
    }
    Token.tpC = new CHAR;
    Token.tpC->numc = temp[0];//ֻ������һ���ַ�
    Token.line = line;
    Token.token = "CT";
    TOKEN_list.push_back(Token);
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
		i--;
		recognizer::State_6();//Խ���򰴽����
		return;
	}
	while (source[i] != 34)
	{
		if (source[i] == '\n' || i >= source.size())
		{//Խ����δƥ�䵽��һ��'��������˻��з�
			Token.line = line;
            Token.token = "ERROR";
            ERRORL newerr;
            newerr.name = temp;
            newerr.line = line;
            newerr.type = 's';
            ERRORL_list.push_back(newerr);
            Token.tpER = --ERRORL_list.end();
            TOKEN_list.push_back(Token);
            return;
		}
		temp.push_back(source[i]);
		i++;
	}
	Token.token = "ST";
    Token.tps = temp;
    Token.line = line;
    TOKEN_list.push_back(Token);
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
	int num = 0, isfind = 0;
	char c = source[i];
	i++;
	temp.push_back(c);
	if (i == source.size())
	{//��ΪԴ��������һ���ַ���ֱ�Ӵ���
	    for(vector<string>::iterator it = PT.begin(); it != PT.end(); it++, num++)
        {
            if(*it == temp)
            {
                Token.tpPT = it;
                string nums;
                stringstream ss;
                ss << num;
                ss >> nums;
                Token.token = "PT" + nums;
                isfind = 1;
                break;
            }
        }
        if(!isfind)
        {
            num = 0;
            for(vector<string>::iterator it = OT.begin(); it != OT.end(); it++)
            {
                if(*it == temp)
                {
                    Token.tpOT = it;
                    string nums;
                    stringstream ss;
                    ss << num;
                    ss >> nums;
                    Token.token = "OT" + nums;
                    break;
                }
            }
        }
        Token.line = line;
        TOKEN_list.push_back(Token);
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
	num = 0;
	isfind = 0;
	for(vector<string>::iterator it = PT.begin(); it != PT.end(); it++, num++)
    {
        if(*it == temp)
        {
            Token.tpPT = it;
            string nums;
            stringstream ss;
            ss << num;
            ss >> nums;
            Token.token = "PT" + nums;
            isfind = 1;
            break;
        }
    }
    if(!isfind)
    {
        num = 0;
        for(vector<string>::iterator it = OT.begin(); it != OT.end(); it++)
        {
            if(*it == temp)
            {
                Token.tpOT = it;
                string nums;
                stringstream ss;
                ss << num;
                ss >> nums;
                Token.token = "OT" + nums;
                break;
            }
        }
    }
    Token.line = line;
    TOKEN_list.push_back(Token);
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
	Token.token = "ERROR";
	ERRORL newerr;
	newerr.name = temp;
	newerr.line = line;
	newerr.type = mode;
	ERRORL_list.push_back(newerr);
	Token.tpER = --ERRORL_list.end();
	TOKEN_list.push_back(Token);
	return;
}

void preprocessor()//����Ԥ����Դ����
{
	testfile.open("testfile.txt");
	source_pt = 0;
	line = 1;
	char ch;
	while ((ch = testfile.get()) != EOF)
	{
		source.push_back(ch);
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

void testprint()
{
    preprocessor();
    int i = 1;
    while(source_pt < source.size())
    {
        SCANNER();
        list<TOKEN>::iterator it = --TOKEN_list.end();
        if((*it).line > i)
        {
        	cout << endl;
        	i = (*it).line;
		}
		cout << "<" << (*it).token << ",";
        if((*it).token.find("KT") != string::npos)cout << *((*it).tpKT);
        else if((*it).token.find("IT") != string::npos)cout << (*((*it).tpIT)).name;
        else if((*it).token.find("PT") != string::npos)cout << *((*it).tpPT);
        else if((*it).token.find("OT") != string::npos)cout << *((*it).tpOT);
        else if((*it).token.find("ZT") != string::npos)cout << (*it).tpI->numi;
        else if((*it).token.find("RT") != string::npos)cout << (*it).tpR->numf;
        else if((*it).token.find("CT") != string::npos)cout << (*it).tpC->numc;
        else if((*it).token.find("ST") != string::npos)cout << (*it).tps;
        else if((*it).token == "ERROR") cout << (*((*it).tpER)).name;
        cout << ">";
    }
    cout << endl;
    cout << "--------------------------------" << endl;
    for(list<ERRORL>::iterator it = ERRORL_list.begin(); it != ERRORL_list.end(); it++)
    {
        cout << "line:" << (*it).line << "\t[ERROR] " << (*it).name << " ";
        switch((*it).type)
        {//n.i,R,Z,c,s
        case 'n':
            cout << "δ֪����" << endl;
            break;
        case 'i':
            cout << "��ʶ������ַ����Ϸ�" << endl;
            break;
        case 'R':
            cout << "ʵ����д���Ϸ�" << endl;
            break;
        case 'Z':
            cout << "������д���Ϸ�" << endl;
            break;
        case 'c':
            cout << "�ַ�������" << endl;
            break;
        case 's':
            cout << "�ַ���������" << endl;
            break;
        default:
            cout << "�������" << endl;
        }
    }
}
