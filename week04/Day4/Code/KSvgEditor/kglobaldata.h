#pragma once

#include <QObject>

class KGlobalData  : public QObject
{
	Q_OBJECT

public:
	// ��ͼ��־ ,enum class : ����ö�ٵ����÷�Χ
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
	// ��ǰ��������ɫ
	QString m_canvasColor = "000000";
	static KGlobalData* s_globalDataObj;
};
