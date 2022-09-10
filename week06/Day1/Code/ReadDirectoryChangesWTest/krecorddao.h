#pragma once

#include <QObject>

class KRecordDao  : public QObject
{
	Q_OBJECT

public:
	KRecordDao(QObject *parent);
	~KRecordDao();
};
