// -------------------------------------------------------
// KRunnable.h
// 创建者： xie tingyu
// 创建时间： 2022/7/15
// 功能描述： 可执行的接口类
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
