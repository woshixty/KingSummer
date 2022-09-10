// -------------------------------------------------------
// kprofilepage.h
// �����ߣ� xie tingyu
// ����ʱ�䣺 2022/08/16
// ���������� �����ļ�ҳ��
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
	// ��Ծ�����ļ����޸��ź�
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