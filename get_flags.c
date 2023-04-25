#include "main.h"

/**
 * get_flags - Calculates the active flags in a given format string.
 *
 * The following flags are supported:
 * - '+' always print a sign (+ or -) for signed conversions
 * - '0' pad with zeros instead of spaces
 * - '#' use an alternative form for the conversion (e.g., 0x prefix for hex)
 * - ' ' print a space before a positive number(ignored if '+'flag is present)
 * - '-' left-justify the argument within the field width
 *
 * @format:The format string that wanted to count the flages in.
 * @index: the current index in the format string (pointer).
 * This value will be updated to the last index read by this function.
 * Return: The flags as a bitfield (see the F_* macros in main.h).
 */

int get_flags(const char *format, int *index)
{
	int flags = 0;

	const char *flags_str = "+0# -";

	const int flags_val[] = {F_PLUS, F_ZERO, F_HASH, F_SPACE, F_MINUS};

	int i, j;

	for (i = *index + 1; format[i] != '\0'; i++)
	{
		int b = (int)sizeof(flags_str);

		for (j = 0; j < b ; j++)
		{
			char current_format_letter = format[i];
			char current_flag = flags_str[j];

			if (current_format_letter == current_flag)
			{
				flags |= flags_val[j];
				break;
			}
		}
		if (j == sizeof(flags_str))
			break;
	}

	*index = i - 1;
	return (flags);
}
