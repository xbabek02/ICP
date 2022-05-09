#include "textstateitem.h"

TextStateItem::TextStateItem(QGraphicsItem *parent, int id) : QGraphicsTextItem(parent)
{
   this->id = id;

  currentState = 0;
  numberOfStates = 0;
  setPlainText(" ");

  QFont f;
  f.setPixelSize(15);
  f.setBold(true);

  this->setFont(f);
  setFlag(QGraphicsItem::ItemIsSelectable);
}

int TextStateItem::GetID()
{
    return id;
}

void TextStateItem::FillAccess()
{
  setPlainText("+");
  AddState("+");
  AddState("-");
  AddState("#");
  AddState("~");
}

void TextStateItem::FillCardinalities()
{
  setPlainText(" 1  ");
  AddState(" 1  ");
  AddState("0..n");
  AddState("1..n");
}

void TextStateItem::AddState(QString text)
{
  textStates.append(text);
  numberOfStates++;
}

void TextStateItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  NextState();
  emit stateChange(id);
  QGraphicsTextItem::mousePressEvent(event);
}

void TextStateItem::NextState()
{
  currentState = (currentState + 1) % numberOfStates;
  if(currentState < 0)
      currentState = 0;
  setPlainText(textStates[currentState]);
}

void TextStateItem::SetState(int state)
{
  currentState = state % numberOfStates;
  setPlainText(textStates[state]);
}

int TextStateItem::GetState()
{
  return currentState;
}

void TextStateItem::UpdatePosition(QPointF *position1, QPointF *position2)
{
  double newX = position1->x();
  double newY = position1->y();
  double deltaY = position1->y() - position2->y();
  double deltaX = position1->x() - position2->x();

  newX = newX - (deltaX / 8);
  newY = newY - (deltaY / 8);
  setPos(newX, newY);
}
