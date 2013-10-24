#ifndef CONTROLEWIDGET_H
#define CONTROLEWIDGET_H

#include <QWidget>

namespace Ui {
class ControleWidget;
}

class ControleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControleWidget(QWidget *parent = 0);
    ~ControleWidget();

private:
    Ui::ControleWidget *ui;
};

#endif // CONTROLEWIDGET_H
