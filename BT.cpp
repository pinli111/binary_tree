#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class ExpressionNode
{
    public:
    char exp;
    int val;
    ExpressionNode* left;
    ExpressionNode* right;
    ExpressionNode(char ch){
        this->exp = ch;
    }
    ExpressionNode(int val){
        this->val = val;
    }
};

bool isDigit(char ch)
{
    if((ch - '0') >=0 && (ch - '0')<=9)
    {
        return true;
    }
    return false;
}

bool isOperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch =='(' || ch == 'x') 
    {
        return true;
    }
    return false;
}

ExpressionNode* constructBTFromStringExpression(string str)
{
    stack<char> chStack;
    stack<ExpressionNode*> pNodeStack;
    bool previousIsDigit = false;
    bool previousIsOperator = false;
    bool isNegative = false;
    int currentNumber = 0;
    for(int i = 0; i< str.length(); i++)
    {
        if(isOperator(str[i]))
        {
            if(currentNumber!= 0)
            {
                cout<< currentNumber << " ";
                ExpressionNode* newNode = new ExpressionNode(currentNumber);
                pNodeStack.push(newNode);
                currentNumber = 0;
                previousIsDigit = false;
            }
            if(previousIsOperator && str[i] == '-')
            {
                isNegative = true;
            }
            previousIsOperator = true;
            //cout<< str[i] << " ";
            chStack.push(str[i]);
        }
        else if(isDigit(str[i]))
        {
            if(!previousIsDigit)
            {
                previousIsDigit = true;
            }
            previousIsOperator = false;
            currentNumber = currentNumber*10 + (str[i] - '0');
        }
        else if(str[i] == ')')
        {
            if(currentNumber!= 0)
            {
                //cout<< currentNumber << " ";
                ExpressionNode* newNode = new ExpressionNode(currentNumber);
                pNodeStack.push(newNode);
                currentNumber = 0;
                previousIsDigit = false;
            }
            previousIsOperator = false;
            if(isNegative)
            {
                isNegative = false;
                ExpressionNode* negativeRootNode = new ExpressionNode(chStack.top());
                chStack.pop();
                if(pNodeStack.size() != 1)
                {
                    negativeRootNode->right = pNodeStack.top();
                }
                else
                {
                    negativeRootNode->left = pNodeStack.top();
                }
                pNodeStack.pop();
                pNodeStack.push(negativeRootNode);
            }
            ExpressionNode* newRootNode = new ExpressionNode(chStack.top());
            chStack.pop();
            newRootNode->right = pNodeStack.top();
            pNodeStack.pop();
            newRootNode->left = pNodeStack.top();
            pNodeStack.pop();
            chStack.pop(); // pop left bracket
            pNodeStack.push(newRootNode);
        }
    }

    if(currentNumber!= 0)
    {
        ExpressionNode* newNode = new ExpressionNode(currentNumber);
        pNodeStack.push(newNode);
    }
     if(isNegative)
            {
                isNegative = false;
                ExpressionNode* negativeRootNode = new ExpressionNode(chStack.top());
                chStack.pop();
                if(pNodeStack.size() != 1)
                {
                    negativeRootNode->right = pNodeStack.top();
                }
                else
                {
                    negativeRootNode->left = pNodeStack.top();
                }
                pNodeStack.pop();
                pNodeStack.push(negativeRootNode);
            }
   while(!chStack.empty())
    {
        ExpressionNode* newRootNode = new ExpressionNode(chStack.top());
        //cout<< newRootNode->exp;
            chStack.pop();
            newRootNode->right = pNodeStack.top();
            //cout<< pNodeStack.top()->val;
            pNodeStack.pop();
            newRootNode->left = pNodeStack.top();
            //cout<< pNodeStack.top()->val;
            pNodeStack.pop();
            pNodeStack.push(newRootNode);
    }
    if(pNodeStack.top() == NULL)
    {
        return NULL;
    }
    return pNodeStack.top();

}

int getResult(ExpressionNode* root)
{
    if(root == NULL) return 0;
    if(root->left == NULL && root->right == NULL){
        cout<< root->val;
        return root->val;
    } 
    int l = getResult(root->left);
    int r = getResult(root->right);
    cout<< "l " << l << "r " << r << endl;
    if(root->exp == '*' || root->exp == 'x')
    {
        return l*r;
    }
    else if(root->exp == '/' )
    {
        return l/r;
    }
    else if(root->exp == '+')
    {
        return l+r;
    }
     else if(root->exp == '-')
    {
        return l-r;
    }
    return 0;
}

void inOrder(ExpressionNode* root)
{
    if(root == NULL) return;
    inOrder(root->left);
     if(root->exp!= 0)
     {
         cout<< root->exp << " ";
     }
     else if(root->val!= 0)
     {
         cout<< root->val << " ";
     }
    inOrder(root->right);
}

int main()
{
    string str7 = "(1+-4)*-3";
    string str8 = "((15/(7-(1+1)))*-3)-(2+(1+1))";
    inOrder(constructBTFromStringExpression(str7));
    cout<< getResult(constructBTFromStringExpression(str7));
    return 0;
}