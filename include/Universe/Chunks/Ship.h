#ifndef SHIP_H
#define SHIP_H

#include "Chunk.h"

struct ShipData : public ChunkData//initialized
{
    ShipData() :
        ChunkData()
        {}
};

class Ship : public Chunk
{
    public:
        Ship();
        Ship(const ShipData& data);
        virtual ~Ship();

    protected:
    private:
        virtual void f_initialize(const ShipData& data);

};

#endif // SHIP_H