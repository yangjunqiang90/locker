#ifndef VOICEHINTDIALOG_H
#define VOICEHINTDIALOG_H

#include <QDialog>

namespace Ui {
class VoiceHintDialog;
}

class VoiceHintDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit VoiceHintDialog(QWidget *parent = 0);
    ~VoiceHintDialog();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::VoiceHintDialog *ui;
};

#endif // VOICEHINTDIALOG_H
