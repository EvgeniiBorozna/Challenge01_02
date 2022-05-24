// Parameters: [source_file] [key] [shift] [mode: e(encrypt) d(decrypt)]

#include <iostream>
#include <random>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    char cMode = 'e';//*argv[4];
    char iUSec = 'q';//argv[2];
    int iShift = 3; // (int)*argv[3] - 48; //Shift value
    bool sX, sX1, cSec;
    int iKeySize = 1;// strlen(iUSec);
    std::ofstream fRandKey;
    std::ofstream fUserKey;
    std::ifstream fOrigin;

    if (cMode == 'e') {
        fUserKey.open("file_user.txt", std::ios::out | std::ios::binary); // File encrypted user defined key
    }
    if (cMode == 'd') {
        fUserKey.open("file_user_decr.txt", std::ios::out | std::ios::binary); // File decrypted by user key
    }
        bool iSec;
        fRandKey.open("file_random.txt", std::ios::out); // File encrypted random key 
        
        fOrigin.open("file.txt", std::ios::binary);
        //fOrigin.open(argv[1], std::ios::in | std::ios::binary);

        std::random_device random_device;   //random key generation
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, 255);
        iSec = distribution(generator);

        int e = 0, s = 1, iCount = 0 ;
        while (!fOrigin.eof())
        {
            fOrigin >> sX;
            cSec = sX ^ iSec;   //XOR with random key
            fRandKey << cSec;
            cSec = sX ^ iUSec;//[e]; // XOR with user key
            if (e < (iKeySize - 1)) e++; else e = 0;
            /*if (s < iShift) s++; else { // Moving every [iShift] symbol
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
            } */
            fUserKey << cSec;
            iCount++;
            
        }
        std::cout << iCount;
    fOrigin.close();
    fRandKey.close();
    fUserKey.close();
    std::cout << "Encryption is done" << std::endl;
    system("pause");
    return 0;
}
