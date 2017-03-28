#include "timedialog.h"
#include "ui_timedialog.h"

TimeDialog::TimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeDialog)
{
    ui->setupUi(this);
    sumTime=0;
    ui->lineEdit_time->setText(QString::number(sumTime));
}

TimeDialog::~TimeDialog()
{
    delete ui;
}
QString TimeDialog::addSumTime(){
    int res = ++sumTime;
    return QString::number(res);
}
QString TimeDialog::subSumTime(){
    int res = --sumTime;
    if(res<=0)
    {
        res=0;
        sumTime=0;
    }
    return QString::number(res);
}
 int TimeDialog::getSumTime(){
     return sumTime;
 }
void TimeDialog::on_pushButton_addTime_clicked()
{
    ui->lineEdit_time->setText(addSumTime());
}


void TimeDialog::on_pushButton_subTime_clicked()
{
     ui->lineEdit_time->setText(subSumTime());
}

void TimeDialog::on_pushButton_confirm_clicked()
{
    accept();
}

void TimeDialog::on_pushButton_cancel_clicked()
{
     reject();
}
