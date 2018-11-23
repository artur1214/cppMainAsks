#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    this->netManager = new QNetworkAccessManager();
    ui->setupUi(this);
    ui->saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    ui->openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    QObject::connect(ui->openAction, SIGNAL(triggered(bool)), SLOT(addFileToTab()));
    QObject::connect(ui->saveAction, SIGNAL(triggered(bool)), SLOT(save()) );
    QObject::connect(ui->exitAction, SIGNAL(triggered(bool)), SLOT(close()) );
    QObject::connect(ui->netAction, SIGNAL(triggered(bool)), SLOT(openNet()) );
    this->setFixedSize(this->size());
    l = new QLabel(this);
    ui->statusBar->addWidget(l);
    ui->currTextEdit->setAcceptDrops(false);
    //ui->openAction->trigger();
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

        QWidget *curWidget = ui->tabPanel->currentWidget();

        QTextEdit *t = curWidget->findChild<QTextEdit*>("currTextEdit");
        t->setText(in.readAll());
        file.close();
        l->setText(fileName);
       // ui->statusBar->addWidget(l);
    }



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
            stream << ui->tabPanel->currentWidget()->findChild<QTextEdit*>("currTextEdit")->toPlainText();
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
        QWidget *curWidget = ui->tabPanel->currentWidget();

        QTextEdit *t = curWidget->findChild<QTextEdit*>("currTextEdit");
        ui->tabPanel->setTabText(ui->tabPanel->currentIndex(), getFileName(fileName));
        t->setText(in.readAll());

        file.close();
        l->setText(fileName);
        //ui->statusBar->addWidget(l);
    }



}


void MainWindow::goToHtml(){
    //buffer = ui->tabPanel->currentWidget()->findChild<QTextEdit*>("currTextEdit")->getHtml
}


void MainWindow::addFileToTab(){

    QString path = getPath();
    QString filename = getFileName(path);
    QString data = openNew(path);
    if(data == NULL){
        return;
    }
    QWidget *w;
    w = new QWidget();
    w->setObjectName("buff");
    QTextEdit *txtEdit = new QTextEdit(w);
    txtEdit->setGeometry(ui->currTextEdit->x(), ui->currTextEdit->y(), ui->currTextEdit->width(), ui->currTextEdit->height() );
    txtEdit->setObjectName("currTextEdit");
    //QString filename = open();
    txtEdit->setText(data);
    txtEdit->setAcceptDrops(false);

    ui->tabPanel->addTab(w, filename);

    ui->tabPanel->setCurrentIndex(ui->tabPanel->count() - 1);
    ui->tabPanel->update();
}


QString MainWindow::getFileName(QString path){
    int pos = path.lastIndexOf(QChar('/'));
    QString res = path.right(pos + 1);
    return res;
}


QString MainWindow::getPath(){
    QString path = QFileDialog::getOpenFileName(this, tr("Открыть файл"));
    return path;
}

QString MainWindow::openNew(QString path){
    QString fileName = path;

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Ошибка"), tr("Не могу открыть файл"));
            return "";
        }
        QTextStream in(&file);
        l->setText(fileName);
        //ui->statusBar->addWidget(l);
        return in.readAll();
        file.close();
    }
    return NULL;

}


void MainWindow::openNet(){

    QString url = "http";
    QNetworkReply *data = this->netManager->get(QNetworkRequest(QUrl("http://avartur92.pythonanywhere.com")));

    if(!data->error()){
        QJsonDocument doc = QJsonDocument::fromJson(data->readAll());
        QJsonObject root = doc.object();
        if(doc.isObject()){
            qDebug() << "пришел объект";
        }
        if(doc.isArray()){
            qDebug() << "Пришел массив";
        }
        if(doc.isEmpty()){
            qDebug() << "я дибил";
        }

        QWidget *w;
        w = new QWidget();
        w->setObjectName("buff");
        QTextEdit *txtEdit = new QTextEdit(w);
        txtEdit->setGeometry(ui->currTextEdit->x(), ui->currTextEdit->y(), ui->currTextEdit->width(), ui->currTextEdit->height() );
        txtEdit->setObjectName("currTextEdit");
        //QString filename = open();
        //txtEdit->setText(root.value(root.keys().at(0)).toString());
        txtEdit->setAcceptDrops(false);

        ui->tabPanel->addTab(w, url);

        ui->tabPanel->setCurrentIndex(ui->tabPanel->count() - 1);
        ui->tabPanel->update();
        }

}
