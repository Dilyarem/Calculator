#include <iostream>
#include <queue>
#include <stack>

#include "numeral_system.h"
#include "postfix_notation.h"



int main() {
    std::string arithmetic_expression;
    while (std::getline(std::cin, arithmetic_expression)) {
        if (arithmetic_expression.empty()) {
            break;
        }
        try {
            std::queue<std::string> postfix_notation = InputToPostfixAndArabic(arithmetic_expression);
            int answer = CalculatePostfix(postfix_notation);
            std::cout << TranslArabicToRoman(answer) << '\n';
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << '\n';
        }
    }
    return 0;
}
