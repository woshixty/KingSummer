// -------------------------------------------------------
// kglobaldata.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/09
// ���������� ȫ��������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_GLOBALDATA_H_
#define _K_GLOBALDATA_H_

#include <QObject>
#include <QBrush>
#include <QPen>

class KGlobalData final : public QObject
{
	Q_OBJECT

public:
	// ��ͼ��־
	enum class KDrawFlag
	{
		NoneFlag = 0,
		MouseFlag,
		PenFlag,
		LineFlag,
		CircleFlag,
		RectFlag,
		PengatonFlag,
		HexagonFlag,
		StarFlag,
		TextFlag,
		ZoomFlag
	};

	// �������ͱ�־
	enum class KParamFlag
	{
		CanvasWidth = 0,
		CanvasHeight,
		CanvasScaling,
		CanvasColor,
		BorderWidth,
		BorderStyle,
		BorderColor,
		FillColor,
	};

	// ��������
	enum class KLineFlag
	{
		NoneFlag = 0,
		SolidFlag,
		DottedFlag,
	};

	// ��״����
	enum class KShapeType
	{
		None = 0,
		FreeLine,
		StraightLine,
		Circle,
		Rect,
		Pentagon,
		Hexagon,
		Star,
		Text,
	};

	int canvasWidth() const;
	int canvasHeight() const;
	int getCanvasScaling() const;
	int getBorderWidth() const;
	KLineFlag getBorderStyle() const;
	QString getBorderColor() const;
	QString getCanvasColor() const;
	QString getFillColor() const;
	bool removable() const { return m_removable; }

	KDrawFlag getDrawFlag() const;

	void setCanvasWidth(int width);
	void setCanvasHeight(int height);
	void setCanvasScaling(int scaling);
	void setBorderWidth(int width);
	void setBorderStyle(KLineFlag flag);
	void setBorderColor(QString colorStr);
	void setCanvasColor(QString colorStr);
	void setFillColor(QString colorStr);
	void setRemovable(bool removable) { m_removable = removable; }

	void setCurrentFlag(KDrawFlag flag);
	void setMouseCursorShape(Qt::CursorShape shape);

	static KGlobalData* getGlobalDataInstance(QObject* parent = nullptr);
	void setPen(QPen& pen) const;

private:
	KGlobalData(QObject* parent = nullptr);
	int m_canvasWidth = 600;
	int m_canvasHeight = 400;
	int m_canvasScaling = 100;
	int m_borderWidth = 4;
	QString m_borderColor = "000000";
	QString m_canvasColor = "FFFFFF";
	QString m_fillColor = "FFFFFF";
	static KGlobalData* s_globalDataObj;
	KDrawFlag m_drawFlag = KDrawFlag::MouseFlag;
	KLineFlag m_lineFlag = KLineFlag::SolidFlag;
	Qt::CursorShape m_mouseCursorShape = Qt::ArrowCursor;
	bool m_removable = false;
};

#endif
