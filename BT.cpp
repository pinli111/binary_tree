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

bool updatePreviousDigitStatus(stack<ExpressionNode*>& node, int number)
{
    if(number!= 0)
    {
        ExpressionNode* newNode = new ExpressionNode(number);
        node.push(newNode);
        return false;
    }
    return false;
}

bool handleNegative(stack<char>& chStack, stack<ExpressionNode*>& pNodeStack, bool isNegative)
{
    if(isNegative)
    {
        ExpressionNode* negativeRootNode = new ExpressionNode(chStack.top());
        chStack.pop();
        negativeRootNode->right = pNodeStack.top();
        pNodeStack.pop();
        pNodeStack.push(negativeRootNode);
       
    }
    return false;
}

void buildSubtree(stack<char>& chStack, stack<ExpressionNode*>& pNodeStack)
{
     ExpressionNode* newRootNode = new ExpressionNode(chStack.top());
     chStack.pop();
     newRootNode->right = pNodeStack.top();
     pNodeStack.pop();
     newRootNode->left = pNodeStack.top();
     pNodeStack.pop();
     if(!chStack.empty())
     {
         chStack.pop(); // pop left bracket
     }
     pNodeStack.push(newRootNode);
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
            previousIsDigit = updatePreviousDigitStatus(pNodeStack,currentNumber);
            currentNumber = 0;
            if(previousIsOperator && str[i] == '-')
            {
                isNegative = true;
            }
            previousIsOperator = true;
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
            previousIsDigit = updatePreviousDigitStatus(pNodeStack,currentNumber);
            currentNumber = 0;
            previousIsOperator = false;
            isNegative = handleNegative(chStack,pNodeStack, isNegative);
            buildSubtree(chStack,pNodeStack);
        }
    }

    previousIsDigit = updatePreviousDigitStatus(pNodeStack,currentNumber);
    isNegative =  handleNegative(chStack,pNodeStack, isNegative);

   while(!chStack.empty())
    {
        buildSubtree(chStack,pNodeStack);
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
        return root->val;
    } 
    int l = getResult(root->left);
    int r = getResult(root->right);
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
    string testCases[4] = { "2-2", "9x9" , "(1+1)x2", "((15/(7-(1+1)))*-3)-(2+(1+1))"};
    for(int i= 0; i< 4; i++)
    {
        cout<< endl << "The binary tree is presented with inorder traversal: ";
        inOrder(constructBTFromStringExpression(testCases[i]));
        cout<< endl << "The answer is " << getResult(constructBTFromStringExpression(testCases[i]));
    }
    return 0;
}