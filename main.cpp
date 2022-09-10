#include <stack>
#include <iostream>
#include <cstring>

using namespace std;

//ö���������
enum propositionOperator
{
    equivalent = 1, imply, Or, And, Not, Lbracket, Rbracket
};

//����ֵ��ȷ��һ�����������
bool determineVariables(char c, int trueValue);

bool isVariable(char c);

bool calculate(bool a, int op, bool b);

void process(int op, stack<bool> &variables, stack<int> &operators);

int main()
{
    stack<bool> variables;
    stack<int> operators;
    bool variableUsed[26] = {0};
    string input;
    int trueValue = 0;
    char binaryTrueValue[28] = {0};
    int numOfVariables = 0;
    int maxTrueValue = 0;

    cout << "���������⹫ʽ���������пո��Իس�����" << endl;
    cout << "����������ΪСд��ĸ�������a��ʼ" << endl;
    cout << "�� : !" << endl;
    cout << "��ȡ : &" << endl;
    cout << "��ȡ : |" << endl;
    cout << "�̺� : >" << endl;
    cout << "�ȼ� : =" << endl;
    cout << "���� : ( �� )" << endl;

    cin >> input;

    for(auto c : input)
    {
        
        if(isVariable(c) && variableUsed[c - 'a'] == false)
        {
            variableUsed[c - 'a'] = true;
            numOfVariables++;
            //ע�⣬�ӷ����ȼ���������
            maxTrueValue = (maxTrueValue << 1) + 1;
        }
    }
    
    for(trueValue = 0; trueValue <= maxTrueValue; trueValue++)
    {
        for(auto c : input)
        {
            if(isVariable(c))
            {
                variables.push(determineVariables(c, trueValue));
            }
            else
            {
                switch(c)
                {
                case '(':
                    process(Lbracket, variables, operators);
                    break;
                case ')':
                    process(Rbracket, variables, operators);
                    break;
                case '!':
                    process(Not, variables, operators);
                    break;
                case '&':
                    process(And, variables, operators);
                    break;
                case '|':
                    process(Or, variables, operators);
                    break;
                case '>':
                    process(imply, variables, operators);
                    break;
                case '=':
                    process(equivalent, variables, operators);
                    break;
                }
            }
        }

        process(0, variables, operators);
        
        itoa(trueValue + (1 << numOfVariables), binaryTrueValue, 2);

        for(int i = numOfVariables; i >= 1; i--) cout << binaryTrueValue[i];
        
        cout << "\t" << variables.top() << endl;

        while(operators.empty() == false) operators.pop();
        while(variables.empty() == false) variables.pop();
    }

    cout << "���س��˳�" << endl;
    getchar();
    getchar();
    return 0;
}

void process(int op, stack<bool> &variables, stack<int> &operators)
{
    if(op == Rbracket)
    {
        while(operators.top() != Lbracket)
        {
            bool b, a;
            int topOp = operators.top();
            operators.pop();
            switch(topOp)
            {
            case Not:
                a = variables.top();
                variables.pop();
                variables.push(calculate(a, topOp, 0));
                break;
            default:
                b = variables.top();
                variables.pop();
                a = variables.top();
                variables.pop();
                variables.push(calculate(a, topOp, b));
                break;
            }
        }
        operators.pop();
        return;
    }

    while(operators.empty() == false && operators.top() >= op)
    {
        bool b, a;
        int topOp = operators.top();

        if(topOp == Lbracket) break;

        operators.pop();
        switch(topOp)
        {
        case Not:
            a = variables.top();
            variables.pop();
            variables.push(calculate(a, topOp, 0));
            break;
        default:
            b = variables.top();
            variables.pop();
            a = variables.top();
            variables.pop();
            variables.push(calculate(a, topOp, b));
            break;
        }
    }

    operators.push(op);
}

bool calculate(bool a, int op, bool b)
{
    switch(op)
    {
    case Not:
        return !a;
        break;
    case And:
        return a & b;
        break;
    case Or:
        return a | b;
        break;
    case imply:
        return !a | b;
        break;
    case equivalent:
        return !(a ^ b);
        break;
    }
}

bool determineVariables(char c, int trueValue)
{
    int id = c - 'a';
    if(trueValue & (1 << id))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isVariable(char c)
{
    if('a' <= c && c <= 'z')
    {
        return true;
    }
    else
    {
        return false;
    }
}