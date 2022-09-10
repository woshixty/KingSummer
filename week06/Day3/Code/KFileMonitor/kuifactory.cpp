#include "kuifactory.h"

QPushButton* KUIFactory::createToolBtn(QWidget* parent, const QString& name, const QString& text)
{
	const auto btn = new QPushButton(parent);
    btn->setObjectName(name);
    btn->setText(text);
    btn->setMinimumSize(QSize(80, 30));
    btn->setMaximumSize(QSize(80, 30));
    return btn;
}

QPushButton* KUIFactory::createAddOrBtn(QWidget* parent, const QString& name, const QString& iconStr)
{
    const auto btn = new QPushButton(parent);
    btn->setObjectName(name);
    btn->setMinimumSize(QSize(20, 20));
    btn->setMaximumSize(QSize(20, 20));
    btn->setIcon(QIcon(iconStr));
	btn->setIconSize(QSize(20, 20));
    btn->setStyleSheet(QString("border: none;"));
    return btn;
}

QLabel* KUIFactory::createIconLabel(QWidget* parent, const QString& name, const QString& iconStr)
{
	const auto label = new QLabel(parent);
    label->setMinimumSize(QSize(30, 30));
    label->setMaximumSize(QSize(30, 30));
    label->setObjectName(name);
    QPixmap image(iconStr);
    image = image.scaled(label->width() - 10, label->height() - 10);
    label->setPixmap(image);
    return label;
}

QLabel* KUIFactory::createValueLabel(QWidget* parent, const QString& name, const QString& value)
{
    const auto label = new QLabel(parent);
    label->setObjectName(name);
    label->setMinimumSize(QSize(80, 30));
    label->setStyleSheet("background-color: rgb(225, 225, 225);");
    return label;
}

QLabel* KUIFactory::createStatusLabel(QWidget* parent, const QString& name, const QString& value)
{
    const auto label = new QLabel(parent);
    label->setObjectName(name);
    label->setMinimumSize(QSize(100, 30));
    label->setMaximumWidth(100);
    return label;
}
