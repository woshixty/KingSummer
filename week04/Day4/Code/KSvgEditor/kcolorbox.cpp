#include "kcolorbox.h"

KColorBox::KColorBox(QString title, const QString& colorStr, QWidget* parent)
	: KParamBox(std::move(title), parent)
{
	m_pColorBtn = new QPushButton(this);
	m_pColorBtn->setMaximumSize(70, 50);
	m_pColorBtn->setStyleSheet(
		QString("border-width: 0px; background-color:#%1; border-style:outset;margin:5px").arg(colorStr));
	// ��ӵ�������
	m_pVLayout->addWidget(m_pColorBtn);

	// ���õ�ǰ��ťΪ��ɫ
	const QString str = KGlobalData::getGlobalDataIntance()->getCanvasColor();
	m_pColorBtn->setStyleSheet(
		QString("border-width: 0px; background-color:#%1; border-style:outset;margin:5px").arg(str));

	// ���Ӱ�ť�����ź����Ӧ�ۺ��� ������ɫ�Ի���ѡ����ɫ
	(void)connect(m_pColorBtn, SIGNAL(clicked()), this, SLOT(showPickColorDlg()));
}

KColorBox::~KColorBox()
= default;

void KColorBox::mouseReleaseEvent(QMouseEvent* event)
{
	// �����ť�ͷ�ʱ,������ť����ź�,�����Ի���
	m_pColorBtn->click();
}

void KColorBox::showPickColorDlg()
{
	QString str = KGlobalData::getGlobalDataIntance()->getCanvasColor();
	// QColorDialog : ϵͳʵ����ɫѡ���
	const QColor color = 
		QColorDialog::getColor(QColor(str.toUInt(nullptr, 16)), nullptr, QStringLiteral("ѡ����ɫ"),
		                       QColorDialog::ShowAlphaChannel);
	if (!color.isValid())
		return;

	// �� 16���Ƶ���ɫֵת���� str �ַ���
	str = QString::number(color.rgb(), 16);

	// ����ǰ��ɫֵ���浽ȫ�����ݶ�����
	KGlobalData::getGlobalDataIntance()->setCanvasColor(str);

	// ���ð�ť������ɫΪ��ǰѡ�����ɫ
	m_pColorBtn->setStyleSheet(
		QString("border-width: 0px; background-color:#%1; border-style:outset;margin:5px").arg(str));

	// �����ź�
	emit pickedColor();
}
