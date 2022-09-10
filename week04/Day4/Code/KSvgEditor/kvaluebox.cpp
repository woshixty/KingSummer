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
}

KValueBox::~KValueBox()
= default;

// 获取焦点事件处理函数,前面设置单击来触发获取焦点事件
void KValueBox::focusInEvent(QFocusEvent* event)
{
	// 全选文本
	m_pParamEdit->selectAll();
//	m_pParamEdit->setFocus();// 设置文本输入器获得焦点
}
