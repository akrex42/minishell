#include <stdio.h>
#include <string.h>

void ft_echo(const char *str);

int main(int argc, char **argv)
{
	int flag;
	flag = 0;

	if (argc < 2)
	{
		return (0);
	}
	int i = 1;
	// Parse key -n if needed
	if (!(strcmp(argv[1], "-n")))
	{
		flag = 1;
		++i;
	}
	while (i < argc)
	{
		ft_echo(argv[i]);
		i++;
	}
	if (!flag)
	{
		printf("\n");
	}
	return (0);
}