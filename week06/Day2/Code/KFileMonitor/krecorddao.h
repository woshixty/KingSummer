// -------------------------------------------------------
// krecorddao.h
// 创建者： xie tingyu
// 创建时间： 2022/08/12
// 功能描述： 
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