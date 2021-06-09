#include "minishell.h"

void	ft_parser_6(char **command, const char *str, int *i)
{
	if (str[*i] == ';' || (str[*i] == '|' && (str[*i - 2] == '>' || str[*i - 2] == '<')))
	{
		ft_command_add_to_list(command);
		ft_strjoin_char_and_free(command, str[*i]);
		ft_command_add_to_list(command);
		ft_handler();
		ft_free_tokens();
		ft_free_comands();
		ft_init_parse_flags();
		ft_malloc_one_char_str(command);
	}
	else if (str[*i] == '|')
		ft_common_split_part(command, "|");
	else
		ft_strjoin_char_and_free(command, str[*i]);
}

void	ft_parser_5(char **command, const char *str, int *i)
{
	if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			ft_common_split_part(command, ">>");
			(*i)++;
		}
		else
			ft_common_split_part(command, ">");
	}
	else if (str[*i] == '<')
		ft_common_split_part(command, "<");
	else
		ft_parser_6(command, str, i);
}

int	ft_parser_4(char **command, const char *str, int *i)
{
	if (str[*i] == '\\')
		g_all.flags.esc = 1;
	else if (g_all.flags.double_quote)
	{
		g_all.flags.special_value = 0;
		ft_strjoin_char_and_free(command, str[*i]);
	}
	else if (str[*i] == '\'')
	{
		(*i)++;
		g_all.flags.special_value = 0;
		g_all.flags.quotes = 1;
		while (str[*i] != '\'' && str[*i])
			ft_strjoin_char_and_free(command, str[(*i)++]);
	}
	else if (str[*i] == ' ' || str[*i] == '	')
	{
		while (str[*i] == ' ' || str[*i] == '	')
			(*i)++;
		ft_command_add_to_list(command);
		return (1);
	}
	else
		ft_parser_5(command, str, i);
	return (0);
}

int	ft_parser_3(char **command, const char *str, int *i)
{
	if (g_all.flags.esc)
	{
		if (!g_all.flags.double_quote || (g_all.flags.double_quote
				&& (str[*i] == '$' || str[*i] == '\\' || str[*i] == '"')))
			ft_strjoin_char_and_free(command, str[*i]);
		else
		{
			(*i)--;
			ft_strjoin_char_and_free(command, str[*i]);
		}
		g_all.flags.special_value = 0;
		g_all.flags.esc = 0;
	}
	else if (str[*i] == '\"' && g_all.flags.double_quote)
		g_all.flags.double_quote = 0;
	else if (str[*i] == '\"')
	{
		g_all.flags.quotes = 1;
		g_all.flags.special_value = 0;
		g_all.flags.double_quote = 1;
	}
	else
		return (ft_parser_4(command, str, i));
	return (0);
}
