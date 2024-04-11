#include <iostream>

const double pi = 3.14159265358979323846; // Константа pi

// Определение класса ComplexNumber для комплексных чисел
class ComplexNumber {
private:
    double real;
    double imaginary;

public:
    // Конструктор
    ComplexNumber(double realPart, double imaginaryPart) : real(realPart), imaginary(imaginaryPart) {}

    // Методы для получения реальной и мнимой частей
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    // Оператор сложения
    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(real + other.real, imaginary + other.imaginary);
    }

    // Оператор умножения
    ComplexNumber operator*(const ComplexNumber& other) const {
        double realPart = real * other.real - imaginary * other.imaginary;
        double imaginaryPart = real * other.imaginary + imaginary * other.real;
        return ComplexNumber(realPart, imaginaryPart);
    }
};

// Функция для вычисления ДПФ
ComplexNumber** discreteFourierTransform(const double* signal, int N) {
    ComplexNumber** spectrum = new ComplexNumber * [N]; // Результирующий спектр

    // Проход по каждой частоте в спектре
    for (int k = 0; k < N; ++k) {
        spectrum[k] = new ComplexNumber(0.0, 0.0);
        // Проход по каждому элементу входного сигнала для вычисления суммы
        for (int n = 0; n < N; ++n) {
            double angle = -2 * pi * k * n / N; // Угол для текущей частоты k и времени n
            double cos_val = cos(angle); // Вычисляем косинус угла
            double sin_val = sin(angle); // Вычисляем синус угла
            ComplexNumber complex_exp(cos_val, sin_val); // Создаем комплексное число из косинуса и синуса
            *spectrum[k] = *spectrum[k] + ComplexNumber(signal[n], 0) * complex_exp; // Умножение на экспоненту и суммирование
        }
    }

    return spectrum; // Возвращаем спектр
}

int main() {
    const int N = 8; // Длина входного сигнала
    double signal[N] = { 1, -1.414, 1, -1.414, 1,1.414, -3, 1.414 }; // Входной сигнал

    // Вычисляем ДПФ входного сигнала
    ComplexNumber** spectrum = discreteFourierTransform(signal, N);

    // Выводим результаты
    std::cout << "Спектр сигнала:" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << "S[" << i << "] = " << spectrum[i]->getReal() << " + " << spectrum[i]->getImaginary() << "i" << std::endl;
    }

    // Освобождаем память, выделенную для спектра
    for (int i = 0; i < N; ++i) {
        delete spectrum[i];
    }
    delete[] spectrum;

    return 0;
}
