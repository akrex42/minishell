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

void	ft_manage_str(void)
{
	char	*tmp;

	tmp = NULL;
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
		ft_handler();
	}
	ft_free_comands();
	ft_free_tokens();
	free(g_all.str);
	free(g_all.str_hist);
}

void	ft_init_term_all(char **env)
{
	g_all.history = NULL;
	g_all.tokens = NULL;
	g_all.commands = NULL;
	g_all.exit_status = 0;
	g_all.env = ft_allocate_env(env);
	g_all.path = NULL;
	ft_rewrite_path();
	ft_init_history(&(g_all.history));
	// tgetent(0, getenv("TERM"));
	tgetent(0, "xterm-256color");
	signal(SIGINT, ft_sighnd);
	signal(SIGQUIT, ft_sighnd);
}

int	main(int argc, char *argv[], char *env[])
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
				if ((g_all.str[0] == '\0' && g_all.curr_str == 1)
					|| (g_all.str_hist[0] == '\0' && g_all.curr_str == 2))
					ft_exit(NULL);
				else
					continue ;
			}
			if (ft_cycle_body())
				continue ;
		}
		ft_manage_str();
	}
	return (0);
}
