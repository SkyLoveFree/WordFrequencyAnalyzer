#ifndef TIPPANEL_H
#define TIPPANEL_H

#include <QObject>
#include <QWidget>

class TipPanel: public QWidget
{
    Q_OBJECT
public:
    explicit TipPanel(QWidget*parent=nullptr);

public slots:
    void showTip(const QString& text);
    void showError(const QString& message);

private:
    QLabel* label;
};

#endif // TIPPANEL_H
