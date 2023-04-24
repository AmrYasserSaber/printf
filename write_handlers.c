#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 *
 * @buffer: Buffer array to handle print
 * @flags:Calculates active flags.
 * @size: Size specifier
 * @c: char types.
 * @width: get width.
 * @precision: precision specifier
 *
 * Return: Number of chars printed.
 */

int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{
	int count = 0;

	if (!(flags & F_MINUS))
	{
		char pad_char = (flags & F_ZERO) ? '0' : ' ';
		int pad_count = width - 1;

		while (pad_count > 0)
		{
			buffer[count++] = pad_char;
			pad_count--;
		}
	}
	buffer[count++] = c;
	if (flags & F_MINUS)
	{
		char pad_char = ' ';
		int pad_count = width - 1;

		while (pad_count > 0)
		{
			buffer[count++] = pad_char;
			pad_count--;
		}
	}
	return (count);
}


/************************* WRITE NUMBER *************************/
/**
 * write_number - Writes a number to the output buffer.
 * @num: The number to write.
 * @base: The base of the number (e.g., 10 for decimal, 16 for hex).
 * @buffer: Buffer to store the output.
 * @flags: Active flags.
 * @width: Field width.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters written to buffer.
 */

int write_number(unsigned long long num, int base, char buffer[],
		int flags, int width, int precision, int size)
{
	const char *digits = "0123456789abcdef";
	int written = 0;
	char tmp_buffer[32];
	int tmp_written = 0;
	int pad_count = 0;
	char pad_char = (flags & F_ZERO) ? '0' : ' ';

	do {
		tmp_buffer[tmp_written++] = digits[num % base];
		num /= base;
	} while (num);
	if (precision >= 0)
	{
		pad_count = precision - tmp_written;
		if (pad_count > 0)
		{
			while (pad_count--)
				buffer[written++] = '0';
		}
	}
	pad_count = width - tmp_written - pad_count;
	if (pad_count > 0 && !(flags & F_MINUS))
	{
		while (pad_count--)
			buffer[written++] = pad_char;
	}
	while (tmp_written--)
		buffer[written++] = tmp_buffer[tmp_written];
	if (pad_count > 0 && (flags & F_MINUS))
	{
		while (pad_count--)
			buffer[written++] = pad_char;
	}
	return (written);
}


/**
 * write_num - Converts a number to a string and writes it to a buffer
 * @num: The number to convert
 * @base: The base to use for the conversion (must be between 2 and 36)
 * @buffer: Buffer to store the output
 * @flags: Active flags
 * @width: Field width
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters written to buffer.
 */
int write_num(unsigned long long num, int base, char buffer[],
		int flags, int width, int precision, int size)
{
	const char digits[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *ptr = buffer;

	if (precision < 0)
		precision = 1;
	do {
		*ptr++ = digits[num % base];
		num /= base;
	} while (num > 0);
	int pad_count = width - (ptr - buffer);
	char pad_char = (flags & F_ZERO) ? '0' : ' ';

	if (flags & F_MINUS)
	{
		while (*ptr)
			*buffer++ = *ptr++;
		while (pad_count-- > 0)
			*buffer++ = pad_char;
	}
	else
	{
		while (pad_count-- > 0)
			*ptr++ = pad_char;
		while (ptr > buffer)
			*buffer++ = *(--ptr);
	}
	return (buffer - ptr);
}


/**
 *write_unsgnd-Converts an unsigned integer to a string and writes it to buffer
 * @num: The number to convert and write
 * @buffer: Buffer to store the output
 * @flags: Active flags
 * @width: Field width
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters written to buffer.
 */
int write_unsgnd(unsigned int num, char buffer[],
		int flags, int width, int precision, int size)
{
	if (num == 0 && precision == 0)
		return (0);

	char *start = buffer;
	char *hex_chars = (flags & F_LOWER) ? "0123456789abcdef" : "0123456789ABCDEF";
	int len = 0, padding = 0;

	do {
		buffer[len++] = hex_chars[num % 16];
		num /= 16;
	} while (num > 0);

	if (flags & F_HASH && len > 0)
		buffer[len++] = (flags & F_LOWER) ? 'x' : 'X';

	padding = width - len;
	if (padding > 0)
		buffer = (flags & F_MINUS) ?
			append_char(append_str(buffer, start, len), ' ', padding) :
			append_char(append_char(buffer, (flags & F_ZERO) ? '0' :
						' ', padding), '\0', 0);
	else
		buffer = append_char(buffer, '\0', 0);

	return (buffer - start);
}


/**
 * write_pointer - Writes a pointer address to the output buffer.
 * @arg: The pointer to write.
 * @buffer: Buffer to store the output.
 * @flags: Active flags.
 * @width: Field width.
 * @precision: Precision specifier.
 * @size: Size specifier.
 *
 * Return: Number of characters written to buffer.
 */
int write_pointer(void *arg, char buffer[],
		int flags, int width, int precision, int size)
{
	uintptr_t ptrval = (uintptr_t)arg;
	int len = snprintf(NULL, 0, "%p", arg);

	if (len < 0)
	{
		return (0);
	}
	if (width <= len + 2)
	{
		snprintf(buffer, len + 1, "%p", arg);
		return (len);
	}
	char pad_char = (flags & F_ZERO) ? '0' : ' ';
	int pad_count = width - len - 2;
	int idx = 0;

	if (!(flags & F_MINUS))
	{
		for (int i = 0; i < pad_count; i++)
		{
			buffer[idx++] = pad_char;
		}
	}
	buffer[idx++] = '0';
	buffer[idx++] = 'x';
	snprintf(buffer + idx, len + 1, "%p", arg);
	if (flags & F_MINUS)
	{
		for (int i = 0; i < pad_count; i++)
		{
			buffer[idx + len + i] = pad_char;
		}
	}
	return (width);
}


