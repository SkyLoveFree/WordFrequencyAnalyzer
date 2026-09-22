#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>
#include"TextAnalyzer.h"
#include"TextSearcher.h"

class InputPanel;


class GuiController: public QObject
{
    Q_OBJECT
public:
    explicit GuiController(QObject*parent=nullptr);

public slots:
    void handleAnalyzeRequest(const QString&filePath,const QString&word);

    void handleContextRequest(int occurence,int before,int after);

signals:
    void resultReady(const QString& result);
    void errorOccurred(const QString& message);

private:
    SkyReader::TextAnalyzer* textAnalyzer;
    InputPanel* inputPanel;
    SkyReader::SearchResult m_lastResult;//保留最近的搜索结果
};

#endif // GUICONTROLLER_HSearchResult;

