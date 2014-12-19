#include <cstdlib>
#include <iostream>
#include "Fortuna.h"
#include "MySource.h"
#include "LinuxSeedFileManager.h"

void printBytes(uint8_t* hash)
{
    int i;
    printf("\n");
    if (hash == NULL)
    {
        std::cout << "hash is null";
        return;
    }
    for (i = 0; i < 8; i++)
    {
        char hex[] = "0123456789abcdef";
        char var1 = hex[hash[i] >> 4];
        char var2 = hex[hash[i]&0xf];
        std::cout << var1 << var2;
    }
    printf("\n");
}

void printHash(uint8_t* hash)
{
    int i;
    printf("\n");
    if (hash == NULL)
    {
        std::cout << "hash is null";
        return;
    }
    for (i = 0; i < 32; i++)
    {
        char hex[] = "0123456789abcdef";
        char var1 = hex[hash[i] >> 4];
        char var2 = hex[hash[i]&0xf];
        std::cout << var1 << var2;
        //        printf("%c",var1);
        //        printf("%c",var2);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
}

void printHash2(uint8_t* hash, int num)
{
    int i;
    printf("\n");
    if (hash == NULL)
    {
        std::cout << "hash is null";
        return;
    }
    char hex[] = "0123456789abcdef";
    for (i = 0; i < num; i++)
    {
        if (i % 10 == 0)
        {
            std::cout << "\n";
        }

        char var1 = hex[hash[i] >> 4];
        char var2 = hex[hash[i]&0xf];
        std::cout << var1 << var2;
        //        printf("%c",var1);
        //        printf("%c",var2);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
}

void setup()
{
    printf("Test: FIPS 180-2 B.1\n");
    printf("Expect:ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad\n");
    printf("Result:");
    Sha256Class sha;
    sha.init();
    uint32_t value = 0x1010101;
    sha.write('a');    
    sha.write('b');
    sha.write('c');
    uint8_t *ans = sha.result();
    printHash(ans);
    printf("\n");

}

int main(int argc, char** argv)
{
    setup();

    LinuxSeedFileManager ls;
    SeedFile *s1 = &ls;
    //    
    //    uint8_t vw[] = 
    //    {
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //        0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    //    };
    //    
    //    s1->writeSeedFile(vw);
    //    uint8_t *ooooo = s1->readSeedFile();
    //    printHash2(ooooo, 128);
    //    delete[] ooooo;



    Fortuna f(s1);
    MySource mp;
    MySource mp2;
    MySource mp3;
    Source *p = &mp;
    Source *p2 = &mp2;
    Source *p3 = &mp3;
    //    f.FortunaSerialPrint();
    f.registerSource(p);
    f.registerSource(p2);
    f.registerSource(p3);
    uint8_t* datawerwer = f.getRandomData(2);
    printHash2(datawerwer, 2);
    delete[] datawerwer;

    for (int i = 0; i < 4 * 64; i++)
    {
        f.gatherEntropy();
    }
    f.gatherEntropy();
    sleep(2); //Need the sleep as the "First reseed" is at boot.
    uint8_t* data1 = f.getRandomData(2);
    printHash2(data1, 2);



    std::cout << "Banter1";
    //printBytes(data1);
    delete[] data1;
    data1 = f.getRandomData(2);
    printHash2(data1, 2);
    //printBytes(data1);
    int ire = 25;
    delete[] data1;
    data1 = f.getRandomData(ire);
    printHash2(data1, ire);
    std::cout << "Banter2";

    //    mp.setReturnValue(0x02);    
    //    mp2.setReturnValue(0x02);    
    //    mp3.setReturnValue(0x02);   

    for (int i = 0; i < 4 * 64; i++)
    {
        if (i == 32)
        {
            uint16_t l;
            l = 1;
        }
        f.gatherEntropy();
    }
    f.gatherEntropy();
    sleep(2); //Need the sleep as the "First reseed" is at boot.
    delete[] data1;
    data1 = f.getRandomData(2);
    std::cout << "Banter1";
    //printBytes(data1);
    delete[] data1;
    data1 = f.getRandomData(2);
    //printBytes(data1);
    ire = 128;
    delete[] data1;
    data1 = f.getRandomData(ire);
    printHash2(data1, ire);
    //    for(int e = 0 ; e < 128; e++)
    //    for(int e = 0 ; e < 1024; e++)
    //    {
    //        data1 = f.getRandomData(ire); 
    //        //printHash2(data1,ire);
    //    }
    std::cout << "Banter2";
    delete[] data1;


    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4 * 64; i++)
        {
            if (i == 32)
            {
                uint16_t l;
                l = 1;
            }
            f.gatherEntropy();

        }
        f.gatherEntropy();
        sleep(2); //Need the sleep as the "First reseed" is at boot.
        data1 = f.getRandomData(2);
        delete[] data1;
        std::cout << "Banter1";
    }

    return 0;
}

