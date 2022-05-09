/**
 * @file RelationEntity.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Storage entity for relation data
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __RELATION_ENTITY__
#define __RELATION_ENTITY__

#include <string>
#include "DiagramEntity.h"
#include "../Common/enums.h"
#include "../ClsDiagItems/connection.h"
#include "../ClsDiagItems/singletonconnection.h"

class Connection;
class DiagramEntity;
class SingletonConnection;

/**
 * @brief The RelationEntity class
 * Stores data for relations
 */
class RelationEntity
{
private:
    static int ID_generator;
    int ID;
    std::string relation_name;

    Connection *thisViewItem;
    SingletonConnection *thisSingletonView;

    DiagramEntity *first, *second, *relation_diagramEntity;

    Enums::Cardinalities cardinality1, cardinality2;

    Enums::RelationTypes type;
    Enums::RelationSide side;

    int node1, node2;
    int distance = 0; // used only for relation between the same class

    std::pair<DiagramEntity *, DiagramEntity *> enitites;
    std::pair<Enums::Cardinalities, Enums::Cardinalities> cardinalities;

public:
    RelationEntity(std::string, DiagramEntity *, DiagramEntity *,
                   Enums::RelationTypes, Enums::RelationSide,
                   Enums::Cardinalities, Enums::Cardinalities,
                   int node1, int node2, int distance); // for creating from file
    RelationEntity(DiagramEntity *, DiagramEntity *);   // for creating by user

    bool inline HasRelationEntity();
    void AddRelationEntity();
    void AddRelationEntity(DiagramEntity *);

    int GetId();
    std::string GetName();
    bool SetName(std::string);
    std::pair<DiagramEntity *, DiagramEntity *> &GetEntites();

    void ChangeCardinality1(Enums::Cardinalities);
    void ChangeCardinality2(Enums::Cardinalities);
    std::pair<Enums::Cardinalities, Enums::Cardinalities> GetCardinalities();

    void SetThisViewItem(Connection *thisViewItem);

    void SetSingletonViewItem(SingletonConnection *thisViewItem);
    SingletonConnection *GetSingletonViewItem();

    int GetNode1();
    int GetNode2();
    int GetDistance();

    void ChangeNode1(int);
    void ChangeNode2(int);
    void ChangeDistance(int);

    void SwitchRelationSide();
    Enums::RelationSide GetSide();

    void SetRelationType(Enums::RelationTypes);
    Enums::RelationTypes GetType();

    bool operator==(RelationEntity &other);
    bool operator!=(RelationEntity &other);

    Connection *GetViewItem();

    ~RelationEntity();

    class ReplacingRelationEntityException
    {
    };
};

#endif
