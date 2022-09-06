#include <stack>
#include <iostream>
#include <cstring>

using namespace std;

//枚举运算符号
enum propositionOperator
{
    Not = 2, And, Or, imply, equivalent, Lbracket, Rbracket
};

//用真值，确定一个变量的真假
bool determineVariables(char c, int trueValue);

int main()
{
    stack<int> formula;
    string input;

    cin >> input;
    cout << input;
    return 0;
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