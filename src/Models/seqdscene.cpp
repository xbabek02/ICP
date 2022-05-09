#include "seqdscene.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <./SeqDiagItems/instanceitem.h>
#include <./SeqDiagItems/rectangle.h>
#include <./SeqDiagItems/messageitem.h>
#include <./SeqDiagItems/userinstance.h>
#include <QKeyEvent>
#include <./Common/enums.h>

SeqDScene::SeqDScene(MethodModel*mm, QObject *parent) :
    mm(mm), QGraphicsScene(parent)
{
    connect(this, SIGNAL(selectionChanged()), this, SLOT(selChanged()));
}

void SeqDScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    for (auto item : items(event->scenePos())) {
        if (auto ii = dynamic_cast<Rectangle*>(item)){
            editedMessage = new MessageItem(Enums::MessageTypes::sync, ii, event->scenePos().y());
            addItem(editedMessage);
        }
    }
    qDebug() << event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void SeqDScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (editedMessage == nullptr){
        QGraphicsScene::mouseMoveEvent(event);
        return;
    }

    editedMessage->UpdateDrawMessage(event->scenePos());

    QGraphicsScene::mouseMoveEvent(event);
}

void SeqDScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (editedMessage == nullptr){
        QGraphicsScene::mouseReleaseEvent(event);
        return;
    }

    QLineF line(editedMessage->line());
    bool left_to_right = line.p1().x() < line.p2().x();
    InstanceItem *last_colider = editedMessage->sender->instance;

    QList<QGraphicsItem*> list = editedMessage->collidingItems();

    for (QGraphicsItem *i : list)
    {
        InstanceItem *item= dynamic_cast<InstanceItem *>(i);
        if (item){
            if (left_to_right){
                last_colider = last_colider->x() < item->x() ? item : last_colider;
            }
            else{
                last_colider = last_colider->x() > item->x() ? item : last_colider;
            }
        }
    }
    if (last_colider == editedMessage->sender->instance){
        removeItem(editedMessage);
        delete editedMessage;
        editedMessage = nullptr;
    }
    else{
        editedMessage->owner = new Rectangle(last_colider, editedMessage, line.p1().y());
        if (left_to_right){
            editedMessage->setLine(QLineF(line.x1()+ Rectangle::width/2, line.p1().y(), last_colider->pos().x() + last_colider->width /2 - Rectangle::width/2, line.p1().y()));
        }
        else {
            editedMessage->setLine(QLineF(line.x1() - Rectangle::width/2, line.p1().y(), last_colider->pos().x() + last_colider->width /2 + Rectangle::width/2, line.p1().y()));
        }
        editedMessage->solid = true;
        editedMessage->sender->AddMessage(editedMessage);
        editedMessage->update();
        editedMessage = nullptr;
    }
    
    QGraphicsScene::mouseReleaseEvent(event);
}

void SeqDScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete){
        for (auto item : selectedItems()){
            if (auto message = dynamic_cast<MessageItem*>(item)){
                   DeleteMessage(message);
            }
        }
        for (auto item : selectedItems()){
            if (auto rectangle = dynamic_cast<Rectangle*>(item)){
                   DeleteRectangle(rectangle);
            }
        }
    }
    QGraphicsScene::keyPressEvent(event);
}


void SeqDScene::DeleteRectangle(Rectangle*rectangle){
    if (!rectangle->origin){
        // Deleting Initial Block
        for (auto message : rectangle->sent){
            DeleteMessage(message);
        }
        Rectangle::initial_block = nullptr;
        removeItem(rectangle);
        rectangle->instance->rectangles.clear();
        delete rectangle;
        return;
    }
    DeleteMessage(rectangle->origin);
}

void SeqDScene::DeleteMessage(MessageItem*message){
    //delete returning message
    if (message->type == Enums::MessageTypes::returnal){
        int i = 0;
        for (auto item : message->owner->returning_messages){
            if (item->GetID() == message->GetID()){
                message->owner->returning_messages.removeAt(i);
                break;
            }
            i++;
        }
        message->sender->return_message = nullptr;
    }
    else { //deleting any other message
        int i = 0;
        for (auto item : message->sender->sent){
            if (item->GetID() == message->GetID()){
                message->sender->sent.removeAt(i);
                break;
            }
            i++;
        }
        for (auto item :message->owner->sent){
            DeleteMessage(item);
        }
        if (message->owner->return_message){
            DeleteMessage(message->owner->return_message);
        }
        i = 0;
        if (!message->owner->instance){
            qDebug() << "OWNER IS NULL!!!!";
        }
        for (auto item : message->owner->instance->rectangles){
            if (item->GetID() == message->owner->GetID()){
               message->owner->instance->rectangles.removeAt(i);
               break;
            }
            i++;
        }
        removeItem(message->owner);
        delete message->owner;
    }
    this->removeItem(message);
    delete message;
}

void SeqDScene::GetAllDependent(Rectangle *rectangle, QList<QGraphicsItem*>*list)
{
    for (auto message : rectangle->sent){
        GetAllDependent(message->owner, list);
    }
    if (rectangle->return_message){
        list->append(rectangle->return_message);
    }

    list->append(rectangle);
    if (rectangle->origin){
        list->append(rectangle->origin);
    }

}

QList<QGraphicsItem *> *SeqDScene::GetAllDependent(InstanceItem *instance)
{
    QList<QGraphicsItem*>*list = new QList<QGraphicsItem*>;
    for (auto item : instance->rectangles){
        auto list2 = new QList<QGraphicsItem*>;
        GetAllDependent(item, list);
        for (auto list_item : *list2){
            list->append(list_item);
        }
        delete list2;
    }
    return list;
}

void SeqDScene::selChanged()
{
    QList<QGraphicsItem*> list = selectedItems();
    if (list.count() != 1) {
        return;
    }
    MessageItem*message = dynamic_cast<MessageItem*>(list.at(0));
    if (message){
        if (message->type == Enums::MessageTypes::sync || message->type == Enums::MessageTypes::async)
            mm->setMessage(message);
    }
}
