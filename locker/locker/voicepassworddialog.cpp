#include "voicepassworddialog.h"
#include "ui_voicepassworddialog.h"

VoicePasswordDialog::VoicePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoicePasswordDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("文本框");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    buf=NULL;
    proc = new QProcess;
    isConfimFlag=0;
    this->hintMessage = new QMessageBox(QMessageBox::NoIcon,"提示","正在录音...",QMessageBox::Yes,this);
    this->dealMessage = new QMessageBox(QMessageBox::NoIcon,"提示","正在处理音频...",QMessageBox::Yes,this);

    //QMessageBox::NoIcon,"In formation","Really to clear data?",QMessageBox::Yes,NULL);
    hintMessage->setButtonText (QMessageBox::Yes,QString("请稍后"));
    dealMessage->setButtonText (QMessageBox::Yes,QString("请稍后"));

    manager = new QNetworkAccessManager(this);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinishedVideo(QNetworkReply*)));

    //外部程序执行完毕
    connect(proc, SIGNAL(finished(int,QProcess::ExitStatus )), this, SLOT(QProcess_voice_finished(int ,QProcess::ExitStatus )));
}

VoicePasswordDialog::~VoicePasswordDialog()
{

    qDebug("%s,%d",__FILE__,__LINE__);
    if(buf){
         qDebug("%s,%d",__FILE__,__LINE__);
    delete buf;
    buf=NULL;
    }
    qDebug("%s,%d",__FILE__,__LINE__);
    if(proc!=NULL)
    delete proc;

    delete ui;
}


void VoicePasswordDialog::setConfirmButton(){
    ui->pushButton_confirm_send->setText("确认");
    isConfimFlag=1;
}

void VoicePasswordDialog::setText(QString text){
    this->text=text;
}
QString VoicePasswordDialog::getText(){
    return text;
}

void VoicePasswordDialog::replyFinishedVideo(QNetworkReply* reply){


    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray b = reply->readAll();
        QString data(b);
        qDebug()<<"服务器响应的数据="+data;
        data.remove(0,data.indexOf(";")+1);
        this->appendData(data);

    }else
    {
         QMessageBox::about(NULL, "提示", "获取数据失败");
    }
    dealMessage->close();
        reply->deleteLater();
}
 void VoicePasswordDialog::QProcess_voice_finished(int code,QProcess::ExitStatus exitStat){
     qDebug()<<"外部程序执行完毕";
     qDebug()<<"录音结束";
     hintMessage->close();
     qDebug()<<"开始处理音频";
     dealMessage->show();
     QFile file("./test.wav");
     if(!file.open(QIODevice::ReadOnly))
     {
         qDebug()<<"打开文件失败";
         return ;
     }
     int file_len = file.size();
     QDataStream in(&file);
     buf = new char[file_len];
     in.readRawData( buf, file_len);
     file.close();
 //static QString serverUrl = "http://192.168.1.106:8080/WebServer/servlet/myServler";
     request.setUrl(QUrl("http://"+ip+":8080/WebServer/servlet/myServler?filename=test.wav&cmd=4&filelen="+QString::number(file_len)));

     video_data.clear();
     video_data = QByteArray(buf, file_len);
     manager->post(request,video_data);
 }

void VoicePasswordDialog::on_pushButton_begin_record_clicked()
{
    if(hintMessage)
    hintMessage->show();
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
void VoicePasswordDialog::appendData(QString str){
   QString data =ui->textEdit_voice_result->toPlainText();
   if(data==NULL)
   {
       ui->textEdit_voice_result->setPlainText(str);
       return ;
   }
   data.append(str);
   ui->textEdit_voice_result->setPlainText(data);

}



void VoicePasswordDialog::on_pushButton_delete_text_clicked()
{
    QString data =ui->textEdit_voice_result->toPlainText();
    if(data==NULL)
    {
        return ;
    }
    ui->textEdit_voice_result->setPlainText(data.remove(data.length()-1,1));
}

void VoicePasswordDialog::on_pushButton_confirm_send_clicked()
{
    if(isConfimFlag==1)
    {
        //是确认键
        setText(ui->textEdit_voice_result->toPlainText());
       // qDebug()<<"dsfsd";


    }else{
        //是发送键
        setText(ui->textEdit_voice_result->toPlainText());
        //cmd=7
    }
    accept();
}

void VoicePasswordDialog::on_pushButton_cancel_send_clicked()
{
    reject();
}
