#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ocilib::Environment::Initialize();
    ui->lstResult->addItem("Environment::Initialize success.");
}

MainWindow::~MainWindow()
{
    OracleCleanup();
    ui->lstResult->addItem("Cleanup()");
    qApp->processEvents();

    delete ui;
}

void MainWindow::OracleCleanup()
{
    if(ocilib::Environment::Initialized())
        ocilib::Environment::Cleanup();
    ui->lstResult->addItem("Cleanup success.");
}

void MainWindow::on_btnConnect_clicked()
{
    if(ui->btnConnect->text() == "Connect")
    {
        ui->lstResult->clear();
        QString db = ui->leDatabase->text();
        QString host = ui->leHost->text();
        QString port = ui->lePort->text();
        QString user = ui->leLogin->text();
        QString pass = ui->lePassword->text();
        QString role = ui->cbRole->currentText();
        QString home = "";

        if(!host.isEmpty())
        {
            home += host;
            if(!port.isEmpty())
                home += ":" + port;
            db = home + "/" + db;
        }
        ui->lstResult->addItem("Db: " + db);


        qApp->processEvents();


        try{

            con = ocilib::Connection (db.toLocal8Bit().constData(),
                                         user.toLocal8Bit().constData(),
                                         pass.toLocal8Bit().constData(),
                                         ocilib::Environment::SessionSysDba);
            state = ocilib::Statement(con);
            ui->lstResult->addItem("Connection success.");
            ui->btnConnect->setText("Disconnect");

        }catch(std::exception &ex)
        { 
            ui->lstResult->addItem(ex.what());
        }

    }else {
        con.Close();
        ui->lstResult->addItem("Connection close().");
        ui->btnConnect->setText("Connect");
    }
}




void MainWindow::on_btnQuery_clicked()
{
    ui->lstResult->clear();
    try {
        state.Execute(ui->teSQL->document()->toPlainText().toLocal8Bit().constData());
        ocilib::Resultset rs = state.GetResultset();

        while(rs++)
        {
            ui->lstResult->addItem(QString::fromLocal8Bit(rs.Get<std::string>(1).data()));
        }

    } catch (std::exception &ex) {
        ui->lstResult->addItem(ex.what());
    }
}
