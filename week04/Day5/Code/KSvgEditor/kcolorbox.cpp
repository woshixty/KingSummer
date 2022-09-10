#include "kcolorbox.h"

KColorBox::KColorBox(QString title, const QString& colorStr, QWidget* parent)
	: KParamBox(std::move(title), parent)
{
	m_pColorBtn = new QPushButton(this);
	m_pColorBtn->setStyleSheet(
		QString("border-width: 0px; background-color:#%1; border-style:outset;margin:5px").arg(colorStr));
	// 添加到布局器
	m_pVLayout->addWidget(m_pColorBtn);

	// 设置当前按钮为白色
	const QString str = KGlobalData::getGlobalDataInstance()->getCanvasColor();
	m_pColorBtn->setStyleSheet(
		QString("border-width: 0px; background-color:#%1; border-style:outset;margin:5px").arg(str));

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
	QString str = KGlobalData::getGlobalDataInstance()->getCanvasColor();
	// QColorDialog : 系统实现颜色选择框
	const QColor color = 
		QColorDialog::getColor(QColor(str.toUInt(nullptr, 16)), nullptr, QStringLiteral("选择颜色"),
		                       QColorDialog::ShowAlphaChannel);
	if (!color.isValid())
		return;

	// 将 16进制的颜色值转换成 str 字符串
	str = QString::number(color.rgb(), 16);

	// 将当前颜色值保存到全局数据对象中
	KGlobalData::getGlobalDataInstance()->setCanvasColor(str);

	// 设置按钮背景颜色为当前选择的颜色
	m_pColorBtn->setStyleSheet(
		QString("border-width: 0px; background-color:#%1; border-style:outset;margin:5px").arg(str));

	// 发出信号
	emit pickedColor();
}
