#pragma once

#include <QObject>

class KGlobalData final : public QObject
{
	Q_OBJECT

public:
	// 绘图标志, enum class : 限制枚举的作用范围
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

	enum class KLineFlag
	{
		NoneFlag = 0,
		SolidFlag,
		DottedFlag,
	};

	static KGlobalData* getGlobalDataInstance();
	~KGlobalData() override;

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
	void setCurrentFlag(KDrawFlag flag);
	void setBorderColor(QString colorStr);
	void setCanvasColor(QString colorStr);
	void setFillColor(QString colorStr);
	void setRemovable(bool removable) { m_removable = removable; }

private:
	KGlobalData();
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
	bool m_removable = false;
};
