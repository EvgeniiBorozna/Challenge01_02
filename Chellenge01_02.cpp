// [source_file] [key] [shift]

#include <iostream>
#include <random>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    char cMove;
    int iSec;
    char cXOR;
    cMove = *argv[3];
    std::ofstream fRandKey;
    fRandKey.open("file_random.txt", std::ios::out);
    std::ofstream fUserKey;
    fUserKey.open("file_user.txt", std::ios::out);
    std::ifstream fOrigin;
    fOrigin.open(argv[1], std::ios::in);

    std::random_device random_device;   //random key generation
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, 1000);
    iSec = distribution(generator);

    char sX, cSec;
    char* iUSec = argv[2];

    while (!fOrigin.eof())
    {
        fOrigin >> sX;
        cSec = sX ^ iSec;
        fRandKey << cSec;
        cSec = sX ^ iUSec[0];
        fUserKey << cSec;
    }

    fOrigin.close();
    fRandKey.close();
    fUserKey.close();
    system("pause");
    return 0;
}

