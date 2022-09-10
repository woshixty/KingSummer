#include "kvaluebox.h"

#include <utility>

KValueBox::KValueBox(QString title, int val, QWidget* parent)
	: KParamBox(std::move(title), parent)
{
	m_pParamEdit = new QLineEdit(this);
	m_pParamEdit->setText(QString::number(val));
	m_pParamEdit->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
	m_pParamEdit->setStyleSheet("background-color:#3f3f3c; font-size:20px; color:#4f80ff; font-family: Microsoft YaHei; font-weight: bold; border-width:0; border-style:outset");
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
}

KValueBox::~KValueBox()
= default;

// ��ȡ�����¼�������,ǰ�����õ�����������ȡ�����¼�
void KValueBox::focusInEvent(QFocusEvent* event)
{
	// ȫѡ�ı�
	m_pParamEdit->selectAll();
//	m_pParamEdit->setFocus();// �����ı���������ý���
}
