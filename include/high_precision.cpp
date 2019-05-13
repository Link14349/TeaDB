#include "high_precision.h"

TeaDB::high_precision TeaDB::high_precision::operator+(high_precision& n) {
    high_precision res;

    if (value.length() < n.value.length()) {
        // 补零，为了增加速度，两个两补，最后如果位数差是奇数，就再补一个零
        int m = (n.value.length() - value.length());
        int c = m / 2;
        for (int i = 0; i < c; i++) value = "00" + value;
        if (m % 2) value = "0" + value;
    } else {
        // 补零，为了增加速度，两个两补，最后如果位数差是奇数，就再补一个零
        int m = (value.length() - n.value.length());
        int c = m / 2;
        for (int i = 0; i < c; i++) n.value = "00" + n.value;
        if (m % 2) n.value = "0" + n.value;
    }
    auto len = value.length();

    // 补零，为res补零，为了增加速度，两个两补，最后如果位数差是奇数，就再补一个零
    int c = len / 2;
    for (int i = 0; i < c; i++) res.value = "00" + res.value;
    if (len % 2) res.value = "0" + res.value;

    short p(0);
    for (int i = 1; i <= len; i++) {
        short av = value[len - i] - '0';
        short bv = n.value[len - i] - '0';
        short r = av + bv + p;
        res.value[len - i] = (char)(r % 10) + '0';
        p = (r > 9);
    }
    return res;
}


TeaDB::high_precision TeaDB::high_precision::operator-(high_precision& n) {
    high_precision res;
    if (value < n.value) {
        auto v = n - (*this);
        res.value = v.value;
        res.value = "-" + res.value;
        return res;
    }

    if (value.length() < n.value.length()) {
        // 补零，为了增加速度，两个两补，最后如果位数差是奇数，就再补一个零
        int m = (n.value.length() - value.length());
        int c = m / 2;
        for (int i = 0; i < c; i++) value = "00" + value;
        if (m % 2) value = "0" + value;
    } else {
        // 补零，为了增加速度，两个两补，最后如果位数差是奇数，就再补一个零
        int m = (value.length() - n.value.length());
        int c = m / 2;
        for (int i = 0; i < c; i++) n.value = "00" + n.value;
        if (m % 2) n.value = "0" + n.value;
    }
    auto len = value.length();

    // 补零，为res补零，为了增加速度，两个两补，最后如果位数差是奇数，就再补一个零
    int c = len / 2;
    for (int i = 0; i < c; i++) res.value = "00" + res.value;
    if (len % 2) res.value = "0" + res.value;

    short p(0);
    for (int i = 1; i <= len; i++) {
        short av = value[len - i] - '0';
        short bv = n.value[len - i] - '0';
        short r = av - bv - p;
        if (r < 0) {
            r += 10;
            p = 1;
        } else {
            p = 0;
        }
        res.value[len - i] = (char)(r % 10) + '0';
    }
    return res;
}