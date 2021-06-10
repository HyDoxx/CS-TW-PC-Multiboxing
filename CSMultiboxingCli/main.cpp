#include <Windows.h>
#include <iostream>
//#include "DK_cmdline.hpp"
int main(int argc, const char *argv[]) {
	FILE* NUL;
	fopen_s(&NUL ,"NUL", "w");
	fprintf_s(NUL, "%s", "weweeeeeee");
	return 0;
}