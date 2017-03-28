#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingdialog.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include<QUrl>
#include<QByteArray>
#include <QTextCodec>
#include<string.h>
#include<stdio.h>
#include <QProcess>

#include <QFileDialog>
#include "info.h"
#include"configs.h"
#include"timedialog.h"
#include"voicepassworddialog.h"
#include"MyLock.h"
//是哪种http返回的标志
#define LOCK 0
//更新设备的信息
#define ROOT 1
#define UPDATA 2
#define REFRESH 3
//监控的http返回
#define MONITORING 4
//一键开锁
#define ONELOCK 5
#define MESSAGE 6

#define onlysetlock 7

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    
private slots:
    void on_pushButton_text_password_clicked();

    void on_pushButton_setting_clicked();

    //连接请求结束信号

    void replyFinished(QNetworkReply* reply);
    //连接响应时返回数据信号
   // void on_readyRead();

    void on_pushButton_refresh_clicked();

    void on_pushButton_monitoring_clicked();

    void QProcess_monitoring_finished(int exitCode,QProcess::ExitStatus exitStatus);
    void on_pushButton_voice_clicked();



    void on_pushButton_open_anyway_clicked();


    void on_pushButton_closeLock_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    //QNetworkAccessManager *manager_video;

    QProcess *proc;
    QProcess *procMP4Box;
    QProcess *procrm;

    //从服务器得到的语音数据
    //QString voiceDataFromServer;
    //用于判定是不是本次从服务器得到的数据
    //int isCurrentData;
    QNetworkRequest request;
    //QNetworkRequest request_video;


    //QNetworkReply *reply ;

    QByteArray post_data;
    //QByteArray video_data;
    int flag;
    int isOpenMonitor;
     int monitorPid;
    QString password;
    void setFlag(int flag);
    int  getFlag();

    void setIsOpenMonitor(int monitorStat);
    int  getIsOpenMonitor();

    void setMonitorPid(int monitorPid);
    int  getMonitorPid();


   void setPassword(QString password);
   QString getPassword();

 //  void setVoiceDataFromServer(int isCuttentData,QString password);
   //QString getVoiceDataFromServer();

   void showInfo2User(const QString& info,const QString& title);
   void rmVideoFile();
   void dealCloseLock();
   void dealOpenLock();

   //打开是0
   //关上是1
   int isCloseLock;
   //是否显示更新成功提示
  // int isShowUpdate;
};

#endif // MAINWINDOW_H
