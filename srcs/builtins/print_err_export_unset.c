#include "minishell.h"

void		print_err_export_unset(char *str)
{
	int i = 1;

	if (!ft_isalpha(str[0]))
	{
		printf("%s%c%s", "bash: export: `", str[0], "': not a valid identifier\n");
		exit(1); // errno?
	}
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '=')
		{
			printf("%s%s%s", "bash: export: `", str, "': not a valid identifier\n");
			exit(1);
		}
		i++;
	}
}