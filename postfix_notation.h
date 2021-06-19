#ifndef POSTFIX_NOTATION_H
#define POSTFIX_NOTATION_H
std::queue<std::string> InputToPostfixAndArabic(const std::string& arithmetic_expression);
int CalculatePostfix(std::queue<std::string> postfix_notation);
#endif //POSTFIX_NOTATION_H
