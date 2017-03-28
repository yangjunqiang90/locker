#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

#include <QDebug>
#include <QDialog>
#include <QProcess>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include<QUrl>
#include<QByteArray>
#include<QMessageBox>
#include<voicehintdialog.h>
#include"configs.h"
namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PasswordDialog(QWidget *parent = 0);
    PasswordDialog(int flag,QWidget *parent = 0);
    ~PasswordDialog();
    QString getPassword();
    void setSettingPass(QString title);

    
private slots:

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_delete_all_clicked();

    void on_pushButton_confim_clicked();

    void on_pushButton_cancel_clicked();


    void on_pushButton_voice_input_clicked();

    void replyFinishedVideo(QNetworkReply*);

    void QProcess_voice_finished(int code,QProcess::ExitStatus exitStat);

    void on_pushButton_voice_verify_clicked();

private:
    Ui::PasswordDialog *ui;
    QString password;
    //哪种密码的标志
    int flag;

    QNetworkRequest request;
    QNetworkAccessManager *manager;
     void appendData(QString str);
     QByteArray video_data;

     QString chTo123(const QString &c);
     QMessageBox *hintMessage;
    QMessageBox *dealMessage;
     char * b;
     QProcess *proc;

     int isVoiceInput;


};

#endif // PASSWORDDIALOG_H
