#include "minishell.h"

int		print_err_export_unset(char *str)
{
	int i;

	i = 1;
	if (!ft_isalpha(str[0]))
	{
		ft_putstr_fd("bash: export: `", 1);
		ft_putchar_fd(str[0], 1);
		ft_putstr_fd("': not a valid identifier", 1);
		ft_putchar_fd('\n', 1);
		return(1); // errno?
	}
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '=')
		{
			ft_putstr_fd("bash: export: `", 1);
			ft_putstr_fd(str, 1);
			ft_putstr_fd("': not a valid identifier", 1);
			ft_putchar_fd('\n', 1);
			return(1);
		}
		i++;
	}
	return(0);
}

// void	ft_print_env(void)
// {
// 	char **beg_env = g_all.env;
// 	while (*g_all.env != NULL)
// 	{
// 		char *this_env = *g_all.env;
// 		char *equal = ft_strchr(this_env, '=');
// 		if (equal == NULL)
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd(this_env, 1);
// 			ft_putchar_fd('\n', 1);
// 		}
// 		else
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(equal)), 1);
// 			ft_putchar_fd(equal[0], 1);
// 			ft_putchar_fd('"', 1);
// 			ft_putstr_fd(ft_substr(equal, 1, ft_strlen(equal) - 1), 1);
// 			ft_putchar_fd('"', 1);
// 			ft_putchar_fd('\n', 1);
// 		}
// 		g_all.env++;
// 	}
// 	g_all.env = beg_env;
// }

int 	ft_unset(char **str)
{
	char *key;
	char **beg_env;
	int i;
	char *this_en;

	i = 1;
	// g_all.env = ft_allocate_env(envp);
	beg_env = g_all.env;
	while (*g_all.env != 0 && str[i] != NULL)
	{
		this_en = *g_all.env;
		if (print_err_export_unset(str[i]) == 1)
			return(1);
		key = ft_substr(this_en, 0, ft_strlen(this_en) - ft_strlen(ft_strchr(this_en, '=')));
		if (!(ft_strncmp(key, str[i], ft_strlen(str[i]))))
		{
			g_all.flag_allocate = 1;
			g_all.env = ft_allocate_env_builtins(beg_env, 1, str[i], this_en);
			beg_env = g_all.env;
			i++;
		}
		else
			g_all.env++;
		free(key);
	}
	// ft_print_env();
	g_all.flag_allocate = 0;
	return(0);
}

// int main (int argc, char **argv, char **envp)
// {
// 	ft_unset(argv);
// 	return (0);
// }