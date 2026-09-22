#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>

class GuiController: public QObject
{
    Q_OBJECT
public:
    explicit GuiController(QObject*parent=nullptr);

public slots:
    void handleAnalyzeRequest(const QString&filePath,const QString&word);

signals:
    void resultReady(const QString& result);
    void errorOccurred(const QString& message);
};

#endif // GUICONTROLLER_H
