#include "FileHandle.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	using namespace std;
	if (argc != 3)
	{
		cout << "Error argument" << endl;
		cout << "Press any key to exit..." << endl;
		cin.get();
		exit(EXIT_FAILURE);
	}
	else
	{
		FileHandle(argv[1], argv[2]);
		cout << "Project run complete" << endl;
	}
	system("pause");
	return 0;
}