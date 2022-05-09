/**
 * @file message.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Model for message in sequence diagram
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include "blockentity.h"
#include "../AttributeEntity.h"
#include <QString>

class BlockEntity;

class Message
{
public:
    /**
     * @brief Message is constructor
     * @param sender is block which sended this message
     * @param owner is block which owns the message
     * @param y_cord is y position
     */
    Message(BlockEntity *sender, BlockEntity *owner, int y_cord);

    /**
     * @brief GetID
     * @return id of the object
     */
    int GetID();

    /**
     * @brief SetID sets id of the object
     * @param id
     */
    void SetID(int id);

    /**
     * @brief SetMethod sets pointer to the method in the model
     * @param method
     */
    void SetMethod(AttributeEntity *method);

    /**
     * @brief SetAsync sets whether message is async
     * @param async
     */
    void SetAsync(bool async);

    /**
     * @brief SetName sets name of the message
     * @param name
     */
    void SetName(QString name);

    /**
     * @brief GetName
     * @return name of the message
     */
    QString GetName();

    /**
     * @brief GetSender
     * @return sender block
     */
    BlockEntity *GetSender();

    /**
     * @brief GetOwner
     * @return owner block
     */
    BlockEntity *GetOwner();

    /**
     * @brief GetMethod
     * @return returns pointer to the method in the model
     */
    AttributeEntity *GetMethod();

    /**
     * @brief GetAsync
     * @return whether message is async
     */
    bool GetAsync();

    /**
     * @brief GetYCord
     * @return y position
     */
    int GetYCord();

private:
    /**
     * @brief id
     */
    int id;

    /**
     * @brief id_generator
     */
    static int id_generator;

    /**
     * @brief sender
     */
    BlockEntity *sender;

    /**
     * @brief owner
     */
    BlockEntity *owner;

    /**
     * @brief method
     */
    AttributeEntity  *method = nullptr;

    /**
     * @brief name
     */
    QString name = "";

    /**
     * @brief async
     */
    bool async = true;

    /**
     * @brief y_cord
     */
    int y_cord;
};

#endif // MESSAGE_H
