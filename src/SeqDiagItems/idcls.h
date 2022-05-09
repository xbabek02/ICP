#ifndef ID_CLS_H
#define ID_CLS_H

#include <QList>


class IDcls
{
public:
    IDcls();
    IDcls(const IDcls &item);
    bool operator==(IDcls &);
    void SetID_generator(int value);
    void SetID(int id);
    int GetID();


protected:
    static int ID_generator;
    int ID;
};

#endif // ID_CLS_H
