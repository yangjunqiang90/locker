#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"passworddialog.h"
#include<QtDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    isCloseLock=0;
    //isShowUpdate=1;
    ui->setupUi(this);
//  ui->textEdit_welcome->setText("各班学委请在本班作业上面标注本班总人数，以及未交作业的");
    ui->textEdit_welcome->setText("快递大哥：\n    感谢您送来的快件，您把快件放到袋子里就可以了，在此表示真挚的谢意。\n    祝工作顺心，万事如意！");
    manager = new QNetworkAccessManager(this);
   // manager_video = new QNetworkAccessManager(this);

    proc = new QProcess;
    procMP4Box = new QProcess;
    procrm = new QProcess;

   // this->isCurrentData=0;
    //设置头信息


    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
//    request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

    request.setUrl(QUrl("http://"+ip+":8080/WebServer/servlet/myServler"));


//快递大哥：
//    感谢您送来的快件，您把快件放到袋子里就可以了，在此表示真挚的谢意。
//    祝工作顺心，万事如意！


    //连接请求结束信号
    //只要发送请求成功，它就会下载数据。而当数据下载完成后，
    //manager会发出finished()信号，我们对它进行了关联：
    //下载数据结束时，就会执行replyFinished()函数
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    //on_QProcess_monitoring_finished
    connect(proc, SIGNAL(finished(int,QProcess::ExitStatus )), this, SLOT(QProcess_monitoring_finished(int ,QProcess::ExitStatus )));
    //发送请求，它返回一个QNetworkReply对象，
    //manager->post(request, post_data);

    //连接响应时返回数据信号
   // connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
    setIsOpenMonitor(0);
    this->resize(QSize( 480, 320 ));
  // this->resize(QSize( 320, 320 ));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete proc;
    delete manager;
    delete procMP4Box;
    delete procrm;
    //delete buf;
    //delete manager_video;
}

//void MainWindow::paintEvent(QPaintEvent *)
//{
//   QPainter painter(this);
//   painter.drawPixmap(0,0,width(),height(),QPixmap("image/1.png"));
//}
void MainWindow::setFlag(int flag)
{
    this->flag=flag;
}

int  MainWindow::getFlag()
{
    return this->flag;
}

void MainWindow::setIsOpenMonitor(int monitorStat){
    this->isOpenMonitor = monitorStat;
}

int  MainWindow::getIsOpenMonitor(){
    return isOpenMonitor;
}

void MainWindow::setMonitorPid(int monitorPid){
    this->monitorPid = monitorPid;
}

int  MainWindow::getMonitorPid(){
    return monitorPid;
}

void MainWindow::setPassword(QString password)
{
    this->password=password;
}
QString MainWindow::getPassword()
{
    return this->password;
}
void MainWindow::showInfo2User(const QString & info,const QString & title){

    QMessageBox box(QMessageBox::Warning,title,info);
    box.setButtonText (QMessageBox::Ok,QString("确 定"));
    box.exec();

}
void MainWindow::dealCloseLock(){
    if(!isCloseLock)
    {
        //不处于关闭状态才关闭
    closeLock();
    //标志已经关了
    isCloseLock=1;
    }

}
void MainWindow::dealOpenLock(){

    if(isCloseLock)
    {
        //关闭状态才能打开
    openLock();
    //标志已经打开
    isCloseLock=0;



    }

}
/*
void  MainWindow::setVoiceDataFromServer(int isCuttentData,QString data){
    this->isCurrentData =1;
    this->voiceDataFromServer = data;
}

QString  MainWindow::getVoiceDataFromServer(){
    if(this->isCurrentData==1)
    {
        //本次数据取走，标志为设为0
    this->isCurrentData=0;
    return this->voiceDataFromServer;
    }else
    {
        return NULL;
    }
}
*/
void MainWindow::on_pushButton_text_password_clicked()
{
    PasswordDialog passdialog(PASSWORD_DIALOG);
    passdialog.setWindowTitle("请输入开箱密码");
    if(passdialog.exec()==QDialog::Accepted)
    {

        qDebug()<<passdialog.getPassword();

        setFlag(LOCK);

        post_data.clear();

        post_data.append("LOCK_PASSWORD="+passdialog.getPassword()+"&");
        post_data.append("BUTLERID=0&");
        post_data.append("cmd=1");

         request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
         //发送请求，它返回一个QNetworkReply对象，
         manager->post(request, post_data);
    }else{
        qDebug()<<"取消开箱";
        return ;
    }

}

