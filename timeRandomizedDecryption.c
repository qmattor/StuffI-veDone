/*
*	requirements for arguments (in order): string to decrypt, timestamp to decrypt at (exits if >= 0)
*/
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int		str_len(char *str)
{
	int i;

	i = 0;
	while(str[i++])
		;
	return (i);
}

void	putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	decrypt_string(char *str, long timestamp)
{
	int		r;
	int		nb;
	int		i;
	char	*newstr;

	i = 0;
	newstr = malloc(str_len(str));
	if (timestamp <= 0)
		exit(1);
	srand(timestamp);
	while (str[i])
	{
		//decrypts current number
		nb = atoi(str);
		r = rand() % 128;
		newstr[i] = ((nb - r) < 0) ? nb - r + 128 : nb - r;
		i++;
		//skips the pointer to the next number 
		while (*str >= '0' && *str <= '9')
			str++;
		str += 2;
	}
	putstr(newstr);
	write(1, "\n", 1);
}

int		main(int argc, char **argv)
{
	if (argc != 3)
	{
		return 1;
	}
	decrypt_string(argv[1], atoi(argv[2]));
	return 0;
}


