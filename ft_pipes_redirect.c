#include "minishell.h"

void	ft_execute()
{
	int tmpin = dup(0);
	int tmpout = dup(1);

	int fdin;
	if (infile) // input file g.txt < infile
	{
		fdin = open(infile, O_RDONLY);
	}
	else
	{
		fdin = dup(tmpin);
	}

	int ret;
	int fdout;
	int i = 0;

	while (i < numofcommands)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == numofcommands - 1)
		{
			if (outfile) // output file g.txt > outputfile
			{
				fdout = open(outfile, O_RDWR);
			}
			else
			{
				fdout = dup(tmpout);
			}
		}
		else
		{
			int fdpipe[20];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);

		ret = fork();
		if (ret == 0)
		{
			execvp(scmd[i].args[0], scmd[i].args); //array of commands parsed
			perror("execvp");
			exit (1);
		}
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	if (!background)
	{
		waitpid(ret, NULL);
	}
}