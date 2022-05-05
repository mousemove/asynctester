#ifndef POSTER_H
#define POSTER_H

#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <chrono>
#include <QMutexLocker>
enum REQUEST {GET,POST};
struct result{
    time_t ms;
    QByteArray result;
};

class poster : public QObject
{
    Q_OBJECT
private:
    QUrl _url;
    unsigned _timeoutMS;
    unsigned _count;
    REQUEST _type = GET;
    bool _jsonheader = true;
    QByteArray _data;

public:
    QMutex mutex;
    QVector<result> results;
    QVector<QThread *> threads;
    explicit poster(QObject *parent = nullptr);

    void start();
    void clear();



    QUrl url() const;
    void setUrl(const QUrl &url);

    unsigned timeoutMS() const;
    void setTimeoutMS(const unsigned &timeoutMS);

    unsigned count() const;
    void setCount(const unsigned &count);

    QByteArray data() const;
    void setData(const QByteArray &data);

    REQUEST type() const;
    void setType(const REQUEST &type);

    bool jsonheader() const;
    void setJsonheader(bool jsonheader);

signals:
    void finished();
};

#endif // POSTER_H
