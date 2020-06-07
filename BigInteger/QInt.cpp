#include "QInt.h"

QInt::QInt()
{
	arrayBits[0] = 0;
	arrayBits[1] = 0;
}


QInt::QInt(string X, int radix /*= 10*/)
{

	arrayBits[0] = 0;
	arrayBits[1] = 0;
	ParseQInt(X, radix);
}

QInt::~QInt()
{
}

void QInt::SetBit(bool bit, int i)
{
	long long* pos = arrayBits;

	if (i < 64)
	{
		pos++;
	}
	else
	{
		i -= 64;
	}

	if (bit)
	{
		*pos = ((long long)1 << i) | *pos;
	}
	else
	{
		*pos = ~((long long)1 << i) & *pos;
	}
}

bool QInt::GetBit(int i) const
{
	const long long* pos = arrayBits;

	if (i < 64)
	{
		pos++;
	}
	else
	{
		i -= 64;
	}

	long long tmp = *pos;

	return (tmp >> i) & 1;
}

void QInt::ParseQInt(string X, int radix)
{
	switch (radix)
	{
	case 2:
	{
			  BinaryToQInt(X);
	}
		break;
	case 10:
	{
			   DecimalToQInt(X);
	}
		break;
	case 16:
	{
			   HexToQInt(X);
	}
		break;
	default:
		throw "Error radix number in your method ParseQInt.";
		break;
	}
}

string QInt::ToString(int radix) const
{
	string result;
	switch (radix)
	{
	case 2:
	{
			  result = QIntToBinary();
	}
		break;
	case 10:
		result = QIntToDecimal();
		break;
	case 16:
		result = QIntToHex();
		break;
	default:
		throw "Error radix number in your method ParseQInt.";
		break;
	}

	return result;
}

std::string QInt::StrDiv2(string X)
{
	string result;
	int n = X.length();

	if (n < 20 || (n == 20 && X <= to_string(ULLONG_MAX)))
	{
		result = to_string(stoull(X) / 2);
	}
	else
	{
		int div = X[0] - '0';
		int du = 0;
		char index = 1;
		if (div == 1)
		{
			index = 2;
			div *= 10;
			div += X[1] - '0';
		}

		result += (div / 2 + '0');
		du = div & 1;

		for (int i = index; i < n; i++)
		{
			div = du * 10 + X[i] - '0';
			result += (div / 2 + '0');
			du = div & 1;
		}
	}

	return result;
}

std::string QInt::StrMult2(string X)
{
	string result;
	stack<char> res;
	int n = X.length();

	bool remem = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		int tmp = X[i] - '0';

		if (tmp < 5)
		{
			res.push((char)(tmp * 2 + '0' + remem));
			remem = 0;
		}
		else
		{
			res.push((char)(tmp * 2 - 10 + '0' + remem));
			remem = 1;
		}
	}
	if (remem) result += '1';

	while (!res.empty())
	{
		result += res.top();
		res.pop();
	}

	return result;
}

std::string QInt::Pow2(int i)
{

	string result;
	if (i < 65)
	{
		if (i == 64)
		{
			result = to_string(ULLONG_MAX);
			result[result.length() - 1]++;
		}
		else
		{
			result = to_string((unsigned long long)pow(2, i));
		}
	}
	else
	{
		i -= 64;
		result = to_string(ULLONG_MAX);
		result[result.length() - 1]++;

		for (int t = 0; t < i; t++)
		{
			result = StrMult2(result);
		}

	}

	return result;
}

std::string QInt::AddString(string a, string b)
{
	int lenA = a.length();
	int lenB = b.length();

	if (lenA < 19 && lenB < 19)
	{
		return to_string(stoull(a) + stoull(b));
	}

	stack<char> res;
	string result = "";

	auto r_it_a = a.rbegin();
	auto r_it_b = b.rbegin();

	int remem = 0;
	while (r_it_a != a.rend() && r_it_b != b.rend())
	{
		int add = *r_it_a + *r_it_b + remem - 2 * '0';

		if (add > 9)
		{
			remem = 1;
			add -= 10;
		}
		else remem = 0;

		res.push(add + '0');

		r_it_a++;
		r_it_b++;
	}

	if (r_it_a == a.rend())
	{
		while (r_it_b != b.rend())
		{
			int add = *r_it_b + remem - '0';

			if (add > 9)
			{
				remem = 1;
				add -= 10;
			}
			else remem = 0;

			res.push(add + '0');

			r_it_b++;
		}
	}
	else
	{
		while (r_it_a != a.rend())
		{
			int add = *r_it_a + remem - '0';

			if (add > 9)
			{
				remem = 1;
				add -= 10;
			}
			else remem = 0;

			res.push(add + '0');

			r_it_a++;
		}
	}
	if (remem) result += '1';

	while (!res.empty())
	{
		result += res.top();
		res.pop();
	}

	return result;
}

