#include "kparamsbar.h"

#include <utility>

KParamsBar::KParamsBar(QString title, QWidget* parent)
	: QWidget(parent)
{
	m_title = std::move(title);
	setMaximumWidth(170);
	setFocusPolicy(Qt::ClickFocus);
	setStyleSheet("background-color:#2f2f2c");

	m_pVBoxLayout = new QVBoxLayout(this);
	m_pVBoxLayout->setContentsMargins(10, 0, 10, 0);
	m_pVBoxLayout->setAlignment(Qt::AlignTop);

	m_titleLabel = new QLabel(m_title, this);
	m_titleLabel->setAlignment(Qt::AlignCenter);
	m_titleLabel->setStyleSheet("background-color:#2f2f2c; font-size:14px; color:#FFFFFF; font-family: Microsoft YaHei");

	m_pGridLayout = new QGridLayout(this);
	m_pGridLayout->setSpacing(10);

	m_pVBoxLayout->addWidget(m_titleLabel);
	m_pVBoxLayout->addLayout(m_pGridLayout);

	setLayout(m_pVBoxLayout);
}

KParamsBar::~KParamsBar()
= default;
