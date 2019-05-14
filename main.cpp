#include <iostream>
#include <string>
#include <ctime>
#include <sys/time.h>
#include "include/db.h"
using std::string;
using TeaDB::high_precision;

int64_t getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main() {
    time_t start = getCurrentTime();
//    TeaDB::db db("test");
////    db.create();
//    db.insert("test", false);
//
//    auto table = db.tab("test");
//
//    table->insert("value:0");
//    for (int i = 0; i < 1; i++) {
//        auto res = table->find("value", "0");
//        for (auto iter = res.begin(); iter != res.end(); iter++) {
//            std::cout << *iter << std::endl;
//        }
//    }

    for (int i = 0; i < 100; i++) {
        TeaDB::stringValue("adsfjsdalfkjdsalkfhsdakjhfkjsadfsad/-12312321312==").valueOf();
    }
    time_t end = getCurrentTime();
    std::cout << "start: " << start << "ms, end: " << end << "ms, used " << (end - start) << "ms" << std::endl;
    return 0;
}