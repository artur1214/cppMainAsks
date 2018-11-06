#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:

void dragEnterEvent(QDragEnterEvent *event);

void dropEvent(QDropEvent *event);

private:
    QString buffer;
    QLabel* l;
    Ui::MainWindow *ui;
    void openDrop(QString);

    QString openNew(QString);
    QString getPath();
    QString getFileName(QString);

private slots:
    void save();
    void open();
    void goToHtml();
    void addFileToTab();
};

#endif // MAINWINDOW_H
