#ifndef CONTROLEDOCK_H
#define CONTROLEDOCK_H

#include <QDockWidget>

namespace Ui {
class ControleDock;
}

class ControleDock : public QWidget
{
    Q_OBJECT

public:
    explicit ControleDock(QWidget *parent = 0);
    ~ControleDock();

private:
    Ui::ControleDock *ui;
};

#endif // CONTROLEDOCK_H
