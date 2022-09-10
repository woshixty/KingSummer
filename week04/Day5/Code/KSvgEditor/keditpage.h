#pragma once

#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QDebug>

class KEditPage final : public QGraphicsView
{
	Q_OBJECT

public:
	KEditPage(QWidget *parent);
	~KEditPage() override;

	void setViewCord(QLabel* lab) { m_pLabViewCord = lab; }
	void setSceneCord(QLabel* lab) { m_pLabSceneCord = lab; }
	void setItemCord(QLabel* lab) { m_pLabItemCord = lab; }
	
	void iniGraphicsSystem() const;

	void drawPic() const;
	void drawItem(QGraphicsItem* item) const;

protected:
	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

signals:
	void mouseMovePoint(QPoint point);
	void mouseClicked(QPoint point);

private slots:
	void changeSceneColor() const;

private:
	QLabel* m_pLabViewCord{};
	QLabel* m_pLabSceneCord{};
	QLabel* m_pLabItemCord{};

	QPoint m_startPoint;
	QPoint m_endPoint;

	QGraphicsScene* scene{};
};
