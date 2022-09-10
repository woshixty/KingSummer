// -------------------------------------------------------
// kprofilepage.h
// 创建者： xie tingyu
// 创建时间： 2022/08/16
// 功能描述： 配置文件页面
// Copyright 2013 Kingsoft
// --------------------------------------------------------

#ifndef _K_PROFILE_PAGE_H_
#define _K_PROFILE_PAGE_H_

#include "kglobaldata.h"
#include "klistbasepage.h"
#include "kprofileeditdialog.h"
#include "kprofiledao.h"

class KProfilePage final : public KListBasePage
{
	Q_OBJECT

public:
	KProfilePage(QWidget* parent);
	~KProfilePage() override;

	void initData();
	void setProfileDao(KProfileDao* profileDao);
	KProfile getCurrentProfile() { return m_currentProfile; }

signals:
	// 活跃配置文件已修改信号
	void sendCurrentProfile();

private slots:
	void addProfileBtn(bool flag);
	void profileDoubleClicked(QListWidgetItem* item);
	void profileClicked(QListWidgetItem* item);
	void profileEdited(KProfile profile);
	void addDirToWatch(const QString& dir);
	void importProfile();
	void exportProfile();

private:
	KProfileDao* m_profileDao{};
	QList<KProfile> m_profiles;
	KProfile m_currentProfile;

	KGlobalData* m_globalData = KGlobalData::getGlobalDataInstance();
};

#endif