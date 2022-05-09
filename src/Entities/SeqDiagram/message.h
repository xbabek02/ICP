#ifndef MESSAGE_H
#define MESSAGE_H

#include "blockentity.h"
#include "../AttributeEntity.h"
#include <QString>

class BlockEntity;

class Message
{
public:
    Message(BlockEntity *sender, BlockEntity *owner, int y_cord);
    int GetID();
    void SetID(int id);
    void SetMethod(AttributeEntity *method);
    void SetAsync(bool async);
    void SetName(QString name);
    QString GetName();
    BlockEntity *GetSender();
    BlockEntity *GetOwner();
    AttributeEntity *GetMethod();
    bool GetAsync();
    int GetYCord();

private:
    int id;
    static int id_generator;
    BlockEntity *sender;
    BlockEntity *owner;
    AttributeEntity  *method = nullptr;
    QString name = "";
    bool async = true;
    int y_cord;
};

#endif // MESSAGE_H
