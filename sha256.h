#ifndef Sha256_h
#define Sha256_h

#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100 
#include "Print.h"
#else
#include "PrintMod.h"
#endif

#define HASH_LENGTH 32
#define BLOCK_LENGTH 64

union _buffer {
  uint8_t b[BLOCK_LENGTH];
  uint32_t w[BLOCK_LENGTH/4];
};
union _state {
  uint8_t b[HASH_LENGTH];
  uint32_t w[HASH_LENGTH/4];
};

class Sha256Class : public Print
{
  public:
    void init(void);
    void initHmac(const uint8_t* secret, int secretLength);
    uint8_t* result(void);
    uint8_t* resultHmac(void);
    // This used to be virtual void, However for arduino 1.05 and up (I believe?!) it now returns size_t
    virtual size_t write(uint8_t);
    using Print::write;
  private:
    void pad();
    void addUncounted(uint8_t data);
    void hashBlock();
    uint32_t ror32(uint32_t number, uint8_t bits);
    _buffer buffer;
    uint8_t bufferOffset;
    _state state;
    uint32_t byteCount;
    uint8_t keyBuffer[BLOCK_LENGTH];
    uint8_t innerHash[HASH_LENGTH];
};
//extern Sha256Class Sha256;

#endif