void MainWindow::on_pushButton_setting_clicked()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    PasswordDialog passdialog(SETTING_DIALOG);
    passdialog.setWindowTitle("请输入管理员密码");
    if(passdialog.exec()==QDialog::Accepted)
    {
        //qDebug()<<"Accepted 1";
        //qDebug()<<passdialog.getPassword();

        setFlag(ROOT);
        setPassword(passdialog.getPassword());

        post_data.clear();

        post_data.append("ROOT_PASSWORD="+passdialog.getPassword()+"&");
        post_data.append("BUTLERID=0&");
        post_data.append("cmd=3");


        // void setHeader(KnownHeaders header, const QVariant &value);
        request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

        qDebug()<<"只要在此处加上一句输出程序就不崩溃";
       // qDebug()<<post_data;
        //发送请求，它返回一个QNetworkReply对象，
        manager->post(request, post_data);
    }/*else
    {
         //qDebug()<<"只要在此处加上一句输出程序就不崩溃";
    }*/
   // passdialog.deleteLater();
}

void MainWindow::replyFinished(QNetworkReply* reply)
{
   // QString WELCOME;

     if(reply->error() != QNetworkReply::NoError)
     {
//         QMessageBox box(QMessageBox::Warning,"提示","弹出框按钮更改为中文！");
//         box.setButtonText (QMessageBox::Ok,QString("确 定"));
         showInfo2User("没有服务器收到数据，响应错误","提示");
         qDebug()<<"没有服务器收到数据，响应错误";
         reply->deleteLater();
         return ;
     }
   // 读取http响应信息
    QByteArray b = reply->readAll();
    QString data(b);
    //1;WELCOME_TEXT=Welcome to My home;WELCOME=0;"
    qDebug() <<"收到的所有数据="+data;
    //读取第一个字符
    QString res = data.left(1);

    //把第一个;前的删除
    data.remove(0,data.indexOf(";")+1);

    //读取第二个字符
    //QString WELCOME= data.left(data.indexOf("WELCOME="));
//    str = path.section('/', 3, 4);
     QString WELCOME=NULL;
     QString WELCOME_TEXT=NULL;
    if(data.indexOf("WELCOME_TEXT")!=-1)
    {/*
        WELCOME= data.section(";",0,0).right(1);
        //把第二个;前的删除
        data.remove(0,data.indexOf(";")+1);
        qDebug()<<"WELCOME_TEXT="+WELCOME;
    */
        ;//.section(";",0,0).right(1);;
        WELCOME_TEXT=data.section(";",0,0);
        WELCOME_TEXT=WELCOME_TEXT.remove(0,WELCOME_TEXT.indexOf("=")+1);

        WELCOME= data.section(";",1,1);
        WELCOME=WELCOME.remove(0,WELCOME.indexOf("=")+1);

        qDebug()<<"WELCOME_TEXT="+WELCOME_TEXT;
        qDebug()<<"WELCOME="+WELCOME;

    }

    QString S_ONELOCK="0";
    if(data.indexOf("ONEKEY_LOCK=")!=-1)
    {
        S_ONELOCK= data.section(";",0,0).right(1);
        //把第二个;前的删除
       // data.remove(0,data.indexOf(";")+1);
        S_ONELOCK = S_ONELOCK.remove(0,S_ONELOCK.indexOf("=")+1);
        qDebug()<<"ONELOCK="+S_ONELOCK;
    }

    //data.remove(0,data.indexOf("=")+1);
    //这里会输出HTML网页代码
    //去掉标志后的数据
    qDebug() <<"收到的数据="+data;
    qDebug() << "read data end";

    /*
     *
     *#define LOCK 0
     *#define ROOT 1
     *#define UPDATA 2
*/
    if(!res.toInt())
    {
        showInfo2User("操作错误","提示");
        qDebug() << "操作错误";
        return ;
    }
      qDebug() << "操作正确";

    switch(getFlag())
    {
    case onlysetlock:break;
    case LOCK://showInfo2User("正在打开箱子","提示");
        qDebug()<<"可以打开箱子了！";
        dealOpenLock();
        //设置只能使用一次
        setFlag(onlysetlock);
        post_data.clear();

       // post_data.append("LOCK_PASSWORD=901212&");
        post_data.append("BUTLERID=0&");
        post_data.append("lock=1&");
        post_data.append("content=您的设备已被打开。&");
        post_data.append("cmd=7");

         request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
         //发送请求，它返回一个QNetworkReply对象，
         manager->post(request, post_data);
       //  isShowUpdate=0;

                break;
    case UPDATA:
       // if(isShowUpdate)
      //  {
        showInfo2User("修改成功","提示");
      //  }else
      //  {
       //     isShowUpdate=1;
       // }
        on_pushButton_refresh_clicked();
                break;
    case REFRESH:qDebug() <<"case REFRESH";
                if(WELCOME=="1"){
                    qDebug()<<"true";//+"true"+WELCOME;
                    this->ui->textEdit_welcome->setText(WELCOME_TEXT);
                }else
                {
                    //qDebug()<<"WELCOME==1"+"false"+WELCOME;
                    qDebug()<<"false";

                    this->ui->textEdit_welcome->setText(" ");
                }
               // this->ui->textEdit_welcome->setText(data);
                break;
    case ONELOCK:
                    if(S_ONELOCK=="1")
                    {
                         qDebug()<<"可以打开箱子了！";
                         dealOpenLock();

                         setFlag(onlysetlock);
                         post_data.clear();


                         post_data.append("BUTLERID=0&");
                         post_data.append("ONEKEY_LOCK=0&");
                         post_data.append("cmd=6");

                          request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
                          //发送请求，它返回一个QNetworkReply对象，
                          manager->post(request, post_data);
                          //isShowUpdate=0;

                    }else{
                        showInfo2User("未设置一键开锁，无法使用","警告");
                    }
                    break;

    case MONITORING:
                    if(getIsOpenMonitor()){
                        //摄像已经打开了
                        QMessageBox msgBox(QMessageBox::Question,QString(tr("监控已经打开")),QString(tr("是否关闭监控")));
                        QPushButton *yesButton = msgBox.addButton(tr(" 关闭监控 "), QMessageBox::AcceptRole);
                        QPushButton *noButton = msgBox.addButton(tr(" 继续监控 "), QMessageBox::RejectRole);
                        msgBox.setDefaultButton(noButton);
                        int res = msgBox.exec();
                        if(res==QMessageBox::AcceptRole)
                        {
                          qDebug()<<"关闭监控";
                         // QString cmd = "kill -2 "+getMonitorPid();
/*
                          QString  cmd = "kill -2 "+QString::number(getMonitorPid(), 10);
                          char*  ch;
                          QByteArray ba = cmd.toLatin1();
                          ch=ba.data();
                          qDebug()<<ch;

                          proc->start(ch);
                          this->setIsOpenMonitor(0);

                          delete ch;
                          */
                          if(proc)
                          proc->close();
                        }
                        else if(res==QMessageBox::RejectRole)
                        {
                          qDebug()<<"继续监控";
                        }
                        else
                        {
                           qDebug()<<"继续监控，代码出问题了";
                        }
                        delete yesButton;
                        delete noButton;
                    }else{
                        //摄像头没有打开
                        QMessageBox msgBox(QMessageBox::Question,QString(tr("监控未打开")),QString(tr("是否开启监控")));
                        QPushButton *yesButton = msgBox.addButton(tr(" 开启监控 "), QMessageBox::AcceptRole);
                        QPushButton *noButton = msgBox.addButton(tr(" 不开启监控 "), QMessageBox::RejectRole);
                        msgBox.setDefaultButton(noButton);
                        int res = msgBox.exec();
                          qDebug("%s,%d",__FILE__,__LINE__);
                        if(res==QMessageBox::AcceptRole)
                        {
                          qDebug()<<"开启监控";
                          TimeDialog td ;
                            qDebug("%s,%d",__FILE__,__LINE__);
                          if(td.exec()==QDialog::Accepted)
                          {



                             rmVideoFile();
                             double tm=td.getSumTime()*20000;
                             char * cmd_raspivid_ch=NULL;
                             QString cmd_raspivid ="raspivid -t "+QString::number(tm)+" --segment 20000 -o /home/pi/pro/video/video%04d.h264";
//                           proc->start("raspivid -t 10000 --segment 10000 -o video%04d.h264");
                              QByteArray cmd_ba = cmd_raspivid.toLatin1();
                             cmd_raspivid_ch = cmd_ba.data();
                             qDebug()<<cmd_raspivid_ch;
                             proc->start(cmd_raspivid_ch);

                             // 等待进程启动
                                if (!proc->waitForStarted())
                                {

                                    qDebug() << "启动失败\n";
                                    break;
                                }

//                                if(cmd_raspivid_ch)
//                                {

//                             delete cmd_raspivid_ch;
//                                cmd_raspivid_ch=NULL;
//                                 qDebug("%s,%d",__FILE__,__LINE__);
//                                 }
//                                qDebug("%s,%d",__FILE__,__LINE__);
                          }/*else
                          {

                              qDebug()<<"raspivid -t 24000 --segment 3000 -o video%04d.h264";
                               proc->start("raspivid -t 24000 --segment 10000 -o video%04d.h264");
                               // 等待进程启动
                                  if (!proc->waitForStarted())
                                  {
                                      qDebug() << "启动失败\n";
                                      break;
                                  }

                          }*/

                          //this->setMonitorPid(proc->pid());
                          this->setIsOpenMonitor(1);

                        }
                        else if(res==QMessageBox::RejectRole)
                        {
                          qDebug()<<"不开启监控";
                        }
                        else
                        {

                            //点击的事X
                           qDebug()<<"不开启监控，代码出问题了";
                        }

                        delete yesButton;
                        delete noButton;
                    }


        break;
        //这个case必须放到最后
        //这个root是修改设备的各种信息
    case ROOT:SettingDialog setdialog(ui->textEdit_welcome->toPlainText());
                 if(setdialog.exec()==QDialog::Accepted)
                 {
                     //qDebug()<<QString::fromStdString(setdialog.information.getWELCOME_TEXT());
                     setFlag(UPDATA);

                     //发送请求，它返回一个QNetworkReply对象，
                   /* string   ROOT_PASSWORD;
                     string LOCK_PASSWORD;
                     string  WEATHER;
                     string   WELCOME;
                     string   WELCOME_TEXT;
                     string   DYNAMIC_UPDATE_LOCK;
                   */
                     post_data.clear();


                     post_data.append("BUTLERID=0&");
                     if(setdialog.information.getisRecover())
                     {
                         post_data.append("cmd=5");
                     }else
                     {
                         post_data.append("cmd=2&");
                         post_data.append("ROOT_PASSWORD="+QString::fromStdString(setdialog.information.getROOT_PASSWORD())+"&");
                         post_data.append("LOCK_PASSWORD="+QString::fromStdString(setdialog.information.getLOCK_PASSWORD())+"&");
                         post_data.append("WEATHER="+QString::fromStdString(setdialog.information.getWEATHER())+"&");
                         post_data.append("WELCOME="+QString::fromStdString(setdialog.information.getWELCOME())+"&");

                         post_data.append("WELCOME_TEXT="+QString::fromStdString(setdialog.information.getWELCOME_TEXT())+"&");

                         post_data.append("DYNAMIC_UPDATE_LOCK="+QString::fromStdString(setdialog.information.getDYNAMIC_UPDATE_LOCK())+"&");
                     }

                     request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
                     qDebug()<<"发送数据";
                     qDebug()<<post_data.data();
                    manager->post(request, post_data);

                     //
                 }
                break;


    }
//    当reply对象已经完成了它的功能时，我们需要将它释放
    reply->deleteLater();
}

