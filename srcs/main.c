#include "main_term.h"

struct termios g_saved_attributes;

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
	ft_init_history(&history);
	ft_strlcpy(term_name, "xterm-256color", 15);
	tgetent(0, term_name); // инициализируем наш терминал по имени
	str = NULL;
	while (1) //основной цикл
	{
		ft_malloc_one_char_str(&str);
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
			if (!ft_strncmp(wr, "\e[D", 100) || !ft_strncmp(wr, "\e[C", 100))
				continue ;
			if (ft_manage_history(wr, &str, &history))
				continue ;
			if (wr[0] != '\n')
				ft_strjoin_and_free_1(&str, wr);
			ft_putstr_fd(wr, 1); // вывод этих символов
		}
		ft_strjoin_and_free_2(history->content, &str); //добавляет существующую истори к строке
		if (strcmp(str, "\0"))
			ft_history_newline(&history, str); //добавление строки в историю
	}
	return (0);
}
