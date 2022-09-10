#pragma once

#include <QObject>

class KGlobalData  : public QObject
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
		RectFlag,
		CircleFlag,
		TextFlag
	};

	static KGlobalData* getGlobalDataIntance();
	~KGlobalData() override;

	int getCanvasWidth() const;
	int getCanvasHeight() const;

	void setCanvasWidth(int width);
	void setCanvasHeight(int height);

	void setCanvasColor(QString colorStr);

	QString getCanvasColor();

private:
	KGlobalData();
	KGlobalData(const KGlobalData& other)
	{}
	int m_canvasWidth = 600;
	int m_canvasHeight = 400;
	// 当前画布的颜色
	QString m_canvasColor = "000000";
	static KGlobalData* s_globalDataObj;
};
