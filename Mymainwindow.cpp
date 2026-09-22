#include "Mymainwindow.h"

#include"InputPanel.h"
#include"Outputpanel.h"
#include"Tippanel.h"
#include"Guicontroller.h"

#include<QVBoxLayout>



MyMainWindow::MyMainWindow(QWidget *parent)
    :QWidget(parent)
{
    inputPanel=new InputPanel(this);
    outputPanel=new OutputPanel(this);
    tipPanel=new TipPanel(this);

    guiController=new GuiController(this);

    auto* layout=new QVBoxLayout(this);

    layout->addWidget(inputPanel);
    layout->addWidget(outputPanel);
    layout->addWidget(tipPanel);


    connect(inputPanel,&InputPanel::analyzeRequested,guiController,&GuiController::handleAnalyzeRequest);

    connect(
        guiController,&GuiController::resultReady,
        outputPanel,&OutputPanel::showResult
        );

    connect(
        guiController,&GuiController::errorOccurred,
        tipPanel,&TipPanel::showError
        );
}
