#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

class handler : public QObject
{
    Q_OBJECT
private:
    static handler *hand;
private:
    explicit handler(QObject *parent = nullptr);

signals:
    void beatMouse();
public slots:
public:
    static handler *getInstance();
    void addScore();
};

#endif // HANDLER_H
