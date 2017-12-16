#include "state.h"

State::State(const QJsonObject& obj) :
    delayAfter(static_cast<unsigned int>(obj.value("delayAfter").toDouble()))
{
    QJsonObject pinsObj = obj.value("pins").toObject();
    QJsonObject analogObj = pinsObj.value("analog").toObject();
    QJsonObject digitalObj = pinsObj.value("digital").toObject();
    for (int i = 0; i < 55; i++) {
        digital[i] = digitalObj.value(QString("%1").arg(i + 1)).toBool();
    }
    for (int i = 0; i < 15; i++) {
        analog[i] = static_cast<unsigned int>(analogObj.value(QString("%1").arg(i + 1)).toDouble());
    }
}

QJsonObject State::makeJsonObj() {
    QJsonObject jsObj, pinsObj, digitalObj, analogObj;
    for (int i = 0; i < 55; i++) {
        digitalObj.insert(QString("%1").arg(i + 1), digital[i]);
    }
    for (int i = 0; i < 15; i++) {
        analogObj.insert(QString("%1").arg(i + 1), static_cast<double>(analog[i]));
    }
    pinsObj.insert("digital", digitalObj);
    pinsObj.insert("analog", analogObj);
    jsObj.insert("pins", pinsObj);
    jsObj.insert("delayAfter", static_cast<double>(delayAfter));
    return jsObj;
}
