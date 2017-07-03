#ifndef XMLCREATOR_H
#define XMLCREATOR_H
#include "common.h"
#include<QDomDocument>
#include<QFile>
#include "showwidget.h"
class XmlCreator
{
public:
    XmlCreator();
    ~XmlCreator();
    void set(std::vector<INFO> info);
private:
    QFile *file;
};

#endif // XMLCREATOR_H
