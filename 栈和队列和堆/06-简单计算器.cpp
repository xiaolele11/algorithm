//
// Created by mengjiale on 2018/5/15.
//

#include <iostream>
#include <stack>

class Solution {
public:
    int calculate(std::string s)
    {
        static const int STATE_BEGIN = 0;
        static const int NUMBER_STATE = 1;
        static const int OPERATION_STATE = 2;

        std::stack<int> number_stack;
        std::stack<char> operation_stack;

        int number = 0;
        int STATE = STATE_BEGIN;
        int compute_flag = 0;

        // 字符串转换，并且将数字和操作符分别入栈
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ' ') {  // 去除空格
                continue;
            }
            switch (STATE) {
                case STATE_BEGIN:  // 开始状态
                    if (s[i] >= '0' && s[i] <= '9') {
                        STATE = NUMBER_STATE;
                    }
                    else {
                        STATE = OPERATION_STATE;
                    }
                    i--;
                    break;
                case NUMBER_STATE:  // 数字状态，进行数字转换
                    if (s[i] >= '0' && s[i] <= '9') {
                        number = number * 10 + s[i] - '0';
                    }
                    else {
                        number_stack.push(number);
                        if (compute_flag == 1) {
                            compute(number_stack, operation_stack);
                        }
                        number = 0;
                        i--;
                        STATE = OPERATION_STATE;
                    }
                    break;
                case OPERATION_STATE:  // 操作符状态
                    if (s[i] == '+' || s[i] == '-') {
                        operation_stack.push(s[i]);
                        compute_flag = 1;
                    }
                    else if (s[i] == '(') {
                        STATE = NUMBER_STATE;
                        compute_flag = 0;
                    }
                    else if (s[i] >= '0' && s[i] <= '9') {
                        STATE = NUMBER_STATE;
                        i--;
                    }
                    else if (s[i] == ')') {
                        compute(number_stack, operation_stack);
                    }
                    break;
            }
        }
        if (number != 0) {
            number_stack.push(number);
            compute(number_stack, operation_stack);
        }
        if (number == 0 && number_stack.empty()) {
            return 0;
        }
        return number_stack.top();
    }

private:
    void compute(std::stack<int> number_stack, std::stack<char> operation_stack)
    {
        if (number_stack.size() < 2) {
            return;
        }
        int num2 = number_stack.top();
        number_stack.pop();
        int num1 = number_stack.top();
        number_stack.pop();
        if (operation_stack.top() == '+') {
            number_stack.push(num1 + num2);
        }
        else if (operation_stack.top() == '-') {
            number_stack.push(num1 - num2);
        }
        operation_stack.pop();
    }
};

int main()
{
    std::string s = "1+121 - (14+(5-6) )";
    Solution solve;

    int res = solve.calculate(s);
    std::cout << res << std::endl;
}