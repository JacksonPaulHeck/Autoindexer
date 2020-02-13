//
// Created by jacks on 1/26/2020.
//
# include <iostream>

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

    JPString operator+=(const JPString &);

    char &operator[](int) const;

    int size() const;

    JPString& lowercase();

    friend bool operator==(const JPString &, const JPString &);

    friend std::ostream &operator<<(std::ostream &, const JPString &);

    friend std::istream &operator>>(std::istream &, JPString &);

    long toPageNumber();
};


#endif //INC_20S_PA02_AUTOINDEXER_JHECKSMU_JPSTRING_H
