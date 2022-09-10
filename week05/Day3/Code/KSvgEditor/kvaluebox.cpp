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
		[1-9] :匹配 1 到 9 任意数字
		+ : 匹配 + 号前面的字符 一次或者多次
		$ : 以前面匹配的字符结尾
		[0-9] :匹配 0 到 9 任意数字
	*/
	// 正则表达式
	const QRegExp reg("[1-9][0-9]+$");
	const QValidator* validator = new QRegExpValidator(reg, m_pParamEdit);
	// 设置正则表达式
	m_pParamEdit->setValidator(validator);
	// 加入到布局中 m_pVLayout 设置在父类中
	m_pVLayout->addWidget(m_pParamEdit);

	connect(m_pParamEdit, SIGNAL(editingFinished()), this, SLOT(writeFinish()));
}

KValueBox::~KValueBox()
= default;

// 获取焦点事件处理函数, 前面设置单击来触发获取焦点事件
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
