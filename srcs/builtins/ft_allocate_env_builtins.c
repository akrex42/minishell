#include "../includes/minishell.h"

int	ft_cycle(char **env, int len, char *this_env, char **ret)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if ((g_all.flag_allocate == 1) && (!(ft_strncmp(env[i],
						this_env, ft_strlen(this_env)))))
		{
			while (i < len - 1)
			{
				ret[i] = ft_strdup(env[i + 1]);
				i++;
			}
			break ;
		}
		else
		{	
			ret[i] = ft_strdup(env[i]);
			i++;
		}
	}
	return (i);
}

char	**ft_allocate_env_builtins(char **env, char *str,
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
	i = ft_cycle(env, len, this_env, ret);
	if (g_all.flag_allocate == 0)
	{
		ret[i] = ft_strdup(str);
		i++;
		ret[i] = NULL;
	}
	else if (g_all.flag_allocate == 1)
		ret[i] = NULL;
	return (ret);
}
