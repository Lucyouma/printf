#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 * PessyLucy
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_ier = *i + 1;
	int precision = -1;

	if (format[curr_ier] != '.')
		return (precision);

	precision = 0;

	for (curr_ier += 1; format[curr_ier] != '\0'; curr_ier++)
	{
		if (is_digit(format[curr_ier]))
		{
			precision *= 10;
			precision += format[curr_ier] - '0';
		}
		else if (format[curr_ier] == '*')
		{
			curr_ier++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_ier - 1;

	return (precision);
}
