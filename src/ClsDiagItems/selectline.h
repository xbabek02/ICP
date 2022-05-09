/**
 * @file selectline.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Line which emits singal when being selected
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SELECTLINE_H
#define SELECTLINE_H

#include <QGraphicsLineItem>
#include <QPen>
#include <QObject>

class SelectLine : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    /**
     * @brief SelectLine is constructor
     * @param x1
     * @param y1
     * @param x2
     * @param y2
     * @param parent1
     * @param parent2
     */
    SelectLine(int x1, int y1, int x2, int y2, QGraphicsItem *parent1 = nullptr, QObject *parent2 = nullptr);
    /**
     * @brief SetSelectChain sets when this line of currently in the select chain
     */
    void SetSelectChain();

protected:
    /**
     * @brief itemChange emitch selectChange signal when line is selected
     * @param change
     * @param value
     * @return
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    /**
     * @brief selectChain
     */
    bool selectChain;

signals:
    /**
     * @brief selectChange emits when select state changes
     * @param selected
     */
    void selectChange(bool selected);
};

#endif // SELECTLINE_H