std::string QInt::SubString(string a, string b)
{
	bool flagNegaive = false;
	int lenA = a.length();
	int lenB = b.length();

	if (lenA < lenB)
	{
		flagNegaive = true;
		swap(a, b);
	}
	else if (lenA == lenB && a < b)
	{
		flagNegaive = true;
		swap(a, b);
	}

	if (lenA < 19 && lenB < 19)
	{
		return to_string(stoull(a) - stoull(b));
	}

	stack<char> res;
	string result = "";

	auto r_it_a = a.rbegin();
	auto r_it_b = b.rbegin();

	int remem = 0;
	while (r_it_a != a.rend() && r_it_b != b.rend())
	{
		int sub = *r_it_a - *r_it_b - remem;

		if (sub < 0)
		{
			remem = 1;
			sub += 10;
		}
		else remem = 0;

		res.push(sub + '0');

		r_it_a++;
		r_it_b++;
	}

	if (r_it_a == a.rend())
	{
		while (r_it_b != b.rend())
		{
			int sub = *r_it_b - remem - '0';

			if (sub < 0)
			{
				remem = 1;
				sub += 10;
			}
			else remem = 0;

			res.push(sub + '0');

			r_it_b++;
		}
	}
	else
	{
		while (r_it_a != a.rend())
		{
			int sub = *r_it_a - remem - '0';

			if (sub < 0)
			{
				remem = 1;
				sub += 10;
			}
			else remem = 0;

			res.push(sub + '0');

			r_it_a++;
		}
	}

	if (flagNegaive)
	{
		result += '-';
	}

	bool flagNonZero = false;
	while (!res.empty())
	{
		if (res.top() != '0')
		{
			flagNonZero = true;
		}

		if (flagNonZero)
			result += res.top();
		res.pop();
	}

	return result;
}

QInt QInt::abs(const QInt& argu)
{
	QInt result = argu;

	if (result.GetBit(127))
	{
		result = QInt::TComplement(result);
	}

	return result;
}

QInt QInt::TComplement(const QInt& argu)
{
	QInt result;
	QInt one("1", 2);

	result = ~argu + one;

	return result;
}

void QInt::DecimalToQInt(string X)
{
	bool flagNegative = false;
	if (X[0] == '-')
	{
		flagNegative = true;
		X = X.substr(1);
	}
	int n = X.length();
	if (n < 20 || (n == 20 && X <= to_string(ULLONG_MAX)))
	{
		arrayBits[1] = stoull(X);
	}
	else
	{
		int idBit = 0;
		while (X != "0")
		{
			int len = X.length() - 1;

			SetBit((X[len] - '0') % 2, idBit);
			idBit++;

			X = StrDiv2(X);
		}
	}

	if (flagNegative) *this = this->TComplement(*this);
}

std::string QInt::QIntToDecimal() const
{
	string result = to_string((unsigned long long)arrayBits[1]);
	if (arrayBits[0] == 0) return result;

	int i = 126;
	while (i >= 64)
	{
		bool bit_i = GetBit(i);

		if (bit_i)
		{
			result = AddString(result, Pow2(i));
		}

		i--;
	}

	if (GetBit(127))
	{
		result = SubString(result, Pow2(127));
	}

	return result;
}

void QInt::HexToQInt(string X)
{
	int len = X.length();

	for (int i = len - 1; i >= 0; i--)
	{
		char tmp = toupper(X[i]);

		if (isalpha(tmp))
		{
			tmp -= 'A';
			tmp += 10;
		}
		else if (isdigit(tmp))
		{
			tmp -= '0';
		}

		int j = 0;
		while (j < 4)
		{
			if ((tmp >> j) & 1)
			{
				SetBit(1, (len - i - 1) * 4 + j);
			}
			j++;
		}
	}
}

std::string QInt::QIntToHex() const
{
	stack<char> res;
	string result = "";

	for (int i = 0; i < sizeof(arrayBits)* 2; i++)
	{
		char tmp = 0;
		int j = 0;
		while (j < 4)
		{
			if (GetBit(i * 4 + j))
			{
				tmp = tmp | (1 << j);
			}
			j++;
		}

		if (tmp > 9) res.push(tmp - 10 + 'A');
		else res.push(tmp + '0');
	}

	bool flagNonZero = false;
	while (!res.empty())
	{
		if (res.top() != '0')
			flagNonZero = true;

		if (flagNonZero)
			result += res.top();

		res.pop();
	}

	if (flagNonZero == false) result += '0';

	return result;
}

