#ifndef METHODMODEL_H
#define METHODMODEL_H

#include "./Entities/AttributeEntity.h"

#include "./SeqDiagItems/messageitem.h"
#include <QAbstractListModel>
#include <vector>
#include <QString>

class MethodModel : public QAbstractListModel
{
    Q_OBJECT
public:

    explicit MethodModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void loadData(DiagramEntity*de);
    void removeRow(QModelIndex &index);

    void ClearData();
    void setMessage(MessageItem *mi);
    MessageItem*currently_displayed;
private:
    std::vector<AttributeEntity*>m_data;



};

#endif // METHODMODEL_H
