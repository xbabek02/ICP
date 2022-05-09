/**
 * @file instancesmodel.cpp
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Model for List view of instances in sequence diagram window, contains basic model overrides
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "instancesmodel.h"
#include "../SeqDiagItems/userinstance.h"
#include "../SeqDiagItems/instanceitem.h"
#include <QVector>
#include <QIcon>
#include <QColor>

InstancesModel::InstancesModel(QObject *parent, UserInstance *user)
    : QAbstractListModel(parent)
{
    m_data.push_back(user);
    m_data_visible.push_back(true);
}

int InstancesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.size();
}

void InstancesModel::ClearData()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_data.clear();
    m_data_visible.clear();
    endRemoveRows();
}

QVariant InstancesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    InstanceItem *ii = m_data.at(index.row());
    if (!ii)
    {
        return QVariant();
    }
    if (role == Qt::DisplayRole)
        return QVariant::fromValue(ii->text_name);
    if (role == Qt::UserRole)
        return QVariant::fromValue(ii);
    if (role == Qt::DecorationRole)
    {
        if (m_data_visible.at(index.row()))
        {
            return QVariant::fromValue(QColor("blue"));
        }
        return QVariant::fromValue(QColor("gray"));
    }
    return QVariant();
}

void InstancesModel::SwitchVisible(int ID)
{
    int i = 0;
    for (InstanceItem *item : m_data)
    {
        if (item->GetID() == ID)
        {
            m_data_visible.at(i) = !m_data_visible.at(i);
        }
        i++;
    }
    auto index = this->index(i, 0, QModelIndex());
    emit dataChanged(index, index);
}

void InstancesModel::addRow(InstanceItem *ii)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.push_back(ii);
    m_data_visible.push_back(true);
    endInsertRows();
}

void InstancesModel::removeRow(QModelIndex &index)
{
    int row = index.row();
    beginRemoveRows(QModelIndex(), row, row);
    m_data.erase(m_data.begin() + row);
    m_data_visible.erase(m_data_visible.begin() + row);
    endRemoveRows();
}

std::vector<InstanceItem *> InstancesModel::GetDataForReadOnly()
{
    return m_data;
}

Qt::ItemFlags InstancesModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
