#include <iostream>

// The tool outputs the total number of 13-digit "pretty numbers" in tridecimal numeral system
// "Pretty number" is a number in which the sum of first and last 6 digits are the same
// Examples:
// Number 0055237050A00 is pretty, as 0+0+5+5+2+3 = 0+5+0+A+0+0
// Number 1234AB988BABA is not pretty, as 1+2+3+4+A+B != 8+8+B+A+B+A
//
// Solution
// 1. For a pretty 13-digit tridecimal number ABCDEFZKLMNOP: A + B + C + D + E + F + K + L + M + N + O + P =
// A + B + C + D + E + F + 12 - K + 12 - L + 12 - M + 12 - N + 12 - O + 12 - P = 12 * 6 = 72
// So the number required is equal to the number of numbers with sum of digits = 72.
// 2. What is the number of ways to represent 72 as a sum of 12 tridecimal digits? Calculate it by means of DP, with memoizing
// previous results in an array.
// 3. Multiply the result by 13, as we have a "free" digit.
// Result: 9203637295151

// References
// https://oyla.xyz/article/matematika-udaci-isem-scastlivye-bilety
// checkup:
// https://ru.wikipedia.org/wiki/%D0%A1%D1%87%D0%B0%D1%81%D1%82%D0%BB%D0%B8%D0%B2%D1%8B%D0%B9_%D0%B1%D0%B8%D0%BB%D0%B5%D1%82#%D0%AF%D0%B2%D0%BD%D1%8B%D0%B5_%D1%84%D0%BE%D1%80%D0%BC%D1%83%D0%BB%D1%8B
// https://www.wolframalpha.com/input?i=1%2F+%CF%80+*+13+*+integrate+%28%28sin+%2813+*+x%29+%29%2F%28sin+x%29%29%5E12%2C%7Bx%2C0%2C%CF%80%7D
// 9.20363729515099999999999999999999999999999999999999999999999... × 10^12

//#define DEBUG_PRINT

int main() {
    static constexpr int kNumber = 72;
    static constexpr int kDigits = 12;
    static constexpr int kNumericBase = 13;

    std::int64_t numSums[kNumber + 1][kDigits]{}; // number + 1 for zero
    for (auto i = 0; i <= kNumber; ++i) {
        for (auto j = 0; j < kDigits; ++j) {
            if (i == 0 || j == 0 && i < kNumericBase) {
                numSums[i][j] = 1; // base of dp
            } else if (i > 0 && j > 0) {
                numSums[i][j] = numSums[i - 1][j] + numSums[i][j - 1];
                if (i >= kNumericBase) {
                    numSums[i][j] -= numSums[i - kNumericBase][j - 1];
                }
            }
#ifdef DEBUG_PRINT
            std::cout << numSums[i][j] << " ";
#endif
        }
#ifdef DEBUG_PRINT
        std::cout << std::endl;
#endif
    }

    std::cout << numSums[kNumber][kDigits - 1] * kNumericBase << std::endl;
    return 0;
}
