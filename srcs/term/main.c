#include "minishell.h"

void	ft_reset_input_mode(void)
{
	tcsetattr(0, TCSANOW, &(g_all.g_saved_attributes));
}

void	ft_cycle_head(void)
{
	ft_malloc_one_char_str(&(g_all.str));
	ft_malloc_one_char_str(&(g_all.str_hist));
	ft_set_prompt();
	tputs(save_cursor, 1, ft_putchar);
	g_all.wr[0] = '\0';
}

// действия с введенной строкой после цикла
void	ft_manage_str(void)
{
	// ft_strjoin_and_free_2((g_all.history)->content, &(g_all.str_hist));
	if (ft_strncmp(g_all.str_hist, "\0", 10))
	{
		ft_history_newline(&(g_all.history), g_all.str_hist);
		free(g_all.str);
		ft_parser(g_all.str_hist); // передача строки парсеру
	}
	else if (ft_strncmp(g_all.str, "\0", 10))
	{
		ft_history_newline(&(g_all.history), g_all.str);
		free(g_all.str_hist);
		ft_parser(g_all.str); // передача строки парсеру
	}
	else
	{
		free(g_all.str);
		free(g_all.str_hist);
	}
	// ft_display_tokens(); // ! для отладки
	ft_handler();
	//TODO: где-то ошибка free при пустой команде со спец символом
	ft_free_tokens();
	ft_free_comands();
}

// инициализация всех переменных
void	ft_init_term_all(char **env)
{
	g_all.history = NULL;
	g_all.tokens = NULL;
	g_all.comands = NULL;
	g_all.exit_status = 0;
	g_all.env = ft_allocate_env(env);
	g_all.path = ft_split(ft_find_env_var("PATH"), ':'); // добавляет двумерный массив возможных директорий для запуска программ
	ft_init_history(&(g_all.history));
	tgetent(0,  "xterm-256color"); // ! для дебаггера
	// tgetent(0,  getenv("TERM")); // ! основной
	signal(SIGINT, ft_sighnd); //ctrl + с //TODO пофиксить
	signal(SIGQUIT, ft_sighnd); //ctrl + '\'
}

void	ft_delete_one_char(char **str)
{
	int	len;
	char	*tmp;	

	len = ft_strlen(*str);
	if ((len + 10) % tgetnum("co") == 0)
	{
		int	i;
		tputs(cursor_up, 1, ft_putchar);
		i = tgetnum("co");
		while (i)
		{
			tputs(cursor_right, 1, ft_putchar);
			i--;
		}
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		tputs(cursor_right, 1, ft_putchar);
	}
	else
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
	tmp = malloc(sizeof(char) * (len));
	ft_strlcpy(tmp, *str, len);
	free(*str);
	*str = tmp;
}

//!ИСТОРИЯ ДОБАВЛЯЕТ ИСПОЛЬЗОВАННЫЕ БАЙТЫ ПРОГРАММЕ
int	main(int argc, char* argv[], char* env[])
{
	(void)argc;
	(void)argv;
	ft_set_input_mode(&g_all);
	ft_init_term_all(env);
	while (1)
	{
		ft_cycle_head();
		while (g_all.wr[0] != '\n')
		{
			ft_bzero(g_all.wr, 10);
			read(0, g_all.wr, 10);
			if (ft_check_unused_char(g_all.wr))
				continue ;
			if (ft_manage_history(&g_all))
			{
				ft_strjoin_and_free_2((g_all.history)->content, &(g_all.str_hist));
				continue ;
			}
			if (!ft_strncmp(g_all.wr, "\x7f", 10)) //backspace
			{
				if (g_all.str[0] != '\0')
					ft_delete_one_char(&(g_all.str));
				else if (g_all.str_hist[0] != '\0')
					ft_delete_one_char(&(g_all.str_hist));
				continue ;
			}
			if (g_all.wr[0] != '\n')
				ft_add_char_to_correct_str(&g_all);
			if (g_all.str[0] == '\004')
				ft_exit(NULL);
			ft_putstr_fd(g_all.wr, 1);
			if ((ft_strlen(g_all.str) + 10) % tgetnum("co") == 0 ||
				(ft_strlen(g_all.str_hist) + 10) % tgetnum("co") == 0)
				tputs(cursor_down, 1, ft_putchar);
		}
		ft_manage_str();
	}
	return (0);
}


