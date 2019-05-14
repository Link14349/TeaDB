#include <string>
#include "stringValue.h"

TeaDB::high_precision TeaDB::stringValue(string str) {
    high_precision res("0");
    high_precision base("256");
    for (int i = 0; i < str.length(); i++) {
        short v_ = str[i];
        high_precision v(std::to_string(v_));
        high_precision t1(HighPow(base, i).valueOf());
        high_precision t2((t1 * v).valueOf());
        res += t2;
    }
    return res;
}