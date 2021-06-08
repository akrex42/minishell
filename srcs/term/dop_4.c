#include "minishell.h"

void	ft_delete_one_char_2(void)
{
	int	i;

	tputs(cursor_up, 1, ft_putchar);
	i = tgetnum("co");
	while (i)
	{
		tputs(cursor_right, 1, ft_putchar);
		i--;
	}
	tputs(cursor_left, 1, ft_putchar);
	tputs(delete_character, 1, ft_putchar);
	tputs(cursor_right, 1, ft_putchar);
}

void	ft_delete_one_char(char **str)
{
	int		len;
	char	*tmp;

	len = ft_strlen(*str);
	if ((len + 10) % tgetnum("co") == 0)
		ft_delete_one_char_2();
	else
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
	tmp = malloc(sizeof(char) * (len));
	ft_strlcpy(tmp, *str, len);
	free(*str);
	*str = tmp;
}

int	ft_cycle_body(void)
{
	if (!ft_strncmp(g_all.wr, "\x7f", 10))
	{
		if ((g_all.str_hist[0] != '\0') && (g_all.curr_str == 2))
			ft_delete_one_char(&(g_all.str_hist));
		else if ((g_all.str[0] != '\0') && (g_all.curr_str == 1))
			ft_delete_one_char(&(g_all.str));
		return (1);
	}
	if (ft_manage_history(&g_all))
	{
		ft_strjoin_and_free_2((g_all.history)->content, &(g_all.str_hist));
		return (1);
	}
	if (ft_check_unused_char(g_all.wr))
		return (1);
	if (g_all.wr[0] != '\n')
		ft_add_char_to_correct_str(&g_all);
	ft_putstr_fd(g_all.wr, 1);
	if ((((ft_strlen(g_all.str) + 10) % tgetnum("co") == 0)
			&& (g_all.curr_str == 1)) || (((ft_strlen(g_all.str_hist) + 10)
				% tgetnum("co") == 0) && (g_all.curr_str == 2)))
		tputs(cursor_down, 1, ft_putchar);
	return (0);
}
