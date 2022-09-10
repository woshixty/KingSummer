#pragma once

#include <QObject>

class KGlobalData final : public QObject
{
	Q_OBJECT

public:
	// 绘图标志 ,enum class : 限制枚举的作用范围
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

	static KGlobalData* getGlobalDataInstance();
	~KGlobalData() override;

	int getCanvasWidth() const;
	int getCanvasHeight() const;
	QString getCanvasColor();

	void setCanvasWidth(int width);
	void setCanvasHeight(int height);
	void setCanvasColor(QString colorStr);
	void setCurrentFlag(KDrawFlag flag);

private:
	KGlobalData();
	int m_canvasWidth = 600;
	int m_canvasHeight = 400;
	QString m_canvasColor = "FFFFFF";
	static KGlobalData* s_globalDataObj;
	KDrawFlag m_currentFlag = KDrawFlag::NoneFlag;
};
