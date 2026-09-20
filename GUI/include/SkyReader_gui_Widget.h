#include <QWidget>
#include<QMainWindow>
#include"TextAnalyzer.h"

namespace Ui {
class SkyReaderWidget;
}
class SkyReader_gui_Widget :public QWidget
{
    Q_OBJECT
public:
    explicit SkyReader_gui_Widget(QWidget *parent = nullptr);
    ~SkyReader_gui_Widget() override;

private:
    Ui::SkyReaderWidget* ui;
    SkyReader::TextAnalyzer m_TextAnalyzer;
    void dragEnterEvent(QDragEnterEvent* event)override;
    void dropEvent(QDropEvent* event)override;
private:signals:
    void fileSelected(std::string path);//文件被选择完毕，顺便传递路径
private slots:

    void selectFiles();//用户选择文件
    void analyzeFile(std::string path);//分析文件
    void printFrequency();
};
