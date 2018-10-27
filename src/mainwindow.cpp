#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->openAction, SIGNAL(triggered(bool)), SLOT(open()) );
    QObject::connect(ui->saveAction, SIGNAL(triggered(bool)), SLOT(save()) );
    QObject::connect(ui->exitAction, SIGNAL(triggered(bool)), SLOT(close()) );

    l = new QLabel(this);
    ui->textSpace->setAcceptDrops(false);

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Ошибка"), tr("Не могу открыть файл"));
            return;
        }
        QTextStream in(&file);
        ui->textSpace->setText(in.readAll());
        file.close();
    }

    l->setText(fileName);
    ui->statusBar->addWidget(l);
}


void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл") );
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox msgBox; msgBox.setText("Не могу записать файл");
            msgBox.exec();

        }
        else {
            QTextStream stream(&file);
            stream << ui->textSpace->toPlainText();
            stream.flush();
            file.close();
        }
    }
}


void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    if (event->mimeData()->hasFormat("text/uri-list")){
        event->acceptProposedAction();
    }
}


void MainWindow::dropEvent(QDropEvent *event){
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()){
        return;
    }
    QString fileName = urls.first().toLocalFile();
    /*if (fileName.isEmpty()){
        return;
    }
    if (readFile(fileName)){
        setWindowTitle(tr("%1 -%2").arg(fileName).arg(tr("Drag File")));
    }*/
    openDrop(fileName);
}


void MainWindow::openDrop(QString fileName){
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Ошибка"), tr("Не могу открыть файл"));
            return;
        }
        QTextStream in(&file);
        ui->textSpace->setText(in.readAll());
        file.close();
    }

    l->setText(fileName);
    ui->statusBar->addWidget(l);
}
