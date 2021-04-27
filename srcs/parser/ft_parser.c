#include "minishell.h"

// * пример вызова программы
// * исполняемые файлы искать в $PATH
// char *arg[] = {"cat", NULL};
// execve("/bin/cat", arg, NULL);

void	ft_init_parse_flags(void)
{
	g_all.flags.esc = 0;
	g_all.flags.dollar = 0;
	g_all.flags.single_quote = 0;
	g_all.flags.double_quote = 0;
}

// добавляет стркоу в лист
void	ft_command_add_to_list(char **command)
{
	//TODO: записать command в list
	if ((*command)[0] != '\0')
		printf("%s\n", *command);
	free(*command);
	ft_malloc_one_char_str(command);
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

// * Если встретилось что-либо, что разделяет команды, то добавляем
// * command в token list
// $? - exit status variable (содержит код последней команды)
void	ft_parser(const char *str)
{
	int		i;
	char	*command;
	char	*env_str;

	//TODO: в command сохранаям символы
	ft_init_parse_flags();
	ft_malloc_one_char_str(&command);
	i = 0;
	while(str[i])
	{
		if (g_all.flags.dollar)
		{
			if (str[i] == '?')
			{
				// добавить в command exit status variable
			}
			else
			{
				ft_malloc_one_char_str(&env_str);
				while (((str[i] >= 'A' && str[i] <= 'Z')
					|| (str[i] >= 'a' && str[i] <= 'z')
					|| str[i] == '_') && str[i])
				{
					ft_strjoin_char_and_free(&env_str, str[i]);
					i++;
				}
				//TODO: найти данные по этой переменной в env
				ft_putstr_fd("ENVIROMEN VARIABLE\n", 1);
				free(env_str);
			}
			g_all.flags.dollar = 0;
		}
		if (g_all.flags.esc)
		{
			ft_strjoin_char_and_free(&command, str[i]);
			g_all.flags.esc = 0;
		}
		else if (str[i] == '\"' && g_all.flags.double_quote) // $ и '\' сохраняют значения
			g_all.flags.double_quote = 0;
		else if (str[i] == '\"')
			g_all.flags.double_quote = 1;
		else if (str[i] == '$')
			g_all.flags.dollar = 1;
		else if (str[i] == '\\')
			g_all.flags.esc = 1;
		else if (g_all.flags.double_quote) // все что ниже не выполняется
			ft_strjoin_char_and_free(&command, str[i]);
		else if (str[i] == '\'')
		{
			i++;
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
		// ! иначе просто прибавляем к command
		else
			ft_strjoin_char_and_free(&command, str[i]);
		i++;
	}
	ft_command_add_to_list(&command);
	free(command);
}
