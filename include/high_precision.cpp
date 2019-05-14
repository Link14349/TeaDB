#include "high_precision.h"

TeaDB::high_precision TeaDB::high_precision::operator+(high_precision& n) {
    high_precision res;
    if (n.value[0] == '-') {
        n.value.erase(0, 1);
        res.value = "-" + ((*this) - n).value;
        n.value = "-" + n.value;
        return res;
    }
    if (value[0] == '-') {
        value.erase(0, 1);
        res.value = (n - (*this)).value;
        value = "-" + value;
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
        short r = av + bv + p;
        res.value[len - i] = (char)(r % 10) + '0';
        p = (r > 9);
    }
    return res.norm();
}


TeaDB::high_precision TeaDB::high_precision::operator-(high_precision& n) {
    high_precision res;
    if (value < n.value) {
        res.value = "-" + (n - (*this)).value;
        return res.norm();
    }
    if (value[0] == '-') {
        if (n.value[0] == '-') {
            n.value.erase(0, 1);
            res.value = (n + (*this)).value;
            n.value = "-" + n.value;
            return res.norm();
        } else {
            string tmp(std::move(value));
            tmp.erase(0, 1);
            high_precision v1(tmp);
            res.value = "-" + (v1 + n).value;
            return res.norm();
        }
    }
    if (n.value[0] == '-') {
        n.value.erase(0, 1);
        res.value = "-" + (n + (*this)).value;
        n.value = "-" + n.value;
        return res.norm();
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
    return res.norm();
}
TeaDB::high_precision TeaDB::high_precision::operator*(high_precision& n) {
    high_precision res("0");
    bool b(true);// true为正数, false负数
    string av = value;
    string bv = n.value;
    if (av[0] == '-') {
        b = !b;
        av.erase(0, 1);
    }
    if (bv[0] == '-') {
        b = !b;
        bv.erase(0, 1);
    }

    auto alen = av.length();
    auto blen = bv.length();
    for (int i = 1; i <= blen; i++) {
        if (bv[blen - i] == '0') continue;
        high_precision tmp;
        fillzero(tmp.value, alen + 1);
        short p(0);
        for (int j = 1; j <= alen; j++) {
            short r = (bv[blen - i] - '0') * (av[alen - j] - '0') + p;
            p = r / 10;
            tmp.value[alen + 1 - j] = (char)(r % 10) + '0';
        }
        tmp.value[0] = (char)(p) + '0';
        fillzero(tmp.value, i - 1);
        res += tmp;
    }

    if (!b) res.value = "-" + res.value;
    return res.norm();
}


TeaDB::high_precision& TeaDB::high_precision::norm() {
    bool t(true);// true为正数, false负数
    for (; value.length() > 0 && value[0] == '-'; ) {
        value.erase(0, 1);
        t = !t;
    }
    for (; value.length() > 0 && value[0] == '0'; ) {
        value.erase(0, 1);
    }
    if (!t) value = "-" + value;

    return *this;
}

TeaDB::high_precision TeaDB::HighPow(high_precision& n, int c) {
    high_precision r("1");
    for (int i = 0; i < c; i++) {
        r *= n;
    }
    return r;
}
TeaDB::high_precision TeaDB::HighPow(high_precision& n, high_precision& c_) {
    int c(c_.trans());
    high_precision r("1");
    for (int i = 0; i < c; i++) {
        r *= n;
    }
    return r;
}