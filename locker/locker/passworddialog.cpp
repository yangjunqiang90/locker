#include "passworddialog.h"
#include "ui_passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    b=NULL;
}
PasswordDialog::PasswordDialog(int flags,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
    //buf=NULL;
    b=NULL;
isVoiceInput=-1;
    this->flag =flags;
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    //	QMessageBox ( Icon icon, const QString & title, const QString & text,
    //               StandardButtons buttons = NoButton, QWidget * parent = 0,
    //               Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint )

    //父类会帮我们在堆里面删除
    this->hintMessage = new QMessageBox(QMessageBox::NoIcon,"提示","正在录音...",QMessageBox::Yes,this);
    this->dealMessage = new QMessageBox(QMessageBox::NoIcon,"提示","正在处理音频...",QMessageBox::Yes,this);
    //QMessageBox::NoIcon,"In formation","Really to clear data?",QMessageBox::Yes,NULL);
    hintMessage->setButtonText (QMessageBox::Yes,QString("请稍后"));
    dealMessage->setButtonText (QMessageBox::Yes,QString("请稍后"));

    //父类会帮我们在堆里面删除
    manager = new QNetworkAccessManager(this);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedVideo(QNetworkReply*)));

    //外部程序执行完毕
    proc = new QProcess;
    connect(proc, SIGNAL(finished(int,QProcess::ExitStatus )), this, SLOT(QProcess_voice_finished(int ,QProcess::ExitStatus )));


}
PasswordDialog::~PasswordDialog()
{
    qDebug("%s,%d",__FILE__,__LINE__);

     delete ui;

//     if(manager)
//     {
//         qDebug()<<"delete a11";

//         delete manager;
//         qDebug("%s,%d",__FILE__,__LINE__);
//         manager->deleteLater();
//         manager=NULL;
//         qDebug()<<"delete a12";
//          qDebug("%s,%d",__FILE__,__LINE__);
//     }

    if(b)
    {
        qDebug()<<"delete a3";
        delete b;
        b=NULL;
    }

//    if(hintMessage)
//    {
//    qDebug("%s,%d",__FILE__,__LINE__);
//    delete hintMessage;
////    hintMessage->deleteLater();
//    qDebug("%s,%d",__FILE__,__LINE__);
//    hintMessage=NULL;
//    }

    qDebug("%s,%d",__FILE__,__LINE__);
}
QString PasswordDialog::getPassword()
{
    return password;
}

void PasswordDialog::setSettingPass(QString title){
    //ui->pushButton_voice_input->blockSignals(true);
    this->setWindowTitle(title);
}

void PasswordDialog::on_pushButton_confim_clicked()
{
    this->password=ui->lineEdit_password->text();
    accept();
}

void PasswordDialog::on_pushButton_cancel_clicked()
{
  //  qDebug()<<"before";
    reject();
    //qDebug()<<"after";
}

void PasswordDialog::on_pushButton_1_clicked()
{
    ui->lineEdit_password->setText(ui->lineEdit_password->text().append("1"));
}

void PasswordDialog::on_pushButton_2_clicked()
{
   ui->lineEdit_password->setText(ui->lineEdit_password->text().append("2"));
}

void PasswordDialog::on_pushButton_3_clicked()
{
 ui->lineEdit_password->setText(ui->lineEdit_password->text().append("3"));
}
void PasswordDialog::on_pushButton_4_clicked()
{
    ui->lineEdit_password->setText(ui->lineEdit_password->text().append("4"));
}
void PasswordDialog::on_pushButton_delete_clicked()
{
    QString pass =ui->lineEdit_password->text();
    ui->lineEdit_password->setText(pass.remove(pass.length()-1,1));
}

void PasswordDialog::on_pushButton_delete_all_clicked()
{
    ui->lineEdit_password->setText("");
}


void PasswordDialog::on_pushButton_5_clicked()
{
      ui->lineEdit_password->setText(ui->lineEdit_password->text().append("5"));
}

