#include "SkyReader_gui_Widget.h"
#include "ui_SkyReaderWidget.h"

#include<QFileDialog>
#include<QDebug>
#include<QPushButton>
#include<QDragEnterEvent>
#include<QDropEvent>
#include<QMimeData>
#include<QUrl>

SkyReader_gui_Widget::SkyReader_gui_Widget(QWidget* parent)
    : QWidget(parent)
    ,ui(new Ui::SkyReaderWidget)
{
    ui->setupUi(this);
    setAcceptDrops(true);//allow qwidget accept dropevent;
    connect(
        ui->OpenFileButton,
        &QPushButton::clicked,
        this,
        &SkyReader_gui_Widget::selectFiles
        );
    connect(
        ui->WordsFrequencyButton,
        &QPushButton::clicked,
        this,
        &SkyReader_gui_Widget::printFrequency
        );
    connect(
        this,
        &SkyReader_gui_Widget::fileSelected,
        this,
        &SkyReader_gui_Widget::analyzeFile
        );

}

SkyReader_gui_Widget::~SkyReader_gui_Widget()
{
    delete ui;
}

void  SkyReader_gui_Widget::selectFiles()
{
    QString path=QFileDialog::getOpenFileName(
            this,
            "打开文件",
            ".",
            "Text (*.txt)"
        );
    if(path.isEmpty()) return;
    emit fileSelected(path.toStdString());
    //qDebug()<<"Open File::"<<path;
    //m_TextAnalyzer.loadFile(path.toStdString());
};

void SkyReader_gui_Widget::analyzeFile(std::string path)
{
    m_TextAnalyzer.loadFile(path);
    m_TextAnalyzer.analyzeChar("你好");
}

void SkyReader_gui_Widget::printFrequency()
{
    SkyReader::SearchResult temp=m_TextAnalyzer.search(ui->WordsLabel->text().toStdString());
    ui->WordsFrequency->setText(
        QString("出现次数:: %1").arg(temp.count));
}

void SkyReader_gui_Widget::dragEnterEvent(QDragEnterEvent* event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void SkyReader_gui_Widget::dropEvent(QDropEvent* event)
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
            emit fileSelected(path.toStdString()); //这里需要重点注意，当前只是测试，很容易产生bug，比如一次上传多个文件
        }

    }
}