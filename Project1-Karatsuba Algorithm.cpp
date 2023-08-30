#include<cmath>
#include<iostream>
#include<cstdint>

std::int64_t karatsuba(const int& num1, const int& num2);
int sizeBase10(const int& num);
void splitAt(const int& num, const int& digit, int& high, int& low);

int numOne;
int numTwo;

int main()
{
    std::cout << "Enter the first integer to multiply: ";
    std::cin >> numOne;
    std::cout << std::endl;

    std::cout << "Enter the second integer to multiply: ";
    std::cin >> numTwo;
    std::cout << std::endl;

    std::cout << "The product of the two numbers you entered is: " << karatsuba(numOne, numTwo) << std::endl;
}

std::int64_t karatsuba(const int& numOne, const int& numTwo)
{
    if (numOne < 10 || numTwo < 10)
        return static_cast<std::int64_t>(numOne) * static_cast<std::int64_t>(numTwo); /* fall back to traditional multiplication */

    /* Calculates the size of the numbers. */
    int m = std::max(sizeBase10(numOne), sizeBase10(numTwo));
    int m2 = std::floor(static_cast<float>(m) / 2.0);

    int highOne, lowOne, highTwo, lowTwo;

    /* Split the digit sequences in the middle. */
    splitAt(numOne, m2, highOne, lowOne);
    splitAt(numTwo, m2, highTwo, lowTwo);

    /* 3 recursive calls made to numbers approximately half the size. */
    std::int64_t z0 = karatsuba(lowOne, lowTwo);
    std::int64_t z1 = karatsuba(lowOne + highOne, lowTwo + highTwo);
    std::int64_t z2 = karatsuba(highOne, highTwo);

    double a = std::pow(10, m2 * 2);
    double b = std::pow(10, m2);

    return (z2 * a) + ((z1 - z2 - z0) * b) + z0;
}

int sizeBase10(const int& num)
{
    return std::log10(static_cast<double>(num)) + 1;
}

void splitAt(const int& num, const int& digit, int& high, int& low)
{
    double converted = static_cast<double>(num);
    double dividend = std::pow(10, digit);

    converted = converted / dividend;

    high = converted;
    low = round((converted - high) * dividend);
}