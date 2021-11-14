#define _CRT_SECURE_NO_WARNINGS

#include "sort_text.h"

#include <stdio.h>
#include <string.h>
#include <cstdlib>


int main()
{
	FILE* file = fopen("additional_file/text.txt", "rb");
	if (file == NULL)
	{
		fputs("Error file open\n", stderr);
		exit(1);
	}

	int syms = CountSymbols(file);

	char* text = (char*)calloc((syms + 1), sizeof(char));

	int lines = GetParametersFile(file, text, syms);

	fclose(file);

	char** p = (char**)calloc(lines, sizeof(char*));
	if (p == NULL)
	{
		fputs("Error memory allocation for **p\n", stderr);
		exit(2);
	}
	for (int i = 0; i < lines; i++)
	{
		p[i] = (char*)calloc(100, sizeof(char));
		if (p[i] == NULL)
		{
			fputs("Error memory allocation for *p\n", stderr);
			exit(2);
		}
	}

	SeparateTextToLines(text, p);


	printf("\n\n---------------------------------------------\n");

	StringsSort(p, 0, lines - 1, CompareStr);

	for (int i = 0; i < lines; i++)
	{
		printf("%s\n", p[i]);
	}


	free(text);
	for (int i = 0; i < lines; i++)
	{
		free(p[i]);
	}
	free(p);
}

