#include <QXmlStreamReader>
#include <QtXml>
#include <QTextStream>
#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include <QString>

#include "../Entities/Model.h"
#include "../Common/enums.h"

#include <map>
#include <sstream>
#include <string>

 void Model::SaveToFile(const char*path){
    QFile xmlFile(path);
    if (!xmlFile.open(QFile::WriteOnly | QFile::Text ))
    {
        qDebug() << "Already opened or there is another issue";
        xmlFile.close();
    }
    QTextStream xmlContent(&xmlFile);

    QDomDocument document;

    QDomElement root = document.createElement("ClassDiagram");
    document.appendChild(root);

    QDomElement classes = document.createElement("Classes");
    root.appendChild(classes);

    QDomElement class_entity;
    AttributeEntity*at_entity;
    QDomElement attribute;

    for (DiagramEntity *entity : this->entities){
        class_entity = document.createElement(QString::fromStdString("Entity"));
        class_entity.setAttribute("ID", entity->GetId());
        class_entity.setAttribute("name", QString::fromStdString(entity->GetName()));
        class_entity.setAttribute("pos_x", entity->GetPosX());
        class_entity.setAttribute("pos_y", entity->GetPosY());

        for (std::size_t i = 0; i < entity->AttribCount(); i++){
            at_entity = entity->GetAttribAt(i);

            //set attribute data
            attribute = document.createElement(QString::fromStdString("Attribute"));
            attribute.setAttribute("type", at_entity->GetType() == Enums::Attrib_type::field ? "field" : "method");

            attribute.appendChild(document.createTextNode(QString::fromStdString(at_entity->GetData())));

            //insert attribute to the XML
            class_entity.appendChild(attribute);
        }
        classes.appendChild(class_entity);
    }

    QDomElement relations = document.createElement("Relations");
    root.appendChild(relations);

    QDomElement relation_entity;

    for (RelationEntity* entity : this->relations){
        relation_entity = document.createElement(QString::fromStdString("Relation"));
        relation_entity.setAttribute("name", QString::fromStdString(entity->GetName()));
        auto entities = entity->GetEntites();

        relation_entity.setAttribute("ID_first", entities.first->GetId());
        relation_entity.setAttribute("ID_second", entities.second->GetId());

        auto cards = entity->GetCardinalities();
        relation_entity.setAttribute("card_first", Enums::CardinalityToLiteral(cards.first));
        relation_entity.setAttribute("card_second", Enums::CardinalityToLiteral(cards.second));

        relation_entity.setAttribute("type", Enums::TypeToLiteral(entity->GetType()));
        relation_entity.setAttribute("side", entity->GetSide() == Enums::RelationSide::first ? "first" : "second");
        relation_entity.setAttribute("node1", entity->GetNode1());
        relation_entity.setAttribute("node2", entity->GetNode2());

        if (entities.first->GetId() == entities.second->GetId()){
            relation_entity.setAttribute("distance", entity->GetDistance());
        }

        relations.appendChild(relation_entity);
    }

    //writing the content to the file
    xmlContent << document.toString();
    xmlFile.close();
}

bool Model::LoadFromFile(const char*path){
    QDomDocument classXML;
       QFile xmlFile(path);
       if (!xmlFile.open(QIODevice::ReadOnly ))
       {
           // Error while loading file
       }
       classXML.setContent(&xmlFile);
       xmlFile.close();

       QDomElement root = classXML.documentElement();
       QDomElement node = root.firstChild().toElement();
       QDomElement subnode;
       std::stringstream ss;

       std::map<QString, int> id_map;

       //there can be Classes and Relations
       while(node.isNull() == false)
       {
           if(node.tagName() == "Classes"){
               subnode = node.firstChild().toElement();
               int entity_cnt = 1;

               //there can be Entity
               while(!subnode.isNull()){
                   if (subnode.tagName() == "Entity"){
                        QString id = subnode.attribute("ID","0");
                        QString name = subnode.attribute("name","name");
                        QString pos_x = subnode.attribute("pos_x", std::to_string(Model::default_pos_x).c_str());
                        QString pos_y = subnode.attribute("pos_y", std::to_string(Model::default_pos_y).c_str());

                        //checks and conversions
                        int pos_x_conv;
                        int pos_y_conv;

                        ss.str("");
                        ss.clear();

                        //converting position x
                        ss << pos_x.toStdString();
                        ss >> pos_x_conv;

                        if (pos_x != "0"){ //checking position x value
                            pos_x_conv = (!pos_x_conv ? default_pos_x : pos_x_conv);
                        }

                        ss.str("");
                        ss.clear();

                        //converting position y
                        ss << pos_y.toStdString();
                        ss >> pos_y_conv;

                        if (pos_y != "0"){ //checking position y value
                            pos_y_conv = (!pos_y_conv ? default_pos_y : pos_y_conv);
                        }

                        auto e = this->CreateEntity(name.toStdString(), pos_x_conv, pos_y_conv);
                        id_map.insert(std::pair<QString, int>(id, e->GetId())); //link between file id and real id


                        for (auto a_node = subnode.firstChildElement(); !a_node.isNull(); a_node = a_node.nextSiblingElement()){
                            if (a_node.tagName() == "Attribute"){
                                QString type = a_node.attribute("type", "field");
                                Enums::Attrib_type type_conv = (type == "method" ? Enums::Attrib_type::method : Enums::Attrib_type::field);
                                std::string data = a_node.text().toStdString();
                                e->AddAttrib(type_conv, data);
                            }
                        }
                    }
                    subnode = subnode.nextSibling().toElement();
                    entity_cnt++;
              }
           }

           else if (node.tagName() == "Relations"){
               subnode = node.firstChild().toElement();
               //there can be Relation
               while(!subnode.isNull()){
                    QString name = subnode.attribute("name","<<empty>>");
                    QString ID_first = subnode.attribute("ID_first", "0");
                    QString ID_second = subnode.attribute("ID_second", "0");
                    QString card_first = subnode.attribute("card_first", "one");
                    QString card_second = subnode.attribute("card_second", "one");
                    QString type = subnode.attribute("type", "asociation");
                    QString side = subnode.attribute("side", "first");
                    QString node1 = subnode.attribute("node1", "0");
                    QString node2 = subnode.attribute("node2", "0");
                    QString distance = subnode.attribute("distance", "0");

                    auto card1_conv = Enums::LiteralToCardinality(card_first.toStdString().c_str());
                    auto card2_conv = Enums::LiteralToCardinality(card_second.toStdString().c_str());
                    Enums::RelationSide side_conv = side == "second" ? Enums::RelationSide::second : Enums::RelationSide::first;

                    int node1_conv, node2_conv, dist_conv;

                    ss.str("");
                    ss.clear();

                    ss << node1.toStdString();
                    ss >> node1_conv;

                    ss.str("");
                    ss.clear();

                    ss << node2.toStdString();
                    ss >> node2_conv;

                    ss.str("");
                    ss.clear();

                    ss << distance.toStdString();
                    ss >> dist_conv;

                    auto type_conv = Enums::LiteralToType(type.toStdString().c_str());

                    this->CreateRelationById(name.toStdString(), id_map.at(ID_first), id_map.at(ID_second),
                                             type_conv, side_conv,card1_conv,card2_conv, node1_conv, node2_conv, dist_conv);
                    subnode = subnode.nextSibling().toElement();
               }
           }
           node = node.nextSibling().toElement();
       }
       return true;
   }
