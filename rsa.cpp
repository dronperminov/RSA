#include <iostream>

using namespace std;

// расширенный алгоритм Евклида дл нахождения НОД двух чисел (НОД(a, b) = ax + by)
long gcd(long a, long b, long &x, long &y) {
	if (a == 0) {
		x = 0; 
		y = 1;

		return b;
	}

	long x1, y1;
	long d = gcd(b % a, a, x1, y1);

	x = y1 - (b / a) * x1;
	y = x1;

	return d;
}

// алгоритм быстрого возведения числа a в натуральную степень n по модулю m
long modPow(long a, long n, long m) {
	if (n == 0)
		return 1;

	if (n % 2 == 1)
		return (a * modPow(a, n - 1, m)) % m;

	long b = modPow(a, n / 2, m);

	return (b * b) % m;
}

// проверка числа на простоту
bool isPrime(long n) {
	for (long i = 2; i < n; i++)
		if (n % i == 0)
			return false;

	return true;
}

int main() {
	long p, q; // простые числа для шифрования и дешифрования
	long e; // открытая экспонента

	cout << "Enter p, q (must be primes): ";
	cin >> p >> q;

	while (!isPrime(p) || !isPrime(q)) {
		cout << "p or q is not prime. Try again: ";
		cin >> p >> q;
	}

	cout << "Enter public exponent (must be prime): ";
	cin >> e;

	while (!isPrime(e)) {
		cout << "e is not prime. Try again: ";
		cin >> e;
	}

	long n = p * q;
	long phi = (p - 1) * (q - 1);
	long d, y;
	gcd(e, phi, d, y); // находим такое d, что оно является взаимопростым с e

	if (d < 0)
		d += phi;

	long R;
	cout << "Enter value for encrypt (R): ";
	cin >> R;

	long encrypted = modPow(R, e, n);
	long decrypted = modPow(encrypted, d, n);

	cout << endl;
	cout << "e = " << e << endl;
	cout << "n = p * q = " << n << endl;
	cout << "phi = (p - 1) * (q - 1) = " << phi << endl;
	cout << "d = " << d << endl << endl;

	cout << "Encrypted: " << encrypted << endl;
	cout << "Decrypted: " << decrypted << endl;
}