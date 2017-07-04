#ifndef COMMON_H
#define COMMON_H
#include <QMap>
#include<QString>
#include <QImage>
#include<QPoint>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
struct INFO
{
    QString filename;
    QString type;
    QPoint start,end;
    QString score;
};

enum HELMETANDCOAST{humen=1,\
                    red_waistcoat,\
                    helmet_red,\
                    helmet_blue,\
                    helmet_yellow,\
                    helmet_white
                   };

enum VEHICLE{truck_crane=1,\
             excavator,\
             cement_pump_truck,\
             bulldozer,\
             truck_crane_working_arm,\
             tower_crane_arm
            };

typedef QMap<QString, HELMETANDCOAST> HelmetMap;
typedef QMap<QString, VEHICLE> VehicleMap;



QString myprint(HelmetMap map,QString key);
QString myprint(VehicleMap map,QString key);


QImage cvMat2QImage(const cv::Mat& mat);
cv::Mat QImage2cvMat(QImage image);



#endif // COMMON_H
