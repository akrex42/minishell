#include "minishell.h"

void	ft_echo(char **str, int argc)
{
	// char *dollar;
	// char *newstr;
	// int len;
	int flag;
	int i;

	flag = 0;
	// WE CHANGE STDOUT WITH PIPES AND REDIRECTS!!!!!!!

	// int i = 0;
	// ft_putstr_fd(stdout, str);

	/* WE DO THE FOLLOWING IN THE PARSER, NOT HERE */

	// if ((dollar = ft_strchr(str, '$')))
	// {
	// 	while (str[i] != '$')
	// 	{
	// 		i++;
	// 	}
	// 	len = ft_strlen(dollar);
	// 	newstr = ft_substr(str, i, len); // possible leak
	// 	printf("%s\n", getenv(newstr)); //we get the env variable home and change dir to there
	// }
	i = 1;
	// Parse key -n if needed
	if (argc > 1 && !(strcmp(str[1], "-n")))
	{
		flag = 1;
		++i;
	}
	while (i < argc - 1)
	{
		printf("%s ", str[i]);
		i++;
	}
	if (argc > 1)
	{
		printf("%s", str[i]);
	}
	if (!flag)
	{
		printf("%c", '\n');
	}
	//return (0);
}

int main(int argc, char **argv)
{
	ft_echo(argv, argc);
	return (0);
}