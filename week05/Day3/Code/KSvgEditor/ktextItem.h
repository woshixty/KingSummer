#pragma once

#include <qgraphicsitem.h>
#include <QPointF>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsTextItem>
#include <QPen>
#include <QFontMetricsF>
#include <QPainterPath>
#include <QTextCursor>
#include <QColor>

class KTextItem final : public QGraphicsTextItem
{
public:
	explicit KTextItem(QPointF startPoint, QPointF endpoint, QGraphicsItem* parent = nullptr);
	~KTextItem() override;

	void init();
	void setRect(const QRectF& rect);
	void updateFontInfo();
	void setText(QString text);

protected:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
	QRectF boundingRect()const override;

	int type() const override;
	// 焦点进入事件
	void focusInEvent(QFocusEvent* focusEvent) override;
	void focusOutEvent(QFocusEvent* focusEvent) override;
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

	QPainterPath shape() const override;

private:
	QRectF m_rect;
	QPen m_pen;
	QString m_text;
	QFont m_font;
	QColor m_color;
	bool m_focus{};

	QFontMetricsF* m_fontMetricsF = nullptr;
	qreal m_fontWidth{};
	qreal m_fontHeight{};

	bool isMousePress = false;
};
