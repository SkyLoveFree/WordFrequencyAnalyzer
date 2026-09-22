#include "Guicontroller.h"

GuiController::GuiController(QObject*parent):QObject(parent)
{
}

void GuiController::handleAnalyzeRequest(const QString&filePath,const QString&word)
{
    try {
        QString result =
            "文件：" + filePath +
            "\n搜索词：" + word +
                         "\n找到次数：42";
        emit resultReady(result);

    }
    catch (const std::exception& e)
    {
        emit errorOccurred(QString::fromUtf8(e.what()));
    }
}