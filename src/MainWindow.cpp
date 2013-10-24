#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dockWidgetContents->addJoypadOverlay( ui->centralWidget );
    ui->dockWidgetContents_2->addJoypadOverlay( ui->centralWidget );

    ui->centralWidget->setJoypadImage("./xbox.png");
    ui->centralWidget->importOverlay("xbox_overlay.xml");
    ui->centralWidget->importActions("actions_polybox.xml");
    ui->centralWidget->processActionsList();
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
