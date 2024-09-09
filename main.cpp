#include <iostream>

class Fraction {
private:
    int numerator_;
    int denominator_;

    // Собственная реализация НОД
    int gcd(int a, int b) const {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Метод для сокращения дроби
    void reduce() {
    int gcd_value = gcd(abs(numerator_), abs(denominator_));
    numerator_ /= gcd_value;
    denominator_ /= gcd_value;

    // Убедиться, что знак всегда в числителе
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
}


public:
    Fraction(int numerator = 0, int denominator = 1)
        : numerator_(numerator), denominator_(denominator) {
        reduce();  // Сразу сокращаем дробь при создании
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator_ << "/" << frac.denominator_;
        return os;
    }

    // Арифметические операторы
    Fraction operator+(const Fraction& other) const {
        int new_num = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        int new_den = denominator_ * other.denominator_;
        return Fraction(new_num, new_den);
    }

    Fraction operator-(const Fraction& other) const {
        int new_num = (numerator_ * other.denominator_) - (other.numerator_ * denominator_);
        int new_den = denominator_ * other.denominator_;
        return Fraction(new_num, new_den);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator_ * other.numerator_, denominator_ * other.denominator_);
    }

    Fraction operator/(const Fraction& other) const {
        return Fraction(numerator_ * other.denominator_, denominator_ * other.numerator_);
    }

    // Унарный минус
    Fraction operator-() const {
        return Fraction(-numerator_, denominator_);
    }

    // Префиксный инкремент
    Fraction& operator++() {
        numerator_ += denominator_;
        reduce();
        return *this;
    }

    // Постфиксный инкремент
    Fraction operator++(int) {
        Fraction temp = *this;
        numerator_ += denominator_;
        reduce();
        return temp;
    }

    // Префиксный декремент
    Fraction& operator--() {
        numerator_ -= denominator_;
        reduce();
        return *this;
    }

    // Постфиксный декремент
    Fraction operator--(int) {
        Fraction temp = *this;
        numerator_ -= denominator_;
        reduce();
        return temp;
    }

    // Сравнение дробей для операторов == и <
    bool operator==(const Fraction& other) const {
        return numerator_ * other.denominator_ == denominator_ * other.numerator_;
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    bool operator<(const Fraction& other) const {
        return numerator_ * other.denominator_ < denominator_ * other.numerator_;
    }

    bool operator>(const Fraction& other) const {
        return other < *this;
    }

    bool operator<=(const Fraction& other) const {
        return !(*this > other);
    }

    bool operator>=(const Fraction& other) const {
        return !(*this < other);
    }
};

int main() {
    int num1, den1, num2, den2;
    
    std::cout << "Введите числитель дроби 1: ";
    std::cin >> num1;
    std::cout << "Введите знаменатель дроби 1: ";
    std::cin >> den1;
    Fraction f1(num1, den1);

    std::cout << "Введите числитель дроби 2: ";
    std::cin >> num2;
    std::cout << "Введите знаменатель дроби 2: ";
    std::cin >> den2;
    Fraction f2(num2, den2);

    std::cout << f1 << " + " << f2 << " = " << (f1 + f2) << '\n';
    std::cout << f1 << " - " << f2 << " = " << (f1 - f2) << '\n';
    std::cout << f1 << " * " << f2 << " = " << (f1 * f2) << '\n';
    std::cout << f1 << " / " << f2 << " = " << (f1 / f2) << '\n';

    std::cout << "++" << f1 << " * " << f2 << " = " << (++f1 * f2) << '\n';
    std::cout << "Значение дроби 1 = " << f1 << '\n';

    std::cout << f1 << "-- * " << f2 << " = " << (f1-- * f2) << '\n';
    std::cout << "Значение дроби 1 = " << f1 << '\n';

    return 0;
}