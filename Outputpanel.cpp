#include "Outputpanel.h"

#include<QVBoxLayout>

OutputPanel::OutputPanel(QWidget*parent):QWidget(parent)
{
    outputEdit =new QTextEdit(this);
    outputEdit->setReadOnly(true);

    auto* layout=new QVBoxLayout(this);
    layout->addWidget(outputEdit);
}

void OutputPanel::showResult(const QString& result)
{
    outputEdit->setPlainText(result);
}
