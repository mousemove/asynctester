#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QtNetwork>
#include "poster.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_start_clicked();
    void on_post_stateChanged(int arg1);
    void on_poster_finished();
private:
    Ui::Widget *ui;
    QNetworkAccessManager nam;
    poster p;
};
#endif // WIDGET_H
