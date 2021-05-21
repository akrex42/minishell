#include "minishell.h"

void	ft_execute()
{
	int tmpin = dup(0);
	int tmpout = dup(1);
	int fdpipe[20];

	int fdin;
	if (!ft_strncmp(g_all.commands->special, '<', 2)) // input file g.txt < infile
	{
		fdin = open(infile, O_RDONLY, O_CREAT); // g_all.commans->args[after the <]
	}
	else
	{
		fdin = dup(tmpin);
	}

	int ret;
	int fdout;
	int i = 0;

	while (g_all.commands->next)
	{
		dup2(fdin, 0);
		close(fdin);
		if (g_all.commands->next != NULL) // ??
		{
			if (!ft_strncmp(g_all.commands->special, '>', 2)) // output file g.txt > outputfile
			{
				fdout = open(outfile, O_RDWR, O_CREAT); // if we use builtins then we need to change stdout for ft_putstr and ft_putchar, so give one to the current file
			}
			else
			{
				fdout = dup(tmpout);
			}
		}
		else
		{
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);

		ret = fork();
		if (ret == 0)
		{
			if (execve(g_all.commands->prog, g_all.commands->args, NULL)) //array of commands parsed
			{
				strerror(errno);
				exit (1);
			}
		}
		if (ret == -1)
		{
			strerror(errno);
			exit (1);
		}
		g_all.commands = g_all.commands->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	// if (ret != 0)
	// {
	// 	// close(fdpipe[0]);          /* Close unused read end */
    //     // write(fdpipe[1], argv[1], strlen(argv[1]));
    //     // close(fdpipe[1]);          /* Reader will see EOF */
    //     // wait(NULL);                /* Wait for child */
    //     // exit(EXIT_SUCCESS);
	// }
}
