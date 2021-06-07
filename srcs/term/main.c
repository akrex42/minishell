#include "minishell.h"

void	ft_reset_input_mode(void)
{
	tcsetattr(0, TCSANOW, &(g_all.g_saved_attributes));
}

void	ft_cycle_head(void)
{
	ft_malloc_one_char_str(&(g_all.str));
	ft_malloc_one_char_str(&(g_all.str_hist));
	g_all.curr_str = 1;
	ft_set_prompt();
	tputs(save_cursor, 1, ft_putchar);
	g_all.wr[0] = '\0';
}

// действия с введенной строкой после цикла
void	ft_manage_str(void)
{
	char	*tmp;

	if (g_all.curr_str == 2)
		tmp = g_all.str_hist;
	else if (g_all.curr_str == 1)
		tmp = g_all.str;
	ft_history_newline(&(g_all.history), tmp);
	ft_parser_for_errors(tmp);
	if (!ft_syntax_error())
	{
		ft_free_tokens();
		ft_free_comands();
		if (g_all.curr_str == 2)
			ft_parser(g_all.str_hist);
		else if (g_all.curr_str == 1)
			ft_parser(g_all.str);
		// ft_display_tokens(); // ! для отладки
		ft_handler();
	}
	ft_free_comands();
	ft_free_tokens();
	free(g_all.str);
	free(g_all.str_hist);
}

// инициализация всех переменных
void	ft_init_term_all(char **env)
{
	g_all.history = NULL;
	g_all.tokens = NULL;
	g_all.commands = NULL;
	g_all.exit_status = 0;
	g_all.env = ft_allocate_env(env);
	g_all.path = NULL;
	ft_rewrite_path(); // добавляет двумерный массив возможных директорий для запуска программ
	ft_init_history(&(g_all.history));
	tgetent(0,  "xterm-256color"); // ! для дебаггера
	// tgetent(0,  getenv("TERM")); // ! основной
	signal(SIGINT, ft_sighnd); //ctrl + с
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
			if (g_all.wr[0] == '\004')
			{
				if ((g_all.str[0] == '\0' && g_all.curr_str == 1) ||
					(g_all.str_hist[0] == '\0' && g_all.curr_str == 2))
					ft_exit(NULL);
				else
					continue ;
			}
			if (!ft_strncmp(g_all.wr, "\x7f", 10)) //backspace
			{
				if ((g_all.str_hist[0] != '\0') && (g_all.curr_str == 2))
					ft_delete_one_char(&(g_all.str_hist));
				else if ((g_all.str[0] != '\0') && (g_all.curr_str == 1))
					ft_delete_one_char(&(g_all.str));
				continue ;
			}
			if (ft_manage_history(&g_all))
			{
				ft_strjoin_and_free_2((g_all.history)->content, &(g_all.str_hist));
				continue ;
			}
			if (ft_check_unused_char(g_all.wr))
				continue ;
			if (g_all.wr[0] != '\n')
				ft_add_char_to_correct_str(&g_all);
			ft_putstr_fd(g_all.wr, 1);
			if ((((ft_strlen(g_all.str) + 10) % tgetnum("co") == 0) && (g_all.curr_str == 1)) ||
				(((ft_strlen(g_all.str_hist) + 10) % tgetnum("co") == 0) && (g_all.curr_str == 2)))
				tputs(cursor_down, 1, ft_putchar);
		}
		ft_manage_str();
	}
	return (0);
}
