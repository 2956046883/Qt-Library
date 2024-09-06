#include "book.h"
#include<QVector>


Book::Book(QObject *parent) : QObject(parent)
{

}
int GlobalBook=0;
QVector<Book*>vec;
