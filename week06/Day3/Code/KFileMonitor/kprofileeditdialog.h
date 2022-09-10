// -------------------------------------------------------
// kprofileeditdialog.h
// 创建者： xie tingyu
// 创建时间： 2022/08/17
// 功能描述： 配置文件修改对话框
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_PROFILEEDITDIALOG_H_
#define _K_PROFILEEDITDIALOG_H_

#include "kprofile.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QApplication>

class KProfileEditDialog final : public QDialog
{
	Q_OBJECT

public:
	KProfileEditDialog(QWidget* parent);
	~KProfileEditDialog() override;

	void retranslateUi();
	void initPage();
	void setProfile(KProfile& profile);
	QString& getProfileOptions();
	void accept() override;
	void reject() override;

signals:
	void profileFinishEdited(KProfile profile);

private:
    QCheckBox* m_fileNameCheckBox{};
    QCheckBox* m_dirNameCheckBox{};
    QCheckBox* m_fileAttributeCheckBox{};
    QCheckBox* m_fileSizeCheckBox{};

    QCheckBox* m_fileLastWriteCheckBox{};
    QCheckBox* m_fileLastVisitCheckBox{};
    QCheckBox* m_fileCreateCheckBox{};
    QCheckBox* m_fileSecurityCheckBox{};

    QCheckBox* m_fileSubtreeCheckBox{};

    QVBoxLayout* verticalLayout{};
    QGroupBox* m_contentToWatchGroupBox{};
    QGridLayout* gridLayout{};
    QGroupBox* m_dirToWatchGroupBox{};
    QGridLayout* gridLayout_2{};
    QLabel* m_watchDirLabel{};
    QLineEdit* m_watchDirLineEdit{};
    QLabel* m_excludeDirLabel{};
    QLineEdit* m_excludeDirLineEdit{};
    QHBoxLayout* m_profileNameHorizontalLayout{};
    QLabel* m_profileNameLabel{};
    QLineEdit* m_profileNameLineEdit{};
    QDialogButtonBox* m_buttonBox{};

    QString m_profileOptions;
	int m_id = 0;
};

#endif