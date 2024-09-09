#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include "tracking/parts/hand.h"
#include "tracking/history.h"
#include "DTrack/DTrackSDK.hpp"

class Receiver : public QObject
{
    Q_OBJECT

protected:
    DTrackSDK *m_sdk;
    QTimer     m_timer;
    QVector<History<QtDTrack::parts::Hand>> m_hands;


public:
    explicit Receiver(DTrackSDK &sdk, QObject *parent = nullptr);
    void start();
    void stop();
    void setInterval(int interval);
    bool isStarted() const { return m_timer.isActive(); }
    DTrackSDK & getSDK() const;

    History<QtDTrack::parts::Hand> & getHandHistory(int id);
    const History<QtDTrack::parts::Hand> & getHandHistory(int id) const;

signals:
    void onReceive();

public slots:
    bool receive();
};

#endif // RECEIVER_H
