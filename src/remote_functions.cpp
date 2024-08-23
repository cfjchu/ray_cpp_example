#include <ray/api.h>
#include <iostream>
#include <exception>

#include "remote_functions.hpp"

/// common function
int Mul(MyStruct s) { return s.x * s.y; }
/// Declare remote function
RAY_REMOTE(Mul);
