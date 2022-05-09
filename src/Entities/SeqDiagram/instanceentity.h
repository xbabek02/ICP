#ifndef INSTANCEENTITY_H
#define INSTANCEENTITY_H

#include "../DiagramEntity.h"
#include "message.h"
#include "blockentity.h"

class BlockEntity;

class InstanceEntity
{
public:
    InstanceEntity(QString name, int x_cord, int lineLength, DiagramEntity *instanceClass = nullptr);
    ~InstanceEntity();
    int GetID();
    void SetID(int id);
    void AddBlock(BlockEntity *block);
    void RemoveBlock(BlockEntity *block);
    void SetVisible(bool visible);
    void SetLineLength(int lineLength);
    void SetXCord(int x_cord);
    void SetName(QString name);
    DiagramEntity *GetInstanceClass();
    QString GetName();
    QList<BlockEntity*> GetBlocks();
    QString GetClassName();
    int GetXCord();
    int GetLineLength();
    bool GetVisible();

private:
    int id;
    static int id_generator;
    DiagramEntity *instanceClass;
    QString name;
    QString className;
    QList<BlockEntity*> blocks;
    int x_cord;
    int lineLength;
    bool visible = true;
};

#endif // INSTANCEENTITY_H
