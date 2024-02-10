#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void signalHandler(int signal)
{
    if (signal == SIGINT) {
        puts("ctrl + c pressed!!!!");
        exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    // Create a pointer to a function thats returns void and receive int parameter
    // typedef void (*SignalHandlerProcedure)(int);
    // SignalHandlerProcedure shp;

    // shp = signal(SIGABRT, signalHandler);

    // Mapping SIGNAL to a specific handler function
    signal(SIGINT, signalHandler);
    puts("Try to stop me!!!!!!");

    while (1) {}

    return 0;
}