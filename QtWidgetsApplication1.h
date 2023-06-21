#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include"OpenGLWindow.h"
#include <QStandardItemModel>
#include <QTreeView>
#include <QThread>
#include<QTimer>


class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget* parent = nullptr);
    ~QtWidgetsApplication1();
    QTreeView* treeView = new QTreeView(this);
    QStandardItemModel* model = new QStandardItemModel(treeView);
    QThread* actionThread = new QThread();

private:
    Ui::QtWidgetsApplication1Class ui;
    OpenGLWindow* opWindow;
    
    QTimer* timer;
    //void mousePressEvent(QMouseEvent* event) override;

private slots:
    void createLine();
    void createCircle();
    void createRectangle();
    void createPolyline();
    void resetFunction();
};
