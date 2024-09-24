#pragma once
#include "object.h"

class World : public Object
{
    int refCount;

    public:
     World() : refCount(1) {}

    void AddRef() 
    {
        ++refCount;
    }

    void Release() 
    {
        if (--refCount == 0) {
            delete this;
        }
    }

    void draw() override;
    
};
