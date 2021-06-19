#include <unordered_map>
#include <cstdlib>
#include <map>
#include <string>

std::unordered_map<char, int> GetDictRomanToArabic() {
    std::unordered_map<char, int> dict = {
            {'Z', 0},
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
    };
    return dict;
}

int TranslRomanToArabicInt(const std::string& roman) {
    int arabic = 0;
    std::unordered_map<char, int> dict = GetDictRomanToArabic();
    for (uint i = 0; i < roman.length(); ++i) {
        if ((i == roman.length() - 1) || (dict[roman[i]] >= dict[roman[i + 1]])) {
            arabic += dict[roman[i]];
        } else {
            arabic += dict[roman[i+1]] - dict[roman[i]];
            ++i;
        }
    }
    return arabic;
}

std::map<int, std::string, std::greater<>> GetDictArabicToRoman() {
    std::map<int, std::string, std::greater<>> dict = {
            {1, "I"},
            {4, "IV"},
            {5, "V"},
            {9, "IX"},
            {10, "X"},
            {40, "XL"},
            {50, "L"},
            {90, "XC"},
            {100, "C"},
            {400, "CD"},
            {500, "D"},
            {900, "CM"},
            {1000, "M"}
    };
    return dict;
}

std::string TranslArabicToRoman(int arabic) {
    if (arabic == 0) {
        return "Z";
    }
    auto dict = GetDictArabicToRoman();
    std::string roman;
    int abs = std::abs(arabic);
    for (auto [key, value]:dict) {
        while (abs >= key) {
            roman.append(value);
            abs -= key;
        }
    }
    if (arabic < 0) {
        roman = "-" + roman;
    }
    return roman;
}
