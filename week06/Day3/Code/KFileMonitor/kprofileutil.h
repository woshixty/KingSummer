// -------------------------------------------------------
// kprofileutil.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/18
// ���������� �����ļ�������
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_PROFILEUTIL_H_
#define _K_PROFILEUTIL_H_

#include "kprofile.h"

#include <QObject>

class KProfileUtil final : public QObject
{
	Q_OBJECT

public:
	KProfileUtil(QObject *parent);
	~KProfileUtil() override;

	static void toJson(KProfile& profile, QString& json);
	static void parseJson(KProfile& profile, const QString& json);
};

#endif