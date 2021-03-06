#include <string>
#include <queue>
#include <stack>
#include <stdexcept>
#include <cmath>

#include "numeral_system.h"
#include "overflowing.h"


int FloorRoundingDivision(int a, int b);

bool CheckIfMinusForNegative(uint minus_idx, const std::string& arithmetic_expression) {
    int prev_idx = static_cast<int>(minus_idx) - 1;
    while (prev_idx >= 0 && arithmetic_expression[prev_idx] == ' ') {
        --prev_idx;
    }
    if (prev_idx < 0 || arithmetic_expression[prev_idx] == '(') {
        return true;
    }
    return false;
}

std::queue<std::string> InputToPostfixAndArabic(const std::string& arithmetic_expression) {
    std::queue<std::string> postfix_notation;
    std::stack<char> operators;
    std::string number;
    bool is_neg = false;
    for (uint i = 0; i < arithmetic_expression.length(); ++i) {
        auto symbol = arithmetic_expression[i];
        if (symbol >= 'A' && symbol <= 'Z') {
            std::string roman_number;
            while (arithmetic_expression[i]>= 'A' && arithmetic_expression[i] <= 'Z') {
                roman_number.push_back(arithmetic_expression[i]);
                ++i;
            }
            --i;
            std::string arabic(std::to_string(TranslRomanToArabicInt(roman_number)));
            if (is_neg){
                postfix_notation.push("0");
                postfix_notation.push(arabic);
                postfix_notation.push("-");
                is_neg = false;
            } else {
                postfix_notation.push(arabic);
            }
        } else if (symbol >= '*' && symbol <= '/' ) {
            if (symbol == '-' && CheckIfMinusForNegative(i, arithmetic_expression))  {
                is_neg = true;
                continue;
            }

            if (operators.empty() || (operators.top() == '(')) {
                operators.push(symbol);
                continue;
            }

            if (symbol == '*' || symbol == '/') {
                operators.push(symbol);
                continue;
            }

            if (operators.top() == '+' || operators.top() == '-') {
                operators.push(symbol);
                continue;
            }

            while (!(operators.empty() || operators.top() == '+' || operators.top() == '-' || operators.top() == '(')) {
                postfix_notation.push(std::string(1, operators.top()));
                operators.pop();
            }
            operators.push(symbol);
        } else if (symbol == '(') {
            operators.push(symbol);
        } else if (symbol == ')') {
            while (operators.top() != '(') {
                postfix_notation.push(std::string(1, operators.top()));
                operators.pop();
            }
            operators.pop();
        }
    }

    while (!operators.empty()) {
        postfix_notation.push(std::string(1, operators.top()));
        operators.pop();
    }

    return postfix_notation;
}

int CalculatePostfix(std::queue<std::string> postfix_notation) {
    std::stack<int> numbers;
    while (!postfix_notation.empty()) {
        auto symbol = postfix_notation.front();
        postfix_notation.pop();
        if (symbol[0] >= '*' && symbol[0] <= '/' ) {

            if (numbers.size() < 2) {
                throw std::logic_error("wrong expression");
            }

            int a = numbers.top();
            numbers.pop();
            int b = numbers.top();
            numbers.pop();

            switch (symbol[0]) {
                case '+': {
                    CheckSumForOverflowing(a, b);
                    numbers.push(a+b);
                    break;
                }
                case '-': {
                    CheckSumForOverflowing(b, -a);
                    numbers.push(b-a);
                    break;
                }
                case '*': {
                    CheckProdForOverflowing(a, b);
                    numbers.push(a*b);
                    break;
                }
                case '/': {
                    int division_result = FloorRoundingDivision(a, b);
                    numbers.push(division_result);
                    break;
                }
                default: {
                    throw std::logic_error("wrong expression");
                }

            }
        } else {
            numbers.push(std::stoi(symbol));
        }

    }
    if (numbers.size() == 1) {
        return numbers.top();
    } else {
        throw std::logic_error("wrong expression");
    }
}

int FloorRoundingDivision(int a, int b) {
    if (a == 0) {
        throw std::logic_error("division by zero");
    }
    return std::floor(static_cast<float>(b) / static_cast<float>(a));
}
