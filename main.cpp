#include <cstdlib>
#include "Fortuna.h"
#include "MySource.h"

void printBytes(uint8_t* hash)
{
    int i;
    printf("\n");
    if(hash == NULL)
    {
        std::cout<<"hash is null";
        return ;
    }
    for (i = 0; i < 8; i++)
    {
        char hex[] = "0123456789abcdef";
        char var1 =hex[hash[i] >> 4];
        char var2 =hex[hash[i]&0xf];
        std::cout<<var1<<var2;
    }
    printf("\n");
}
void printHash(uint8_t* hash)
{
    int i;
    printf("\n");
    if(hash == NULL)
    {
        std::cout<<"hash is null";
        return ;
    }
    for (i = 0; i < 32; i++)
    {
        char hex[] = "0123456789abcdef";
        char var1 =hex[hash[i] >> 4];
        char var2 =hex[hash[i]&0xf];
        std::cout<<var1<<var2;
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
    if(hash == NULL)
    {
        std::cout<<"hash is null";
        return ;
    }
    for (i = 0; i < num; i++)
    {
        char hex[] = "0123456789abcdef";
        char var1 =hex[hash[i] >> 4];
        char var2 =hex[hash[i]&0xf];
        std::cout<<var1<<var2;
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
    sha.write(value);
    uint8_t *ans = sha.result();
    printHash(ans);
    printf("\n");

}

int main(int argc, char** argv)
{
    
    setup();
    
    Fortuna f;
    MySource mp;
    MySource mp2;
    MySource mp3;
    Source *p = &mp;
    Source *p2 = &mp2;
    Source *p3 = &mp3;
//    f.FortunaSerialPrint();
    f.RegisterSource(p);
    f.RegisterSource(p2);
    f.RegisterSource(p3);
    
    for(int i = 0; i< 4*32;i++)
    {
        if(i == 32)
        {
            uint16_t l;
            l = 1;
        }
        f.GatherEntropy();
    }
    f.GatherEntropy();
    sleep(2); //Need the sleep as the "First reseed" is at boot.
    uint8_t* data1 = f.GetRandomData(2); 
    std::cout << "Banter1";
    printBytes(data1);
    data1 = f.GetRandomData(2); 
    printBytes(data1);
    int ire = 25;
    data1 = f.GetRandomData(ire); 
    printHash2(data1,ire);
    std::cout << "Banter2";
    
    mp.setReturnValue(0x02);    
    mp2.setReturnValue(0x02);    
    mp3.setReturnValue(0x02);   
    
    for(int i = 0; i< 4*32;i++)
    {
        if(i == 32)
        {
            uint16_t l;
            l = 1;
        }
        f.GatherEntropy();
    }
    f.GatherEntropy();
    sleep(2); //Need the sleep as the "First reseed" is at boot.
    data1 = f.GetRandomData(2); 
    std::cout << "Banter1";
    printBytes(data1);
    data1 = f.GetRandomData(2); 
    printBytes(data1);
    ire = 25;
    data1 = f.GetRandomData(ire); 
    printHash2(data1,ire);
    std::cout << "Banter2";
    
    return 0;
}

