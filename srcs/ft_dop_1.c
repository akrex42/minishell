#include "main_term.h"

void	ft_exit()
{
	ft_reset_input_mode();
	exit(0);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_malloc_one_char_str(char **str)
{
	*str = malloc(sizeof(char));
	if (!(*str))
		ft_malloc_error();
	(*str)[0] = '\0';
}

// str1 will be free and rewritten
void	ft_strjoin_and_free_1(char **str1, const char *str2)
{
	char	*tmp;

	if (!str2)
		return ;
	tmp = ft_strjoin(*str1, str2);
	if (!tmp)
		ft_malloc_error();
	free(*str1);
	*str1 = tmp;
}

// str2 will be free and rewritten
void	ft_strjoin_and_free_2(const char *str1, char **str2)
{
	char	*tmp;

	if (!str1)
		return ;
	tmp = ft_strjoin(str1, *str2);
	if (!tmp)
		ft_malloc_error();
	free(*str2);
	*str2 = tmp;
}