void QInt::BinaryToQInt(string X){
	int len = X.length();
	for (int i = len - 1; i >= 0; i--)
	{
		bool bit = X[i] - '0';
		SetBit(bit, len - i - 1);
	}
}

string QInt::QIntToBinary() const{
	string result;
	bool first_one = false;
	int lenBits = sizeof(arrayBits)* 8;
	//bool IsNev = GetBit(127);
	for (int i = lenBits - 1; i >= 0; i--)
	{
		if (GetBit(i)) first_one = true;
		if (first_one)
		{
			char tmp = '0' + GetBit(i);
			result += tmp;
		}
	}
	//if (!IsNev) result = '0' + result;
	return result;
}




QInt QInt::operator&(const QInt& argu) const
{
	QInt result;

	result.arrayBits[0] = this->arrayBits[0] & argu.arrayBits[0];
	result.arrayBits[1] = this->arrayBits[1] & argu.arrayBits[1];

	return result;
}

QInt QInt::operator|(const QInt& argu) const
{
	QInt result;

	result.arrayBits[0] = this->arrayBits[0] | argu.arrayBits[0];
	result.arrayBits[1] = this->arrayBits[1] | argu.arrayBits[1];

	return result;
}

QInt QInt::operator^(const QInt& argu) const
{
	QInt result;

	result.arrayBits[0] = this->arrayBits[0] ^ argu.arrayBits[0];
	result.arrayBits[1] = this->arrayBits[1] ^ argu.arrayBits[1];

	return result;
}

QInt QInt::operator~() const
{
	QInt result;

	result.arrayBits[0] = ~(this->arrayBits[0]);
	result.arrayBits[1] = ~(this->arrayBits[1]);

	return result;
}

QInt QInt::rol()
{
	QInt result = *this;

	bool final_bit = result.GetBit(127);
	result = result << 1;
	result.SetBit(final_bit, 0);

	return result;
}

QInt QInt::ror()
{
	QInt result = *this;

	bool first_bit = result.GetBit(0);
	result = result >> 1;
	result.SetBit(first_bit, 127);

	return result;
}

QInt QInt::operator << (unsigned int shift)
{
	QInt result = *this;

	for (int i = 0; i < shift; i++)
	{
		// Get final bit of arrayBits[1]
		bool bit_63_1 = result.GetBit(63);

		// Shift left
		result.arrayBits[1] = result.arrayBits[1] << 1;
		result.arrayBits[0] = result.arrayBits[0] << 1;

		// Set bit_63_1 to bit_0_0
		result.SetBit(bit_63_1, 64);
	}

	return result;
}

QInt QInt::operator >> (unsigned int shift)
{
	QInt result = *this;

	for (int i = 0; i < shift; i++)
	{
		// Get first bit of arrayBits[0]
		bool bit_0_0 = result.GetBit(64);

		// Shift right
		result.arrayBits[1] = result.arrayBits[1] >> 1;
		result.arrayBits[0] = result.arrayBits[0] >> 1;

		// Set bit_0_0 to bit_63_1
		result.SetBit(bit_0_0, 63);
	}

	return result;
}

QInt QInt::operator+(const QInt& argu) const
{
	QInt result;
	QInt carry = *this & argu;
	result = *this ^ argu;

	while (carry.arrayBits[0] != 0 || carry.arrayBits[1] != 0)
	{
		QInt shiftedcarry = carry << 1;
		carry = result & shiftedcarry;
		result = result ^ shiftedcarry;
	}

	return result;
}

QInt QInt::operator-(const QInt& argu) const
{
	QInt result;

	result = *this + QInt::TComplement(argu);

	return result;
}

QInt QInt::operator*(const QInt& argu) const
{
	QInt Q = argu;
	QInt A;
	bool BitQ_1 = 0;
	int k = 128;

	while (k > 0)
	{
		if (BitQ_1 ^ Q.GetBit(0)) // 10 or 01
		{
			if (BitQ_1 == 0) // 10
			{
				A = A - *this;
			}
			else
			{
				A = A + *this;
			}
		}

		// shift arithmetic right A, Q, Q-1
		{
			bool bit0_A = A.GetBit(0);
			BitQ_1 = Q.GetBit(0);

			A = A >> 1;
			Q = Q >> 1;

			Q.SetBit(bit0_A, 127);

		}
		k--;
	}

	return Q;
}

