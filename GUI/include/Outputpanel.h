#ifndef OUTPUTPANEL_H
#define OUTPUTPANEL_H

#include <QWidget>
#include<QTextEdit>

class OutputPanel :public QWidget
{
    Q_OBJECT
public:
    explicit OutputPanel(QWidget* parent=nullptr);

public slots:
    void showResult(const QString& result);
private:
    QTextEdit* outputEdit;

};

#endif // OUTPUTPANEL_H
