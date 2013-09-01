#include "Juices.h"
#include <QTextStream>

QTextStream cout(stdout);

Juices::Juices(QString name, double price, QString bc) :
    m_Name(name), m_Price(price), m_BarCode(bc){}
QString Juices::getName() const {
    return m_Name;
}
double Juices::getPrice() const {
    return m_Price;
}
void Juices::sell(QString name) {
    if(!(m_Name == name))
        cout << m_Price << endl;
}
QString Juices::getBarCode() const {
    return m_BarCode;
}
QString Juices::toString() const{
    QString sPrice = QString::number(m_Price);
    return  "Name:" + m_Name + "\n" + "Price:R" + sPrice + "\n"
            + "BarCode:" + m_BarCode;
}


