#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
void MainWindow::loadJoystick()
{
    QJoystick *nJoystick = QJoystickEnumerator::enumerate("/dev/input", this);
    if(nJoystick != NULL)
    {
        ui->centralWidget->joystick = nJoystick;
        ui->centralWidget->loadConfig( nJoystick->getInfo().name+"_conf.xml" );

        ui->dockWidgetContents->addJoypadOverlay( ui->centralWidget );
        ui->dockWidgetContents_2->addJoypadOverlay( ui->centralWidget );

        connect(nJoystick, SIGNAL(axisChanged(int,short)),  ui->centralWidget, SLOT(updateAxis(int,short)));
        connect(nJoystick, SIGNAL(buttonChanged(int,bool)),  ui->centralWidget, SLOT(updateButton(int,bool)));
    }
    else
    {
        ::exit( 0 );
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
