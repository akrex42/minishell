#include "main_term.h"

void	ft_add_char_to_rigth_str(t_term_all *all)
{
	if (all->history->content == NULL)
		ft_strjoin_and_free_1(&(all->str), all->wr);
	else
		ft_strjoin_and_free_1(&(all->str_hist), all->wr);
}

// инициализация параметров терминала
void	ft_set_input_mode(t_term_all *all)
{
	struct termios	tattr;

	if (!isatty(0))
	{
		printf("Error term initialization\n");
		exit(1);
	}
	tcgetattr(0, &(all->g_saved_attributes));
	ft_memcpy(&tattr, &(all->g_saved_attributes), sizeof(tattr));
	tattr.c_lflag &= ~(ICANON);
	tattr.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSAFLUSH, &tattr);
}