#ifndef STATE_H
#define STATE_H
#include <QJsonObject>

class State
{
public:
    State() {}
    State(const QJsonObject& obj);
    bool digital[55];
    unsigned int analog[15];
    unsigned int delayAfter;
    QJsonObject makeJsonObj();
};

#endif // STATE_H
