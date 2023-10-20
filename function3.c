#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * PessyLucy
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int jer, curr_ier;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_ier = *i + 1; format[curr_ier] != '\0'; curr_ier++)
	{
		for (jer = 0; FLAGS_CH[jer] != '\0'; jer++)
			if (format[curr_ier] == FLAGS_CH[jer])
			{
				flags |= FLAGS_ARR[jer];
				break;
			}

		if (FLAGS_CH[jer] == 0)
			break;
	}

	*i = curr_ier - 1;

	return (flags);
}
