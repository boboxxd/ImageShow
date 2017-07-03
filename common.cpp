#include "common.h"
#include <QMap>
#include <QString>







QString myprint(HelmetMap map,QString key)
{
    switch(map.value(key))
    {
    case 1:
        return QString("humen");
    case 2:
        return QString("red_waistcoat");
    case 3:
        return QString("helmet_red");
    case 4:
        return QString("helmet_blue");
    case 5:
        return QString("helmet_yellow");
    case 6:
        return QString("helmet_white");
    }
}

QString myprint(VehicleMap map,QString key)
{
    switch(map.value(key))
    {
    case 1:
        return QString("truck_crane");
    case 2:
        return QString("excavator");
    case 3:
        return QString("cement_pump_truck");
    case 4:
        return QString("bulldozer");
    case 5:
        return QString("truck_crane_working_arm");
    case 6:
        return QString("tower_crane_arm");
    }
}




