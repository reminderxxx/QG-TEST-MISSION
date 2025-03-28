#include<iostream>
#include<stdexcept>
#include<stack>
#include<string>
#include<cctype>
#include<cstdlib>
#include<cmath>
using namespace std;

template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(NULL) {}
    };
    Node* head;
    int size;

public:
    Stack() : head(NULL), size(0) {};
    ~Stack();
    void push(T element);
    T pop();
    T top() const;
    int getSize() const;
};

template<typename T>
Stack<T>::~Stack() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename T>
void Stack<T>::push(T element) {
    Node* newNode = new Node(element);
    newNode->next = head;
    head = newNode;
    ++size;
}

template<typename T>
T Stack<T>::pop() {
    if (head == NULL) {
        throw std::out_of_range("Stack<>::pop(): empty stack");
    }
    Node* temp = head;
    T data = head->data;
    head = head->next;
    delete temp;
    --size;
    return data;
}

template<typename T>
T Stack<T>::top() const {
    if (head == NULL) {
        throw std::out_of_range("Stack<>::top(): empty stack");
    }
    return head->data;
}

template<typename T>
int Stack<T>::getSize() const {
    return size;
}



int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 执行运算
double calculate(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) throw runtime_error("除数不能为零");
        return a / b;
    default: throw runtime_error("无效运算符");
    }
}

// 计算表达式
double evaluateExpression(const string& expr) {
    Stack<double> values;
    Stack<char> ops;

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') continue;

        // 处理数字
        if (isdigit(expr[i]) || expr[i] == '.') {
            string numStr;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                numStr += expr[i++];
            }
            i--;
            values.push(stod(numStr));
        }
        // 处理左括号
        else if (expr[i] == '(') {
            ops.push(expr[i]);
        }
        // 处理右括号
        else if (expr[i] == ')') {
            while (ops.getSize() > 0 && ops.top() != '(') {
                if (values.getSize() < 2) {
                    throw runtime_error("表达式错误：缺少操作数");
                }
                double val2 = values.pop();
                double val1 = values.pop();
                char op = ops.pop();
                values.push(calculate(val1, val2, op));
            }
            if (ops.getSize() == 0) {
                throw runtime_error("括号不匹配");
            }
            ops.pop(); // 弹出左括号
        }
        // 处理运算符
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            // 处理负号情况（如-3）
            if (expr[i] == '-' && (i == 0 || expr[i - 1] == '(')) {
                string numStr = "-";
                i++;
                while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                    numStr += expr[i++];
                }
                i--;
                values.push(stod(numStr));
                continue;
            }

            while (ops.getSize() > 0 && ops.top() != '(' &&
                getPriority(ops.top()) >= getPriority(expr[i])) {
                if (values.getSize() < 2) {
                    throw runtime_error("表达式错误：缺少操作数");
                }
                double val2 = values.pop();
                double val1 = values.pop();
                char op = ops.pop();
                values.push(calculate(val1, val2, op));
            }
            ops.push(expr[i]);
        }
        else {
            throw runtime_error("无效字符: " + string(1, expr[i]));
        }
    }

    // 处理剩余运算符
    while (ops.getSize() > 0) {
        if (ops.top() == '(') {
            throw runtime_error("括号不匹配");
        }
        if (values.getSize() < 2) {
            throw runtime_error("表达式错误：缺少操作数");
        }
        double val2 = values.pop();
        double val1 = values.pop();
        char op = ops.pop();
        values.push(calculate(val1, val2, op));
    }

    if (values.getSize() != 1) {
        throw runtime_error("表达式不完整");
    }

    return values.pop();
}

int main() {
    Stack<string> s;
    cout << "******************" << endl;
    cout << "这是一个计算器，请输入你的表达式:" << endl;
    cout << "支持加减乘除(+ - * /)和括号()运算" << endl;
    cout << "******************" << endl;

    while (true) {
        cout << "> ";
        string input;
        getline(cin, input);


        try {
            double result = evaluateExpression(input);
            cout << "结果: " << result << endl;
        }
        catch (const exception& e) {
            cout << "错误: " << e.what() << endl;
        }
    }

    return 0;
}