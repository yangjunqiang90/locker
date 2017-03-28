#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
     ui->checkBox_is_show_welcome->setCheckState( Qt::Checked ) ;
     this->setWindowTitle("设置");
     setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}
SettingDialog::SettingDialog(QString welcome,QWidget *parent):
    QDialog(parent),welcome(welcome),
    ui(new Ui::SettingDialog)
{
     ui->setupUi(this);
     ui->checkBox_is_show_welcome->setCheckState( Qt::Checked ) ;
     this->setWindowTitle("设置");
     setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

SettingDialog::~SettingDialog()
{
    delete ui;
    qDebug("%s,%d",__FILE__,__LINE__);
}

void SettingDialog::showInfo2User(const QString & info,const QString & title){

    QMessageBox box(QMessageBox::Warning,title,info);
    box.setButtonText (QMessageBox::Ok,QString("确 定"));
    box.exec();

}

void SettingDialog::on_pushButton_set_welcome_clicked()
{
//        bool isOK;

//        QString text = QInputDialog::getText(NULL, "设置提示语", "请输入新的提示语",QLineEdit::Normal,welcome, &isOK);

//        if(isOK)
//        {
//                this->information.setWELCOME_TEXT(text.toStdString());
//        }

    VoicePasswordDialog vpd ;
    vpd.setConfirmButton();
    if(vpd.exec()==QDialog::Accepted)
    {
        qDebug()<<vpd.getText();
        this->information.setWELCOME_TEXT(vpd.getText().toStdString());
    }


}


void SettingDialog::on_pushButton_confirm_change_clicked()
{
    int i = 0;

    QList<QAbstractButton *> buttonlist = ui->buttonGroup->buttons();
    QList<QAbstractButton *>::iterator begin,end;
    begin = buttonlist.begin();
    end = buttonlist.end();
    while(begin!=end)
    {

/*
        if((*begin)->isChecked())
        {
              qDebug()<<i;

            qDebug()<<"选中了";
        }
        */
        if(i==0)
        {
            if((*begin)->isChecked())
            {
               this->information.setWEATHER("1");
            }else
            {
                this->information.setWEATHER("0");
            }

        }
        if(i==1)
        {
            if((*begin)->isChecked())
            {
                this->information.setWELCOME("1");
            }else
            {
                this->information.setWELCOME("0");
            }
        }
        begin++;
        i++;
    }

    accept();
    qDebug("%s,%d",__FILE__,__LINE__);
}

void SettingDialog::on_pushButton_cancel_change_clicked()
{
    reject();
}

void SettingDialog::on_pushButton_set_root_password_clicked()
{
//    bool isOK;

//    QString text = QInputDialog::getText(NULL, "设置新的密码", "请输入新的密码",QLineEdit::Normal,welcome, &isOK);

//    if(isOK)
//    {
//        qDebug()<<text;
//            //this->information.setROOT_PASSWORD(text.toStdString());
//    }

    PasswordDialog pd1 ;
    QString text1 ;
    pd1.setSettingPass("请输入新的管理员密码");
    if(pd1.exec()==QDialog::Accepted)
    {
        text1= pd1.getPassword();
        qDebug()<<text1;
        //this->information.setROOT_PASSWORD(text.toStdString());
    }

    PasswordDialog pd2 ;
    if(text1!=NULL)
    {
        pd2.setSettingPass("请再次输入新的管理员密码");
        if(pd2.exec()==QDialog::Accepted)
        {
            QString text = pd2.getPassword();
            qDebug()<<"第一次"+text1;
            qDebug()<<"第二次"+text;
            if(text1==text)
            {
             qDebug()<<"两次输入的一样";
            this->information.setROOT_PASSWORD(text.toStdString());
             accept();

            }else
            {
                showInfo2User("两次密码输入的不一致","提示");
            }
        }
    }
    qDebug("%s,%d",__FILE__,__LINE__);

}

void SettingDialog::on_checkBox_recover_clicked(bool checked)
{
    if(checked==true)
    {
//       QMessageBox info(this, "恢复出厂设置", "恢复出厂设置将初始化用户密码，是否确认？", QMessageBox::Yes | QMessageBox::No,QMessageBox::NoButton );
         QMessageBox info(QMessageBox::Warning,"恢复出厂设置","恢复出厂设置将初始化用户密码");
         info.setStandardButtons (QMessageBox::Yes|QMessageBox::No);
         info.setButtonText (QMessageBox::Ok,QString("确 定"));
         info.setButtonText (QMessageBox::Cancel,QString("取 消"));
         if(info.exec() == QMessageBox::Yes)
         {
               //恢复出厂设置
            qDebug()<<"恢复出厂设置";
            this->information.setisRecover(true);
            accept();
         }

    }else
    {
        qDebug()<<"没有选中";
    }
}


void SettingDialog::on_pushButton_set_lock_password_clicked()
{
    PasswordDialog pd1 ;
    QString text1 ;
    pd1.setSettingPass("请输入新的开锁密码");
    if(pd1.exec()==QDialog::Accepted)
    {
        text1= pd1.getPassword();
        qDebug()<<text1;
        //this->information.setROOT_PASSWORD(text.toStdString());
    }

    PasswordDialog pd2 ;
    if(text1!=NULL)
    {
        pd2.setSettingPass("请再次输入新的开锁密码");
        if(pd2.exec()==QDialog::Accepted)
        {
            QString text = pd2.getPassword();
            //qDebug()<<"第一次"+text1;
           // qDebug()<<"第二次"+text;
            if(text1==text)
            {
             qDebug()<<"两次输入的一样";
            this->information.setLOCK_PASSWORD(text.toStdString());
             accept();

            }else
            {
                showInfo2User("两次密码输入的不一致","提示");
            }
        }
    }
    qDebug("%s,%d",__FILE__,__LINE__);

}

void SettingDialog::on_pushButton_recover_clicked()
{
    QMessageBox info(QMessageBox::Warning,"恢复出厂设置","恢复出厂设置将初始化用户密码");
    info.setStandardButtons (QMessageBox::Yes|QMessageBox::No);
    info.setButtonText (QMessageBox::Ok,QString("确 定"));
    info.setButtonText (QMessageBox::Cancel,QString("取 消"));
    if(info.exec() == QMessageBox::Yes)
    {
          //恢复出厂设置
       qDebug()<<"恢复出厂设置";
       this->information.setisRecover(true);
       accept();
    }
}

