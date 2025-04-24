#pragma once
#include "Engine/Director.h"

class FWindowDirector : public  FDirector
{
public:
    static FDirector* GetInstance() 
    {
        static FWindowDirector Director;
        return &Director;
    }
};
