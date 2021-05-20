#include "minishell.h"

int	ft_cycle(int len, char **env, char *this_env, char **ret)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (g_all.flag_allocate == 1 && !(ft_strncmp(env[i],
					this_env, ft_strlen(this_env))))
		{
			while (i < len - 1)
			{
				ret[i] = ft_strdup(env[i + 1]); // free 
				i++;
			}
		}
		else
		{
			ret[i] = ft_strdup(env[i]); // free
			i++;
		}
	}
	return (i);
}

// перевыделяет память для переменных окружения // we need to free all of this
char	**ft_allocate_env_builtins(char **env, int args, char *str,
char *this_env)
{
	char	**ret;
	int		len;
	int		i;

	len = 0;
	while (env[len] != NULL)
		len++;
	if (g_all.flag_allocate == 1)
		ret = malloc(sizeof(char *) * (len));
	else
		ret = malloc(sizeof(char *) * (len + 2));
	i = ft_cycle(len, env, this_env, ret);
	if (!g_all.flag_allocate)
	{
		ret[i] = ft_strdup(env[i]); // free
		i++;
		ret[i] = ft_strdup(str);
		i++;
		ret[i] = NULL;
	}
	else
		ret[i] = NULL;
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
