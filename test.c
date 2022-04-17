#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>

int		main()
{
	printf("%d\n%d\n", chdir("/"), chdir("/Users"));
}