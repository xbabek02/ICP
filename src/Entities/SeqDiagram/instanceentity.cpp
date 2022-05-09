/**
 * @file seqdscene.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "instanceentity.h"

int InstanceEntity::id_generator = 1;

InstanceEntity::InstanceEntity(QString name, int x_cord, int lineLength, DiagramEntity *instanceClass)
{
    this->id = id_generator;
    id_generator++;

    this->name = name;
    this->instanceClass = instanceClass;
    if (instanceClass != nullptr){
        this->className = QString::fromStdString(instanceClass->GetName());
    }
    else{
        this->className = "@user@";
    }

    this->x_cord = x_cord;
    this->lineLength = lineLength;
    visible = true;
    if(this->instanceClass != nullptr)
        this->instanceClass->AddSeqDiagramInstace(this);
}

void InstanceEntity::SetID(int id)
{
    this->id = id;
}

QString InstanceEntity::GetClassName()
{
    return this->className;
}

void InstanceEntity::AddBlock(BlockEntity *block)
{
    blocks.append(block);
}

void InstanceEntity::RemoveBlock(BlockEntity *block)
{
    for(int i {0}; i < blocks.count(); i++)
    {
        if(blocks[i] == block)
        {
            blocks.removeAt(i);
        }
    }
}

void InstanceEntity::SetVisible(bool visible)
{
    this->visible = visible;
}

void InstanceEntity::SetLineLength(int lineLength)
{
    this->lineLength = lineLength;
}

void InstanceEntity::SetXCord(int x_cord)
{
    this->x_cord = x_cord;
}

void InstanceEntity::SetName(QString name)
{
    this->name = name;
}


DiagramEntity *InstanceEntity::GetInstanceClass()
{
    return instanceClass;
}

QString InstanceEntity::GetName()
{
    return name;
}

QList<BlockEntity*> InstanceEntity::GetBlocks()
{
    return blocks;
}

int InstanceEntity::GetXCord()
{
    return x_cord;
}

int InstanceEntity::GetID()
{
    return id;
}

int InstanceEntity::GetLineLength()
{
    return lineLength;
}

bool InstanceEntity::GetVisible()
{
    return visible;
}

InstanceEntity::~InstanceEntity()
{
}
