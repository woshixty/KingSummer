// -------------------------------------------------------
// kmessage.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/12
// ���������� 
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