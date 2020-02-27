//
// Created by jacks on 1/26/2020.
//
#include <iostream>
#include <cstring>
#include <exception>

#ifndef INC_20S_PA02_AUTOINDEXER_JHECKSMU_JPSTRING_H
#define INC_20S_PA02_AUTOINDEXER_JHECKSMU_JPSTRING_H


class JPString {
private:
    char *data;
    int length;
public:
    JPString();

    JPString(const char *);

    JPString(const JPString &);

    ~JPString();

    JPString &operator=(const JPString &);

    JPString &operator=(const char *);

    bool operator!=(char);

    bool operator!=(const JPString &);

    JPString operator+=(const JPString &);

    JPString operator+=(const char *);

    JPString operator+=(int);

    friend bool operator<(const JPString &, const JPString &);

    char &operator[](int) const;

    int size() const;

    friend bool operator==(const JPString &, const JPString &);

    friend bool operator==(const JPString &, const char *);

    friend std::ostream &operator<<(std::ostream &, const JPString &);

    friend std::istream &operator>>(std::istream &, JPString &);

    friend bool operator>(const JPString &, const JPString &);

    JPString & lowercase();

    JPString substring(int, int);

};
#endif //INC_20S_PA02_AUTOINDEXER_JHECKSMU_JPSTRING_H
