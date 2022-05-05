#include "poster.h"

QUrl poster::url() const
{
    return _url;
}

void poster::setUrl(const QUrl &url)
{
    _url = url;
}

unsigned poster::timeoutMS() const
{
    return _timeoutMS;
}

void poster::setTimeoutMS(const unsigned &timeoutMS)
{
    _timeoutMS = timeoutMS;
}

unsigned poster::count() const
{
    return _count;
}

void poster::setCount(const unsigned &count)
{
    _count = count;
}

QByteArray poster::data() const
{
    return _data;
}

void poster::setData(const QByteArray &data)
{
    _data = data;
}

REQUEST poster::type() const
{
    return _type;
}

void poster::setType(const REQUEST &type)
{
    _type = type;
}

bool poster::jsonheader() const
{
    return _jsonheader;
}

void poster::setJsonheader(bool jsonheader)
{
    _jsonheader = jsonheader;
}

poster::poster(QObject *parent)
{

}

void poster::start()
{
    QNetworkRequest endpoint(_url);
    results.clear();
    if (_jsonheader) endpoint.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    for(unsigned i = 0; i < _count;i++)
    {
        QThread::currentThread()->msleep(_timeoutMS);
        QThread * t = QThread::create([=](){
            QNetworkAccessManager nm ;
            QNetworkReply * reply;
            reply= _type ? nm.post(endpoint, _data) : nm.get(endpoint);
            auto begin = std::chrono::steady_clock::now();
            QEventLoop el;
            connect(reply, SIGNAL(finished()), &el, SLOT(quit()));
            el.exec();
            QByteArray response_data = reply->readAll();
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            result r;
            r.ms = elapsed_ms.count();
            r.result = response_data;
            QMutexLocker ml(&mutex);
            results.push_back(r);
        }
        );

        threads.push_back(t);
        t->start();
    }

    for(auto &i: threads)
    {
        i->wait();
    }
    for(auto &t:threads)
    {
        delete t;
    }
    threads.clear();
    qDebug() << "finished";
    emit finished();
}

void poster::clear()
{

}
