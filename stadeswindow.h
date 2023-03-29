#ifndef STADESWINDOW_H
#define STADESWINDOW_H
#include <QMainWindow>
#include <QListWidget>

class StadesWindow : public QMainWindow{
    Q_OBJECT
public:
    StadesWindow(QWidget *parent = nullptr);
private:
    QListWidget *listWidget;
};

#endif