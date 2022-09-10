#include "kcanvasparamsbar.h"

#include <utility>

KCanvasParamsBar::KCanvasParamsBar(QWidget* parent)
	: KParamsBar(QStringLiteral("��������"), parent)
{
	m_pWidthBox = new KValueBox(QStringLiteral("���"), KGlobalData::getGlobalDataIntance()->getCanvasWidth(), this);
	m_pHeightBox = new KValueBox(QStringLiteral("�߶�"), KGlobalData::getGlobalDataIntance()->getCanvasHeight(), this);
	m_pColorBox = new KColorBox(QStringLiteral("��ɫ"), KGlobalData::getGlobalDataIntance()->getCanvasColor(), this);

	// ��ӵ����񲼾�
	// �� 0 �� �� 0 ��
	m_pGridLayout->addWidget(m_pWidthBox, 0, 0);
	// �� 0 �� �� 1 ��
	m_pGridLayout->addWidget(m_pHeightBox, 0, 1);
	m_pGridLayout->addWidget(m_pColorBox, 1, 0);
}

KCanvasParamsBar::~KCanvasParamsBar()
= default;
