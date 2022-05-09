/**
 * @file blockentity.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Model of the block in sequence diagram
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

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
    /**
     * @brief BlockEntity is constructor
     * @param owner is owning instance of the block
     * @param y_offset if offsed from the upper side
     * @param originMessage is the message which created this block, null when initial block
     */
    BlockEntity(InstanceEntity *owner, int y_offset, Message *originMessage = nullptr);

    /**
     * @brief GetID
     * @return id of the block
     */
    int GetID();

    /**
     * @brief SetID sets id of the block
     * @param id
     */
    void SetID(int id);

    /**
     * @brief SetAddedLength set added length of the block
     * @param addedLength
     */
    void SetAddedLength(int addedLength);

    /**
     * @brief SetYOffset sets new y offset
     * @param y_offset
     */
    void SetYOffset(int y_offset);

    /**
     * @brief SetHasReturnMessage sets wheter block has return message
     * @param hasReturnMessage
     */
    void SetHasReturnMessage(bool hasReturnMessage);

    /**
     * @brief SetOriginMessage sets message which created this block
     * @param originMessage
     */
    void SetOriginMessage(Message *originMessage);

    /**
     * @brief GetOriginMessage
     * @return message which created this block
     */
    Message *GetOriginMessage();

    /**
     * @brief GetMessages
     * @return messages which come out the block
     */
    QList<Message*> GetMessages();

    /**
     * @brief GetOwner
     * @return instance which owns this block
     */
    InstanceEntity *GetOwner();

    /**
     * @brief SetOwner sets instance which owns this block
     * @param owner
     */
    void SetOwner(InstanceEntity *owner);

    /**
     * @brief GetAddedLength
     * @return added length of the block
     */
    int GetAddedLength();

    /**
     * @brief GetYOffset
     * @return y offset
     */
    int GetYOffset();

    /**
     * @brief HasReturnMessage
     * @return wheter block has return message
     */
    bool HasReturnMessage();

    /**
     * @brief AddMessage adds new message to the message list
     * @param message
     */
    void AddMessage(Message *message);

    /**
     * @brief RemoveMessage removes message from the message list
     * @param message
     */
    void RemoveMessage(Message *message);

    /**
     * @brief SetOriginMessageID sets id of message which created this block
     * @param messageID
     */
    void SetOriginMessageID(int messageID);

    /**
     * @brief GetOriginMessageID
     * @return id of message which created this block
     */
    int GetOriginMessageID();

private:
    /**
     * @brief id
     */
    int id;

    /**
     * @brief originMessageID
     */
    int originMessageID = 0;

    /**
     * @brief id_generator
     */
    static int id_generator;

    /**
     * @brief originMessage
     */
    Message *originMessage = nullptr;

    /**
     * @brief messages
     */
    QList<Message*> messages;

    /**
     * @brief owner
     */
    InstanceEntity *owner;

    /**
     * @brief addedLength
     */
    int addedLength = 0;

    /**
     * @brief y_offset
     */
    int y_offset;

    /**
     * @brief hasReturnMessage
     */
    bool hasReturnMessage = false;
};

#endif // BLOCKENTITY_H
