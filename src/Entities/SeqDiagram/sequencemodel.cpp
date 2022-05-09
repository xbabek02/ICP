#include "sequencemodel.h"
#include "../../Common/enums.h"
#include "../../ClassDiagramCommands/createclasscommand.h"

SequenceModel::SequenceModel(Model *mainModel, InstancesModel *instances_model)
{
    this->mainModel = mainModel;
    this->instModel = instances_model;
}

QList<BlockEntity *> SequenceModel::GetBlockList()
{
    return this->blockEntities;
}

QList<InstanceEntity *> SequenceModel::GetInstanceList()
{
    return this->instanceEntities;
}

QList<Message *> SequenceModel::GetMessageList()
{
    return this->messageEntities;
}

void SequenceModel::SetInstancesModel(InstancesModel *im)
{
    instModel = im;
}

void SequenceModel::LoadFromAppState()
{
    //loading Instances
    instancesIdMap.clear();
    auto instances = instModel->GetDataForReadOnly();
    for (InstanceItem *item : instances){
        InstanceEntity* ie = this->CreateInstance(item->text_name, item->scenePos().x(), item->length, item->classEntity);
        instancesIdMap.emplace(item->GetID(), ie);
    }
    if (Rectangle::initial_block){
        IterateBlocksRec(Rectangle::initial_block);
    }

}

BlockEntity *SequenceModel::IterateBlocksRec(Rectangle*block)
{
    auto b1 = CreateBlock(instancesIdMap.at(block->instance->GetID()), block->vertical_offset, nullptr);
    instancesIdMap.at(block->instance->GetID())->AddBlock(b1); //adding block to the instance
    b1->SetHasReturnMessage(block->return_message != nullptr);
    b1->SetAddedLength(block->addedLength);

    for (auto message :block->sent){
        auto b2 = IterateBlocksRec(message->owner); //recursive call
        auto m = CreateMessage(b1, b2, message->owner->GetStartOfBlock());
        m->SetAsync(message->type == Enums::MessageTypes::async);
        m->SetName(message->method_str);
        if (message->method_str != "<No Method>"){
            if (message->owner->instance != nullptr)
            m->SetMethod(mainModel->GetAttributeEntityByName(b2->GetOwner()->GetInstanceClass(), message->method_str.toStdString()));
        }
        else{
            m->SetMethod(nullptr);
        }

        b2->SetOriginMessage(m);
    }
    return b1;
}

void SequenceModel::LoadToAppState(SeqDScene*newscene)
{
    std::map<InstanceEntity*, InstanceItem*> instanceMap;
    std::map<int, Rectangle*> rectIdMap;
    instModel->ClearData();

    //generating instances
    for (auto instance : GetInstanceList()){
        InstanceItem*ii;
        if (instance->GetInstanceClass()){
            ii = new InstanceItem(nullptr, instance->GetInstanceClass(), QString::fromStdString(instance->GetInstanceClass()->GetName()));
            ii->text_name = instance->GetName();
        }
        else {
            ii = new UserInstance();
        }

        ii->length = instance->GetLineLength();
        ii->moveBy(instance->GetXCord(), 0);
        instModel->addRow(ii);
        newscene->addItem(ii);
        instanceMap.emplace(instance, ii);
        ii->visible = instance->GetVisible();
        ii->setVisible(instance->GetVisible());

        //generating blocks for instances
        for (auto block : instance->GetBlocks()){
            auto rect_item = new Rectangle(ii,nullptr,block->GetYOffset());
            rect_item->setVisible(instance->GetVisible());
            rect_item->addedLength = block->GetAddedLength();
            rect_item->instance = ii;
            rectIdMap.emplace(block->GetID(), rect_item);
        }
    }

    //generating messages
    for (auto messageEnt : GetMessageList()){
        Rectangle *owner = rectIdMap.at(messageEnt->GetOwner()->GetID());
        Rectangle *sender = rectIdMap.at(messageEnt->GetSender()->GetID());
        auto mi = new MessageItem(messageEnt->GetAsync()? Enums::MessageTypes::async : Enums::MessageTypes::sync, sender, messageEnt->GetYCord());
        owner->origin = mi;
        sender->sent.append(mi);
        mi->owner = owner;
        mi->setVisible(mi->sender->isVisible());
        mi->method_str = messageEnt->GetName();
        mi->solid = true;
        int sender_x = sender->instance->scenePos().x();
        int owner_x = owner->instance->scenePos().y();
        int offset = sender->instance->width/2;
        offset += sender_x < owner_x ? - Rectangle::width/2 : sender->width/2;
        mi->setLine(sender->instance->scenePos().x() + offset, mi->line().y1(), owner->instance->scenePos().x() + offset - Rectangle::width, mi->line().y2());
        newscene->addItem(mi);
    }

    //generating return messages
    for (auto block : GetBlockList()){
        Rectangle*rect = rectIdMap.at(block->GetID());
        if (block->HasReturnMessage()){
            auto mi = new MessageItem(Enums::MessageTypes::returnal, rect, rect->GetEndOfBlock());
            rect->return_message = mi;
            Rectangle*owner = rect->origin->sender;
            owner->returning_messages.append(mi);
            mi->owner = owner;
            mi->solid = true;
            newscene->addItem(mi);
        }
    }

    //setting initial block
    BlockEntity*initialBlock;
    for (auto block : GetBlockList()){
        if (block->GetOriginMessage() == nullptr){
            initialBlock = block;
            break;
        }
    }
    if (!this->blockEntities.isEmpty()){
        Rectangle::initial_block = rectIdMap.at(initialBlock->GetID());
        Rectangle::initial_block->origin = nullptr;
    }
}

