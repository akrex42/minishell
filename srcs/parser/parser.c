#include "minishell.h"

void	ft_parser(char *str)
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
		if (str[i] == '$' && !g_all.flags.esc)
		{
			old_i = i;
			i++;
			if (str[i] == '?')
			{
				env_str = ft_itoa(g_all.exit_status);
				ft_strjoin_and_free_1(&command, env_str);
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
				if (tmp == NULL)
					ft_malloc_one_char_str(&tmp);
				ft_join_env_to_str(&str, old_i, env_str, tmp);
				i = old_i;
				//TODO: запомнить до какого мимвола мы раскрыли переменную и сделать все эти символы незначимыми
			}
			free(env_str);
		}
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
		{
			// ft_display_tokens(); // ! для отладки
			ft_command_add_to_list(&command);
			ft_strjoin_char_and_free(&command, str[i]);
			ft_command_add_to_list(&command);
			ft_handler();
			ft_free_tokens();
			ft_free_comands();
			ft_init_parse_flags();
			ft_malloc_one_char_str(&command);
		}
		else
			ft_strjoin_char_and_free(&command, str[i]);
		i++;
	}
	ft_command_add_to_list(&command);
	free(command);
}
