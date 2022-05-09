/**
 * @file DiagramEntity.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Class diagram storage entity, is a substitution of database
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __DIAGRAM_ENTITY__
#define __DIAGRAM_ENTITY__

#include <vector>
#include <string>

#include "RelationEntity.h"
#include "ModelObject.h"
#include "../Common/enums.h"
#include <QMetaType>
#include "Model.h"
#include "AttributeEntity.h"
#include "../ClsDiagItems/classdiagramitem.h"
#include "SeqDiagram/instanceentity.h"

class InstanceEntity;
class RelationEntity;
class Model;
class ClassDiagramItem;

class DiagramEntity : public ModelObject
{
private:
    const int ID;
    static int ID_generator;
    int width = 150;
    int firstMethodIndex = 0;

    ClassDiagramItem *thisDiagramItem = nullptr;

    QList<InstanceEntity *> seqDiagramInstances;

    std::string name;
    std::vector<AttributeEntity *> attributes;
    std::vector<RelationEntity *> relations;

public:
    /**
     * @brief Construct a new Diagram Entity object, fills default values in parameters
     *
     */
    DiagramEntity();

    /**
     * @brief Construct a new Diagram Entity object when name is known
     *
     */
    explicit DiagramEntity(std::string name);

    /**
     * @brief Adds Attribute to the class entity
     *
     * @param type type of entity
     * @param data string display value
     */
    void AddAttrib(Enums::Attrib_type type, std::string data);

    /**
     * @brief Get the attribute at given index
     *
     * @param index
     * @return AttributeEntity* pointer to the attribute
     */
    AttributeEntity *GetAttribAt(std::size_t index);

    /**
     * @brief Returns count of attributes
     *
     * @return std::size_t count of attributes
     */
    std::size_t AttribCount();

    /**
     * @brief Updates the attribute at given index
     *
     * @param index of attribute
     * @param new_data new string display value
     */
    inline void UpdateAttribAt(std::size_t index, std::string new_data);

    /**
     * @brief Makes method out of field and the other way around
     *
     * @param index attribute to be changed
     */
    inline void SwitchAttribTypeAt(std::size_t index);

    /**
     * @brief Removes the most bottom attribute of the class
     *
     */
    void RemoveAttribLast();

    /**
     * @brief Removes attribute of the class at specified index
     *
     * @param index
     */
    void RemoveAttribAt(std::size_t index);

    /**
     * @brief Get the attribute Name at index (display value)
     *
     * @param index
     * @return std::string
     */
    std::string GetAttributeName(int index);

    /**
     * @brief Get the Methods of the class
     *
     * @return QList<AttributeEntity *>
     */
    QList<AttributeEntity *> GetMethods();

    /**
     * @brief Adds the instance of a class to the InstanceEntity data model of sequence diagram
     *
     * @param instace pointer to the model of an instance
     */
    void AddSeqDiagramInstace(InstanceEntity *instace);

    /**
     * @brief Removes all the instance of the class
     *
     * @param instace sequence diagram class instance model
     */
    void RemoveSeqDiagramInstace(InstanceEntity *instace);

    /**
     * @brief Get the Seq Diagram Instances object
     *
     * @return QList<InstanceEntity *>
     */
    QList<InstanceEntity *> GetSeqDiagramInstances();

    /**
     * @brief Get the all the connections/relations of an instance
     *
     * @return QList<Connection *>
     */
    QList<Connection *> GetRelationViewItems();

    /**
     * @brief Get the Relations object
     *
     * @return std::vector<RelationEntity *>
     */
    std::vector<RelationEntity *> GetRelations();

    /**
     * @brief Get the graphic representation of an instance
     *
     * @return ClassDiagramItem*
     */
    ClassDiagramItem *GetView();

    /**
     * @brief Get the Name of an class entity
     *
     * @return std::string
     */

    std::string GetName();
    /**
     * @brief Set the Name of an class entity
     *
     */

    void SetName(std::string);
    /**
     * @brief Get the Id of an Entity
     *
     * @return int
     */
    int GetId();

    /**
     * @brief Set the Width of the entity
     *
     * @param value
     */
    void SetWidth(int value);

    /**
     * @brief Get the Width of the entity
     *
     * @return int
     */
    int GetWidth();

    /**
     * @brief Get the First Method index of a class entity
     *
     * @return int
     */
    int GetFirstMethodIndex();

    /**
     * @brief Sets the First Method index of a class entity
     *
     * @param value
     */
    void SetFirstMethodIndex(int value);

    /**
     * @brief Finds the attribute by its name
     *
     * @param data display value (QString)
     * @return AttributeEntity* return value, if not found, nullptr is returned
     */
    AttributeEntity *FindAttributeByData(QString data);

    /**
     * @brief Create a Relation object
     *
     * @param entity second entity
     * @param m model context
     * @return RelationEntity* that was created
     */
    RelationEntity *CreateRelation(DiagramEntity &entity, Model *m); // for use by user

    /**
     * @brief Create a Relation object with all parameters known
     *
     * @param name of relation
     * @param entity second class diagram entity
     * @param type of relation
     * @param site which site is affected by the type
     * @param cardinality1 enum value of cardinality, first side
     * @param cardinality2 enum value of cardinality, second side
     * @param m model context
     * @param node1 0-7 value to specify the joint of relation at first entity
     * @param node2 0-7 value to specify the joint of relation at second entity
     * @param distance distance from entity for singular relation
     * @return RelationEntity*
     */
    RelationEntity *CreateRelation(std::string name, DiagramEntity &entity,
                                   Enums::RelationTypes type, Enums::RelationSide site,
                                   Enums::Cardinalities cardinality1, Enums::Cardinalities cardinality2, Model *m,
                                   int node1, int node2, int distance); // for use from file

    /**
     * @brief Eraser of relation from entities known relations, does not destruct the object
     *
     * @param entity
     * @return true if succeeded
     * @return false if fails
     */
    bool RemoveRelationFromVector(RelationEntity *entity);

    /**
     * @brief Set the graphical representation of an object
     *
     * @param item QGraphicsItem view
     */
    void SetDiagramItem(ClassDiagramItem *item);

    /**
     * @brief Gets the Diagram Item object of class entity
     *
     * @return ClassDiagramItem*
     */
    ClassDiagramItem *GetDiagramItem();

    bool operator==(DiagramEntity &);
    bool operator!=(DiagramEntity &);

    /**
     * @brief Changes the data stored values in model of object, does not affect view directly
     *
     * @param pos_x
     * @param pos_y
     */
    void ChangePosition(int pos_x, int pos_y);

    ~DiagramEntity();
};

Q_DECLARE_METATYPE(DiagramEntity *)

#endif
