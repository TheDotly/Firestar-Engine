#pragma once

#include <stdint.h>

class IComposite
{
private:
    void setData(unsigned char* data);
    void setID(uint8_t id);

public:
    unsigned char* getData();
    uint8_t getID();
};

