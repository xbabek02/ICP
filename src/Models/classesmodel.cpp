#include "classesmodel.h"
#include "../Entities/DiagramEntity.h"
#include <QString>
#include <QAbstractListModel>

ClassesModel::ClassesModel(Model*m, QObject *parent)
    : QAbstractListModel(parent), m(m)
{
    loadData();
}

int ClassesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.size();
}

QVariant ClassesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    DiagramEntity *de = m_data.at(index.row());
    if (role == Qt::DisplayRole)
        return QVariant(QString::fromStdString(de->GetName()));
    if (role == Qt::UserRole)
        return QVariant::fromValue(de);
    return QVariant();
}

void ClassesModel::addRow(DiagramEntity* de){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.push_back(de);
    endInsertRows();
}
void ClassesModel::ClearData(){
    beginRemoveRows(QModelIndex(), 0, rowCount());
    m_data.clear();
    endRemoveRows();
}

void ClassesModel::loadData()
{
    auto classes = m->GetEntities();
    ClearData();

    beginInsertRows(QModelIndex(), 0, classes.size());
    for(auto item : classes){
        m_data.push_back(item);
    }
    endInsertRows();

    auto index1 = this->index(0,0,QModelIndex());
    auto index2 = this->index(classes.size(),0,QModelIndex());
    emit dataChanged(index1, index2);
}

void ClassesModel::removeRow(QModelIndex &index){
    int row = index.row();
    beginInsertRows(QModelIndex(), row, row);
    m_data.erase(m_data.begin() + row);
    endInsertRows();
}

void ClassesModel::SetClassDiagModel(Model *m)
{
    this->m = m;
}

Qt::ItemFlags ClassesModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
