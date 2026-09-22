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

    void contextRequested(int occurence,int before,int after);

private slots:
    void selectFiles();

    void startAnalyze();

    void startOutputtingThecontext();

private:
    QLineEdit* fileEdit;
    QLineEdit* wordEdit;
    QLineEdit* wordOccurrence;
    QLineEdit* contextBefore;
    QLineEdit* contextAfter;
    QPushButton* openButton;
    QPushButton* analyzeButton;
    QPushButton* contextButton;
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

};
