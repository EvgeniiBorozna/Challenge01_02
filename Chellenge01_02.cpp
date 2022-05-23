// Parameters: [source_file] [key] [shift] [mode: e(encrypt) d(decrypt)]

#include <iostream>
#include <random>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    char cMode = *argv[4];
    char* iUSec = argv[2];
    char sX, sX1, cSec;
    std::ofstream fRandKey;
    std::ofstream fUserKey;
    std::ifstream fOrigin;

    if (cMode == 'e') {
        int iSec;
        int iShift = (int)*argv[3] - 48; //Shift value
        fRandKey.open("file_random.txt", std::ios::out); // File encrypted random key 
        fUserKey.open("file_user.txt", std::ios::out); // File encrypted user defined key
        fOrigin.open(argv[1], std::ios::in);

        std::random_device random_device;   //random key generation
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, 1000);
        iSec = distribution(generator);
        
        int iKeySize = strlen(iUSec);

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
    }
    if (cMode == 'd') {
        fUserKey.open("file_user_decr.txt", std::ios::out); // File decrypted by user key
        fOrigin.open(argv[1], std::ios::in);
    }
    fOrigin.close();
    fRandKey.close();
    fUserKey.close();
    std::cout << "Encryption is done" << std::endl;
    system("pause");
    return 0;
}
