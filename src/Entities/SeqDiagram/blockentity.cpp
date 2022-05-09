#include "blockentity.h"

int BlockEntity::id_generator = 1;

BlockEntity::BlockEntity(InstanceEntity *owner, int y_offset, Message *originMessage)
{
    this->id = id_generator;
    id_generator++;
    this->owner = owner;
    this->y_offset = y_offset;
    this->originMessage = originMessage;
}

void BlockEntity::SetID(int id)
{
    this->id = id;
}

void BlockEntity::SetOriginMessageID(int messageID)
{
    this->originMessageID = messageID;
}

int BlockEntity::GetOriginMessageID()
{
    return this->originMessageID;
}

void BlockEntity::SetOriginMessage(Message *originMessage)
{
    this->originMessage = originMessage;
}

void BlockEntity::SetAddedLength(int addedLength)
{
    this->addedLength = addedLength;
}

void BlockEntity::SetYOffset(int y_offset)
{
    this->y_offset = y_offset;
}

void BlockEntity::SetHasReturnMessage(bool hasReturnMessage)
{
    this->hasReturnMessage = hasReturnMessage;
}

int BlockEntity::GetID()
{
    return id;
}

Message *BlockEntity::GetOriginMessage()
{
    return originMessage;
}

QList<Message*> BlockEntity::GetMessages()
{
    return messages;
}

InstanceEntity *BlockEntity::GetOwner()
{
    return owner;
}

void BlockEntity::SetOwner(InstanceEntity *owner)
{
    this->owner = owner;
}

int BlockEntity::GetAddedLength()
{
    return addedLength;
}

int BlockEntity::GetYOffset()
{
    return y_offset;
}

bool BlockEntity::HasReturnMessage()
{
    return hasReturnMessage;
}

void BlockEntity::AddMessage(Message *message)
{
    messages.append(message);
}

void BlockEntity::RemoveMessage(Message *message)
{
    for(int i {0}; i < messages.count(); i++)
    {
        if(messages[i] == message)
        {
            messages.removeAt(i);
        }
    }
}

