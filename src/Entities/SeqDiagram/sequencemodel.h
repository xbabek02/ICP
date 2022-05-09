/**
 * @file sequencemodel.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Main model for the sequence diagram
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SEQUENCEMODEL_H
#define SEQUENCEMODEL_H

#include "blockentity.h"
#include "instanceentity.h"
#include "message.h"
#include <QList>
#include "../../ClsDiagItems/classdiagramitem.h"
#include "../DiagramEntity.h"
#include "../../Models/instancesmodel.h"
#include <QFile>
#include <QDomElement>

#include "../../Models/seqdscene.h"
#include "../../SeqDiagItems/instanceitem.h"
#include "../../SeqDiagItems/rectangle.h"
#include "../../SeqDiagItems/messageitem.h"
#include "../../SeqDiagItems/userinstance.h"

#include <map>
#include <sstream>
#include <string>

class SequenceModel
{
public:
    /**
     * @brief SequenceModel
     * @param mainModel is pointer to the model of class diagram
     * @param instances_model is the pointer to the model of instances
     */
    SequenceModel(Model *mainModel, InstancesModel *instances_model = nullptr);

    /**
     * @brief CreateInstance creates new instance
     * @param name is the name of the instance
     * @param x_cord is the initial x position of the instance
     * @param lineLength is initial line length
     * @param instanceClass in the class of the instance
     * @return pointer to the instance
     */
    InstanceEntity *CreateInstance(QString name, int x_cord, int lineLength, DiagramEntity *instanceClass = nullptr);

    /**
     * @brief CreateBlock creates new block
     * @param owner is the instance which owns this block
     * @param y_offset is the y offset from top
     * @param originMessage is the message which created this block
     * @return pointer to the created block
     */
    BlockEntity *CreateBlock(InstanceEntity *owner, int y_offset, Message *originMessage = nullptr);

    /**
     * @brief CreateMessage creates new message
     * @param sender block which sended the message
     * @param owner block who is the owner of message (method)
     * @param y_cord y position
     * @return pointer the message
     */
    Message *CreateMessage(BlockEntity *sender, BlockEntity *owner, int y_cord);

    /**
     * @brief GetInstanceByID
     * @param id
     * @return instance based on the id
     */
    InstanceEntity *GetInstanceByID(int id);

    /**
     * @brief GetMethods
     * @param id
     * @return list of names of the possible methods if the instance
     */
    QList<QString> GetMethods(int id);

    /**
     * @brief GetBlockByID
     * @param id
     * @return block based on the if
     */
    BlockEntity *GetBlockByID(int id);

    /**
     * @brief GetMessageByID
     * @param id
     * @return message based on the id
     */
    Message *GetMessageByID(int id);

    /**
     * @brief GetMainModel
     * @return pointer to the main class diagram model
     */
    Model *GetMainModel();

    /**
     * @brief ConsistencyCheck unused
     */
    void ConsistencyCheck();

    /**
     * @brief RemoveInstance removes instance from the model
     * @param instance
     */
    void RemoveInstance(InstanceEntity *instance);

    /**
     * @brief RemoveBlock removes block from the model
     * @param block
     */
    void RemoveBlock(BlockEntity *block);

    /**
     * @brief RemoveMessage removes message from the model
     * @param message
     */
    void RemoveMessage(Message *message);

    /**
     * @brief Clear delets all the created object
     */
    void Clear();

    /**
     * @brief SaveIntoFile save model data into the file in xml formal
     * @param path
     */
    void SaveIntoFile(const char*path);

    /**
     * @brief LoadFromFile loads model from the file
     * @param path to the file
     * @param model pointer to the main class diagram model
     * @param items created items in class diagram
     * @param change when false, inconsistency fill stop the process of loading
     * @return message of the success
     */
    int LoadFromFile(const char*path, Model *model, QList<ClassDiagramItem*> *items, bool change);

    /**
     * @brief LoadFromAppState load model from the current app state
     */
    void LoadFromAppState();

    /**
     * @brief IterateBlocksRec
     * @param block
     * @return
     */
    BlockEntity *IterateBlocksRec(Rectangle*block);

    /**
     * @brief instancesIdMap
     */
    std::map<int,InstanceEntity*> instancesIdMap;

    /**
     * @brief LoadToAppState loads current model state into the scene
     * @param newscene
     */
    void LoadToAppState(SeqDScene*newscene);

    /**
     * @brief GetBlockList
     * @return list of blocks
     */
    QList<BlockEntity*> GetBlockList();

    /**
     * @brief GetInstanceList
     * @return list of instances
     */
    QList<InstanceEntity *> GetInstanceList();

    /**
     * @brief GetMessageList
     * @return list of messages
     */
    QList<Message *> GetMessageList();

    /**
     * @brief SetInstancesModel sets model of instances
     * @param im
     */
    void SetInstancesModel(InstancesModel *im);

private:
    /**
     * @brief blockEntities
     */
    QList<BlockEntity*> blockEntities;

    /**
     * @brief instanceEntities
     */
    QList<InstanceEntity*> instanceEntities;

    /**
     * @brief messageEntities
     */
    QList<Message*> messageEntities;

    /**
     * @brief mainModel
     */
    Model *mainModel;

    /**
     * @brief instModel
     */
    InstancesModel* instModel;
};

#endif // SEQUENCEMODEL_H
