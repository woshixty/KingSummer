#include "kcolorbox.h"

KColorBox::KColorBox(QString title, const QString& colorStr, KGlobalData::KParamFlag flag, QWidget* parent)
	: KParamBaseBox(std::move(title), flag, parent)
{
	// ��ȡ��ǰ��ť��ɫ������
	const QString str = KGlobalData::getGlobalDataInstance()->getCanvasColor();
	m_pColorBtn = new QPushButton(this);
	m_pColorBtn->setStyleSheet(
		QString(
			"border-width: 0px;"\
			"background-color:#%1;"\
			"border-style:outset;"\
			"margin:5px").arg(colorStr));
	m_pColorBtn->setMinimumHeight(40);
	// ��ӵ�������
	m_pVLayout->addWidget(m_pColorBtn);

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
	QString colorStr = KGlobalData::getGlobalDataInstance()->getCanvasColor();
	// QColorDialog : ϵͳʵ����ɫѡ���
	const QColor color = 
		QColorDialog::getColor(
			QColor(colorStr.toUInt(nullptr, 16)), 
			nullptr, 
			QStringLiteral("ѡ����ɫ"),
			QColorDialog::ShowAlphaChannel);
	if (!color.isValid())
		return;
	// �� 16���Ƶ���ɫֵת�����ַ���
	colorStr = QString::number(color.rgb(), 16);
	// ���ð�ť������ɫΪ��ǰѡ�����ɫ
	m_pColorBtn->setStyleSheet(
		QString(
			"border-width: 0px;"\
			"background-color:#%1;"\
			"border-style:outset;"\
			"margin:5px").arg(colorStr));
	switch (m_flag) {
		case KGlobalData::KParamFlag::CanvasWidth:
		case KGlobalData::KParamFlag::CanvasHeight:
		case KGlobalData::KParamFlag::CanvasScaling:
		case KGlobalData::KParamFlag::BorderWidth:
		case KGlobalData::KParamFlag::BorderStyle:
			break;
		case KGlobalData::KParamFlag::BorderColor: 
			m_pData->setBorderColor(colorStr);
			emit borderColorChanged();
			break;
		case KGlobalData::KParamFlag::CanvasColor:
			m_pData->setCanvasColor(colorStr);
			emit canvasColorChanged();
			break;
		case KGlobalData::KParamFlag::FillColor: 
			m_pData->setFillColor(colorStr);
			emit fillColorChanged();
			break;
		default:
			break;
	}
}