InstanceEntity *SequenceModel::CreateInstance(QString name, int x_cord, int lineLength, DiagramEntity *instanceClass)
{
    auto newInstance = new InstanceEntity(name, x_cord, lineLength, instanceClass);
    instanceEntities.append(newInstance);
    return newInstance;
}

BlockEntity *SequenceModel::CreateBlock(InstanceEntity *owner, int y_offset, Message *originMessage)
{
    auto newBlock = new BlockEntity(owner, y_offset, originMessage);
    blockEntities.append(newBlock);
    return newBlock;
}

Message *SequenceModel::CreateMessage(BlockEntity *sender, BlockEntity *owner, int y_cord)
{
    auto newMessage = new Message(sender, owner, y_cord);
    messageEntities.append(newMessage);
    return newMessage;
}

InstanceEntity *SequenceModel::GetInstanceByID(int id)
{
    for(auto instance : instanceEntities)
    {
        if(instance->GetID() == id)
            return instance;
    }
    return nullptr;
}

BlockEntity *SequenceModel::GetBlockByID(int id)
{
    for(auto block : blockEntities)
    {
        if(block->GetID() == id)
            return block;
    }
    return nullptr;
}

Message *SequenceModel::GetMessageByID(int id)
{
    for(auto message : messageEntities)
    {
        if(message->GetID() == id)
            return message;
    }
    return nullptr;
}

void SequenceModel::RemoveInstance(InstanceEntity *instance)
{
    if(instance->GetInstanceClass() != nullptr)
        instance->GetInstanceClass()->RemoveSeqDiagramInstace(instance);

    for(int i {0}; i < instance->GetBlocks().count(); i++)
    {
        this->RemoveBlock(instance->GetBlocks()[i]);
    }

    for(int i {0}; i < instanceEntities.count(); i++)
    {
        if(instanceEntities[i] == instance)
        {
            instanceEntities.removeAt(i);
        }
    }
}

void SequenceModel::RemoveBlock(BlockEntity *block)
{
    block->GetOwner()->RemoveBlock(block);

    for(auto message : block->GetMessages())
    {
        this->RemoveMessage(message);
    }

    for(int i {0}; i < blockEntities.count(); i++)
    {
        if(blockEntities[i] == block)
        {
            blockEntities.removeAt(i);
        }
    }

    delete block;
}

void SequenceModel::RemoveMessage(Message *message)
{
    message->GetOwner()->RemoveMessage(message);
    message->GetSender()->RemoveMessage(message);

    for(int i {0}; i < messageEntities.count(); i++)
    {
        if(messageEntities[i] == message)
        {
            messageEntities.removeAt(i);
        }
    }

    delete message;
}

QList<QString> SequenceModel::GetMethods(int id)
{
    auto entity = mainModel->GetEntityById(id);
    QList<QString> methodNames;
    for(auto method : entity->GetMethods())
        methodNames.append(QString::fromStdString(method->GetData()));
    return methodNames;
}

