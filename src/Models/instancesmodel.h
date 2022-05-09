#ifndef INSTANCESMODEL_H
#define INSTANCESMODEL_H

#include "./SeqDiagItems/instanceitem.h"
#include "./SeqDiagItems/userinstance.h"
#include <vector>
#include <QAbstractListModel>


class InstancesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit InstancesModel(QObject *parent = nullptr, UserInstance*UserInstance = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void SwitchVisible(int ID);
    void addRow(InstanceItem*);
    void removeRow(QModelIndex &index);
    std::vector<InstanceItem *> GetDataForReadOnly();
    void ClearData();

private:
    std::vector<InstanceItem*> m_data;
    std::vector<bool> m_data_visible;
};
#endif // INSTANCESMODEL_H
