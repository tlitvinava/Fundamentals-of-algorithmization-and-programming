#include "binpow.h"

int BinPow::calculate(int digit, int powder, int mod)
{
    int result = 1;
    while (powder > 0)
    {
        if (powder & 1)
            result = (result * digit) % mod;
        digit = (digit * digit) % mod;
        powder >>= 1;
    }
    return result;
}
