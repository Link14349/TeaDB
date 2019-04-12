#include <iostream>
#include <fstream>
#include <string>
#include "../include/table.h"
#include "../base64-master/base64.h"
using std::fstream;
using std::ofstream;
using std::cout;
using std::endl;


void TeaDB::table::create() {
//    std::cout << path << ", " << dbName << ", " << name << std::endl;

    // 创建表文件夹
    string command("mkdir " + path + dbName + "/" + name);
    system(command.c_str());

    // 存储系统最大_id字段
    ofstream _idFile(path + dbName + "/" + name + "/_id.txt");
//    cout << path + dbName + "/" + name + "/_id.txt" << endl;
    _idFile << "0";
    _idFile.close();
}

void TeaDB::table::insert(string line) {
    long long maxId;
    fstream _idFileIn(path + dbName + "/" + name + "/_id.txt");

    _idFileIn >> maxId;
    _idFileIn.close();
    maxId++;

//    line = line;
    long long _IdFileID = maxId / TABLE_SIZE;
    string maxIdString = lltoString(maxId);
    fstream _idFileSaver(path + dbName + "/" + name + "/_id-" + lltoString(_IdFileID), std::ios::app);
    _idFileSaver << "_id:" + maxIdString + "," + line << endl;
    _idFileSaver.close();

    string token(""), value("");
    bool stringT = false;
    bool gettingToken = true;
    bool escape = false;
    bool isString = false;
    long lineLen = line.length();
    long lineLastIndex = line.length() - 1;

    for (long i = 0; i < lineLen; i++) {
        if (gettingToken) {// 获取字段名
            if (line[i] == ':') {
                gettingToken = false;
            } else {
                token += line[i];
            }
        } else {// 获取字段值
            if (line[i] == ',' || i == lineLastIndex) {
                if (!stringT) {
                    token = trim(token);
                    // 写入链接表
                    if (isString) {
                        value.erase(value.begin());
                        value.erase(value.end() - 1);
                        long long n = 0;
                        while (true) {
                            fstream file(path + dbName + "/" + name + "/string-" + token + "-" + lltoString(n));
                            if (!file) {
                                file.close();
                                fstream writer(path + dbName + "/" + name + "/string-" + token + "-" + lltoString(n), std::ios::out);
                                writer << value << endl << maxId;
                                writer.close();
                                break;
                            }
                            string content("");
                            file >> content;
                            if (content < value) n = 2 * n + 1;
                            if (content > value) n = 2 * n + 2;
                            file.close();
                        }
                    } else {
                        long long v = (long long) ((double)(FLOAT_ACC) * atof(value.c_str()));
                        long long fileId = v / TABLE_SIZE;
                        fstream fileSaver(path + dbName + "/" + name + "/" + token + "-" + lltoString(fileId), std::ios::app);
                        fileSaver << token << ":" << lltoString(v) << ",_id:" << maxIdString << endl;
                        fileSaver.close();
                    }

                    // 重置
                    token = "";
                    value = "";
                    stringT = false;
                    gettingToken = true;
                    escape = false;
                    isString = false;
                } else {
                    value += line[i];
                }
            } else {
                value += line[i];
            }
            if (line[i] == '\\') {
                escape = !escape;
            }
            if (line[i] == '\"') {
                if (!escape) {
                    isString = true;
                    stringT = !stringT;
                }
            }
        }
    }

    fstream _idFileOut(path + dbName + "/" + name + "/_id.txt", std::ios::in | std::ios::out | std::ios::trunc);
    _idFileOut.write(maxIdString.c_str(), maxIdString.length());
    _idFileOut.close();
}
