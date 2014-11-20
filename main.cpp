#include <cstdlib>
#include "Fortuna.h"

//void printHash(uint8_t* hash)
//{
//    int i;
//    for (i = 0; i < 32; i++)
//    {
//        char hex[] = "0123456789abcdef";
//        printf("%c",hex[hash[i] >> 4]);
//        printf("%c",hex[hash[i]&0xf]);
//    }
//    printf("\n");
//}

void setup()
{
//    printf("Test: FIPS 180-2 B.1\n");
//    printf("Expect:ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad\n");
//    printf("Result:");
//    Sha256.init();
//    Sha256.write("abc");
//    printHash(Sha256.result());
//    printf("\n");

}

int main(int argc, char** argv)
{
    Fortuna f;
    std::cout << "Banter";
    f.FortunaSerialPrint();
    setup();
    return 0;
}

