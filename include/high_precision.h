#ifndef TEADB_HIGH_PRECISION_H
#define TEADB_HIGH_PRECISION_H

#include <iostream>
#include <cstdlib>
#include <string>
using std::string;

namespace TeaDB {
    class high_precision {
    public:
        high_precision() : value("") { }
        high_precision(string v) : value(std::move(v)) { }
        high_precision(high_precision& v) : value(v.value) { }
        high_precision(long long v) : value(std::to_string(v)) { }
        high_precision operator+(high_precision&);
        high_precision& operator+=(high_precision& n) {
            value = ((*this) + n).value;
            return *this;
        }
        high_precision operator-(high_precision&);
        high_precision& operator-=(high_precision& n) {
            value = ((*this) - n).value;
            return *this;
        }
        high_precision operator*(high_precision&);
        high_precision& operator*=(high_precision& n) {
            value = ((*this) * n).value;
            return *this;
        }

        // 实现除法过于麻烦，而且TeaDB中目前用不到，所以不予实现

        high_precision & operator=(high_precision const& n) {
            value = n.value;
            return *this;
        }
        string& valueOf() {
            return value;
        }
        long long trans() {
            return std::stoll(value);
        }
        high_precision& norm();
    private:
        string value;
        static void fillzero(string& text, unsigned long len) {
            // 补零函数，为了增加速度，两个两补，最后如果位数差是奇数，就再补一个零
            auto c(len / 2);
            for (int i = 0; i < c; i++) text += "00";
            if (len % 2) text += "0";
        }
    };
    high_precision HighPow(high_precision&, int);
    high_precision HighPow(high_precision&, high_precision&);
}


#endif //TEADB_HIGH_PRECISION_H
