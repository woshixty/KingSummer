// -------------------------------------------------------
// krecorddao.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/12
// ���������� 
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_RECORDDAO_H_
#define _K_RECORDDAO_H_

#include <QObject>

class KRecordDao final : public QObject
{
	Q_OBJECT

public:
	KRecordDao(QObject *parent);
	~KRecordDao();
};

#endif