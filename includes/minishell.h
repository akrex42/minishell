#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <termios.h>
# include <term.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_history_list
{
	char					*content;
	struct s_history_list	*next;
	struct s_history_list	*prev;
}	t_history_list;

typedef struct s_tokens_list
{
	char					*content;
	struct s_tokens_list	*next;
	struct s_tokens_list	*prev;
}	t_tokens_list;

typedef struct s_parse_flags
{
	int		esc;			// '\\'
	int		dollar;			// $
	int		double_quote;	// '
}	t_parse_flags;

typedef struct s_term_all
{
	//TODO: добавить код предыдущей ошибки (отлавливать во время вызывов программ)
	struct termios	g_saved_attributes;
	char			wr[10];
	char			*str;
	char			*str_hist;
	char			**env;
	t_history_list	*history;
	t_tokens_list	*tokens;
	t_parse_flags	flags;
}	t_term_all;

t_term_all		g_all;

void	ft_init_history(t_history_list **history);
void	ft_history_newline(t_history_list **list,
			char *content);
int		ft_manage_history(t_term_all *all);
void	ft_malloc_error(void);
void	ft_file_open_error(void);
void	ft_history_step_back(t_history_list **history);
void	ft_history_step_front(t_history_list **history);
int		ft_putchar(int c);
void	ft_strjoin_and_free_1(char **str1, const char *str2);
void	ft_strjoin_and_free_2(const char *str1, char **str2);
void	ft_strjoin_char_and_free(char **str1, char ch);
void	ft_malloc_one_char_str(char **str);
void	ft_malloc_one_char_str(char **str);
void	ft_exit(void);
void	ft_set_prompt(void);
void	ft_sighnd(int signo);
void	ft_reset_input_mode(void);
void	ft_set_input_mode(t_term_all *all);
void	ft_add_char_to_correct_str(t_term_all *all);
void	ft_parser(const char *str);
int		ft_check_unused_char(const char *wr);
char	**ft_allocate_env(char **env);
void	ft_tokens_step_back(void);
void	ft_tokens_step_front(void);
void	ft_tokens_newline(char *content);
void	ft_tokens_to_beginning(void);
void	ft_free_tokens(void);
char	*ft_find_env_var(char *str);

void	ft_display_tokens(void);

#endif
