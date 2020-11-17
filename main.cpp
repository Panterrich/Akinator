#include "Akinator.h"


int main(int argc, char *argv[])
{
    const char* name_base = nullptr;

    if (argc == 1)
    {
        name_base = "Base.txt";
    }

    else if (argc == 2)
    {
        name_base = argv[1];
    }

    Menu(name_base);

    return 0;
}
