#include "minishell.h"

void	ft_common_split_part(char **command, const char *str)
{
	ft_command_add_to_list(command);
	ft_strjoin_and_free_1(command, str);
	ft_command_add_to_list(command);
}

void	ft_command_add_to_list(char **command)
{
	if ((*command)[0] != '\0' || g_all.flags.quotes)
	{
		ft_tokens_newline(*command);
		if (!g_all.flags.special_value)
		{
			g_all.tokens->special_value = 0;
			g_all.flags.special_value = 1;
		}
		g_all.flags.quotes = 0;
		ft_malloc_one_char_str(command);
	}
}

void	ft_init_parse_flags(void)
{
	g_all.flags.esc = 0;
	g_all.flags.dollar = 0;
	g_all.flags.double_quote = 0;
	g_all.flags.special_value = 1;
	g_all.flags.quotes = 0;
}

char	*ft_find_env_var(char *str)
{
	int		i;
	int		len;
	char	*equal;

	i = 0;
	len = ft_strlen(str);
	while (g_all.env[i] != NULL)
	{
		equal = ft_strchr(g_all.env[i], '=');
		if (equal == NULL)
		{
			i++;
			continue ;
		}
		else
		{
			if (!ft_strncmp(g_all.env[i], str, len)
				&& g_all.env[i][len] == '=')
				return (&(g_all.env[i][len + 1]));
		}
		i++;
	}
	return (NULL);
}
