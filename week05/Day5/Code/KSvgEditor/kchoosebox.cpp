#include "kchoosebox.h"

KChooseBox::KChooseBox(QString title, KGlobalData::KParamFlag flag, QWidget* parent)
	: KParamBaseBox(std::move(title), flag, parent)
{
	m_pLineChooser = new QComboBox(this);
	m_solidIcon.addFile(":/icons/line/solid.svg");
	m_dottedIcon.addFile(":/icons/line/dotted.svg");
	m_pLineChooser->addItem(m_solidIcon, "solid");
	m_pLineChooser->addItem(m_dottedIcon, "dotted");
	m_pLineChooser->setMinimumHeight(30);
	m_pLineChooser->setStyleSheet("background-color: rgb(255, 255, 255); border-style: none;");
	m_pVLayout->addWidget(m_pLineChooser);

	connect(m_pLineChooser, SIGNAL(currentIndexChanged(int)),
		this, SLOT(selectLineType(int)));
}

KChooseBox::~KChooseBox()
= default;

void KChooseBox::selectLineType(int index)
{
	KGlobalData::KLineFlag flag;
	switch (index)
	{
	case 0:
		flag = KGlobalData::KLineFlag::SolidFlag;
		break;
	case 1:
		flag = KGlobalData::KLineFlag::DottedFlag;
		break;
	default:
		flag = KGlobalData::KLineFlag::NoneFlag;
		break;
	}
	m_pData->setBorderStyle(flag);
	emit borderStyleChanged();
}
