#include "minishell.h"

void	ft_malloc_one_char_str(char **str)
{
	*str = malloc(sizeof(char));
	if (!(*str))
		ft_malloc_error();
	(*str)[0] = '\0';
}

void	ft_strjoin_char_and_free(char **str1, char ch)
{
	char	*tmp;
	char	dup[2];

	if (!ch)
		return ;
	dup[0] = ch;
	dup[1] = '\0';
	tmp = ft_strjoin(*str1, dup);
	if (!tmp)
		ft_malloc_error();
	free(*str1);
	*str1 = tmp;
}

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
