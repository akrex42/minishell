#ifndef GENERAL_H
# define GENERAL_H

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
}	t_hystory_list;

void	ft_init_history(t_hystory_list **history);
void	ft_history_newline(t_hystory_list **list,
					char *content);
int		ft_manage_history(const char *wr, char **str,
		t_hystory_list **history);
void	ft_malloc_error(void);
void	ft_file_open_error(void);
void	ft_history_step_back(t_hystory_list **history);
void	ft_history_step_front(t_hystory_list **history);
int		ft_putchar(int c);
void	ft_strjoin_and_free_1(char **str1, const char *str2);
void	ft_strjoin_and_free_2(const char *str1, char **str2);
void	ft_malloc_one_char_str(char **str);
void	ft_malloc_one_char_str(char **str);
void	ft_exit();
void	ft_reset_input_mode(void);
void	ft_set_prompt(void);

#endif
