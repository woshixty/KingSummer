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
	// ����Ĭ���ı���ɫ
	setDefaultTextColor(QColor(255, 255, 255));
	setEnabled(true);
	// ����item�ɱ༭
	setTextInteractionFlags(Qt::TextEditorInteraction);
	setFlags(ItemIsMovable | ItemIsSelectable | ItemIsFocusable);
}

void KTextItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	qDebug() << "********** KTextItem::paint *************";
	// ����painter��ʼ״̬
	painter->save();
	painter->setPen(QPen(QBrush(m_color), 2, Qt::SolidLine));
	//��ѡ���itemʱ��������ɫ��Ϊ��ɫ͸��
	if (isSelected())
		// ��ɫ��rgb 240 240 240 ͸����Ϊ60
		painter->setBrush(QColor(0, 0, 0, 60));
	painter->setFont(m_font);
	// ��ֹ���־�����󣨷���ݻ��ƣ�
	painter->setRenderHint(QPainter::Antialiasing, true);
	// ����
	painter->drawRect(boundingRect());
	const QString text = toPlainText();
	// �����ı��򳤶�
	setText(text);
	// �ָ�painter״̬
	painter->restore();
	QGraphicsTextItem::paint(painter, option, widget);
}

QRectF KTextItem::boundingRect() const
{
	// qreal labelwidth = 50;
	return {m_rect.x(), m_rect.y(), m_rect.width(), m_rect.height()};
}

//�����ɵ��ô˺���ʵ���Զ���༭���С
void KTextItem::setRect(const QRectF& rect)
{
	m_rect = rect;
}

// ����m_fontWidth,m_fontHeight���Զ����boundingRectʹ��
// ͬʱΪQGraphicsTextItem����font��plainTex
void KTextItem::updateFontInfo()
{
	delete m_fontMetricsF;

	m_fontMetricsF = new QFontMetricsF(m_font);
	m_fontWidth = m_fontMetricsF->width(m_text);
	m_fontHeight = m_fontMetricsF->height();
	// ���������ִ����ı���ʱ
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
		// �������ı���󣬹���λ�����ã��ı���ĩβ
		QTextCursor cursor = this->textCursor();
		cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor, 1);
		this->setTextCursor(cursor);
	}
	// ����������С���ı���ʱ
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

// �����Զ����TextItem������
int KTextItem::type() const
{
	return UserType + 5;
}

// ��ȡ�����¼�
void KTextItem::focusInEvent(QFocusEvent* focusEvent)
{
	qDebug() << "********** focus in *************";
	setTextInteractionFlags(Qt::TextEditorInteraction);
	QGraphicsTextItem::focusInEvent(focusEvent);
}

// ʧȥ�����¼�
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
		// ѡ���ı�
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

