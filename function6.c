#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 * PessyLucy
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_ier;
	int width = 0;

	for (curr_ier = *i + 1; format[curr_ier] != '\0'; curr_ier++)
	{
		if (is_digit(format[curr_ier]))
		{
			width *= 10;
			width += format[curr_ier] - '0';
		}
		else if (format[curr_ier] == '*')
		{
			curr_ier++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_ier - 1;

	return (width);
}
