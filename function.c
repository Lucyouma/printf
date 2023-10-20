#include "main.h"

/* PRINT CHAR */

/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * PessyLucy
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ch = va_arg(types, int);

	return (handle_write_char(ch, buffer, flags, width, precision, size));
}
/* PRINT A STRING */
/**
 * print_string - Prints a string
 * PessyLucy
 * @types: The specifier
 * @buffer: the buffer
 * @flags: The flags
 * @width: the width specifier
 * @precision: the precision
 * @size: the size
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, ier;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (ier = width - length; ier > 0; ier--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (ier = width - length; ier > 0; ier--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/* PRINT INT */
/**
 * print_int - Print int
 * PessyLucy
 * @types: The specifier
 * @buffer: the buffer
 * @flags: The flags
 * @width: the width specifier
 * @precision: the precision
 * @size: the size
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int ier = BUFF_SIZE - 2;
	int is_negative = 0;
	long int ner = va_arg(types, long int);
	unsigned long int num;
	int numb = 0;

	ner = convert_size_number(ner, size);

	if (ner == 0)
		buffer[ier--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)ner;

	if (ner < 0)
	{
		num = (unsigned long int)((-1) * ner);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[ier--] = (num % 10) + '0';
		num /= 10;
	}

	ier++;

	numb = write_number(is_negative, ier, buffer, flags, width, precision, size);
	return (numb);
}

/* PRINT BINARY */
/**
 * print_binary - Prints an unsigned number
 * PessyLucy
 * @types: The specifier
 * @buffer: the buffer
 * @flags: The flags
 * @width: the width specifier
 * @precision: the precision
 * @size: the size
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int ner, mer, ier, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	ner = va_arg(types, unsigned int);
	mer = 2147483648; /* (2 ^ 31) */
	a[0] = ner / mer;
	for (ier = 1; ier < 32; ier++)
	{
		mer /= 2;
		a[ier] = (ner / mer) % 2;
	}
	for (ier = 0, sum = 0, count = 0; ier < 32; ier++)
	{
		sum += a[ier];
		if (sum || ier == 31)
		{
			char z = '0' + a[ier];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

/* PRINT PERCENT SIGN */
/**
 * print_percent - Prints a percent sign
 * PessyLucy
 * @types: The specifier
 * @buffer: the buffer
 * @flags: The flags
 * @width: the width specifier
 * @precision: the precision
 * @size: the size
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
