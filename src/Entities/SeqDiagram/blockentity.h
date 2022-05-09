#ifndef BLOCKENTITY_H
#define BLOCKENTITY_H

#include "message.h"
#include "instanceentity.h"
#include <QList>

class InstanceEntity;
class Message;

class BlockEntity
{
public:
    BlockEntity(InstanceEntity *owner, int y_offset, Message *originMessage = nullptr);
    int GetID();
    void SetID(int id);
    void SetAddedLength(int addedLength);
    void SetYOffset(int y_offset);
    void SetHasReturnMessage(bool hasReturnMessage);
    void SetOriginMessage(Message *originMessage);
    Message *GetOriginMessage();
    QList<Message*> GetMessages();
    InstanceEntity *GetOwner();
    void SetOwner(InstanceEntity *owner);
    int GetAddedLength();
    int GetYOffset();
    bool HasReturnMessage();
    void AddMessage(Message *message);
    void RemoveMessage(Message *message);
    void SetOriginMessageID(int messageID);
    int GetOriginMessageID();

private:
    int id;
    int originMessageID = 0;
    static int id_generator;
    Message *originMessage = nullptr;
    QList<Message*> messages;
    InstanceEntity *owner;
    int addedLength = 0;
    int y_offset;
    bool hasReturnMessage = false;
};

#endif // BLOCKENTITY_H
