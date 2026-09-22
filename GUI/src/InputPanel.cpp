#pragma once

#include"InputPanel.h"

#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QFileDialog>

#include<QDragEnterEvent>
#include<QDropEvent>
#include<QMimeData>
#include<QUrl>

#include<QString>

InputPanel::InputPanel(QWidget*parent):QWidget(parent)
{

    setAcceptDrops(true);

    fileEdit=new QLineEdit(this);
    wordEdit=new QLineEdit(this);
    wordOccurrence=new QLineEdit(this);
    contextBefore=new QLineEdit(this);
    contextAfter=new QLineEdit(this);

    openButton =new QPushButton("选择文件",this);
    analyzeButton =new QPushButton("开始分析",this);
    contextButton=new QPushButton("开始输出上下文",this);

    fileEdit->setPlaceholderText("请输入文本路径");
    wordEdit->setPlaceholderText("输入要查询频率的词语");

    wordOccurrence->setPlaceholderText("请输入要查询第几次词语出现的位置");
    contextBefore->setPlaceholderText("输入想要查询词语的前文范围");
    contextAfter->setPlaceholderText("请输入想要查询的词语的后文范围");

    auto* fileLayout=new QHBoxLayout;
    fileLayout->addWidget(fileEdit);
    fileLayout->addWidget(openButton);

    auto* contextLayout=new QHBoxLayout;
    contextLayout->addWidget(wordOccurrence);
    contextLayout->addWidget(contextBefore);
    contextLayout->addWidget(contextAfter);

    auto* mainLayout=new QVBoxLayout(this);
    mainLayout->addLayout(fileLayout);
    mainLayout->addWidget(wordEdit);
    mainLayout->addWidget(analyzeButton);
    mainLayout->addLayout(contextLayout);
    mainLayout->addWidget(contextButton);

    connect(openButton,&QPushButton::clicked,this,&InputPanel::selectFiles);
    connect(analyzeButton,&QPushButton::clicked,this,&InputPanel::startAnalyze);
    connect(contextButton,&QPushButton::clicked,this,&InputPanel::startOutputtingThecontext);

}

void  InputPanel::selectFiles()
{
    QString path=QFileDialog::getOpenFileName(
        this,
        "打开文件",
        ".",
        "Text (*.txt)"
        );
    if(path.isEmpty()) return;
    fileEdit->setText(path);
};

void InputPanel::startAnalyze()
{
    QString path=fileEdit->text();
    QString word=wordEdit->text();

    if(path.isEmpty()||word.isEmpty())
        return;
    emit analyzeRequested(path,word);
}

void InputPanel::dragEnterEvent(QDragEnterEvent* event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void InputPanel::dropEvent(QDropEvent* event)
{
    const QMimeData *mime=event->mimeData();
    if(mime->hasUrls())
    {
        QList<QUrl> urls=mime->urls();
        QList<QString> paths;
        for(auto url:urls)
        {
            paths.append(url.toLocalFile());
        }
        for(auto path:paths)
        {
            fileEdit->setText(path);
        }

    }
}

void InputPanel::startOutputtingThecontext()
{
    int occurrence=wordOccurrence->text().toInt()-1;
    int before=contextBefore->text().toInt();
    int after=contextAfter->text().toInt();
    emit  contextRequested(occurrence,before,after);
    qDebug()<<"上下文功能测试,InputPanel部分正常";
}