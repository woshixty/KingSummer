#include "kcolorbox.h"

KColorBox::KColorBox(QString title, const QString& colorStr, KGlobalData::KParamFlag flag, QWidget* parent)
	: KParamBaseBox(std::move(title), flag, parent)
{
	// 获取当前按钮颜色并设置
	const QString str = KGlobalData::getGlobalDataInstance()->getCanvasColor();
	m_pColorBtn = new QPushButton(this);
	m_pColorBtn->setStyleSheet(
		QString(
			"border-width: 0px;"\
			"background-color:#%1;"\
			"border-style:outset;"\
			"margin:5px").arg(colorStr));
	m_pColorBtn->setMinimumHeight(40);
	// 添加到布局器
	m_pVLayout->addWidget(m_pColorBtn);

	// 连接按钮单击信号与对应槽函数 弹出颜色对话框选择颜色
	(void)connect(m_pColorBtn, SIGNAL(clicked()), this, SLOT(showPickColorDlg()));
}

KColorBox::~KColorBox()
= default;

void KColorBox::mouseReleaseEvent(QMouseEvent* event)
{
	// 点击按钮释放时,触发按钮点击信号,弹出对话框
	m_pColorBtn->click();
}

void KColorBox::showPickColorDlg()
{
	QString colorStr = KGlobalData::getGlobalDataInstance()->getCanvasColor();
	// QColorDialog : 系统实现颜色选择框
	const QColor color = 
		QColorDialog::getColor(
			QColor(colorStr.toUInt(nullptr, 16)), 
			nullptr, 
			QStringLiteral("选择颜色"),
			QColorDialog::ShowAlphaChannel);
	if (!color.isValid())
		return;
	// 将 16进制的颜色值转换成字符串
	colorStr = QString::number(color.rgb(), 16);
	// 设置按钮背景颜色为当前选择的颜色
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
