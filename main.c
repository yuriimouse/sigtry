#include "sigtry.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Try block starting...\n");

    Try(SIGINT, SIGTERM, SIGSEGV)
    {
        printf("Inside Try block\n");
        // raise(SIGSEGV);
        char *str = NULL;
        *str = '!';
        printf("This line will not be printed if signal occurs.\n");
    }
    Catch
    {
        On(SIGINT)
        {
            printf("Caught SIGINT\n");
        }
        On(SIGTERM)
        {
            printf("Caught SIGTERM\n");
        }
        On(SIGSEGV)
        {
            printf("Caught SIGSEGV\n");
        }
    }

    printf("After Try/Catch block\n");
    return 0;
}
