#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char dir[1000]; //WE WILL PARSE THIS SO IT WILL BE ALLOCATED DYNAMICALLY
	getcwd(dir, 1000); //add realloc and errors
	printf("Current directory is %s", dir);
	return (0);
}