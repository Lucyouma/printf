#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * PessyLucy
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int curr_ier = *i + 1;
	int size = 0;

	if (format[curr_ier] == 'l')
		size = S_LONG;
	else if (format[curr_ier] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_ier - 1;
	else
		*i = curr_ier;

	return (size);
}
