#pragma once

#include <QWidget>

class InputPanel; //前置声明
class OutputPanel;
class TipPanel;
class GuiController;

class MyMainWindow :public QWidget
{
    Q_OBJECT
public:
    explicit MyMainWindow(QWidget*parent=nullptr);

private:
    InputPanel* inputPanel;
    OutputPanel* outputPanel;
    TipPanel* tipPanel;
    GuiController* guiController;
};


