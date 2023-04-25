#include "main.h"

/**
 * get_width-Calculates the width for
 * printing based on the given format string.
 *
 * The width can be specified in one of two ways:
 *   1. As a decimal integer in the format string (e.g., "%5d" will print a
 *      minimum of 5 characters wide)
 *   2. As an asterisk followed by an integer argument (e.g., "%*d" will print
 *      a minimum width specified by the integer argument)
 *
 * @format: The format string to parse for the width.
 * @index: Pointer to the current index in the format string. This will
 *               be updated to the last index read by this function.
 * @list: The variable argument list containing the arguments to be
 *               printed. This is needed in case the width is specified using
 *               an asterisk followed by an integer argument.
 *
 * Return: The width specified in the format string, or zero if no width is
 *         specified.
 */

int get_width(const char *format, int *index, va_list list)
{
	int i = *index + 1;

	int width = 0;

	while (format[i] != '\0')
	{
		if (format[i] == '*')
		{

			width = va_arg(list, int);

			i++;

			break;

		}
		else if (is_digit(format[i]))
		{
			width *= 10;

			width += format[i] - '0';

			i++;

		}
		else
		{
			break;
		}
	}

	*index = i - 1;

	return (width);
}
