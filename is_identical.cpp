#include <iostream>
#include <cstdio>
#include <cstring>
bool is_identical(FILE*, FILE*);

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("Multiple files are required.\n");
		system("pause");
		return 1;
	}
	FILE* fp[2];
	int i;
	if (fopen_s(&fp[0], argv[1], "rb") || fopen_s(&fp[1], argv[2], "rb"))
	{
		printf("An error occurred while opening the first 2 files."
			" Make sure they are secure.\n");
		system("pause");
		return 1;
	}
	std::cout << "The files are "
		<< (is_identical(fp[0], fp[1]) ? "identical" : "UNIDENTICAL")
		<< ".\n";
	for (i = 3; i < argc; i++)
	{
		if (freopen_s(&fp[1], argv[i], "rb", fp[1]))
		{
			std::cout <<
				"An error occurred while opening the file \"" <<
				argv[i] <<
				"\". Make sure it is secure." << std::endl;
			_fcloseall();
			system("pause");
			return i - 1;
		}
		if (!is_identical(fp[0], fp[1])) {
			std::cout << "The files are UNIDENTICAL." << std::endl;
			_fcloseall();
			system("pause");
			return 0;
		}
		std::cout << argv[i] << " is identical to the first file." << std::endl;
	}
	system("pause");
	return 0;
}

bool is_identical(FILE* a, FILE* b)
{
	if (!(a && b))return false;
	char* bufa = new char[1 << 20], * bufb = new char[1 << 20];
	fseek(a, 0, SEEK_SET), fseek(b, 0, SEEK_SET);
	while (!(feof(a) || feof(b)))
	{
		fread_s(bufa, 1 << 20, 1, 1 << 20, a);
		fread_s(bufb, 1 << 20, 1, 1 << 20, b);
		if (memcmp(bufa, bufb,1<<20))return false;
	}
	delete[] bufa;
	delete[] bufb;
	return true;
}