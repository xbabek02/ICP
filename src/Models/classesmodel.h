/**
 * @file classesmodel.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Model for List view of classes in sequence diagram window, contains basic model overrides
 * @version 0.1
 * @date 2022-05-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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

    /**
     * @brief Counts the rows of model
     * 
     * @param parent 
     * @return int count of rows or 0 if root index is not given to the function
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    
    /**
     * @brief Returns data based on role, UserRole returns whole DiagramEntity* to the item
     * 
     * @param index must be valid of a list
     * @param role DisplayRole or UserRole
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
     * @brief Adds the DiagramEntity class to the model to the end of list
     * 
     */
    void addRow(DiagramEntity*);

    /**
     * @brief Removes the row at given valid index
     * 
     * @param index 
     */
    void removeRow(QModelIndex &index);

    /**
     * @brief Set the Class Diagram Model object reference
     * 
     * @param m 
     */
    void SetClassDiagModel(Model*m);

    /**
     * @brief Clears the model data
     * 
     */
    void ClearData();

public slots:
    /**
     * @brief Loads the data from Class Diagram Model
     * 
     */
    void loadData();

private:
    std::vector<DiagramEntity*> m_data;
    Model*m;
};

#endif // CLASSESMODEL_H
