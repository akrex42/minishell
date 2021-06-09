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
# include <errno.h>
# include <dirent.h>
# include "libft.h"

typedef struct s_execute
{
	int		ret;
	char	*str;
	char	*tmp;
	int		i;
}	t_execute;

typedef struct s_history_list
{
	char					*content;
	struct s_history_list	*next;
	struct s_history_list	*prev;
}	t_history_list;

// special_value для определения того, имеет ли элемент специальное значение
// или он был экранирован
typedef struct s_tokens_list
{
	int						special_value; // 1 - значимый элемент, 0 - просто символ
	char					*content;
	struct s_tokens_list	*next;
	struct s_tokens_list	*prev;
}	t_tokens_list;

// для передачи исполнителю команд
typedef struct s_comands_list
{
	char					*prog;
	char					**args;
	char					special[3];
	int						used;
	struct s_comands_list	*next;
	struct s_comands_list	*prev;
}	t_comands_list;

typedef struct s_parse_flags
{
	int		esc;			// '\\'
	int		dollar;			// $
	int		double_quote;	// '
	int		special_value;	// был ли элемень в строке экранирован
	int		quotes;
}	t_parse_flags;

typedef struct s_term_all
{
	struct termios	g_saved_attributes;
	int				flag_allocate;
	int				flag_echo;
	int				fd_in;
	int				fd_out;
	int				**pipes;
	int				**pid;
	int				exit_status;
	char			wr[10];
	char			*str;
	char			*str_hist;
	int				curr_str; // 1 - str 2 - str_hist
	char			**env;
	char			**path; //разделенные директории по которым нужно искать прогу 
	t_history_list	*history;
	t_tokens_list	*tokens;
	t_comands_list	*commands;
	t_parse_flags	flags;
	t_execute		exec;
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
void	ft_set_prompt(void);
void	ft_sighnd(int signo);
void	ft_reset_input_mode(void);
void	ft_set_input_mode(t_term_all *all);
void	ft_add_char_to_correct_str(t_term_all *all);
void	ft_parser(const char *str);
void	ft_parser_for_errors(const char *str);
void	ft_common_split_part(char **command, const char *str);
void	ft_command_add_to_list(char **command);
void	ft_init_parse_flags(void);
int		ft_check_unused_char(const char *wr);
char	**ft_allocate_env(char **env);
void	ft_tokens_step_back(void);
void	ft_tokens_step_front(void);
void	ft_tokens_newline(char *content);
void	ft_tokens_to_beginning(void);
void	ft_free_tokens(void);
char	*ft_find_env_var(char *str);
void	ft_handler(void);
void	ft_new_prog_node(void);
void	ft_tokens_go_next_spec(void);
int		ft_progs_count_args(void);
int		ft_compare_tokens_cont_to_spec(void);
void	ft_comands_list_add_args_and_prog(void);
void	ft_commands_go_beginning(void);
void	ft_free_comands(void);
int		ft_is_relative(void);
void	ft_error_handler(int ret);
void	ft_sighnd_exec(int signo);
void	ft_cycle_head(void);
int		ft_syntax_error(void);
int		ft_compare_prog_to_redirect(void);
void	ft_join_env_to_str(char **str, int i,
			char *str_to_find, char *str_to_join);
void	ft_rewrite_path(void);
int		ft_comp_to_spec(t_tokens_list *token);
void	ft_delete_one_char(char **str);
int		ft_cycle_body(void);
int		ft_parser_3(char **command, const char *str, int *i);

//BUILTINS
int 	ft_cd(char **str);
char	**ft_allocate_env_builtins(char **env, int args, char *str,
char *this_env);
int		ft_check_equal2(int i, int flag_equal, char *key, char **str);
int		ft_echo(char **str);
int 	ft_env(char **str);
unsigned char 	ft_exit(char **str);
int		ft_export(char **str);
int		ft_pwd(char **str);
int		ft_unset(char **str);
int		print_err_export(char *str);
int		flag_zero(char **str, int flag_equal, int i);
int		internal_circle(int flag_equal, char **str, int i);
int		ft_error(char *dir, char *this_env, char *equal, char **str);
int		ft_home(void);
void	ft_print_equal(char **env, int i, char *equal);
int		ft_insertion_sort(char **env, char *min, int change, int i);
void	ft_print_env_sorted(char *equal, char **env);
void	ft_swap_and_free(char *min, int change, char **env, int i);
int		ft_cycle_export(char **str, int i, char *equal, int flag_equal);
int		ft_cycle_unset(char **str, int i, char *equal);
int		ft_print_error_cd(char **str);
void	ft_chdir_normal(char *dir, char *dir1, char *this_env, char *equal);
int		print_err_unset(char *str);
int		inner_circle3(int j, int i, char **str, char *equal);
int		ft_equal_null(char **str, int flag_equal, char *equal, int i);
int 	print_1(char str);
int 	print(char *str);
int		check_cond(void);
int		ft_print_err_exit_return(char **str);
void	ft_print_err_exit(char **str);


//tmp
void	ft_display_tokens(void);
void	ft_display_comands(void);

#endif
