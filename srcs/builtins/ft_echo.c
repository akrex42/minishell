#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>

void	ft_echo(const char *str)
{
	char *dollar;
	char *newstr;
	int len;
	int i = 0;
	//ft_putstr_fd(stdout, str);
	if ((dollar = ft_strchr(str, '$')))
	{
		while (str[i] != '$')
		{
			i++;
		}
		len = ft_strlen(dollar);
		newstr = ft_substr(str, i, len); // possible leak
		printf("%s\n", getenv(newstr)); //we get the env variable home and change dir to there
	}
	else
	{
		printf("%s ", str);
	}
	//return (0);
}