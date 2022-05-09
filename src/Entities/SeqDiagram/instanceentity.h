/**
 * @file instanceentity.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Model for instance in the sequence diagram
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef INSTANCEENTITY_H
#define INSTANCEENTITY_H

#include "../DiagramEntity.h"
#include "message.h"
#include "blockentity.h"

class BlockEntity;

class InstanceEntity
{
public:
    /**
     * @brief InstanceEntity is constructor
     * @param name is name of the instance
     * @param x_cord is x position
     * @param lineLength is length of the instance line
     * @param instanceClass is pointer to the class is the main model
     */
    InstanceEntity(QString name, int x_cord, int lineLength, DiagramEntity *instanceClass = nullptr);
    ~InstanceEntity();

    /**
     * @brief GetID
     * @return id of the instance
     */
    int GetID();

    /**
     * @brief SetID sets id of the instance
     * @param id
     */
    void SetID(int id);

    /**
     * @brief AddBlock adds block in list of the block this
     * object owns
     * @param block
     */
    void AddBlock(BlockEntity *block);

    /**
     * @brief RemoveBlock removes block from the block list this
     * object owns
     * @param block
     */
    void RemoveBlock(BlockEntity *block);

    /**
     * @brief SetVisible sets wheter instance is visible
     * @param visible
     */
    void SetVisible(bool visible);

    /**
     * @brief SetLineLength sets length of the sequence line
     * @param lineLength
     */
    void SetLineLength(int lineLength);

    /**
     * @brief SetXCord sets x position
     * @param x_cord
     */
    void SetXCord(int x_cord);

    /**
     * @brief SetName sets name of the instance
     * @param name
     */
    void SetName(QString name);

    /**
     * @brief GetInstanceClass
     * @return pointer to the model of the class of the instance
     */
    DiagramEntity *GetInstanceClass();

    /**
     * @brief GetName
     * @return name of the instance
     */
    QString GetName();

    /**
     * @brief GetBlocks
     * @return list of the block this instance owns
     */
    QList<BlockEntity*> GetBlocks();

    /**
     * @brief GetClassName
     * @return name of the class
     */
    QString GetClassName();

    /**
     * @brief GetXCord
     * @return x position
     */
    int GetXCord();

    /**
     * @brief GetLineLength
     * @return length of the sequence line
     */
    int GetLineLength();

    /**
     * @brief GetVisible
     * @return wheter item is visible
     */
    bool GetVisible();

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
     * @brief instanceClass
     */
    DiagramEntity *instanceClass;

    /**
     * @brief name
     */
    QString name;

    /**
     * @brief className
     */
    QString className;

    /**
     * @brief blocks
     */
    QList<BlockEntity*> blocks;

    /**
     * @brief x_cord
     */
    int x_cord;

    /**
     * @brief lineLength
     */
    int lineLength;

    /**
     * @brief visible
     */
    bool visible = true;
};

#endif // INSTANCEENTITY_H
