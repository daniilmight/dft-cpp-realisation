#include <iostream>

const double pi = 3.14159265358979323846; // ��������� pi

// ����������� ������ ComplexNumber ��� ����������� �����
class ComplexNumber {
private:
    double real;
    double imaginary;

public:
    // �����������
    ComplexNumber(double realPart, double imaginaryPart) : real(realPart), imaginary(imaginaryPart) {}

    // ������ ��� ��������� �������� � ������ ������
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    // �������� ��������
    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(real + other.real, imaginary + other.imaginary);
    }

    // �������� ���������
    ComplexNumber operator*(const ComplexNumber& other) const {
        double realPart = real * other.real - imaginary * other.imaginary;
        double imaginaryPart = real * other.imaginary + imaginary * other.real;
        return ComplexNumber(realPart, imaginaryPart);
    }
};

// ������� ��� ���������� ���
ComplexNumber** discreteFourierTransform(const double* signal, int N) {
    ComplexNumber** spectrum = new ComplexNumber * [N]; // �������������� ������

    // ������ �� ������ ������� � �������
    for (int k = 0; k < N; ++k) {
        spectrum[k] = new ComplexNumber(0.0, 0.0);
        // ������ �� ������� �������� �������� ������� ��� ���������� �����
        for (int n = 0; n < N; ++n) {
            double angle = -2 * pi * k * n / N; // ���� ��� ������� ������� k � ������� n
            double cos_val = cos(angle); // ��������� ������� ����
            double sin_val = sin(angle); // ��������� ����� ����
            ComplexNumber complex_exp(cos_val, sin_val); // ������� ����������� ����� �� �������� � ������
            *spectrum[k] = *spectrum[k] + ComplexNumber(signal[n], 0) * complex_exp; // ��������� �� ���������� � ������������
        }
    }

    return spectrum; // ���������� ������
}

int main() {
    const int N = 8; // ����� �������� �������
    double signal[N] = { 1, -1.414, 1, -1.414, 1,1.414, -3, 1.414 }; // ������� ������

    // ��������� ��� �������� �������
    ComplexNumber** spectrum = discreteFourierTransform(signal, N);

    // ������� ����������
    std::cout << "������ �������:" << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << "S[" << i << "] = " << spectrum[i]->getReal() << " + " << spectrum[i]->getImaginary() << "i" << std::endl;
    }

    // ����������� ������, ���������� ��� �������
    for (int i = 0; i < N; ++i) {
        delete spectrum[i];
    }
    delete[] spectrum;

    return 0;
}
