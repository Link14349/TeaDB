#ifndef TEADB_HIGH_PRECISION_H
#define TEADB_HIGH_PRECISION_H

#include <iostream>
using std::string;

namespace TeaDB {
    class high_precision {
    public:
        high_precision() : value("") { }
        high_precision(string v) : value(std::move(v)) { }
        high_precision operator+(high_precision&);
        high_precision operator-(high_precision&);
        string valueOf() {
            return value;
        }
    private:
        string value;
    };
}


#endif //TEADB_HIGH_PRECISION_H
