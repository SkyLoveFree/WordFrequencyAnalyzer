#include "Guicontroller.h"
#include<QDebug>


GuiController::GuiController(QObject*parent):QObject(parent)
{
    textAnalyzer=new SkyReader::TextAnalyzer();
}

void GuiController::handleAnalyzeRequest(const QString&filePath,const QString&word)
{
    try
    {
        textAnalyzer->loadFile(filePath.toStdString());
        m_lastResult=textAnalyzer->search(word.toStdString());
        qDebug()<<m_lastResult.count;
        QString result=word+"出现了  "+QString::number(m_lastResult.count)+" 次  ";
        emit resultReady(result);

    }
    catch (const std::exception& e)
    {
        emit errorOccurred(QString::fromUtf8(e.what()));
    }
}

void GuiController::handleContextRequest(int occurence,int before,int after)
{
    try
    {
        qDebug()<<"上下文功能测试 controller部分正常";
        before=before>0? before:0;
        after=after>0? after:0;
        size_t before_size=static_cast<size_t>(before);
        size_t after_size=static_cast<size_t>(after);
        std::string context=textAnalyzer->getContext(m_lastResult,static_cast<size_t>(occurence),{before_size,after_size});
        QString result=QString::fromStdString(context);
        emit resultReady(result);
    }
    catch(const std::exception& e)
    {
        emit errorOccurred(QString::fromUtf8(e.what()));
    }
}