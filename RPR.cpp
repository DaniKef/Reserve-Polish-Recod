#include <iostream>
#include <string>
#include <stack>
#include <cmath>
using namespace std;

bool isOperator(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {           // Перевіряє, чи ці символи використовуються
		return true;
	}
	else {
		return false;
	}
}

int precedence(char c) {          // Порівнює пріоритети
	if (c == '^')
		return 4;
	else if (c == '/' || c == '*')
		return 3;
	else if (c == '+' || c == '-')
		return 2;
	else 
		return -1;
}

template <typename H>
H printstack(stack <H> st) {          // Друкує стек
	cout << "stack:";
	while (!st.empty()) {
		cout << st.top() << ' ';
		st.pop();
	}
	return 0;
}


string inftopr(string inp) {          // Перетворює в постфіксний форму

	stack<char> operations;
	string out = "";

	for ( int i = 0; i < inp.size(); i++) {        // Проходжу по всіх елементах
		char t = inp[i];

		if (t != '(' && t != ')' && t != '+' && t != '-' && t != '*' && t != '/' && t != '^') {     // Перевіряю кожен символ. Якщо треба, переношу зі string в стек і виробляю операції зі стеком: push(),pop()
			out += t;
		}

		else {

			if (t == '(') {
				operations.push(t);
			}
			
			else if (t == ')') {
				while (operations.top() != '(') {
					out += operations.top();
					operations.pop();
				}
				operations.pop();
			}

			else if(isOperator(t)){
				out += ' ';
				if (operations.empty()) {
					operations.push(t);
				}
				else {
					if (precedence(t) > precedence(operations.top())) {
						operations.push(t);
					}
					else if((precedence(t) > precedence(operations.top())) && t=='^' ) {
						operations.push(t);
					}
					else {
						while ((!operations.empty()) &&(precedence(t)<=precedence(operations.top()))) {
							out += operations.top();
							operations.pop();
						}
						operations.push(t);
					}
				}
			}
            }
		printstack(operations);
		cout << "   string:" << out << endl;
	}
	while (!operations.empty()) {
		out += operations.top();
		operations.pop();
	}
	return out;
}

int result(string inp) {    // Рахує вираз
	stack <int> count;
	int i = 0;
	int x, y;
	while (i < inp.size()) {
		if (int(inp[i]) >= 48 && int(inp[i]) <= 57) {
			string symp = "";
			do {
				symp += inp[i++];
			} while (int(inp[i]) >= 48 && int(inp[i]) <= 57);
			count.push(stoi(symp));
		}
		else  switch (inp[i++]) {

		case '+':
		 x = count.top();
		count.pop();
		 y = count.top();
		count.pop();
		count.push(y + x); 
		break;

		case '-':
		 x = count.top();
		count.pop();
		 y = count.top();
		count.pop();
		count.push(y - x); 
		break;

		case '*':
		 x = count.top();
		count.pop();
		 y = count.top();
		count.pop();
		count.push(y * x); 
		break;

		case '/':
		 x = count.top();
		count.pop();
		 y = count.top();
		count.pop();
		count.push(y / x); 
		break;

		case '^':
		 x = count.top();
		count.pop();
		 y = count.top();
		count.pop();
		count.push(pow(y, x)); 
		break;

		case ' ':
			break;

		default:
			break;
		}
		printstack(count);
		cout << endl;
	}
	return count.top();
}



int main()
{
	setlocale(LC_ALL, "rus");
	

	cout << "Введiть вираз: ";
	string inp;
	getline(cin, inp);
	string out = inftopr(inp);
	cout << "\nЗворотний польський запис:  " << out << endl;
	int answer = result(out);
	cout << "\nВiдповiдь: " << answer;
	
	return 0;
}

