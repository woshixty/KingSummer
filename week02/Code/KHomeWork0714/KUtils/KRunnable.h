// -------------------------------------------------------
// KRunnable.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/7/15
// ���������� ��ִ�еĽӿ���
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _KRUNNABLE_H_
#define _KRUNNABLE_H_

class KRunnable
{
public:
	virtual ~KRunnable() = default;
	virtual void runtask() = 0;
};

#endif
