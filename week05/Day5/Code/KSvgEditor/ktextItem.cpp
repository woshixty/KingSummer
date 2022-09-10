#include "ktextItem.h"
#include <QDebug>
#include <utility>

KTextItem::KTextItem(QPointF startPoint, QPointF endpoint, QGraphicsItem* parent) : QGraphicsTextItem(parent)
{
	m_rect = QRectF(startPoint, endpoint);
	init();
}

KTextItem::~KTextItem()
{
	if (m_fontMetricsF != nullptr) 
	{
		delete m_fontMetricsF;
		m_fontMetricsF = nullptr;
	}
}

void KTextItem::init()
{
	m_text = "";
	m_color = QColor(255, 0, 0);
	m_font = QFont("SimSun", 20);
	// m_font.setPixelSize(30);
	m_focus = false;
	setFont(m_font);
	// 设置默认文本颜色
	setDefaultTextColor(QColor(255, 255, 255));
	setEnabled(true);
	// 设置item可编辑
	setTextInteractionFlags(Qt::TextEditorInteraction);
	setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable);
}

void KTextItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	qDebug() << "********** KTextItem::paint *************";
	// 保存painter初始状态
	painter->save();
	painter->setPen(QPen(QBrush(m_color), 2, Qt::SolidLine));
	//当选择该item时，背景颜色变为白色透明
	if (isSelected())
		// 颜色是rgb 240 240 240 透明度为60
		painter->setBrush(QColor(0, 0, 0, 60));
	painter->setFont(m_font);
	// 防止出现锯齿现象（反锯齿绘制）
	painter->setRenderHint(QPainter::Antialiasing, true);
	// 画框
	painter->drawRect(boundingRect());
	const QString text = toPlainText();
	// 更新文本框长度
	setText(text);
	// 恢复painter状态
	painter->restore();
	QGraphicsTextItem::paint(painter, option, widget);
}

QRectF KTextItem::boundingRect() const
{
	// qreal labelwidth = 50;
	return {m_rect.x(), m_rect.y(), m_rect.width(), m_rect.height()};
}

//类对象可调用此函数实现自定义编辑框大小
void KTextItem::setRect(const QRectF& rect)
{
	m_rect = rect;
}

// 计算m_fontWidth,m_fontHeight给自定义的boundingRect使用
// 同时为QGraphicsTextItem设置font和plainTex
void KTextItem::updateFontInfo()
{
	delete m_fontMetricsF;

	m_fontMetricsF = new QFontMetricsF(m_font);
	m_fontWidth = m_fontMetricsF->width(m_text);
	m_fontHeight = m_fontMetricsF->height();
	// 当输入文字大于文本框时
	if (m_fontWidth > boundingRect().width())
	{
		constexpr qreal adjust = 5;
		this->setRect(
			QRectF(
				boundingRect().x(), boundingRect().y(), m_fontWidth + adjust, 
				boundingRect().height()
			)
		);
		this->setFont(m_font);
		this->setPlainText(m_text);
		// 当更新文本框后，光标的位置设置，文本的末尾
		QTextCursor cursor = this->textCursor();
		cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor, 1);
		this->setTextCursor(cursor);
	}
	// 当输入文字小于文本框时
	if (m_fontHeight > boundingRect().height())
	{
		constexpr qreal adjust = 5;
		this->setRect(
			QRectF(
				boundingRect().x(), boundingRect().y(), 
				boundingRect().width(), m_fontHeight + adjust
			)
		);
		this->setFont(m_font);
		this->setPlainText(m_text);
	}
}

void KTextItem::setText(QString text)
{
	m_text = std::move(text);
	updateFontInfo();
}

// 设置自定义的TextItem的类型
int KTextItem::type() const
{
	return UserType + 5;
}

// 获取焦点事件
void KTextItem::focusInEvent(QFocusEvent* focusEvent)
{
	qDebug() << "********** focus in *************";
	setTextInteractionFlags(Qt::TextEditorInteraction);
	QGraphicsTextItem::focusInEvent(focusEvent);
}

// 失去焦点事件
void KTextItem::focusOutEvent(QFocusEvent* focusEvent)
{
	qDebug() << "focus out";
	//setTextInteractionFlags(Qt::NoTextInteraction);
	QGraphicsTextItem::focusOutEvent(focusEvent);
	isMousePress = false;
}

void KTextItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsTextItem::mousePressEvent(event);
	Q_UNUSED(event);
	if (!isMousePress)
	{
		QTextCursor cursor = this->textCursor();
		// 选中文本
		cursor.select(QTextCursor::Document);
		this->setTextCursor(cursor);
		isMousePress = true;
	}
}

void KTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsTextItem::mouseReleaseEvent(event);
	Q_UNUSED(event)
}

QPainterPath KTextItem::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

