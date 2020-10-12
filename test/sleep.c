#include "syscall.h"

int main()
{
    int i;
    PrintInt(1);

    for (i = 0; i < 8; i++)
    {
        Sleep(1000);
        PrintInt(0);
    }
    return 0;
}
