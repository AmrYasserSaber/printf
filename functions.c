#include "main.h"


/**
 * print_char - Print a single character.
 *
 * @our_types: The list of argument types.
 * @our_buffer: Buffer to hold the printed string.
 * @flag: Flags to determine how the output should be formatted.
 * @widths: Width of the printed string.
 * @precisions: Precision of the printed string.
 * @our_size: Size of the printed string.
 *
 * Return: Number of characters printed.
 *
 * This function is part of print_functions.c, which contains functions to
 *  print various types,
 * including char, string, int, and binary.
 */

/**********This function use to print the char.*************/

int print_char(va_list our_types, char our_buffer[],
	int flag, int widths, int precisions, int our_size)
{
	char c = va_arg(our_types, int);

	return (handle_write_char(c, our_buffer, flag, widths, precisions, our_size));
}

/**
 * print_string - Prints a string
 * @our_types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

/**********This function use to print the string .*************/


int print_string(va_list our_types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(our_types, char *);

	(void)(buffer);
	(void)(size);

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
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}


/**
 * print_percent - to rpint percent sign
 * @our_types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

/**********This function use to print the percent sing .*************/

int print_percent(va_list our_types, char *buffer,
	int flags, int width, int precision, int size)
{
	(void)(our_types);
	(void)(buffer);
	(void)(flags);
	(void)(width);
	(void)(precision);
	(void)(size);

	write(1, "%", 1);

	return (1);
}


/**
 * print_int - Print int
 * @our_types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width from it.
 * @precision: Precision specification
 * @size: Size specifier from it.
 * Return: Number of chars printed
 */

/**********This function use to print the integer .*************/

int print_int(va_list our_types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(our_types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}


/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width from it.
 * @precision: Precision specification
 * @size: Size specifier from it.
 * Return: Number of chars printed
 */

/**********This function use to print the binary.*************/

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648u; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

