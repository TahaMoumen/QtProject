#ifndef EQUIPESWINDOW_H
#define EQUIPESWINDOW_H
#include <QMainWindow>
#include <QListWidget>

class EquipesWindow : public QMainWindow{
    Q_OBJECT
public:
    EquipesWindow(QWidget *parent = nullptr);
private:
    QListWidget *listWidget;
};

#endif