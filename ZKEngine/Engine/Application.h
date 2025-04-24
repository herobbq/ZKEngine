#pragma once
#include <memory>

class FViewport;

class FApplication
{
public:
    /**
    * @js ctor
    */
    FApplication(){};
    /**
    * @js NA
    * @lua NA
    */
    virtual ~FApplication(){};

    /**
    @brief    Run the message loop.
    */
    int run();

    /**
    @brief    Get current application instance.
    @return Current application instance pointer.
    */
    static FApplication* getInstance();

};
