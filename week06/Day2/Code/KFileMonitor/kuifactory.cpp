#include "kuifactory.h"

QPushButton* KUIFactory::createToolBtn(QWidget* parent, const QString& name, const QString& text)
{
	const auto btn = new QPushButton(parent);
    btn->setObjectName(name);
    btn->setText(text);
    btn->setMinimumSize(QSize(40, 40));
    btn->setMaximumSize(QSize(40, 40));
    btn->setStyleSheet(QString("background-color: rgb(169, 169, 169);"));
    return btn;
}
