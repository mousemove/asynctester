#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&p,SIGNAL(finished()),this,SLOT(on_poster_finished()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_start_clicked()
{
    p.setUrl(QUrl(ui->url->text()));
    p.setData(ui->json->toPlainText().toLocal8Bit());
    p.setCount(ui->count->text().toUInt());
    p.setTimeoutMS(ui->ms->text().toUInt());
    p.setType((REQUEST)ui->post->isChecked());
    p.setJsonheader(ui->ajsonheader->isChecked());
    p.start();
}




void Widget::on_post_stateChanged(int arg1)
{
    ui->json->setEnabled(arg1);
}

void Widget::on_poster_finished()
{
    ui->respArea->clear();
    for(auto i : p.results)
    {
      ui->respArea->setText(  ui->respArea->toPlainText() + QString::number(i.ms) + " : " + i.result + "\n");
    }
    qDebug() << "Finish";
}
