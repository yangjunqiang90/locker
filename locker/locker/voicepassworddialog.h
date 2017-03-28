#ifndef VOICEPASSWORDDIALOG_H
#define VOICEPASSWORDDIALOG_H

#include <QDebug>
#include <QDialog>
#include <QProcess>
#include <QFileDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include<QUrl>
#include<QByteArray>
#include<QMessageBox>
#include"configs.h"
namespace Ui {
class VoicePasswordDialog;
}

class VoicePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoicePasswordDialog(QWidget *parent = 0);
    ~VoicePasswordDialog();
    void setConfirmButton();
    QString getText();

private slots:
    void on_pushButton_begin_record_clicked();

    void QProcess_voice_finished(int code,QProcess::ExitStatus exitStat);

    //replyFinishedVideo
     void replyFinishedVideo(QNetworkReply* reply);

     void on_pushButton_delete_text_clicked();

     void on_pushButton_confirm_send_clicked();

     void on_pushButton_cancel_send_clicked();

private:
    Ui::VoicePasswordDialog *ui;
    char * buf;
    QProcess *proc;
    QNetworkAccessManager *manager;

    QByteArray video_data;
    QNetworkRequest request;

    void appendData(QString str);

    int isConfimFlag;
    QString text;
    void setText(QString text);
    QMessageBox *hintMessage;
    QMessageBox *dealMessage;

};

#endif // VOICEPASSWORDDIALOG_H
