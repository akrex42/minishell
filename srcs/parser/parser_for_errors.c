#include "minishell.h"

// void	ft_init_parse_flags(void)
// {
// 	g_all.flags.esc = 0;
// 	g_all.flags.dollar = 0;
// 	g_all.flags.double_quote = 0;
// 	g_all.flags.special_value = 1;
// 	g_all.flags.quotes = 0;
// }

// // добавляет стркоу в лист и выделяет память под новую строку
// void	ft_command_add_to_list(char **command)
// {
// 	if ((*command)[0] != '\0' || g_all.flags.quotes)
// 	{
// 		ft_tokens_newline(*command); // записываем строки в лист
// 		if (!g_all.flags.special_value)
// 		{
// 			// если хоть один элемень в строке был экранирован
// 			// или написан в кавычках
// 			// но проверять это мы будем только на отдельных символах
// 			// "|" ">" ">>" "<"
// 			g_all.tokens->special_value = 0;
// 			g_all.flags.special_value = 1;
// 		}
// 		g_all.flags.quotes = 0;
// 		ft_malloc_one_char_str(command);
// 	}
// }

// // если встречен специальный символ, то добавляет в лист строку,
// // которая уже есть и этот специальный символ, а потом выделяет 
// // место под новую строку
// void	ft_common_split_part(char **command, const char *str)
// {
// 	ft_command_add_to_list(command);
// 	ft_strjoin_and_free_1(command, str);
// 	ft_command_add_to_list(command);
// }

void	ft_parser_for_errors(char *str)
{
	int		i;
	int		old_i;
	char	*command;
	char	*env_str;
	char	*tmp;

	ft_init_parse_flags();
	ft_malloc_one_char_str(&command);
	i = 0;
	while(str[i])
	{
		if (g_all.flags.esc)
		{
			if (!g_all.flags.double_quote || (g_all.flags.double_quote
				&& (str[i] == '$' || str[i] == '\\' || str[i] == '"')))
				ft_strjoin_char_and_free(&command, str[i]);
			else
			{
				i--;
				ft_strjoin_char_and_free(&command, str[i]);
			}
			g_all.flags.special_value = 0;
			g_all.flags.esc = 0;
		}
		else if (str[i] == '\"' && g_all.flags.double_quote)
			g_all.flags.double_quote = 0;
		else if (str[i] == '\"')
		{
			g_all.flags.quotes = 1;
			g_all.flags.special_value = 0;
			g_all.flags.double_quote = 1;
		}
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
			g_all.flags.quotes = 1; //для добавления пустой строки
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
