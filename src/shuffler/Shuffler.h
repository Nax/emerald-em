#ifndef SHUFFLER_H
#define SHUFFLER_H

#include <string>
#include <fstream>
#include <memory>

class Shuffler
{
public:
    Shuffler();
    ~Shuffler();

    int run(const std::string& out);

private:
    std::fstream dataFile(const std::string& name);
    bool         applyLang(const char* lang);
    bool         loadRom();

    std::unique_ptr<char[]> _rom;
    std::string _dataDir;
};

#endif
