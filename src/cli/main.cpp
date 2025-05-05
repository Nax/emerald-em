#include <cstdio>
#include <cstring>
#include <emerald-em.h>

int main(int argc, char** argv)
{
    int res;
    const char* pathOriginal;
    const char* pathOutput;
    const char* arg;
    int index;

    pathOriginal = nullptr;
    pathOutput = nullptr;

    if (argc < 3)
    {
        std::fprintf(stderr, "Usage: %s [flags] <original rom> <output dir>\n", argv[0]);
        return 1;
    }

    EmeraldGenerator* emerald = EmCreate();

    index = 1;
    while (index < argc)
    {
        arg = argv[index++];
        if (strcmp(arg, "--lang-en") == 0)
        {
            EmSetLang(emerald, EMERALDEM_LANG_EN_US);
        }
        else if (strcmp(arg, "--lang-fr") == 0)
        {
            EmSetLang(emerald, EMERALDEM_LANG_FR_FR);
        }
        else
        {
            if (pathOriginal == nullptr)
            {
                pathOriginal = arg;
            }
            else if (pathOutput == nullptr)
            {
                pathOutput = arg;
            }
            else
            {
                fprintf(stderr, "Unknown argument: %s\n", arg);
                EmDestroy(emerald);
                return 1;
            }
        }
    }

    res = EmRun(emerald, pathOriginal, pathOutput);
    EmDestroy(emerald);

    if (!res)
    {
        fprintf(stderr, "Failed to run the generator\n");
        return 1;
    }

    return 0;
}
