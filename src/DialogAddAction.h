#ifndef DIALOGADDACTION_H
#define DIALOGADDACTION_H

#include <QDialog>
#include <QTextEdit>

#include "Action.h"

namespace Ui {
class DialogAddAction;
}

class DialogAddAction : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddAction(QWidget *parent = 0);
    ~DialogAddAction();

private slots:
    void on_cancel_clicked();

    void on_add_clicked();

private:
    Ui::DialogAddAction *ui;
};

#endif // DIALOGADDACTION_H
