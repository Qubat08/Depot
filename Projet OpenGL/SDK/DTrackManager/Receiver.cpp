#include "receiver.h"

Receiver::Receiver(DTrackSDK &sdk, QObject *parent)
    : QObject (parent)
{
    m_sdk = &sdk;
    connect(&m_timer, &QTimer::timeout, this, &Receiver::receive);
}

void Receiver::start()
{
    m_timer.start();
}

void Receiver::stop()
{
    m_timer.stop();
}

void Receiver::setInterval(int interval)
{
    m_timer.setInterval(interval);
}

DTrackSDK &Receiver::getSDK() const
{
    return *m_sdk;
}

History<QtDTrack::parts::Hand> &Receiver::getHandHistory(int id)
{
    return m_hands[id];
}

const History<QtDTrack::parts::Hand> &Receiver::getHandHistory(int id) const
{
    return m_hands[id];
}

bool Receiver::receive()
{
    if (! m_sdk->receive()) {
        return false;
    }
    if (m_hands.size() < m_sdk->getNumHand()) {
        m_hands.resize(m_sdk->getNumHand());
    }
    for (int id = 0; id < m_sdk->getNumHand(); id++) {
        const DTrack_Hand_Type_d &hand = *m_sdk->getHand(id);
        if (hand.quality > -1) {
            m_hands[id].prepend(hand);
        }
    }
    emit onReceive();
    return true;
}