//void MainWindow::on_readyRead()
//{

//    qDebug()<<new QString(reply->readAll());
//}



void MainWindow::rmVideoFile()
{
    int i;
    QDir *dir=new QDir("/home/pi/pro/video/");
    QStringList filter;
    filter<<"*.h264";
    dir->setNameFilters(filter);
    QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));

    for(i = 0;i<fileInfo->count();i++)
    {
        //before after
        QString  b_name = fileInfo->at(i).filePath();
        QString  a_name=b_name.left(b_name.indexOf(".h264"))+".mp4";

        QProcess::execute("rm -f "+b_name);
        QProcess::execute("rm -f "+a_name);
    }
}
void MainWindow::on_pushButton_refresh_clicked()
{
    setFlag(REFRESH);
    post_data.clear();

//    post_data.append("LOCK_PASSWORD="+passdialog.getPassword()+"&");
    post_data.append("BUTLERID=0&");
    post_data.append("cmd=0");

     request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
     //发送请求，它返回一个QNetworkReply对象，
     manager->post(request, post_data);
}


 void MainWindow::QProcess_monitoring_finished(int exitCode,QProcess::ExitStatus exitStatus){

     int i;
     qDebug()<<"发送了结束信号，哈哈哈";
     qDebug()<<"exitCode="+exitCode;
     this->setIsOpenMonitor(0);

     QDir *dir=new QDir("/home/pi/pro/video/");
     QStringList filter;
     filter<<"*.h264";
     dir->setNameFilters(filter);
     QList<QFileInfo> *fileInfo=new QList<QFileInfo>(dir->entryInfoList(filter));
     char*  cmd_ch;
     for(i = 0;i<fileInfo->count();i++)
     {
         //before after
         QString  b_name = fileInfo->at(i).filePath();
         QString  a_name=b_name.left(b_name.indexOf(".h264"))+".mp4";


         QString cmd = "MP4Box -fps 30 -add "+b_name+" "+a_name;
         QByteArray cmd_ba = cmd.toLatin1();

         cmd_ch=cmd_ba.data();
         qDebug()<<cmd_ch;
         procMP4Box->start(cmd_ch);
         // 等待进程启动
            if (!procMP4Box->waitForStarted())
            {
                qDebug() << "启动失败\n";
                break;
            }
            procMP4Box->waitForFinished();
     }
     if(procMP4Box)
     {
         proc->close();
     }
     //delete cmd_ch;
 }