QInt QInt::operator/(const QInt& argu) const
{
	if (this->ToString() == QINT_MIN){
		QInt Tmp1("-170141183460469231731687303715884105727");
		QInt Tmp2("-1");
		QInt quo1 = Tmp1 / argu;
		QInt rem1 = Tmp1 % argu;
		QInt quo2 = (Tmp2 + rem1) / argu;
		return (quo1 + quo2);
	}
	QInt Q = *this;
	QInt M = argu;
	QInt A;

	if (M == A) // M = 0
	{
		throw "Error divide by zero.";
	}
	else if (QInt::abs(Q) < QInt::abs(M)) return A;
	else
	{
		bool QNegative = Q.GetBit(127);
		bool MNegative = M.GetBit(127);

		if (QNegative)
			Q = TComplement(Q);
		if (MNegative)
			M = TComplement(M);

		int k = 128;
		while (k>0)
		{
			//Shift_left [A,Q]
			bool bit127_Q = Q.GetBit(127);
			A = A << 1;
			Q = Q << 1;
			A.SetBit(bit127_Q, 0);

			A = A - M;


			if (A.GetBit(127))
			{
				Q.SetBit(0, 0);
				A = A + M;
			}
			else
			{
				Q.SetBit(1, 0);
			}
			k--;
		}

		if (QNegative ^ MNegative)
		{
			Q = TComplement(Q);
		}

		return Q;
	}


}

QInt QInt::operator%(const QInt& argu) const{
	if (this->ToString() == QINT_MIN){
		QInt Tmp1("-170141183460469231731687303715884105727");
		QInt Tmp2("-1");
		QInt quo1 = Tmp1 / argu;
		QInt rem1 = Tmp1 % argu;
		QInt rem2 = (Tmp2 + rem1) % argu;
		return rem2;
	}
	QInt Q = *this;
	QInt M = argu;
	QInt A;

	if (M == A) // M = 0
	{
		throw "Error divide by zero.";
	}
	else if (QInt::abs(Q) < QInt::abs(M)) return Q;
	else
	{
		bool QNegative = Q.GetBit(127);
		bool MNegative = M.GetBit(127);

		if (QNegative)
			Q = TComplement(Q);
		if (MNegative)
			M = TComplement(M);

		int k = 128;
		while (k>0)
		{
			//Shift_left [A,Q]
			bool bit127_Q = Q.GetBit(127);
			A = A << 1;
			Q = Q << 1;
			A.SetBit(bit127_Q, 0);

			A = A - M;


			if (A.GetBit(127))
			{
				Q.SetBit(0, 0);
				A = A + M;
			}
			else
			{
				Q.SetBit(1, 0);
			}
			k--;
		}
		if (QNegative || MNegative)
		{
			A = TComplement(A);
		}
		return A;
	}
}


bool QInt::operator<(const QInt& argu) const
{
	QInt A = *this;
	QInt B = argu;
	if (A.GetBit(127) && !B.GetBit(127))
	{
		return true;
	}
	else if (!A.GetBit(127) && B.GetBit(127))
	{
		return false;
	}
	else
	{
		for (int i = 127; i >= 0; i--)
		{
			if (A.GetBit(i) ^ B.GetBit(i))
			{
				if (A.GetBit(i))
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool QInt::operator>=(const QInt& argu) const
{
	return !(*this < argu);
}

bool QInt::operator>(const QInt& argu) const
{
	QInt A = *this;
	QInt B = argu;
	if (A.GetBit(127) && !B.GetBit(127))
	{
		return false;
	}
	else if (!A.GetBit(127) && B.GetBit(127))
	{
		return true;
	}
	else
	{
		for (int i = 127; i >= 0; i--)
		{
			if (A.GetBit(i) ^ B.GetBit(i))
			{
				if (B.GetBit(i))
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool QInt::operator<=(const QInt& argu) const
{
	return !(*this > argu);
}

bool QInt::operator==(const QInt& argu) const
{
	if (this->arrayBits[0] == argu.arrayBits[0]
		&& this->arrayBits[1] == argu.arrayBits[1])
	{
		return true;
	}

	return false;
}

QInt& QInt::operator=(const QInt& argu)
{
	this->arrayBits[0] = argu.arrayBits[0];
	this->arrayBits[1] = argu.arrayBits[1];

	return *this;
}
ostream& operator<<(ostream& out, const QInt& q){
	out << q.ToString();
	return out;
}
istream& operator>>(istream& in, QInt& q){
	q.arrayBits[0] = 0;
	q.arrayBits[1] = 0;
	string tmp;
	in >> tmp;

	string radix(tmp.begin(), tmp.begin() + 2);
	if (isalpha(tmp[1])){
		tmp.assign(tmp.begin() + 2, tmp.end());
	}
	if (radix == "0x" || radix == "0X"){
		q.HexToQInt(tmp);
	}
	else if (radix == "0b" || radix == "0B")
		q.BinaryToQInt(tmp);
	else
		q.DecimalToQInt(tmp);
	return in;
}