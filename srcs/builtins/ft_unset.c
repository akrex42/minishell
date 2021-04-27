#include "minishell.h"

void 	ft_unset(char **str, int args, char **envp)
{
    char *end;
	char *key;
	int len;
	int i;
	char *this_env;

	g_all.env = ft_allocate_env(envp, 0, str, this_env); // we need to initialize it somewhere else
	// printf("%s", g_all.env[0]);

	// if (!(ft_isalpha(**str)))
	// {
	// 	printf("%s%s%s", "bash: unset: `", *str, "': not a valid identifier\n"); // error handling func
	// 	return ;
	// }
	i = 1;
	while (*g_all.env != 0 && i < args)
	{
		this_env = *g_all.env;
		// printf("%s\n", this_env);
		end = ft_strchr(this_env, '=');
		// printf("%s\n", end);
		len = ft_strlen(end); //maybe we can add a func for that
		// printf("%d\n", len);
		key = ft_substr(this_env, 0, ft_strlen(this_env) - len); //free
		// printf("%s\n", key);
		if (!(ft_strncmp(key, str[i], ft_strlen(key))))
		{
			// printf("%s\n", str[i]);
			g_all.flag_allocate = 1;
			g_all.env = ft_allocate_env(g_all.env, 1, str, this_env);
			// printf("%s\n", g_all.env[0]);
	// 		break ;
			i++;
		}
		else
			g_all.env++;
	}
	while (*g_all.env != NULL) //this cycle is here just to check
	{
		char *equal;

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
	g_all.flag_allocate = 0;
}

int main (int argc, char **argv, char **envp)
{
	ft_unset(argv, argc, envp);
	return (0);
}
