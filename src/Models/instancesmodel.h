/**
 * @file instancesmodel.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Model for List view of instances in sequence diagram window, contains basic model overrides
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

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
    explicit InstancesModel(QObject *parent = nullptr, UserInstance *UserInstance = nullptr);

    /**
     * @brief Counts the rows of model
     *
     * @param parent
     * @return int count of rows or 0 if root index is not given to the function
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Access function to the model data
     *
     * @param index row specifier
     * @param role DisplayRole - QString name of instance, UserRole - InstanceItem* value of the row
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

    /**
     * @brief Swithces the visibility icon to the opposite value
     *
     * @param ID
     */
    void SwitchVisible(int ID);

    /**
     * @brief Adds the Instance to the model to the end of list
     *
     */
    void addRow(InstanceItem *);

    /**
     * @brief Removes the row at given valid index
     *
     * @param index
     */
    void removeRow(QModelIndex &index);

    /**
     * @brief Get the Data For Read Only purposses
     *
     * @return std::vector<InstanceItem *>
     */
    std::vector<InstanceItem *> GetDataForReadOnly();

    /**
     * @brief Clears the model data
     *
     */
    void ClearData();

private:
    std::vector<InstanceItem *> m_data;
    std::vector<bool> m_data_visible;
};
#endif // INSTANCESMODEL_H
