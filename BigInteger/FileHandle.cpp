#include "FileHandle.h"

void FileHandle(const char* fileInput, const char* fileOutput)
{
	ifstream in(fileInput);
	ofstream out(fileOutput);

	if (!in.is_open())
	{
		throw "Cannot open file input.";
	}

	if (!out.is_open())
	{
		throw "Cannot create file output.";
	}

	string line;
	while (getline(in, line))
	{
		stringstream handle(line);

		int radix;
		handle >> radix;

		string tmp;
		queue<string> store;

		while (handle >> tmp)
		{
			store.push(tmp);
		}

		if (store.size() == 3)
		{
			string toanHang1, toanHang2;
			string toanTu;

			toanHang1 = store.front();
			QInt tH1;
			tH1.ParseQInt(toanHang1, radix);
			store.pop();

			toanTu = store.front();
			store.pop();

			toanHang2 = store.front();
			store.pop();
			QInt tH2;
			tH2.ParseQInt(toanHang2, radix);

			QInt result;

			if (toanTu.length() == 1)
			{
				switch (toanTu[0])
				{
				case '+':
					result = tH1 + tH2;
					break;
				case '-':
					result = tH1 - tH2;
					break;
				case '*':
					result = tH1 * tH2;
					break;
				case '/':
					result = tH1 / tH2;
					break;
				case '^':
					result = tH1 ^ tH2;
					break;
				case '&':
					result = tH1 & tH2;
					break;
				case '|':
					result = tH1 | tH2;
					break;
				}
			}
			else
			{
				if (toanTu == ">>")
				{
					result = tH1 >> stoi(tH2.ToString(10));
				}
				else if (toanTu == ">>")
				{
					result = tH1 << stoi(tH2.ToString(10));
				}
			}

			out << result.ToString(radix);
		}
		else if (store.size() == 2)
		{
			string s1 = store.front();
			store.pop();

			string s2 = store.front();
			store.pop();

			QInt result;
			result.ParseQInt(s2, radix);

			int radix2 = -1;
			if (s1[0] == 'r')
			{
				if (s1[2] == 'r')
				{
					result = result.ror();
				}
				else if (s1[2] == 'l')
				{
					result = result.rol();
				}
			}
			else if (s1 == "~")
			{
				result = ~result;
			}
			else
			{
				radix2 = stoi(s1);
			}

			if (radix2 != -1)
			{
				out << result.ToString(radix2);
			}
			else
			{
				out << result.ToString(radix);
			}
		}

		out << endl;
	}
}
