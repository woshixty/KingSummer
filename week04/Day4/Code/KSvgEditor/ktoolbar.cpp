#include "ktoolbar.h"

KToolBar::KToolBar(QWidget* parent)
	: QWidget(parent)
{
	setMaximumWidth(50);
	setMinimumWidth(32);
	setAttribute(Qt::WA_StyledBackground, true);
	setStyleSheet("background-color: black;");
	// ��ֱ����
	m_pVLayout = new QVBoxLayout(this);
	// ���뷽ʽ
	m_pVLayout->setAlignment(Qt::AlignCenter | Qt::AlignTop);
	// ����������
	m_pVLayout->setSpacing(25);

	m_pBtnGroup = new QButtonGroup(this);
	// ���û���
	m_pBtnGroup->setExclusive(true);

	// �����Զ��尴ť
	m_pMouseBtn = new KToolButton("mouse.svg", this);
	m_pPenBtn = new KToolButton("pen.svg", this);
	m_pLineBtn = new KToolButton("line.svg", this);
	m_pRectBtn = new KToolButton("rect.svg", this);
	m_pCircleBtn = new KToolButton("circle.svg", this);
	m_pTextBtn = new KToolButton("text.svg", this);

	// ����ť��ӵ���ť��
	m_pBtnGroup->addButton(m_pMouseBtn);
	m_pBtnGroup->addButton(m_pPenBtn);
	m_pBtnGroup->addButton(m_pLineBtn);
	m_pBtnGroup->addButton(m_pRectBtn);
	m_pBtnGroup->addButton(m_pCircleBtn);
	m_pBtnGroup->addButton(m_pTextBtn);

	// ��Ӳ���
	m_pVLayout->addWidget(m_pMouseBtn);
	m_pVLayout->addWidget(m_pPenBtn);
	m_pVLayout->addWidget(m_pLineBtn);
	m_pVLayout->addWidget(m_pRectBtn);
	m_pVLayout->addWidget(m_pCircleBtn);
	m_pVLayout->addWidget(m_pTextBtn);

	// ��Ӳ�����
	setLayout(m_pVLayout);
}

KToolBar::~KToolBar()
= default;
