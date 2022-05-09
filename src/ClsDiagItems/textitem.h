/**
 * @file textitem.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Text item emiting signal when being changed
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QObject>
#include <QGraphicsTextItem>

class TextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    /**
     * @brief TextItem is constructor
     * @param parent
     */
    explicit TextItem(QGraphicsItem  *parent = nullptr);

    /**
     * @brief setText
     * @param value is the text
     */
    void setText(QString value);

    /**
     * @brief SetId sets id of the object
     * @param id
     */
    void SetId(int id);

    /**
     * @brief SetLock sets wheter text box is locked
     * @param lock
     */
    void SetLock(bool lock);

    /**
     * @brief GetId
     * @return id of the object
     */
    int GetId();

protected:
    /**
     * @brief keyReleaseEvent emits signal when key os pressed
     * @param event
     */
    virtual void keyReleaseEvent(QKeyEvent * event) override;

private:
    /**
     * @brief id
     */
    int id;

signals:
    /**
     * @brief valueChanged emits when value is changed
     * @param value
     * @param id
     */
    void valueChanged(QString value, int id);

};

#endif // TEXTITEM_H
