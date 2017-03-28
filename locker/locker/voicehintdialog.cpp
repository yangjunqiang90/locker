#include "voicehintdialog.h"
#include "ui_voicehintdialog.h"

VoiceHintDialog::VoiceHintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoiceHintDialog)
{
    ui->setupUi(this);
}

VoiceHintDialog::~VoiceHintDialog()
{
    delete ui;
}

void VoiceHintDialog::on_pushButton_clicked()
{
    accept();
}
