#ifndef CLASSESMODEL_H
#define CLASSESMODEL_H

#include <QAbstractListModel>
#include "./Entities/DiagramEntity.h"
#include "./Entities/Model.h"
#include <vector>

class ClassesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ClassesModel( Model*m, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void addRow(DiagramEntity*);
    void removeRow(QModelIndex &index);
    void SetClassDiagModel(Model*m);
    void ClearData();

public slots:
    void loadData();

private:
    std::vector<DiagramEntity*> m_data;
    Model*m;
};

#endif // CLASSESMODEL_H