void PasswordDialog::on_pushButton_6_clicked()
{
      ui->lineEdit_password->setText(ui->lineEdit_password->text().append("6"));
}

void PasswordDialog::on_pushButton_7_clicked()
{
      ui->lineEdit_password->setText(ui->lineEdit_password->text().append("7"));
}

void PasswordDialog::on_pushButton_8_clicked()
{
      ui->lineEdit_password->setText(ui->lineEdit_password->text().append("8"));
}

void PasswordDialog::on_pushButton_9_clicked()
{
      ui->lineEdit_password->setText(ui->lineEdit_password->text().append("9"));
}

void PasswordDialog::on_pushButton_0_clicked()
{
      ui->lineEdit_password->setText(ui->lineEdit_password->text().append("0"));
}
 void PasswordDialog::appendData(QString str){
     QString data =ui->lineEdit_password->text();
     //textEdit_voice_result->toPlainText();
     if(data==NULL)
     {
         ui->lineEdit_password->setText(str);
                 //setPlainText(str);
         return ;
     }
     data.append(str);
     ui->lineEdit_password->setText(data);
 }


void PasswordDialog::replyFinishedVideo(QNetworkReply* reply){


    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray b = reply->readAll();
        QString data(b);

        //把第一个;前的删除
        data.remove(0,data.indexOf(";")+1);
//qDebug();
        //qDebug("%s %d",__FILE__,__LINE__);
        data=chTo123(data);
       // qDebug("%s %d",__FILE__,__LINE__);
        int index;
        while((index=data.indexOf("，"))!=-1)
        {
            data.remove(index,1);
        }

        qDebug()<<data;
        this->appendData(data);

        if(!isVoiceInput)
        {
            this->password=ui->lineEdit_password->text();
            accept();

        }

    }else
    {
         QMessageBox::about(NULL, "提示", "获取数据失败");
    }
    dealMessage->close();
        reply->deleteLater();
}

void PasswordDialog::QProcess_voice_finished(int code,QProcess::ExitStatus exitStat){
    qDebug()<<"外部程序执行完毕";
    qDebug()<<"录音结束";
    hintMessage->close();
    dealMessage->show();

    QFile file("./test.wav");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"打开文件失败";
        return ;
    }
    int file_len = file.size();
    QDataStream in(&file);
    b = new char[file_len];
    in.readRawData( b, file_len);
    file.close();
