#include "main.h"

/**
 * print_unsigned - Prints an unsigned number from our passed function
 * @our_types: List a of arguments
 * @our_buffer: Buffer array to handle print
 * @flags:  Calculates active flags that is used in it.
 * @width: get width
 * @our_precision: our_Precision specification used.
 * @size: Size specifier one used.
 * Return: Number of chars printed.
 */
/******* this function used to print Unsisgned number *********/

int print_unsigned(va_list our_types, char our_buffer[],
	int flags, int width, int our_precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(our_types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		our_buffer[i--] = '0';

	our_buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		our_buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, our_buffer, flags, width, our_precision, size));
}


/**
 * print_octal - Prints an unsigned number from our passed function
 * @our_types: List a of arguments
 * @our_buffer: Buffer array to handle print
 * @flags:  Calculates active flags that is used in it.
 * @width: get width
 * @our_precision: our_Precision specification used.
 * @size: Size specifier one used.
 * Return: Number of chars printed.
 */
/******* this function used to print Unsisgned number *********/
int print_octal(va_list our_types, char our_buffer[],
	int flags, int width, int our_precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(our_types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		our_buffer[i--] = '0';

	our_buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		our_buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		our_buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, our_buffer, flags, width, our_precision, size));
}

/**
 * print_hexadecimal - - Prints an unsigned number from our passed function
 * @our_types: List a of arguments
 * @our_buffer: Buffer array to handle print
 * @flags:  Calculates active flags that is used in it.
 * @width: get width
 * @our_precision: our_Precision specification used.
 * @size: Size specifier one used.
 * Return: Number of chars printed.
 */

/************** print unsinded number in hex **************/

int print_hexadecimal(va_list our_types, char our_buffer[],
	int flags, int width, int our_precision, int size)
{
	return (print_hexa(our_types, "0123456789abcdef", our_buffer,
		flags, 'x', width, our_precision, size));
}


/**
 * print_hexa_upper - - Prints an unsigned number from our passed function
 * @our_types: List a of arguments
 * @our_buffer: Buffer array to handle print
 * @flags:  Calculates active flags that is used in it.
 * @width: get width
 * @our_precision: our_Precision specification used.
 * @size: Size specifier one used.
 * Return: Number of chars printed.
 */
/******* this function used to print Unsisgned number *********/

int print_hexa_upper(va_list our_types, char our_buffer[],
	int flags, int width, int our_precision, int size)
{
	return (print_hexa(our_types, "0123456789ABCDEF", our_buffer,
		flags, 'X', width, our_precision, size));
}

/**
 * print_hexa -- Prints an unsigned number from our passed function
 * @our_types: List a of arguments
 * @map_to: array
 * @our_buffer: Buffer array to handle print
 * @flags:  Calculates active flags that is used in it.
 * @flag_ch: a flage of char
 * @width: get width
 * @our_precision: our_Precision specification used.
 * @size: Size specifier one used.
 * Return: Number of chars printed.
 */
/******* this function used to print Unsisgned number *********/
int print_hexa(va_list our_types, char map_to[], char our_buffer[],
	int flags, char flag_ch, int width, int our_precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(our_types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		our_buffer[i--] = '0';

	our_buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		our_buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		our_buffer[i--] = flag_ch;
		our_buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, our_buffer, flags, width, our_precision, size));
}
