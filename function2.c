#include "main.h"

/* PRINT POINTER */
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * PessyLucy
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ig = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addr;
	char map_to[] = "0123456789abcdef";
	void *addr = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addr == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addr = (unsigned long)addr;

	while (num_addr > 0)
	{
		buffer[ig--] = map_to[num_addr % 16];
		num_addr /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ig++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ig, length,
		width, flags, padd, extra_c, padd_start));
}

/* PRINT NON PRINTABLE */
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * PessyLucy
 * @types: The specifier
 * @buffer: the buffer
 * @flags: The flags
 * @width: the width specifier
 * @precision: the precision
 * @size: the size
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int ier = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[ier] != '\0')
	{
		if (is_printable(str[ier]))
			buffer[ier + offset] = str[ier];
		else
			offset += append_hexa_code(str[ier], buffer, ier + offset);

		ier++;
	}

	buffer[ier + offset] = '\0';

	return (write(1, buffer, ier + offset));
}

/* PRINT REVERSE */
/**
 * print_reverse - Prints reverse string.
 * PessyLucy
 * @types: The specifier
 * @buffer: the buffer
 * @flags: The flags
 * @width: the width specifier
 * @precision: the precision
 * @size: the size
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int ier, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (ier = 0; str[ier]; ier++)
		;

	for (ier = ier - 1; ier >= 0; ier--)
	{
		char z = str[ier];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/* PRINT A STRING IN ROT13 */
/**
 * print_rot13string - Print a string in rot13.
 * PessyLucy
 * @types: The specifier
 * @buffer: the buffer
 * @flags: The flags
 * @width: the width specifier
 * @precision: the precision
 * @size: the size
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char xer;
	char *str;
	unsigned int ier, jer;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (ier = 0; str[ier]; ier++)
	{
		for (jer = 0; in[jer]; jer++)
		{
			if (in[jer] == str[ier])
			{
				xer = out[jer];
				write(1, &xer, 1);
				count++;
				break;
			}
		}
		if (!in[jer])
		{
			xer = str[ier];
			write(1, &xer, 1);
			count++;
		}
	}
	return (count);
}
