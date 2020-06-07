#pragma once
#include <string>
#include <stack>
using namespace std;

// Khai báo miền giá trị -2^127 <= QInt <= 2^127-1 (Số nhị phân không vượt quá 128 bit)
#define QINT_MAX "170141183460469231731687303715884105727"
#define QINT_MIN "-170141183460469231731687303715884105728"

class QInt
{
private:
	long long arrayBits[2];
public:
	QInt();
	QInt(string X, int radix = 10);
	~QInt();

	// Get - Set Bit
	void SetBit(bool bit, int i);
	bool GetBit(int i) const;

	// Parse - Convert
	void ParseQInt(string X, int radix = 10);
	string ToString(int radix = 10) const;
	void DecimalToQInt(string X);
	string QIntToDecimal() const;
	void HexToQInt(string X);
	string QIntToHex() const;
	void BinaryToQInt(string X);
	string QIntToBinary() const;


	// Bitwise Operator
	QInt operator&(const QInt& argu) const;
	QInt operator|(const QInt& argu) const;
	QInt operator^(const QInt& argu) const;
	QInt operator~() const;
	// Shift Operator
	QInt operator<<(unsigned int shift);
	QInt operator>>(unsigned int shift);
	// Rotate Function
	QInt ror();
	QInt rol();
	//IO Operator
	friend ostream& operator<<(ostream& out, const QInt& q);
	friend istream& operator>>(istream& in, QInt& q);
	// Calculation Operator
	QInt& operator=(const QInt& argu);
	QInt operator+(const QInt& argu) const;
	QInt operator-(const QInt& argu) const;
	QInt operator*(const QInt& argu) const;
	QInt operator/(const QInt& argu) const;
	QInt operator%(const QInt& argu) const;
	bool operator<(const QInt& argu) const; // Support
	bool operator>=(const QInt& argu) const; // Support
	bool operator>(const QInt& argu) const; // Support
	bool operator<=(const QInt& argu) const; // Support
	bool operator==(const QInt& argu) const; // Support

	// Calculation on string
	static string StrDiv2(string X);
	static string StrMult2(string X);
	static string Pow2(int i);
	static string AddString(string a, string b);
	static string SubString(string a, string b); // Require a >= b

	// Support
	static QInt abs(const QInt& argu);

	// Two's complement
	static QInt TComplement(const QInt& argu);
};