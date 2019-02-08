//
// Created by aurailus on 06/02/19.
//

#ifndef ZEUS_SERIALIZER_H
#define ZEUS_SERIALIZER_H

#include <string>
#include <vector>

using namespace std;

class Serializer {
public:
    static void encodeInt     (string &target, int num);
    static void encodeFloat   (string &target, float num);
    static void encodeString  (string &target, string str);

    static void encodeIntVec  (string &target, vector<int>& vec);
    static void encodeFloatVec(string &target, vector<float>& vec);

    static int    decodeInt     (char* intStart);
    static float  decodeFloat   (char* floatStart);
    static string decodeString  (char* stringStart);

    static vector<int>   decodeIntVec  (string &string);
    static vector<float> decodeFloatVec(string &string);
private:
    typedef union {
        float fl;
        int   in;
        char bytes[4];
    } convert_union;
};


#endif //ZEUS_SERIALIZER_H
