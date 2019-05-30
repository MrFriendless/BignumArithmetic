#include <iostream>

#include "number.h"

short Number::char_to_short(char c) {
    return c-'0';
}

Number::Number() {
    length = 1;
    num = new short[1];
    num[0] = 0;
}

Number::Number(std::string& num_str) {
    length = num_str.length();
    num = new short[length];
    for (int i = 0; i < length; i++)
        num[i] = char_to_short(num_str[length-1-i]);
}

Number::Number(const Number& arg) {
    delete[] num;
    length = arg.length;
    num = new short[length];
    for (int i = 0; i < length; i++)
        num[i] = arg.num[i];
}

Number::Number(Number&& arg) {
    delete[] num;
    length = arg.length;
    num = arg.num;
    arg.num = NULL;
}

void Number::print() {
    for (int i = length-1; i >= 0; i--)
        std::cout << num[i];
    std::cout << std::endl;
}

Number Number::operator+ (const Number& arg) {
    int newlen = (length > arg.length) ? length+1 : arg.length+1;
    short * newnum = new short[newlen];
    for (int i = 0; i < length; i++)
        newnum[i] = num[i];

    short tmp = 0;
    for (int i = 0; i < arg.length; i++) {
        short sum = newnum[i] + arg.num[i] + tmp;
        newnum[i] = sum % 10;
        tmp = (sum > 9) ? 1 : 0;
    }

    for (int i = arg.length; i < newlen && tmp == 1; i++) {
        short sum = newnum[i] + tmp;
        newnum[i] = sum % 10;
        tmp = (sum > 9) ? 1 : 0;
    }

    Number result;
    delete[] result.num;
    if (newnum[newlen-1] == 0) {
        --newlen;
        result.num = new short[newlen];
        for (int i = 0; i < newlen; i++)
            result.num[i] = newnum[i];
        delete[] newnum;
    } else {
        result.num = newnum;
        newnum = NULL;
    }
    result.length = newlen;

    return result;
}

Number Number::operator* (const Number& arg) {
    int newlen = length + arg.length;
    short * newnum = new short[newlen];

    for (int j = 0; j < arg.length; j++) {
        int tmp = 0;
        for (int i = 0; i < length; i++) {
            short sum = newnum[i+j] + num[i] * arg.num[j] + tmp;
            newnum[i+j] = sum % 10;
            tmp = sum / 10;
        }
        newnum[length+j] = tmp;
    }

    Number result;
    delete[] result.num;
    if (newnum[newlen-1] == 0) {
        --newlen;
        result.num = new short[newlen];
        for (int i = 0; i < newlen; i++)
            result.num[i] = newnum[i];
        delete[] newnum;
    } else {
        result.num = newnum;
        newnum = NULL;
    }
    result.length = newlen;

    return result;
}

Number& Number::operator= (const Number& arg) {
    delete[] num;
    length = arg.length;
    num = new short[length];
    for (int i = 0; i < length; i++)
        num[i] = arg.num[i];
    return *this;
}

Number& Number::operator= (Number&& arg) {
    delete[] num;
    length = arg.length;
    num = arg.num;
    arg.num = NULL;
    return *this;
}

Number::~Number() {
    delete[] num;
}
