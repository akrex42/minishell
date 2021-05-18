#include "minishell.h"

int		print_err_export_unset(char *str)
{
	int i;

	i = 1;
	if (!ft_isalpha(str[0]))
	{
		printf("%s%c%s", "bash: export: `", str[0], "': not a valid identifier\n");
		return(1); // errno?
	}
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '=')
		{
			printf("%s%s%s", "bash: export: `", str, "': not a valid identifier\n");
			return(1);
		}
		i++;
	}
	return(0);
}

void	ft_print_env(void)
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

int 	ft_unset(char **str, char **envp)
{
	char *key;
	char **beg_env;
	int i;
	char *this_en;

	i = 1;
	g_all.env = ft_allocate_env(envp); 
	while (*g_all.env != 0 && str[i] != NULL)
	{
		this_en = *g_all.env;
		if (print_err_export_unset(str[i]) == 1)
			return(1);
		key = ft_substr(this_en, 0, ft_strlen(this_en) - ft_strlen(ft_strchr(this_en, '=')));
		if (!(ft_strncmp(key, str[i], ft_strlen(key))))
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
	// sleep(1000);
}

int main (int argc, char **argv, char **envp)
{
	ft_unset(argv, envp);
	return (0);
}