void SequenceModel::Clear()
{
    for(auto instance : instanceEntities)
        delete instance;
   instanceEntities.clear();
    for(auto block : blockEntities)
        delete block;
    blockEntities.clear();
    for(auto message : messageEntities)
        delete message;
    messageEntities.clear();
    instancesIdMap.clear();
}

void SequenceModel::ConsistencyCheck()
{
    for(auto instance : instanceEntities)
    {
        for(auto block : instance->GetBlocks())
        {
        }
    }
}

void SequenceModel::SaveIntoFile(const char*path)
{
    QFile xmlFile(path);
    if (!xmlFile.open(QFile::WriteOnly | QFile::Text ))
    {
        qDebug() << "Already opened or there is another issue";
        xmlFile.close();
    }
    QTextStream xmlContent(&xmlFile);

    QDomDocument document;

    QDomElement root = document.createElement("SequenceDiagram");
    document.appendChild(root);

    QDomElement instances = document.createElement("Instances");
    root.appendChild(instances);

    QDomElement instace_entity;

    for (auto instance : this->instanceEntities){
        int id_aux = -1;
        if (instance->GetInstanceClass()){
            id_aux = instance->GetInstanceClass()->GetId();
        }

        instace_entity = document.createElement(QString::fromStdString("Instance"));
        instace_entity.setAttribute("id", instance->GetID());
        instace_entity.setAttribute("class_id", id_aux);
        instace_entity.setAttribute("name", instance->GetName());
        instace_entity.setAttribute("x_cord", instance->GetXCord());
        instace_entity.setAttribute("class_name", instance->GetClassName());
        instace_entity.setAttribute("line_length", instance->GetLineLength());
        instace_entity.setAttribute("visible", instance->GetVisible());
        instances.appendChild(instace_entity);
    }

    QDomElement blocks = document.createElement("Blocks");
    root.appendChild(blocks);

    QDomElement block_entity;

    for (BlockEntity* block : this->blockEntities)
    {
        block_entity = document.createElement(QString::fromStdString("Block"));
        block_entity.setAttribute("id", block->GetID());
        block_entity.setAttribute("owner_id", block->GetOwner()->GetID());
        block_entity.setAttribute("added_length", block->GetAddedLength());
        block_entity.setAttribute("y_offset", block->GetYOffset());
        block_entity.setAttribute("has_return_message", block->HasReturnMessage());
        if(block->GetOriginMessage() != nullptr)
            block_entity.setAttribute("origin_message_id", block->GetOriginMessage()->GetID());
        else
            block_entity.setAttribute("origin_message_id", "nullptr");
        blocks.appendChild(block_entity);
    }

    QDomElement messages = document.createElement("Messages");
    root.appendChild(messages);

    QDomElement message_entity;

    for (auto message : this->messageEntities){
        message_entity = document.createElement(QString::fromStdString("Message"));
        message_entity.setAttribute("id", message->GetID());
        message_entity.setAttribute("name", message->GetName());
        message_entity.setAttribute("sender_id", message->GetSender()->GetID());
        message_entity.setAttribute("owner_id", message->GetOwner()->GetID());
        message_entity.setAttribute("async", message->GetAsync());
        message_entity.setAttribute("y_cord", message->GetYCord());
        messages.appendChild(message_entity);
    }

    //writing the content to the file
    xmlContent << document.toString();
    xmlFile.close();
}


Model *SequenceModel::GetMainModel()
{
    return mainModel;
}