//static QString serverUrl = "http://192.168.1.106:8080/WebServer/servlet/myServler";
    request.setUrl(QUrl("http://"+ip+":8080/WebServer/servlet/myServler?filename=test.wav&cmd=4&filelen="+QString::number(file_len)));

    video_data.clear();
    video_data = QByteArray(b, file_len);
    manager->post(request,video_data);
}
void PasswordDialog::on_pushButton_voice_input_clicked()
{

    isVoiceInput=1;
    /*
     //清空
       buf = NULL;

       PasswordDialog passdialog(PASSWORD_DIALOG);
       passdialog.setWindowTitle("请输入开箱密码");
       if(passdialog.exec()==QDialog::Accepted)
       {
          // qDebug()<<passdialog.getPassword();

           setFlag(LOCK);

           post_data.clear();

           post_data.append("LOCK_PASSWORD="+passdialog.getPassword()+"&");
           post_data.append("BUTLERID=0&");
           post_data.append("cmd=1");

            request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
            //发送请求，它返回一个QNetworkReply对象，
            manager->post(request, post_data);
       }
*/
    hintMessage->show();
       //录音4秒钟，频率：16000 格式：wav 位数：16位 通道数：单通道 名字：test.wav
       proc->start("arecord -D \"plughw:1,0\" -d 4 -r 16000 -t wav -f S16_LE -c 1 test.wav");
       // 等待进程启动
          if (!proc->waitForStarted())
          {
              QMessageBox::about(NULL, "提示", "启动失败");
              qDebug() << "启动失败\n";

              return ;
          }
}
QString PasswordDialog::chTo123(const QString &c){

    int index;
    QString res = c;

    index = -1;
    while((index=res.indexOf("一"))!=-1)
    {
        //qDebug("%s %d %d",__FILE__,__LINE__,index);
       // qDebug()<<res;
        res.replace(index,1,"1");
        //qDebug("%s %d",__FILE__,__LINE__);
       // qDebug()<<res;
    }
//qDebug("%s %d",__FILE__,__LINE__);
    index = -1;
    while((index=res.indexOf("二"))!=-1)
    {
       // qDebug("%s %d",__FILE__,__LINE__);
        res.replace(index,1,"2");
    }
//qDebug("%s %d",__FILE__,__LINE__);
    index = -1;
    while((index=res.indexOf("三"))!=-1)
    {
       // qDebug("%s %d",__FILE__,__LINE__);
        res.replace(index,1,"3");
    }
//qDebug("%s %d",__FILE__,__LINE__);
    index = -1;
    while((index=res.indexOf("四"))!=-1)
    {
        //qDebug("%s %d",__FILE__,__LINE__);
        res.replace(index,1,"4");
    }
//qDebug("%s %d",__FILE__,__LINE__);
    index = -1;
    while((index=res.indexOf("五"))!=-1)
    {
        res.replace(index,1,"5");
    }

    index = -1;
    while((index=res.indexOf("六"))!=-1)
    {
        res.replace(index,1,"6");
    }

    index = -1;
    while((index=res.indexOf("七"))!=-1)
    {
        res.replace(index,1,"7");
    }

    index = -1;
    while((index=res.indexOf("八"))!=-1)
    {
        res.replace(index,1,"8");
    }

    index = -1;
    while((index=res.indexOf("九"))!=-1)
    {
        res.replace(index,1,"9");
    }

    index = -1;
    while((index=res.indexOf("零"))!=-1)
    {
        res.replace(index,1,"0");
    }

     int i,j,flag,size;
     QString tem;
     size=res.size();
     qDebug("%s %d",__FILE__,__LINE__);
     qDebug()<<res;
     for(i=0;i<size;i++)
     {
         flag=0;
         tem=res.at(i);
         for(j = 0 ;j<10;j++)
         {

             if(tem==QString::number(j))
             {
                 flag=1;
                 break;
             }
         }
         if(!flag){
             qDebug("%s %d %d",__FILE__,__LINE__,i);
             qDebug()<<res.at(i);
             //中文
             res.remove(i,1);
             i--;
             size--;
         }
         qDebug("%s %d",__FILE__,__LINE__);
         qDebug()<<res;
     }
     qDebug("%s %d",__FILE__,__LINE__);
     qDebug()<<res;
    return res;
}

void PasswordDialog::on_pushButton_voice_verify_clicked()
{

    isVoiceInput=0;
    ui->lineEdit_password->setText("");



    /*
     //清空
       buf = NULL;

       PasswordDialog passdialog(PASSWORD_DIALOG);
       passdialog.setWindowTitle("请输入开箱密码");
       if(passdialog.exec()==QDialog::Accepted)
       {
          // qDebug()<<passdialog.getPassword();

           setFlag(LOCK);

           post_data.clear();

           post_data.append("LOCK_PASSWORD="+passdialog.getPassword()+"&");
           post_data.append("BUTLERID=0&");
           post_data.append("cmd=1");

            request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
            //发送请求，它返回一个QNetworkReply对象，
            manager->post(request, post_data);
       }
*/
    hintMessage->show();
       //录音4秒钟，频率：16000 格式：wav 位数：16位 通道数：单通道 名字：test.wav
       proc->start("arecord -D \"plughw:1,0\" -d 4 -r 16000 -t wav -f S16_LE -c 1 test.wav");
       // 等待进程启动
          if (!proc->waitForStarted())
          {
              QMessageBox::about(NULL, "提示", "启动失败");
              qDebug() << "启动失败\n";

              return ;
          }
}