void MainWindow::on_pushButton_monitoring_clicked()
{
//    MONITORING_DIALOG
    //监控的密码输入框
    PasswordDialog passdialog(MONITORING_DIALOG);
   passdialog.setWindowTitle("请输入管理员密码");
    //验证的是root
    if(passdialog.exec()==QDialog::Accepted)
    {
        //qDebug()<<"Accepted";
        //qDebug()<<passdialog.getPassword();

        setFlag(MONITORING);
        //设置输入的密码
        setPassword(passdialog.getPassword());

        //清空post数据
        post_data.clear();

        //post数据
        post_data.append("ROOT_PASSWORD="+passdialog.getPassword()+"&");
        post_data.append("BUTLERID=0&");
        post_data.append("cmd=3");

        request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
        //发送请求，它返回一个QNetworkReply对象，
        manager->post(request, post_data);

    }
}
/*
 void MainWindow::replyFinishedVideo(QNetworkReply* reply){
     //获取响应的信息，状态码为200表示正常
     QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
     //无错误返回
     if(reply->error() == QNetworkReply::NoError)
     {
         // 读取http响应信息
          QByteArray b = reply->readAll();
          QString data(b);

          //读取第一个字符
          QString res = data.left(1);
          //把第一个;前的删除
          data.remove(0,data.indexOf(";")+1);
          if(res.toInt()==1)
          {
              qDebug()<<"语音识别成功";
              //去掉标志后的数据
              qDebug() <<"收到的数据="+data;

              setVoiceDataFromServer(1,data);


          }else
          {
              qDebug()<<"语音识别失败";
          }
     }else
     {
         //处理错误
         qDebug()<<"返回错误，没有从服务器上面获取到数据";
     }

     //收到响应，因此需要处理

     // 读取http响应信息
    //  QByteArray b = reply->readAll();
    //  QString data(b);
      //qDebug()<<"语音返回的数据="+data;
    reply->deleteLater();
 }
 */
void MainWindow::on_pushButton_voice_clicked()
{

   VoicePasswordDialog vdd;
   if(vdd.exec()==QDialog::Accepted)
   {
       setFlag(MESSAGE);
        post_data.clear();

       // ONEKEY_LOCK = getONEKEY_LOCK(sqlproject, BUTLERID);
        //           WELCOME = getWELCOME(sqlproject, BUTLERID);

       post_data.append("BUTLERID=0&");

       post_data.append("cmd=7&");

       //post_data.append("title=2016/6/5&");
       post_data.append("content="+vdd.getText()+"&");

       request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
       qDebug()<<"发送数据";
       qDebug()<<post_data.data();
       manager->post(request, post_data);

   }
}




void MainWindow::on_pushButton_open_anyway_clicked()
{
    //先验证是否允许，如果允许，打开然后设为不允许，即只能一键开锁一次
   setFlag(ONELOCK);
    post_data.clear();
   post_data.append("BUTLERID=0&");

   post_data.append("cmd=8");

   request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
   qDebug()<<"发送数据";
   qDebug()<<post_data.data();
   manager->post(request, post_data);
}



void MainWindow::on_pushButton_closeLock_clicked()
{
  dealCloseLock();
}
