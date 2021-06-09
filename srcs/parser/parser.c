#include "minishell.h"

void	ft_split_by_spaces(char **command, const char *found)
{
	char	**split;
	int		i;

	split = ft_split(found, ' ');
	if (!split)
	{
		ft_strjoin_and_free_1(command, found);
		return ;
	}
	ft_strjoin_and_free_1(command, split[0]);
	i = 1;
	while (split[i])
	{
		g_all.flags.special_value = 0;
		ft_command_add_to_list(command);
		ft_strjoin_and_free_1(command, split[i]);
		i++;
	}
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	ft_parser_2_1(char **command, const char *str, int *i,
					char **env_str)
{
	char	*tmp;

	ft_malloc_one_char_str(env_str);
	while (((str[*i] >= 'A' && str[*i] <= 'Z')
			|| (str[*i] >= 'a' && str[*i] <= 'z')
			|| (str[*i] >= '0' && str[*i] <= '9')
			|| str[*i] == '_') && str[*i])
	{
		ft_strjoin_char_and_free(env_str, str[*i]);
		(*i)++;
	}
	if ((*env_str)[0] == '\0')
		tmp = "$";
	else
		tmp = ft_find_env_var(*env_str);
	if (tmp == NULL)
	{
		free(*env_str);
		return (1);
	}
	if (g_all.flags.double_quote)
		ft_strjoin_and_free_1(command, tmp);
	else
		ft_split_by_spaces(command, tmp);
	return (0);
}

int	ft_parser_2(char **command, const char *str, int *i)
{
	char	*env_str;

	if (str[*i] == '$' && !g_all.flags.esc)
	{
		(*i)++;
		if (str[*i] == '?')
		{
			env_str = ft_itoa(g_all.exit_status);
			ft_strjoin_and_free_1(command, env_str);
			(*i)++;
		}
		else
		{
			if (ft_parser_2_1(command, str, i, &env_str))
				return (1);
		}
		free(env_str);
		return (1);
	}
	return (0);
}

void	ft_parser(const char *str)
{
	int		i;
	char	*command;

	ft_init_parse_flags();
	ft_malloc_one_char_str(&command);
	i = 0;
	while (str[i])
	{
		if (ft_parser_2(&command, str, &i))
			continue ;
		if (ft_parser_3(&command, str, &i))
			continue ;
		i++;
	}
	ft_command_add_to_list(&command);
	free(command);
}
