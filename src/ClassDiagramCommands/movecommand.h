#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include <QObject>

class MoveCommand : public QObject
{
    Q_OBJECT
public:
    explicit MoveCommand(QObject *parent = nullptr);

signals:

};

#endif // MOVECOMMAND_H
