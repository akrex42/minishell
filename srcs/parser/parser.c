#include "minishell.h"

void	ft_init_parse_flags(void)
{
	g_all.flags.esc = 0;
	g_all.flags.dollar = 0;
	g_all.flags.double_quote = 0;
	g_all.flags.special_value = 1;
}

// добавляет стркоу в лист и выделяет память под новую строку
void	ft_command_add_to_list(char **command)
{
	if ((*command)[0] != '\0')
	{
		ft_tokens_newline(*command); // записываем строки в лист
		if (!g_all.flags.special_value)
		{
			// если хоть один элемень в строке был экранирован
			// или написан в кавычках
			// но проверять это мы будем только на отдельных символах
			// "|" ">" ">>" "<"
			g_all.tokens->special_value = 0;
			g_all.flags.special_value = 1;
		}
		ft_malloc_one_char_str(command);
	}
}

// если встречен специальный символ, то добавляет в лист строку,
// которая уже есть и этот специальный символ, а потом выделяет 
// место под новую строку
void	ft_common_split_part(char **command, const char *str)
{
	ft_command_add_to_list(command);
	ft_strjoin_and_free_1(command, str);
	ft_command_add_to_list(command);
}

void	ft_parser(const char *str)
{
	int		i;
	char	*command;
	char	*env_str;
	char	*tmp;

	ft_init_parse_flags();
	ft_malloc_one_char_str(&command);
	i = 0;
	while(str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				env_str = ft_itoa(g_all.exit_status);
				if (!env_str)
					ft_malloc_error();
				ft_strjoin_and_free_1(&command, env_str);
				free(env_str);
				i++;
			}
			else
			{
				ft_malloc_one_char_str(&env_str);
				while (((str[i] >= 'A' && str[i] <= 'Z')
					|| (str[i] >= 'a' && str[i] <= 'z')
					|| (str[i] >= '0' && str[i] <= '9')
					|| str[i] == '_') && str[i])
				{
					ft_strjoin_char_and_free(&env_str, str[i]);
					i++;
				}
				if (env_str[0] == '\0')
					tmp = "$";
				else
					tmp = ft_find_env_var(env_str);
				free(env_str);
				ft_strjoin_and_free_1(&command, tmp);
			}
		}
		if (g_all.flags.esc)
		{
			ft_strjoin_char_and_free(&command, str[i]);
			g_all.flags.special_value = 0;
			g_all.flags.esc = 0;
		}
		else if (str[i] == '\"' && g_all.flags.double_quote)
			g_all.flags.double_quote = 0;
		else if (str[i] == '\"')
			g_all.flags.double_quote = 1;
		else if (str[i] == '\\')
			g_all.flags.esc = 1;
		else if (g_all.flags.double_quote) // все что ниже не выполняется внутри " "
		{
			g_all.flags.special_value = 0;
			ft_strjoin_char_and_free(&command, str[i]);
		}
		else if (str[i] == '\'')
		{
			i++;
			g_all.flags.special_value = 0;
			while (str[i] != '\'' && str[i])
				ft_strjoin_char_and_free(&command, str[i++]);
		}
		else if (str[i] == ' ' || str[i] == '	')
		{
			while (str[i] == ' ' || str[i] == '	')
				i++;
			ft_command_add_to_list(&command);
			continue ;
		}
		else if (str[i] == '>')
			if (str[i + 1] == '>') // >>
			{
				ft_common_split_part(&command, ">>");
				i++;
			}
			else
				ft_common_split_part(&command, ">");
		else if (str[i] == '<')
			ft_common_split_part(&command, "<");
		else if (str[i] == '|')
			ft_common_split_part(&command, "|");
		else if (str[i] == ';')
			ft_common_split_part(&command, ";");
		else
			ft_strjoin_char_and_free(&command, str[i]);
		i++;
	}
	ft_command_add_to_list(&command);
	free(command);
}
