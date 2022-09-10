// -------------------------------------------------------
// kdirectorypage.h
// 创建者： xie tingyu
// 创建时间： 2022/08/16
// 功能描述： 配置文件监听的文件夹
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_DIRECTORYPAGE_H_
#define _K_DIRECTORYPAGE_H_

#include "kglobaldata.h"
#include "klistbasepage.h"
#include "kprofile.h"

class KDirectoryPage final : public KListBasePage
{
	Q_OBJECT

public:
	KDirectoryPage(QWidget* parent);
	~KDirectoryPage() override;

signals:
	void addDirectory(QString dir);

public slots:
	void addProfileDir(bool flag);
	void activeProfileChanged() const;

private:
	KGlobalData* m_globalData = KGlobalData::getGlobalDataInstance();
};

#endif