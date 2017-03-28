#ifndef TIMEDIALOG_H
#define TIMEDIALOG_H

#include <QDialog>

namespace Ui {
class TimeDialog;
}

class TimeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TimeDialog(QWidget *parent = 0);
    int getSumTime();
    ~TimeDialog();
    
private slots:
    void on_pushButton_addTime_clicked();

    void on_pushButton_subTime_clicked();

    void on_pushButton_confirm_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::TimeDialog *ui;
    int sumTime;
    QString addSumTime();
    QString subSumTime();

};

#endif // TIMEDIALOG_H
