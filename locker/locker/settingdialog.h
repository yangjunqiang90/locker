#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include<QtDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <iterator>
#include "info.h"
#include "passworddialog.h"
#include "voicepassworddialog.h"
namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT
    
public:
    Info information;
    explicit SettingDialog(QWidget *parent = 0);
    SettingDialog(QString welcome,QWidget *parent = 0);
    ~SettingDialog();
    
private slots:

    void on_pushButton_set_welcome_clicked();

    void on_pushButton_confirm_change_clicked();

    void on_pushButton_cancel_change_clicked();

    void on_pushButton_set_root_password_clicked();

    void on_checkBox_recover_clicked(bool checked);


    void on_pushButton_set_lock_password_clicked();

    void on_pushButton_recover_clicked();



private:

    Ui::SettingDialog *ui;
    QString welcome;
    void showInfo2User(const QString & info,const QString & title);
    bool  is_show_weather;
    bool  is_show_welcome;

};

#endif // SETTINGDIALOG_H
