#include "minishell.h"

void    ft_error_handler(int errno_exec)
{
    void    *dir;
    dir = NULL;
    // ft_putnbr_fd(errno_exec, 1);
    if (errno_exec != 8 && errno_exec != 0 && errno_exec != 1)
    {
		if (!ft_strncmp(g_all.commands->prog, ".", 2))
		{
			ft_putstr_fd("my_bash: ", 2);
        	ft_putstr_fd(g_all.commands->prog, 2);
        	ft_putstr_fd(": ", 2);
			ft_putstr_fd("filename argument required", 2);
			ft_putchar_fd('\n', 2);
			ft_putstr_fd(".: usage: . filename [arguments]", 2);
			g_all.exec.ret = 2;

		}
		else
		{
			ft_putstr_fd("my_bash: ", 2);
        	ft_putstr_fd(g_all.commands->prog, 2);
        	ft_putstr_fd(": ", 2);
        	if (!ft_is_relative() && errno_exec == 2) // cnf
        	{
            	ft_putstr_fd("command not found", 2);
           	 	g_all.exec.ret = 127;
      	  	}
        	else if (errno_exec == 2)
        	{
            	dir = opendir(g_all.commands->prog);
            	// ft_putnbr_fd(errno, 1);
            	if (errno == 20)
            	{
                	ft_putstr_fd(strerror(20), 2); // is not a directory // .
                	g_all.exec.ret = 126;
            	}
            	else if (errno == 2)
            	{
                	ft_putstr_fd(strerror(errno_exec), 2); // no such file or directory
                	g_all.exec.ret = 127;
            	}
            	if (dir != NULL)
                	closedir(dir);
        	}
        	else
        	{
           	 	dir = opendir(g_all.commands->prog);
           	 	if (dir != NULL || errno == 13)
            	{
               		ft_putstr_fd(strerror(21), 2); // is a directory
                	g_all.exec.ret = 126;
           		}
            	else if (errno_exec == 13)
            	{
                	ft_putstr_fd(strerror(13), 2); // permission denied
                	g_all.exec.ret = 126;
            	}
            	else if (errno == 20)
            	{
                	ft_putstr_fd(strerror(errno), 2); // is not a directory
                	g_all.exec.ret = 126;
            	}
        	}
		}
        ft_putstr_fd("\n", 2);
    }
    if (dir != NULL)
        closedir(dir);
    if (g_all.exit_status == 500)
        g_all.exec.ret = 130;
    if (g_all.exit_status == 501)
        g_all.exec.ret = 131;
    g_all.exit_status = g_all.exec.ret;
    // ft_putnbr_fd(g_all.exit_status, 1);
}

int	ft_comp_to_spec(t_tokens_list *token) // 1 - ошибка
{
	if (token == NULL)
		return (1);
	return ((!ft_strncmp(token->content, "|", 2) ||
			!ft_strncmp(token->content, ">", 2) ||
			!ft_strncmp(token->content, ">>", 3) ||
			!ft_strncmp(token->content, "<", 2) ||
			!ft_strncmp(token->content, ";", 2)) &&
			token->special_value);
}

int	ft_syntax_error(void)
{
	ft_tokens_to_beginning();
	while (g_all.tokens)
	{
		if (ft_comp_to_spec(g_all.tokens))
		{
			if ((g_all.tokens->content[0] == ';' || g_all.tokens->content[0] == '|') &&
				ft_comp_to_spec(g_all.tokens->prev))
			{
				ft_putstr_fd("my_bash: syntax error near unexpected token `", 2);
				ft_putstr_fd(g_all.tokens->content, 2);
				ft_putstr_fd("'\n", 2);
				g_all.exit_status = 258;
				return 1;
			}
			else if ((g_all.tokens->content[0] == '<' ||
				g_all.tokens->content[0] == '>') && ft_comp_to_spec(g_all.tokens->next))
			{
				ft_putstr_fd("my_bash: syntax error near unexpected token `", 2);
				if (g_all.tokens->next != NULL)
					ft_putstr_fd(g_all.tokens->next->content, 2);
				else
					ft_putstr_fd("newline", 2);
				ft_putstr_fd("'\n", 2);
				g_all.exit_status = 258;
				return 1;
			}
		}
		if (g_all.tokens->next == NULL)
			break ;
		else
			g_all.tokens = g_all.tokens->next;
	}
	ft_tokens_to_beginning();
	return 0;
}
