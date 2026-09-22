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

    openButton =new QPushButton("选择文件",this);
    analyzeButton =new QPushButton("开始分析",this);

    fileEdit->setPlaceholderText("请输入文本路径");
    wordEdit->setPlaceholderText("输入要查询频率的词语");

    auto* fileLayout=new QHBoxLayout;
    fileLayout->addWidget(fileEdit);
    fileLayout->addWidget(wordEdit);

    auto* mainLayout=new QVBoxLayout(this);
    mainLayout->addLayout(fileLayout);
    mainLayout->addWidget(wordEdit);
    mainLayout->addWidget(analyzeButton);

    connect(openButton,&QPushButton::clicked,this,&InputPanel::selectFiles);
    connect(analyzeButton,&QPushButton::clicked,this,&InputPanel::startAnalyze);


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
    QString word=fileEdit->text();

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