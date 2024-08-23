#pragma once
#include <msgpack.hpp>


struct MyStruct {
    int x;
    int y;
    MSGPACK_DEFINE(x, y);
};

int Mul(MyStruct s);