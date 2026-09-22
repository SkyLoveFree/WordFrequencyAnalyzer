#include "Tippanel.h"

#include<QLabel>
#include<QHBoxLayout>

TipPanel::TipPanel(QWidget* parent)
    :QWidget(parent)
{
    label=new QLabel(this);

    auto* layout=new QHBoxLayout(this);
    layout->addWidget(label);

}

void TipPanel::showTip(const QString&text)
{
    label->setText(text);
}

void TipPanel::showError(const QString&message)
{
    label->setText(message);
}