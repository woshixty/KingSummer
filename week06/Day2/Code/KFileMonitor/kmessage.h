// -------------------------------------------------------
// kmessage.h
// 创建者： xie tingyu
// 创建时间： 2022/08/12
// 功能描述： 
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_MESSAGE_H_
#define _K_MESSAGE_H_

#include <QObject>

class KMessage final : public QObject
{
	Q_OBJECT

public:
	KMessage(QObject *parent);
	~KMessage();
};

#endif