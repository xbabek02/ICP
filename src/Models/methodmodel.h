/**
 * @file methodmodel.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Model for List view of methods of selected message in sequence diagram window, contains basic model overrides
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

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
    /**
     * @brief Construct a new Method Model object, consider making a view a parent
     *
     * @param parent
     */
    explicit MethodModel(QObject *parent = nullptr);

    /**
     * @brief Counts the rows of model
     *
     * @param parent
     * @return int count of rows or 0 if root index is not given to the function
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Returns display role mainly of row at given index
     *
     * @param index
     * @param role Qt model role
     * @return QVariant
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Specification of model flags
     *
     * @param index
     * @return Qt::ItemFlags
     */
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void loadData(DiagramEntity *de);
    void removeRow(QModelIndex &index);

    void ClearData();
    void setMessage(MessageItem *mi);
    MessageItem *currently_displayed;

private:
    std::vector<AttributeEntity *> m_data;
};

#endif // METHODMODEL_H
