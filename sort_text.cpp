#include "sort_text.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void SwapValues(char* first, char* second)
{
	char* tmp = first;
	first = second;
	second = tmp;
}


inline int MissNotSymbols(char sym)
{
	return (((sym < 'A') || (sym > 'z') || (sym > 'Z' && sym < 'a')));
}


int CountSymbols(FILE* file)
{
	fseek(file, 0, SEEK_END);
	int syms = ftell(file);
	rewind(file);
	return syms;
}


int CompareStr(char first[], char second[])
{
	int f_len = strlen(first);
	int s_len = strlen(second);
	for (int i = 0, k = 0; (i < f_len + 1) && (k < s_len + 1); i++, k++)
	{
		while (MissNotSymbols(first[i]) && i < f_len)
		{
			i++;
		}
		while (MissNotSymbols(second[k]) && k < s_len)
		{
			k++;
		}
		char current_s_f = (char)tolower(first[i]);
		char current_s_s = (char)tolower(second[k]);
		if (current_s_f - current_s_s > 0)
		{
			return 1;
		}
		else if (current_s_f - current_s_s < 0)
		{
			return -1;
		}
	}
	return 0;
}


int CompareStrReverse(char first[], char second[])
{
	int f_len = strlen(first);
	int s_len = strlen(second);
	for (int i = 0, k = 0; i < (f_len + 1) && k < (s_len + 1); i++, k++)
	{
		while (MissNotSymbols(first[f_len - i]) && i < f_len)
		{
			i++;
		}
		while (MissNotSymbols(second[s_len - k]) && k < s_len)
		{
			k++;
		}
		char current_s_f = (char)tolower(first[f_len - i]);
		char current_s_s = (char)tolower(second[s_len - k]);
		
		if (current_s_f - current_s_s > 0)
		{
			return 1;
		}
		else if (current_s_f - current_s_s < 0)
		{
			return -1;
		}
	}
	return 0;
}


void StringsSort(char** array, int low, int high, int (*compare) (char*, char*))
{
	int i = low;
	int j = high;
	char* pivot = array[low + (high - low) / 2];
	do
	{
		while (compare(array[i], pivot) < 0)
		{
			i++;
		}
		while (compare(array[j], pivot) > 0)
		{
			j--;
		}
		if (i <= j)
		{
			if (compare(array[i], array[j]) > 0)
			{
				char* tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			if (j > 0)
			{
				j--;
			}
			i++;
		}
	} while (i <= j);

	if (i < high)
	{
		StringsSort(array, i, high, compare);
	}
	if (j > low)
	{
		StringsSort(array, low, j, compare);
	}
}


int GetParametersFile(FILE* file, char* text, int syms)
{
	if (text == NULL)
	{
		fputs("Error memory allocation for *text\n", stderr);
		exit(2);
	}
	if (fread(text, 1, syms, file) != syms)
	{
		fputs("Error reading", stderr);
		exit(3);
	}
	int lines = 0;
	for (int i = 0; i < syms; i++)
	{
		if (text[i] == '\n')
		{
			lines++;
		}
	}
	lines++;

	return lines;
}


void SeparateTextToLines(char* text, char** p)
{
	int sum = 0;
	int k = 0;
	for (int i = 0; text[sum] != '\0'; i++)
	{
		for (k = 0; text[sum] != '\0'; k++)
		{
			if (text[sum] == '\n')
			{
				sum++;
				break;
			}
			p[i][k] = text[sum];
			sum++;
		}
		p[i][++k] = '\0';
		p[i] = (char*)realloc(p[i], k * sizeof(char));
		if (p[i] == NULL)
		{
			fputs("Error memory reallocation for *p\n", stderr);
			exit(2);
		}
	}
}
