#include "minishell.h"

void 	ft_export(int argc, char **str, char **envp)
{
	char *equal;
	char *this_env;

	g_all.flag_allocate = 0;
	if (!(g_all.env = ft_allocate_env(g_all.env, argc, str, this_env)))
	{
		printf("%s", "error"); // error handling errors: g_all.env[0] != alpha, 
		// g_all.env[i] != isalphanum except for '=' and mb other bash reserved symbols
		exit (-1);
	}
	while (*g_all.env != NULL)
	{
		this_env = *g_all.env;
		equal = ft_strchr(this_env, '=');
		if (equal == NULL)
		{
			printf("%s%s", "declare -x ", this_env);
		}
		else 
		{
			printf("%s", "declare -x ");
			printf("%s", ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(equal)));
			printf("%c", equal[0]);
			printf("%c", '"');
			printf("%s", ft_substr(equal, 1, ft_strlen(equal) - 1));
			printf("%c%c", '"', '\n');
		}
		g_all.env++;
	}
}

int main (int argc, char **argv, char **envp)
{
	ft_export(argc, argv, envp);
	return (0);
}