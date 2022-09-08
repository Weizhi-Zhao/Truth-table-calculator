#include <stack>
#include <iostream>
#include <cstring>

using namespace std;

//枚举运算符号
enum propositionOperator
{
    Lbracket = 1, Rbracket = 1, Not, And, Or, imply, equivalent
};

//用真值，确定一个变量的真假
bool determineVariables(char c, int trueValue);

bool isVariable(char c);

int main()
{
    stack<char> variables;
    stack<int> operators;
    string input;

    cin >> input;

    for(auto c : input)
    {
        if(isVariable(c))
        {
            variables.push(c);
        }
        else
        {
            switch(c)
            {
            case '(':
                operators.push(Lbracket);
                break;
            case ')':

                break;
            case '!':
                break;
            case '&':
                break;
            case '|':
                break;
            case '>':
                break;
            case '=':
                break;
            }
        }
    }


    cout << input;
    return 0;
}

bool calculate(char a, int op, char b, int trueValue)
{
    switch(op)
    {
    case Not:
        return !determineVariables(a, trueValue);
        break;
    case And:
        return determineVariables(a, trueValue) & determineVariables(b, trueValue);
        break;
    case Or:
        return determineVariables(a, trueValue) | determineVariables(b, trueValue);
        break;
    case imply:
        return (!determineVariables(a, trueValue)) | determineVariables(b, trueValue);
        break;
    case equivalent:
        return ( (!determineVariables(a, trueValue)) | determineVariables(b, trueValue) )
            & ( (!determineVariables(b, trueValue)) | determineVariables(a, trueValue) );
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