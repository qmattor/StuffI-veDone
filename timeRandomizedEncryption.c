/*
*	requirements for arguments (in order): string to encrypt, timestamp to encrypt at (0 if NULL)
*/
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void	putnbr(long nb)
{
	int		x[20];
	int		i;
	char	c;

	i = 0;
	while (i < 20)
		x[i++] = 0;
	i = 0;
	while (nb > 0)
	{
		x[i++] = nb % 10;
		nb /= 10;
	}
	while (i > 0)
	{
		c = x[--i] + '0';
		write(1, &c, 1);
	}
}

void	putstrnums(char *str)
{
	while (*str)
	{
		putnbr(*str);
		write(1, ", ", 2);
		str++;
	}
}


void	encrypt_string(char *str, long timestamp)
{
	int r;
	int i;

	i = 0;
	if (timestamp <= 0)
		timestamp = time(NULL);
	srand(timestamp);
	while (str[i])
	{
		r = rand() % 128;
		str[i] = ((str[i] + r) > 128) ? str[i] + r - 128 : str[i] + r;
		i++;
	}
	putstrnums(str);
	putnbr(timestamp);
	write(1, "\n", 1);
}

int		main(int argc, char **argv)
{
	if (argc != 3)
	{
		return 1;
	}
	encrypt_string(argv[1], atoi(argv[2]));
	return 0;
}


