#ifndef DETECTOR_H
#define DETECTOR_H

#include <QDebug>
#include <QTimer>
#include <QVector>
#include "constants.h"
#include "gameobject.h"
#include "detections/detection.h"
#include "reactions/reaction.h"
#include "player.h"

class Detector : public GameObject
{
public:
    explicit Detector(QObject *parent = nullptr, qreal x = 0, qreal y = 0, qreal width = 0, qreal height = 0);
    virtual ~Detector();

    void addRule(Detection *detection, Reaction *reaction, QString target);
    void paint(QPainter *painter) override;

    void setPassenger(Detector *newPassenger);

    bool hasPassenger() const;
    void moveTop(qreal pos);
    void moveLeft(qreal pos);

public slots:
    void detectTo(GameObject *target);
    void update() override;
    void moveDown(qreal movement) override;

private:
    // map(key: taregt's class, value: map(key: detection, value: reactions))
    QMap< QString, QMap< Detection*, QVector<Reaction*> > > rules;
    Detector* passenger;

    QTimer *timer;
};

#endif // DETECTOR_H
