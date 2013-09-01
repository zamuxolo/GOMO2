#ifndef JUICES_H
#define JUICES_H
#include <QString>

class Juices {
public:
    Juices() {}
    Juices(QString name, double price, QString bc);
    QString getName() const;
    double getPrice() const;
    virtual QString toString() const;
    QString getBarCode() const;
    void sell(QString name);
    void calcPrice(QString name);
protected:
    QString m_BarCode;
    QString m_Name;
    double m_Price;
};

#endif // JUICES_H
