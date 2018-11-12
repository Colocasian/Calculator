#include <iostream>
#include <string>
#include <stack>
#include <exception>
using namespace std;

string infixToPostfix(string &infix)
{
	stack<char> yolo;
	string ans("");
	yolo.push('(');
	infix += ')';
	for (int i = 0; !yolo.empty(); i++)
	{
		if (infix[i] == '(')
			yolo.push('(');
		else if (infix[i] == ')')
		{
			while (yolo.top() != '(')
			{
				ans += yolo.top();
				yolo.pop();
			}
			yolo.pop();
		}
		else if (infix[i] >= '0' && infix[i] <= '9')
		{
			ans += '|';
			while (infix[i] == '.' || (infix[i] >= '0' && infix[i] <= '9') || infix[i] == '_')
			{
				if (infix[i] != '_')
					ans += infix[i];
				i++;
			}
			i--;
			ans += '|';
		}
		else if (infix[i] == '*' || infix[i] == '/' || infix[i] == '%')
		{
			while (yolo.top() == '*' || yolo.top() == '/' || yolo.top() == '%')
			{
				ans += yolo.top();
				yolo.pop();
			}
			yolo.push(infix[i]);
		}
		else if (infix[i] == '+' || infix[i] == '-')
		{
			while (yolo.top() == '*' || yolo.top() == '/' || yolo.top() == '%' || yolo.top() == '+' || yolo.top() == '-')
			{
				ans += yolo.top();
				yolo.pop();
			}
			yolo.push(infix[i]);
		}
		else if (infix[i] != ' ')
		{
			throw new exception;
		}
	}
	infix.pop_back();
	return ans;
}

double calculate(string postfix)
{
	stack<double> regis;
	for (int i = 0; i < postfix.length(); i++)
	{
		if (postfix[i] == '|')
		{
			i++;
			string tmp;
			while (postfix[i] != '|')
				tmp += postfix[i++];
			regis.push(stod(tmp));
		}
		else
		{
			double b = regis.top();
			regis.pop();
			switch (postfix[i])
			{
				case '+':
					regis.top() += b;
					break;
					
				case '-':
					regis.top() -= b;
					break;
					
				case '*':
					regis.top() *= b;
					break;
					
				case '/':
					regis.top() /= b;
					break;
					
				case '%':
					regis.top() = (int)regis.top() % (int)b;
					break;
			}
		}
	}
	return regis.top();
}

int main()
{
	string exp;
	while (true)
	{
		printf("Enter your expression (-1 to exit)\n");
		getline(cin, exp);
		if (exp == "-1")
			break;
		string post = infixToPostfix(exp);
		cout << post << endl;
		cout << calculate(post) << endl;
	}
}