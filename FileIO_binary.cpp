#include <iostream>
#include <random>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    //char cMode = *argv[4];
    //char* iUSec = argv[2];
    unsigned char sX, cSec, iUSec = { 'a' };
    std::ofstream fUserKey;
    std::ifstream fOrigin;

        fUserKey.open("file_user.txt", std::ios::out | std::ios::binary); // File encrypted user defined key
        fOrigin.open("file.txt", std::ios::in | std::ios::binary);

        std::fstream fs(L"data.txt", std::ios::in | std::ios::binary);
        if (fs.is_open())
        {
            char byte;
            while (1) {
                fs.read(&byte, sizeof(char));
                if (fs.eof()) break;
                std::cout << byte;
            }
            std::cout << std::endl;
            fs.close();
        }

        int e = 0, s = 1;
        fOrigin.seekg(5, std::ios::end);
        e = fOrigin.tellg();
        fOrigin.seekg(0, std::ios::beg);
        while (1)
        {
            fOrigin >> sX;
            if (fOrigin.eof()) break;
            cSec = sX ^ iUSec; // XOR with user key
            fUserKey << cSec;
            //std::cout << sX << " " << cSec << std::endl;
        }
    fOrigin.close();
    fUserKey.close();

    fUserKey.open("file_dec.txt", std::ios::out | std::ios::binary);
    fOrigin.open("file_user.txt", std::ios::in | std::ios::binary);
    while (1)
    {
        fOrigin >> sX;
        if (fOrigin.eof()) break;
        cSec = sX ^ iUSec; // XOR with user key
        fUserKey << cSec;
        //std::cout << sX << " " << cSec << std::endl;
    }
    fOrigin.close();
    fUserKey.close();
    std::cout << "Encryption is done" << std::endl;
    //system("pause");
    return 0;
}
