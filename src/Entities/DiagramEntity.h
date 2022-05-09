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

/**
 * @brief The DiagramEntity class
 * Represents stored data of relation entities
 * Data stored are used for both class diagram and sequence diagram entities
 */
class DiagramEntity : public ModelObject
{
private:
    const int ID;
    static int ID_generator;
    //*******************
    int width = 150;
    //*******************
    int firstMethodIndex = 0;

    ClassDiagramItem *thisDiagramItem = nullptr;

    QList<InstanceEntity*> seqDiagramInstances;

    std::string name;
    std::vector<AttributeEntity *> attributes;
    std::vector<RelationEntity *> relations;

public:
    DiagramEntity();
    explicit DiagramEntity(std::string);

    void AddAttrib(Enums::Attrib_type, std::string);
    AttributeEntity*GetAttribAt(std::size_t index);
    std::size_t AttribCount();
    inline void UpdateAttribAt(std::size_t, std::string new_data);
    inline void SwitchAttribTypeAt(std::size_t);
    void RemoveAttribLast();
    void RemoveAttribAt(std::size_t);
    std::string GetAttributeName(int index);
    QList<AttributeEntity*> GetMethods();

    void AddSeqDiagramInstace(InstanceEntity *instace);
    void RemoveSeqDiagramInstace(InstanceEntity *instace);
    QList<InstanceEntity*> GetSeqDiagramInstances();

    QList<Connection*> GetRelationViewItems();

    ClassDiagramItem *GetView();

    std::string GetName();
    void SetName(std::string);
    int GetId();
    void SetWidth(int value);
    int GetWidth();
    int GetFirstMethodIndex();
    void SetFirstMethodIndex(int value);

    AttributeEntity *FindAttributeByData(QString data);

    RelationEntity *CreateRelation(DiagramEntity &, Model *); // for use by user
    RelationEntity *CreateRelation(std::string, DiagramEntity &,
                                   Enums::RelationTypes, Enums::RelationSide,
                                   Enums::Cardinalities, Enums::Cardinalities, Model *,
                                   int node1, int node2, int distance); // for use from file
    bool RemoveRelationFromVector(RelationEntity *);

    void SetDiagramItem(ClassDiagramItem *item);
    ClassDiagramItem *GetDiagramItem();

    bool operator==(DiagramEntity &);
    bool operator!=(DiagramEntity &);

    void ChangePosition(int pos_x, int pos_y);

    ~DiagramEntity();
};

Q_DECLARE_METATYPE(DiagramEntity*)

#endif
