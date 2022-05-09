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
    SequenceModel(Model *mainModel, InstancesModel *instances_model = nullptr);
    InstanceEntity *CreateInstance(QString name, int x_cord, int lineLength, DiagramEntity *instanceClass = nullptr);
    BlockEntity *CreateBlock(InstanceEntity *owner, int y_offset, Message *originMessage = nullptr);
    Message *CreateMessage(BlockEntity *sender, BlockEntity *owner, int y_cord);
    InstanceEntity *GetInstanceByID(int id);
    BlockEntity *GetBlockByID(int id);
    Message *GetMessageByID(int id);
    Model *GetMainModel();
    void ConsistencyCheck();
    void RemoveInstance(InstanceEntity *instance);
    void RemoveBlock(BlockEntity *block);
    void RemoveMessage(Message *message);
    void Clear();
    void SaveIntoFile(const char*path);
    int LoadFromFile(const char*path, Model *model, QList<ClassDiagramItem*> *items, bool change);
    void Test(QGraphicsScene *scene, QList<ClassDiagramItem*> items);
    void LoadFromAppState();
    BlockEntity *IterateBlocksRec(Rectangle*block);
    std::map<int,InstanceEntity*> instancesIdMap;
    void LoadToAppState(SeqDScene*newscene);
    QList<BlockEntity*> GetBlockList();
    QList<InstanceEntity *> GetInstanceList();
    QList<Message *> GetMessageList();
    void SetInstancesModel(InstancesModel *im);

private:
    QList<BlockEntity*> blockEntities;
    QList<InstanceEntity*> instanceEntities;
    QList<Message*> messageEntities;
    Model *mainModel;
    InstancesModel* instModel;
};

#endif // SEQUENCEMODEL_H
