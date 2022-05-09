/**
 * @file methodmodel.cpp
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Model for List view of methods of selected message in sequence diagram window, contains basic model overrides
 * @version 0.1
 * @date 2022-05-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "methodmodel.h"
#include "../Entities/DiagramEntity.h"
#include "../Entities/AttributeEntity.h"
#include <QString>
#include <QAbstractListModel>

MethodModel::MethodModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int MethodModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant MethodModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QString method_name = QString::fromStdString(m_data.at(index.row())->GetData());
    if (role == Qt::DisplayRole)
        return QVariant(method_name);
    return QVariant();
}

void MethodModel::removeRow(QModelIndex &index){
    int row = index.row();
    beginRemoveRows(QModelIndex(), row, row);
    m_data.erase(m_data.begin() + row);
    endRemoveRows();
}

Qt::ItemFlags MethodModel::flags(const QModelIndex &index) const
{
    // I ought to handle !index.isValid(), but again just a demo.
    return QAbstractListModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void MethodModel::ClearData(){
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_data.clear();
    endRemoveRows();
}

void MethodModel::loadData(DiagramEntity *de)
{
    if (!de){
        return;
    }

    ClearData();
    beginInsertRows(QModelIndex(), 0, de->AttribCount());
    for (std::size_t i = 0; i < de->AttribCount(); i++){
        AttributeEntity*ae = de->GetAttribAt(i);
        if (ae->IsMethod()){
            m_data.push_back(ae);
        }

    }
    endInsertRows();
}

void MethodModel::setMessage(MessageItem*mi){
    if (mi == currently_displayed){
        return;
    }
    currently_displayed = mi;

    if (!mi->owner){
        return;
    }
    if (!mi->owner->instance){
        ClearData();
        return;
    }
    loadData(mi->owner->instance->classEntity);
}
