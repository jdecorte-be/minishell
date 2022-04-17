#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv, char **env)
{

    (void)argc;
    (void)argv;
    free(env[0]);

}