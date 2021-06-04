#include "minishell.h"

void	ft_join_env_to_str(char **str, int i,
			char *str_to_find, char *str_to_join)
{
	int	j;
	int	tmp;
	char	*ret;

	j = ft_strlen(*str) -
		ft_strlen(str_to_find) + ft_strlen(str_to_join);
	ret = malloc(sizeof(char) * j);
	j = 0;
	while (j < i)
	{
		ret[j] = (*str)[j];
		j++;
	}
	tmp = i;
	j = 0;
	while (str_to_join[j])
	{
		ret[i] = str_to_join[j];
		i++;
		j++;
	}
	j = tmp + ft_strlen(str_to_find) + 1;
	while ((*str)[j])
	{
		ret[i] = (*str)[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	free(*str);
	*str = ret;
}

void	ft_malloc_one_char_str(char **str)
{
	*str = malloc(sizeof(char));
	if (!(*str))
		ft_malloc_error();
	(*str)[0] = '\0';
}

// str1 will be free and rewritten
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