int SequenceModel::LoadFromFile(const char*path, Model *model, QList<ClassDiagramItem*> *items, bool change)
{
    QList<std::pair<int, int>> newIDs;
    QDomDocument classXML;
    QFile xmlFile(path);
    if (!xmlFile.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        return -1;
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
        if(node.tagName() == "Instances")
        {
            subnode = node.firstChild().toElement();
            //there can be Relation
            while(!subnode.isNull())
            {
                QString id = subnode.attribute("id");
                QString class_id = subnode.attribute("class_id");
                QString name = subnode.attribute("name");
                QString class_name = subnode.attribute("class_name");
                QString x_cord = subnode.attribute("x_cord");
                QString line_length = subnode.attribute("line_length");
                QString visible = subnode.attribute("visible");


                for(auto pair : newIDs)
                {
                    if(class_id.toInt() == pair.first)
                    {
                        class_id = QString::number(pair.second);
                    }
                }

                DiagramEntity *entity;
                if(mainModel->GetEntities().size() != 0)
                    entity = mainModel->GetEntityById(class_id.toInt());
                else
                    entity = nullptr;

                if((entity == nullptr || class_name.toStdString() != entity->GetName()) && class_name.toStdString() != "@user@")
                {
                    if(change == false)
                    {
                        Clear();
                        return 1;
                    }
                    auto command = new CreateClassCommand(mainModel, items, model->GetScene());
                    model->GetUndoStack()->push(command);
                    items->last()->SetUndoStack(model->GetUndoStack());
                    entity = items->last()->GetModel();
                    entity->SetDiagramItem(items->last());
                    entity->SetName(class_name.toStdString());
                    items->last()->ModelNameChanged(class_name);
                    newIDs.append(std::make_pair(class_id.toInt(), entity->GetId()));
                }

                auto instance = CreateInstance(name, x_cord.toInt(), line_length.toInt(), entity);
                instance->SetID(id.toInt());
                instance->SetVisible(visible.toInt());
                subnode = subnode.nextSibling().toElement();
            }
        }
        else if (node.tagName() == "Blocks")
        {
            subnode = node.firstChild().toElement();
            //there can be Relation
            while(!subnode.isNull())
            {
                QString id = subnode.attribute("id");
                QString owner_id = subnode.attribute("owner_id");
                QString added_length = subnode.attribute("added_length");
                QString y_offset = subnode.attribute("y_offset");
                QString has_return_message = subnode.attribute("has_return_message");
                QString origin_message_id = subnode.attribute("origin_message_id");

                auto block = CreateBlock(GetInstanceByID(owner_id.toInt()), y_offset.toInt(), nullptr);

                block->SetID(id.toInt());
                block->SetAddedLength(added_length.toInt());
                block->SetHasReturnMessage(has_return_message.toInt());
                if(origin_message_id != "nullptr")
                    block->SetOriginMessageID(origin_message_id.toInt());
                else
                    block->SetOriginMessageID(0);

                qDebug() << block->GetOriginMessageID();

                subnode = subnode.nextSibling().toElement();
            }
        }
        else if (node.tagName() == "Messages")
        {
            subnode = node.firstChild().toElement();
            //there can be Relation
            while(!subnode.isNull())
            {
                QString id = subnode.attribute("id");
                QString sender_id = subnode.attribute("sender_id");
                QString owner_id = subnode.attribute("owner_id");
                QString async = subnode.attribute("async");
                QString y_cord = subnode.attribute("y_cord");
                QString name = subnode.attribute("name");

                auto message = CreateMessage(GetBlockByID(sender_id.toInt()), GetBlockByID(owner_id.toInt()), y_cord.toInt());
                message->SetAsync(async.toInt());
                message->SetID(id.toInt());
                message->SetName(name);
                message->GetSender()->AddMessage(message);

                subnode = subnode.nextSibling().toElement();
            }
        }
        node = node.nextSibling().toElement();
    }
    for(auto block : blockEntities)
    {
        block->GetOwner()->AddBlock(block);
        if(block->GetOriginMessageID() != 0)
            block->SetOriginMessage(GetMessageByID(block->GetOriginMessageID()));
        if(block->GetOriginMessage() == nullptr)
            continue;
        if(block->GetOriginMessage()->GetName() == "<No Method>")
            continue;
        if(block->GetOwner()->GetInstanceClass() == nullptr)
            continue;
        auto method = block->GetOwner()->GetInstanceClass()->FindAttributeByData(block->GetOriginMessage()->GetName());
        if(method == nullptr)
        {
            if(change == false)
            {
                Clear();
                return 1;
            }
            block->GetOwner()->GetInstanceClass()->AddAttrib(static_cast<Enums::Attrib_type>(1), block->GetOriginMessage()->GetName().toStdString());
            block->GetOwner()->GetInstanceClass()->GetView()->AddRow(block->GetOriginMessage()->GetName(), Qt::green);
        }
    }
    return 0;
}
