#include "minishell.h"

void 	ft_unset(char **str, int args, char **envp)
{
	char *end;
	char *key;
	int len;
	int i;
	char *this_env;
	int j;

	g_all.env = ft_allocate_env(envp); // we need to initialize it somewhere else
	// printf("%s", g_all.env[0]);

	// if (args > 1)
	// {
		// if (!(ft_isalpha(str[1][0])))
		// {
		// 	// print_err(-3);
		// 	printf("%s%s%s", "bash: unset: `", str[1], "': not a valid identifier\n"); // error handling func
		// 	return ;
		// }
		// i = 1;
		// j = 0;
		// while (*str != NULL)
		// {
		// 	char *this_arg = *str;
		// 	if (ft_strncmp(this_arg, "./a.out", 7))
		// 	{
		// 		while (this_arg != '\0')
		// 		{
		// 			if (!(ft_isalnum(*this_arg)))
		// 			{
		// 				// print_err(-3);
		// 				printf("%s%s%s", "bash: unset: `", this_arg, "': not a valid identifier\n"); // error handling func
		// 				return ;
		// 			}
		// 			this_arg++;
		// 		}
		// 	}
		// 	str++;
		// }
	// }
	i = 1;
	char **beg_env;

	beg_env = g_all.env;
	while (*g_all.env != 0 && i < args)
	{
		this_env = *g_all.env;
		print_err_export_unset(str[i]);
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
			g_all.env = ft_allocate_env_builtins(beg_env, 1, str[i], this_env);
			// printf("%s\n", g_all.env[0]);
			beg_env = g_all.env;
			i++;
		}
		else
			g_all.env++;
		free(key);
	}
	while (*beg_env != NULL) //this cycle is here just to check
	{
		char *equal;

		this_env = *beg_env;
		equal = ft_strchr(this_env, '=');
		if (equal == NULL)
		{
			printf("%s%s", "declare -x ", this_env);
		}
		else
		{
			printf("%s", "declare -x ");
			char *env = ft_substr(this_env, 0, ft_strlen(this_env) - ft_strlen(equal));
			printf("%s", env);
			free(env);
			printf("%c", equal[0]);
			printf("%c", '"');
			env = ft_substr(equal, 1, ft_strlen(equal) - 1);
			printf("%s", env);
			free(env);
			printf("%c%c", '"', '\n');
		}
		beg_env++;
	}
	g_all.flag_allocate = 0;
	sleep(1000);
}

int main (int argc, char **argv, char **envp)
{
	ft_unset(argv, argc, envp);
	return (0);
}