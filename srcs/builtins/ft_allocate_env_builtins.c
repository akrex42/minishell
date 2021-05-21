#include "minishell.h"

int	ft_cycle(int len, char *this_env, char **ret)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (g_all.flag_allocate == 1 && !(ft_strncmp(g_all.env[i],
					this_env, ft_strlen(this_env))))
		{
			while (i < len - 1)
			{
				// free(env[i]);
				if (g_all.env[len] == NULL)
					return (i);
				// ft_putstr_fd(g_all.env[i + 1], 1);
				else
					ret[i] = ft_strdup(g_all.env[i + 1]); // free
				// ft_putstr_fd(ret[i], 1);
				i++;
			}
		}
		else
		{	
			ret[i] = ft_strdup(g_all.env[i]); // free
			i++;
		}
	}
	return (i);
}

// перевыделяет память для переменных окружения // we need to free all of this
char	**ft_allocate_env_builtins(int args, char *str,
char *this_env)
{
	char	**ret;
	int		len;
	int		i;

	len = 0;
	while (g_all.env[len] != NULL)
		len++;
	if (g_all.flag_allocate == 1)
		ret = malloc(sizeof(char *) * (len));
	else
		ret = malloc(sizeof(char *) * (len + 2));
	i = ft_cycle(len, this_env, ret);
	if (!g_all.flag_allocate)
	{
		ret[i] = ft_strdup(g_all.env[i]); // free
		i++;
		ret[i] = ft_strdup(str);
		i++;
		ret[i] = NULL;
	}
	else
		ret[i] = NULL;
	// int k = 0;
	// while (env[k] != NULL)
	// {
	// 	free(env[k]);
	// 	k++;
	// }
	// free(env);
	return (ret);
}

/* void	ft_print_env(void)
{
	char **beg_env = g_all.env;
	while (*g_all.env != NULL)
	{
		char *this_en = *g_all.env;
		char *equal = ft_strchr(this_en, '=');
		if (equal == NULL)
		{
			printf("%s%s%c", "declare -x ", this_en, '\n');
		}
		else
		{
			printf("%s", "declare -x ");
			printf("%s", ft_substr(this_en, 0, ft_strlen(this_en) - ft_strlen(equal)));
			printf("%c", equal[0]);
			printf("%c", '"');
			printf("%s", ft_substr(equal, 1, ft_strlen(equal) - 1));
			printf("%c%c", '"', '\n');
		}
		g_all.env++;
	}
	g_all.env = beg_env;
}

int		main(int argc, char **argv, char **env)
{
	char *str = "HOME";
	char *this_env = "HOME";

	g_all.flag_allocate = 1;
	g_all.env = ft_allocate_env_builtins(env, 1, str, this_env);
	ft_print_env();
} */
