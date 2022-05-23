// Parameters: [source_file] [key] [shift]

#include <iostream>
#include <random>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    int iSec;
    int iShift = (int)*argv[3] - 48; //Shift value
    std::ofstream fRandKey;
    fRandKey.open("file_random.txt", std::ios::out); // File encrypted random key 
    std::ofstream fUserKey;
    fUserKey.open("file_user.txt", std::ios::out); // File encrypted user defined key
    std::ifstream fOrigin;
    fOrigin.open(argv[1], std::ios::in);

    std::random_device random_device;   //random key generation
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, 1000);
    iSec = distribution(generator);

    char sX, sX1, cSec;
    char* iUSec = argv[2];
    int iKeySize = strlen(iUSec);
 /*   for (int e = 0; e < iKeySize; e++) {
        std::cout << iUSec[e];
    }*/

    int e = 0, s = 1;
    while (!fOrigin.eof())
    {
        fOrigin >> sX;
        cSec = sX ^ iSec;   //XOR with random key
        fRandKey << cSec;
        cSec = sX ^ iUSec[e]; // XOR with user key
        if (e < (iKeySize - 1)) e++; else e = 0;
        if (s < iShift) s++; else { // Moving every [iShift] symbol
            s = 1;
            fOrigin >> sX1;
            fOrigin >> sX;
            cSec = sX ^ iSec;
            fRandKey << cSec;
            cSec = sX ^ iUSec[e];
            if (e < (iKeySize - 1)) e++; else e = 0;
            fUserKey << cSec;
            cSec = sX1 ^ iSec;
            fRandKey << cSec;
            cSec = sX1 ^ iUSec[e];
            if (e < (iKeySize - 1)) e++; else e = 0;
        }
        fUserKey << cSec;
    }

    fOrigin.close();
    fRandKey.close();
    fUserKey.close();
    std::cout << "Encryption is done" << std::endl;
    system("pause");
    return 0;
}
