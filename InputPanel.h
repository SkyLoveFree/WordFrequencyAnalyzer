#pragma once

#include<QWidget>
#include<QString>

class QLineEdit;
class QPushButton;

class InputPanel: public QWidget
{
    Q_OBJECT

public:
    explicit InputPanel(QWidget*parent =nullptr);

signals:
    void analyzeRequested(const QString& FilePath,const QString& word);

private slots:
    void selectFiles();

    void startAnalyze();

private:
    QLineEdit* fileEdit;
    QLineEdit* wordEdit;
    QPushButton* openButton;
    QPushButton* analyzeButton;
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

};
