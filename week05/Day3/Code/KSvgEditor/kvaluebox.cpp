#include "kvaluebox.h"

#include <utility>

KValueBox::KValueBox(QString title, int val, KGlobalData::KParamFlag flag, QWidget* parent)
	: KParamBaseBox(std::move(title), flag, parent)
{
	m_pParamEdit = new QLineEdit(this);
	m_pParamEdit->setAlignment(Qt::AlignCenter);
	m_pParamEdit->setText(QString::number(val));
	m_pParamEdit->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	m_pParamEdit->setStyleSheet(
		"background-color:#3f3f3c;"\
		"font-size:20px;"\
		"color:#4f80ff;"\
		"font-family: Microsoft YaHei;"\
		"font-weight: bold;"\
		"border-width:0;"\
		"border-style:outset"
	);
	m_pParamEdit->setMaxLength(4);

	/*
		[1-9] :ƥ�� 1 �� 9 ��������
		+ : ƥ�� + ��ǰ����ַ� һ�λ��߶��
		$ : ��ǰ��ƥ����ַ���β
		[0-9] :ƥ�� 0 �� 9 ��������
	*/
	// ������ʽ
	const QRegExp reg("[1-9][0-9]+$");
	const QValidator* validator = new QRegExpValidator(reg, m_pParamEdit);
	// ����������ʽ
	m_pParamEdit->setValidator(validator);
	// ���뵽������ m_pVLayout �����ڸ�����
	m_pVLayout->addWidget(m_pParamEdit);

	connect(m_pParamEdit, SIGNAL(editingFinished()), this, SLOT(writeFinish()));
}

KValueBox::~KValueBox()
= default;

// ��ȡ�����¼�������, ǰ�����õ�����������ȡ�����¼�
void KValueBox::focusInEvent(QFocusEvent* event)
{
	m_pParamEdit->selectAll();
}

void KValueBox::writeFinish()
{
	switch (m_flag) {
		case KGlobalData::KParamFlag::CanvasWidth: 
			m_pData->setCanvasWidth(m_pParamEdit->text().toInt());
			emit canvasWidthChanged();
			break;
		case KGlobalData::KParamFlag::CanvasHeight: 
			m_pData->setCanvasHeight(m_pParamEdit->text().toInt());
			emit canvasHeightChanged();
			break;
		case KGlobalData::KParamFlag::CanvasScaling: 
			m_pData->setCanvasScaling(m_pParamEdit->text().toInt());
			emit canvasScalingChanged();
			break;
		case KGlobalData::KParamFlag::BorderWidth: 
			m_pData->setBorderWidth(m_pParamEdit->text().toInt());
			emit borderWidthChanged();
			break;
		case KGlobalData::KParamFlag::BorderStyle: 
		case KGlobalData::KParamFlag::CanvasColor: 
		case KGlobalData::KParamFlag::BorderColor: 
		case KGlobalData::KParamFlag::FillColor:
		default:
			break;
	}
}
