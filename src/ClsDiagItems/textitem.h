#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QObject>
#include <QGraphicsTextItem>

class TextItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit TextItem(QGraphicsItem  *parent = nullptr);
    void setText(QString value);
    void SetId(int id);
    void SetLock(bool lock);
    int GetId();

protected:
    virtual void keyReleaseEvent(QKeyEvent * event) override;

private:
    int id;

signals:
    void valueChanged(QString value, int id);

};

#endif // TEXTITEM_H
