#include <cstdio>
#include <emerald-em.h>

int main(int argc, char** argv)
{
    int res;

    if (argc != 3)
    {
        std::fprintf(stderr, "Usage: %s <original rom> <output dir>\n", argv[0]);
        return 1;
    }

    EmeraldGenerator* emerald = EmCreate();
    res = EmRun(emerald, argv[1], argv[2]);
    EmDestroy(emerald);

    if (!res)
    {
        fprintf(stderr, "Failed to run the generator\n");
        return 1;
    }

    return 0;
}
