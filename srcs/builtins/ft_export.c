#include "minishell.h"

int		flag_zero(char **str, int flag_equal, int i)
{
	char **env1;
	char *this_env;

	if (flag_equal == 0)
	{
		// all the keys without value that do not repeat OR first time appeared repeating ones
		env1 = g_all.env;
		g_all.env = ft_allocate_env_builtins(g_all.env, 1, str[i], this_env);
		int k = 0;
		while (env1[k] != NULL)
		{
			free(env1[k]);
			k++;
		}
		free(env1);
	}		
	flag_equal = 0;
	return(flag_equal);
}

int		ft_key_value2(char **str, int i, int j, int flag_equal)
{
	char *key;
	char *this_env;

	key = ft_substr(g_all.env[j], 0, ft_strlen(g_all.env[j]) - ft_strlen(ft_strchr(g_all.env[j], '=')));
	char *key1 = ft_substr(str[i], 0, ft_strlen(str[i]) - ft_strlen(ft_strchr(str[i], '=')));
	if (ft_strlen(key) == ft_strlen(key1)
			&& ft_strncmp(key, key1, ft_strlen(key1)) == 0)
	{
		// if key-=value already exists in the list and we change it, including final variant
		this_env = g_all.env[j];
		g_all.env[j] = ft_strdup(str[i]);
		free(this_env);
		flag_equal = 1;
		free(key);
		free(key1);
	}
	else
	{
		free(key);
		free(key1);
	}
	return(flag_equal);
}

int		ft_key_value1(char **str, int i, int j, int flag_equal)
{
	char *key;
	char *this_env;

	key = ft_substr(str[i], 0, ft_strlen(str[i]) - ft_strlen(ft_strchr(str[i], '=')));
	if (ft_strlen(g_all.env[j]) == ft_strlen(key) 
		&& !(ft_strncmp(g_all.env[j], key, ft_strlen(key))))
	{
		// if we assign value to an existing key for the first time
		this_env = g_all.env[j];
		g_all.env[j] = ft_strdup(str[i]);
		free(this_env);
		flag_equal = 1;
		free(key);
	}
	else
		free(key);
	return(flag_equal);
}

int		internal_circle(int flag_equal, char **str, int i)
{
	int j;
	char *equal;

	j = 0;
	while (g_all.env[j] != NULL)
	{
		equal = ft_strchr(g_all.env[j], '=');
		if (equal == NULL)
		{					
			flag_equal = ft_key_value1(str, i, j, flag_equal);
			if (flag_equal == 1)
				break ;
		}
		if (equal != NULL)
		{
			flag_equal = ft_key_value2(str, i, j, flag_equal);
			if (flag_equal == 1)
				break ;
		}
		j++;
	}
	flag_equal = flag_zero(str, flag_equal, i);
	return(flag_equal);
}

int		ft_check_equal2(int i, int flag_equal, char *key, char **str)
{
	if (ft_strlen(key) == ft_strlen(str[i]) && !(ft_strncmp(key,
		str[i], ft_strlen(str[i]))))
	{
		// if keys without values repeat and they have value assigned in the list
		flag_equal = 1;
		free(key);
		return(flag_equal);
	}
	else
		free(key);
	return(flag_equal);
}

int		ft_check_equal(int i, int flag_equal, int j, char **str)
{
	if (ft_strlen(g_all.env[j]) 
		== ft_strlen(str[i]) && !(ft_strncmp(g_all.env[j],
		str[i], ft_strlen(str[i]))))
	{
		// if keys without values repeat and they do not have value in the list
		flag_equal = 1;
	}
	return(flag_equal);
}

int		ft_equal_null(char **str, int flag_equal, char *equal, int i)
{
	int j;
	char *key;

	j = 0;
	while (g_all.env[j] != NULL)
	{
		equal = ft_strchr(g_all.env[j], '=');
		if (equal == NULL)
			flag_equal = ft_check_equal(i, flag_equal, j, str);
		if (equal != NULL)
		{
			key = ft_substr(g_all.env[j], 0, ft_strlen(g_all.env[j]) - ft_strlen(ft_strchr(g_all.env[j], '=')));
			flag_equal = ft_check_equal2(i, flag_equal, key, str);		
		}
		j++;
	}
	return(flag_equal);
}

void	ft_print_env(void)
{
	char **beg_env = g_all.env;
	while (*g_all.env != NULL)
	{
		char *this_env = *g_all.env;
		char *equal = ft_strchr(this_env, '=');
		if (equal == NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(this_env, 1);
			ft_putchar_fd('\n', 1);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(equal)), 1);
			ft_putchar_fd(equal[0], 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(ft_substr(equal, 1, ft_strlen(equal) - 1), 1);
			ft_putchar_fd('"', 1);
			ft_putchar_fd('\n', 1);
		}
		g_all.env++;
	}
	g_all.env = beg_env;
}

int		ft_export(char **str)
{
	char *equal;
	int i;
	int j;
	int flag_equal;

	flag_equal = 0;
	// g_all.env = ft_allocate_env(envp); // we need to initialize it somewhere else
	i = 1; // Program name may be omitted with the use of exec* family
	if (str[i] == NULL)
		ft_print_env();
	while (str[i] != NULL)
	{
		if (print_err_export_unset(str[i]))
			return(1);
		equal = ft_strchr(str[i], '=');
		if (equal == NULL) // key without value args cases
		{
			flag_equal = ft_equal_null(str, flag_equal, equal, i);				
			flag_equal = flag_zero(str, flag_equal, i);
		}
		else if (equal != NULL) // key with value args cases
			flag_equal = internal_circle(flag_equal, str, i);
		i++;
	}
	return(0);
}

// int main (int argc, char **argv, char **envp)
// {
// 	ft_export(argv);
// 	return(0);
// }