#include <iostream>
#include <locale>

const double pi = 3.14159265358979323846; // Константа pi

// Определение класса ComplexNumber для комплексных чисел
class ComplexNumber {
private:
    double real; // Действительная часть
    double imaginary; // Мнимая часть

public:
    // Конструктор
    ComplexNumber(double realPart, double imaginaryPart) : real(realPart), imaginary(imaginaryPart) {}

    // Методы для получения действительной и мнимой частей
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    // Оператор сложения для комплексных чисел.
    // Принимает ссылку на другой объект ComplexNumber, который будет добавлен к текущему объекту.
    // const указывает на то, что объект other не будет изменен внутри функции.
    ComplexNumber operator+(const ComplexNumber& other) const {
        // Создаем новый объект ComplexNumber, представляющий собой сумму текущего объекта и объекта other.
        // Суммируем действительные части текущего и переданного объектов ComplexNumber.
        double sumReal = real + other.real;
        // Суммируем мнимые части текущего и переданного объектов ComplexNumber.
        double sumImaginary = imaginary + other.imaginary;
        // Создаем и возвращаем новый объект ComplexNumber, представляющий сумму.
        return ComplexNumber(sumReal, sumImaginary);
    }

    // Оператор умножения для комплексных чисел.
    // Принимает ссылку на другой объект ComplexNumber, на который будет умножен текущий объект.
    // const указывает на то, что объект other не будет изменен внутри функции.
    ComplexNumber operator*(const ComplexNumber& other) const {
        // Вычисляем действительную часть произведения двух комплексных чисел.
        double realPart = real * other.real - imaginary * other.imaginary;
        // Вычисляем мнимую часть произведения двух комплексных чисел.
        double imaginaryPart = real * other.imaginary + imaginary * other.real;
        // Создаем и возвращаем новый объект ComplexNumber, представляющий произведение.
        return ComplexNumber(realPart, imaginaryPart);
    }

};

// Функция для вычисления ДПФ
ComplexNumber** discreteFourierTransform(const double* signal, int N) {
    // Выделяем память под массив указателей на объекты ComplexNumber для хранения спектра
    ComplexNumber** spectrum = new ComplexNumber * [N]; // Результирующий спектр

    // Проходим по каждой частоте в спектре
    for (int m = 0; m < N; ++m) {
        // Выделяем память для каждого элемента спектра и инициализируем его как комплексное число (0, 0)
        spectrum[m] = new ComplexNumber(0.0, 0.0);

        // Проходим по каждому элементу входного сигнала для вычисления суммы
        for (int n = 0; n < N; ++n) {
            // Вычисляем угол для текущей частоты k и времени n в соответствии с формулой ДПФ
            double angle = -2 * pi * m * n / N;

            double cos_val = cos(angle); // Вычисляем косинус угла
            double sin_val = sin(angle); // Вычисляем синус угла

            // Создаем комплексное число из косинуса и синуса
            ComplexNumber complex_exp(cos_val, sin_val);

            // Вычисляем комплексное произведение сигнала и экспоненты и прибавляем его к спектру
            *spectrum[m] = *spectrum[m] + ComplexNumber(signal[n], 0) * complex_exp;
            // Обращаемся к текущему объекту ComplexNumber в спектре через указатель spectrum[m]
            // Затем выполняем операцию умножения на комплексное число complex_exp, а результат прибавляем к текущему объекту
        }
    }

    // Возвращаем спектр - массив указателей на объекты ComplexNumber
    return spectrum;
}


int main() {
    setlocale(LC_ALL, "Russian");
    const int N = 1400; // Длина входного сигнала
    int fs = 14000;
    double ts = 1.0 / fs;
    double signal[N] = {}; // Входной сигнал

    for (int n = 0; n < N; ++n) {
        signal[n] = (2 * cos(2 * pi * 1400 * n * ts + (pi / 2))) + (0.5 * cos(2 * pi * 11900 * n * ts + (pi / 2))) + (3 * cos(2 * pi * 12000 * n * ts + (pi / 2)));
    }

    // Вычисляем ДПФ входного сигнала
    ComplexNumber** spectrum = discreteFourierTransform(signal, N);

    // Выводим результаты
    std::cout << "Спектр сигнала:" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << "X[" << i << "] = " << spectrum[i]->getReal() << " + " << spectrum[i]->getImaginary() << "i" << std::endl;
    }

    // Освобождаем память, выделенную для спектра
    for (int i = 0; i < N; ++i) {
        delete spectrum[i];
    }
    delete[] spectrum;

    return 0;
}
