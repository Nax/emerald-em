#include <shuffler/Shuffler.h>

int main(int argc, char** argv)
{
    Shuffler shuffler;

    if (argc < 2)
    {
        std::fprintf(stderr, "Usage: %s <output dir>\n", argv[0]);
        return 1;
    }

    return shuffler.run(argv[1]);
}
