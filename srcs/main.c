/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzombie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 10:52:20 by yzombie           #+#    #+#             */
/*   Updated: 2021/04/06 10:52:21 by yzombie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"
#include "libft.h"

struct termios g_saved_attributes;

void	ft_malloc_error(void)
{
	printf("Malloc error\n");
	exit(2);
}

void	ft_file_open_error(void)
{
	printf("Can`t open history file\n");
	exit(3);
}

void	ft_reset_input_mode(void)
{
	tcsetattr(0, TCSANOW, &g_saved_attributes);
}

// обработчик сигналов
void	ft_sighnd(int signo)
{
	(void)signo;
	printf("Signal function\n");
	ft_reset_input_mode();
	exit(0);
}

void	ft_set_input_mode(void)
{
	struct termios tattr;

	if (!isatty(0))
	{
		printf("Error idn\n");
		exit(1);
	}
	tcgetattr(0, &g_saved_attributes);
	ft_memcpy(&tattr, &g_saved_attributes, sizeof(tattr));
	tattr.c_lflag &= ~(ICANON);
	tattr.c_lflag &= ~(ECHO);
	// tattr.c_cc[VMIN] = 1;
	// tattr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &tattr);
}

// устанавливает начальные символы
void	ft_set_prompt(void)
{
	char str[] = "\033[0;92m(⌐■_■)☞ \033[0m$ ";

	write(1, str, ft_strlen(str));
}

void	ft_exit()
{
	ft_reset_input_mode();
	exit(0);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

//! проверить на лики
int	main(void)
{
	char			wr[100];
	char			term_name[15];
	char			*str;
	t_hystory_list	*history;

	ft_set_input_mode();
	signal(SIGINT, ft_sighnd); // обработка сигналов 
	signal(SIGTERM, ft_sighnd);
	history = NULL;
	ft_init_hostory(&history);
	ft_strlcpy(term_name, "xterm-256color", 15);
	tgetent(0, term_name); // инициализируем наш терминал по имени
	str = NULL;
	while (1) //основной цикл
	{
		str = malloc(sizeof(char));
		if (!str)
			ft_malloc_error();
		str[0] = '\0';
		ft_set_prompt();
		wr[0] = '\0';
		tputs(save_cursor, 1, ft_putchar);
		// тут происходит ввод одной строки (до \n)
		while (wr[0] != '\n')
		{
			//TODO: объеденить строки между собой если одновременно было введено более 100 символов
			ft_bzero(wr, 100);
			read(0, wr, 100);
			if (wr[0] == '\004')
				ft_exit();
			//TODO: организовать как отдельные функции
			//TODO: редактирование строк
			//TODO: добавление истории к str
			if (!ft_strncmp(wr, "\e[A", 100))
			{
				//prev
				tputs(restore_cursor, 1, ft_putchar);
				tputs(clr_eos, 1, ft_putchar);
				ft_history_step_back(&history);
				ft_putstr_fd(history->content, 1);
				continue;
			}
			if (!ft_strncmp(wr, "\e[B", 100))
			{ 
				//next
				tputs(restore_cursor, 1, ft_putchar);
				tputs(clr_eos, 1, ft_putchar);
				ft_history_step_front(&history);
				if (history->content != NULL)
					ft_putstr_fd(history->content, 1);
				else
					ft_putstr_fd(str, 1);
				continue;
			}
			if (wr[0] != '\n')
				str = ft_strjoin(str, wr); // присоединение введенных символов к строке
			ft_putstr_fd(wr, 1); // вывод этих символов
		}
		if (strcmp(str, "\n"))
			ft_history_newline(&history, str); //добавление строки в историю
	}
	return (0);
}
