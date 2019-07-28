#ifndef MYSTRING_H
#define MYSTRING_H


class mystring
{
public:
    mystring();
    mystring (const char *str);
    ~mystring();
    mystring(const mystring &str);
    int capacity() const;
    int lenght() const;
    mystring &operator=(const mystring &str);
private:
    char *pstr;
    int  icapacity;
};

void mystring_test1();

#endif // MYSTRING_H
