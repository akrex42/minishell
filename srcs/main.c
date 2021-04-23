#include "main_term.h"

t_term_all		g_all;

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
	ft_strjoin_and_free_2((g_all.history)->content, &(g_all.str_hist));
	if (ft_strncmp(g_all.str_hist, "\0", 10))
	{
		ft_history_newline(&(g_all.history), g_all.str_hist);
		free(g_all.str);
	}
	else if (ft_strncmp(g_all.str, "\0", 10))
	{
		ft_history_newline(&(g_all.history), g_all.str);
		free(g_all.str_hist);
	}
	else
	{
		free(g_all.str);
		free(g_all.str_hist);
	}
	// ! передать строку дальше на обрабоку парсеру
}

// инициализация всех переменных
void	ft_init_term_all(void)
{
	g_all.history = NULL;
	ft_init_history(&(g_all.history));
	ft_strlcpy(g_all.term_name, "xterm-256color", 15);
	tgetent(0, g_all.term_name);
	signal(SIGINT, ft_sighnd);
	signal(SIGTERM, ft_sighnd);
}

//! проверить на лики
int	main(void)
{
	ft_set_input_mode(&g_all);
	ft_init_term_all();
	while (1)
	{
		ft_cycle_head();
		while (g_all.wr[0] != '\n')
		{
			ft_bzero(g_all.wr, 10);
			read(0, g_all.wr, 10);
			if (g_all.wr[0] == '\004')
				ft_exit();
			if (!ft_strncmp(g_all.wr, "\e[D", 100)
				|| !ft_strncmp(g_all.wr, "\e[C", 100))
				continue ;
			if (ft_manage_history(&g_all))
				continue ;
			if (g_all.wr[0] != '\n')
				ft_add_char_to_rigth_str(&g_all);
			ft_putstr_fd(g_all.wr, 1);
		}
		ft_manage_str();
	}
	return (0);
}

// char *arg[] = {"cat", NULL};
// execve("/bin/cat", arg, NULL);
