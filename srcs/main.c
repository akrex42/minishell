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
	tattr.c_lflag &= ~(ICANON | ECHO);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
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
	char			*str;
	t_hystory_list	*history;

	ft_set_input_mode();
	signal(SIGINT, ft_sighnd);
	signal(SIGTERM, ft_sighnd);
	str = NULL;
	history = NULL;
	while (1) //основной цикл
	{
		str = malloc(sizeof(char));
		if (!str)
			ft_malloc_error();
		str[0] = '\0';
		ft_set_prompt();
		wr[0] = '\0';
		// тут происходит ввод одной строки (до \n)
		while (wr[0] != '\n')
		{
			//TODO: объеденить строки между собой если одновременно было введено более 100 символов
			ft_bzero(wr, 100);
			read(0, wr, 100);
			if (wr[0] == '\004')
				ft_exit();
			// переход по истории вверх и вниз
			//TODO: организовать как отдельные функции
			//TODO: стирать предыдущую строку при изменении истории
			if (!ft_strncmp(wr, "\e[A", 100))
			{
				//prev
				if (history != NULL)
					ft_putstr_fd(history->content, 1);
				ft_history_step_back(&history);
				continue;
			}
			if (!ft_strncmp(wr, "\e[B", 100))
			{ 
				//next
				if (ft_history_step_front(&history))
					ft_putstr_fd(history->content, 1);
				else
					ft_putstr_fd(str, 1);
				continue;
			}
			// if (!ft_strncmp(wr, "\x7f", 100))
			// {
			// 	tputs("\b", 1, ft_putchar);
			// 	continue;
			// }
			if (wr[0] != '\n')
				str = ft_strjoin(str, wr); // присоединение введенных символов к строке
			ft_putstr_fd(wr, 1); // вывод этих символов
		}
		if (strcmp(str, "\n"))
			history = ft_history_newline(&history, str); //добавление строки в историю
	}
	return (0);
}


//! может пригодиться потом
// char	*ft_add_char_to_str(char *str, char c)
// {
// 	int		len;
// 	char	*tmp;

// 	if (str == NULL)
// 	{
// 		str = malloc(sizeof(char) * 2);
// 		if (!str)
// 			ft_malloc_error();
// 		str[0] = c;
// 		str[1] = '\0';
// 		return (str);
// 	}
// 	len = ft_strlen(str);
// 	tmp = malloc(sizeof(char) * (len + 2));
// 	if (!tmp)
// 		ft_malloc_error();
// 	ft_strlcpy(tmp, str, len + 2);
// 	tmp[len] = c;
// 	tmp[len + 1] = '\0';
// 	free(str);
// 	return (tmp);
// }
