#ifndef READTEXT_H
#define READTEXT_H
#include <QString>
#include <QPoint>
#include <QList>
#include<QStringList>
#include "common.h"

class ReadText
{
public:
    ReadText(const  QString &filename);
    void Set(const QString &filename);
    QList<INFO>  GetInfo() const;
private:
    QList<INFO> info;
};



#endif // READTEXT_H
