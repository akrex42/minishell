#include "minishell.h"

char	**ft_allocate_env(char **env)
{
	char	**ret;
	int		len;
	int		i;

	len = 0;
	while (env[len] != NULL)
		len++;
	ret = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	ft_check_unused_char(const char *wr)
{
	if ((wr[1] == '\0'
			&& ((wr[0] >= 32 && wr[0] <= 126) || wr[0] == '\n')))
		return (0);
	return (1);
}

void	ft_add_char_to_correct_str(t_term_all *all)
{
	if (all->curr_str == 1)
		ft_strjoin_and_free_1(&(all->str), all->wr);
	else
		ft_strjoin_and_free_1(&(all->str_hist), all->wr);
}

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
	tcsetattr(0, TCSANOW, &tattr);
}
