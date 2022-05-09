/**
 * @file seqdscene.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "message.h"

int Message::id_generator = 1;

Message::Message(BlockEntity *sender, BlockEntity *owner, int y_cord)
{
    this->id = id_generator;
    id_generator++;
    this->sender = sender;
    this->owner = owner;
    this->y_cord = y_cord;
    this->async = false;
}

void Message::SetName(QString name)
{
    this->name = name;
}

QString Message::GetName()
{
    return this->name;
}

void Message::SetMethod(AttributeEntity *method)
{
    this->method = method;
}

void Message::SetID(int id)
{
    this->id = id;
}

void Message::SetAsync(bool async)
{
    this->async = async;
}


int Message::GetID()
{
    return id;
}

BlockEntity *Message::GetSender()
{
    return sender;
}


BlockEntity *Message::GetOwner()
{
    return owner;
}

AttributeEntity *Message::GetMethod()
{
    return method;
}

bool Message::GetAsync()
{
    return async;
}

int Message::GetYCord()
{
    return y_cord;
}
