#include "kprofileeditdialog.h"

#include <QFileDialog>

KProfileEditDialog::KProfileEditDialog(QWidget *parent)
	: QDialog(parent)
{
    initPage();
}

KProfileEditDialog::~KProfileEditDialog()
= default;

void KProfileEditDialog::initPage()
{
    setObjectName(QStringLiteral("KProfileEditDialog"));
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    m_contentToWatchGroupBox = new QGroupBox(this);
    m_contentToWatchGroupBox->setObjectName(QStringLiteral("m_contentToWatchGroupBox"));
    gridLayout = new QGridLayout(m_contentToWatchGroupBox);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    m_dirNameCheckBox = new QCheckBox(m_contentToWatchGroupBox);
    m_dirNameCheckBox->setObjectName(QStringLiteral("m_dirNameCheckBox"));

    gridLayout->addWidget(m_dirNameCheckBox, 0, 1, 1, 1);

    m_fileLastWriteCheckBox = new QCheckBox(m_contentToWatchGroupBox);
    m_fileLastWriteCheckBox->setObjectName(QStringLiteral("m_fileLastWriteCheckBox"));

    gridLayout->addWidget(m_fileLastWriteCheckBox, 2, 0, 1, 1);

    m_fileNameCheckBox = new QCheckBox(m_contentToWatchGroupBox);
    m_fileNameCheckBox->setObjectName(QStringLiteral("m_fileNameCheckBox"));

    gridLayout->addWidget(m_fileNameCheckBox, 0, 0, 1, 1);

    m_fileLastVisitCheckBox = new QCheckBox(m_contentToWatchGroupBox);
    m_fileLastVisitCheckBox->setObjectName(QStringLiteral("m_fileLastVisitCheckBox"));

    gridLayout->addWidget(m_fileLastVisitCheckBox, 2, 1, 1, 1);

    m_fileCreateCheckBox = new QCheckBox(m_contentToWatchGroupBox);
    m_fileCreateCheckBox->setObjectName(QStringLiteral("m_fileCreateCheckBox"));

    gridLayout->addWidget(m_fileCreateCheckBox, 2, 2, 1, 1);

    m_fileSubtreeCheckBox = new QCheckBox(m_contentToWatchGroupBox);
    m_fileSubtreeCheckBox->setObjectName(QStringLiteral("m_fileSubtreeCheckBox"));

    gridLayout->addWidget(m_fileSubtreeCheckBox, 2, 4, 1, 1);

    m_fileSecurityCheckBox = new QCheckBox(m_contentToWatchGroupBox);
    m_fileSecurityCheckBox->setObjectName(QStringLiteral("m_fileSecurityCheckBox"));

    gridLayout->addWidget(m_fileSecurityCheckBox, 2, 3, 1, 1);

    m_fileSizeCheckBox = new QCheckBox(m_contentToWatchGroupBox);
    m_fileSizeCheckBox->setObjectName(QStringLiteral("m_fileSizeCheckBox"));

    gridLayout->addWidget(m_fileSizeCheckBox, 0, 3, 1, 1);

    m_fileAttributeCheckBox = new QCheckBox(m_contentToWatchGroupBox);
    m_fileAttributeCheckBox->setObjectName(QStringLiteral("m_fileAttributeCheckBox"));

    gridLayout->addWidget(m_fileAttributeCheckBox, 0, 2, 1, 1);


    verticalLayout->addWidget(m_contentToWatchGroupBox);

    m_dirToWatchGroupBox = new QGroupBox(this);
    m_dirToWatchGroupBox->setObjectName(QStringLiteral("m_dirToWatchGroupBox"));
    gridLayout_2 = new QGridLayout(m_dirToWatchGroupBox);
    gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
    m_watchDirLabel = new QLabel(m_dirToWatchGroupBox);
    m_watchDirLabel->setObjectName(QStringLiteral("m_watchDirLabel"));

    gridLayout_2->addWidget(m_watchDirLabel, 0, 0, 1, 1);

    m_watchDirLineEdit = new QLineEdit(m_dirToWatchGroupBox);
    m_watchDirLineEdit->setObjectName(QStringLiteral("m_watchDirLineEdit"));
    m_watchDirLineEdit->setReadOnly(false);

    gridLayout_2->addWidget(m_watchDirLineEdit, 0, 1, 1, 1);

    m_excludeDirLabel = new QLabel(m_dirToWatchGroupBox);
    m_excludeDirLabel->setObjectName(QStringLiteral("m_excludeDirLabel"));

    gridLayout_2->addWidget(m_excludeDirLabel, 1, 0, 1, 1);

    m_excludeDirLineEdit = new QLineEdit(m_dirToWatchGroupBox);
    m_excludeDirLineEdit->setObjectName(QStringLiteral("m_excludeDirLineEdit"));
    m_excludeDirLineEdit->setReadOnly(false);

    gridLayout_2->addWidget(m_excludeDirLineEdit, 1, 1, 1, 1);


    verticalLayout->addWidget(m_dirToWatchGroupBox);

    m_profileNameHorizontalLayout = new QHBoxLayout();
    m_profileNameHorizontalLayout->setObjectName(QStringLiteral("m_profileNameHorizontalLayout"));
    m_profileNameLabel = new QLabel(this);
    m_profileNameLabel->setObjectName(QStringLiteral("m_profileNameLabel"));

    m_profileNameHorizontalLayout->addWidget(m_profileNameLabel);

    m_profileNameLineEdit = new QLineEdit(this);
    m_profileNameLineEdit->setObjectName(QStringLiteral("m_profileNameLineEdit"));

    m_profileNameHorizontalLayout->addWidget(m_profileNameLineEdit);


    verticalLayout->addLayout(m_profileNameHorizontalLayout);

    m_buttonBox = new QDialogButtonBox(this);
    m_buttonBox->setObjectName(QStringLiteral("m_buttonBox"));
    m_buttonBox->setOrientation(Qt::Horizontal);
    m_buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    m_buttonBox->setCenterButtons(true);

    verticalLayout->addWidget(m_buttonBox);

    retranslateUi();
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void KProfileEditDialog::setProfile(KProfile& profile)
{
    // 根据配置类信息初始化页面
    m_id = profile.id();
    m_profileNameLineEdit->setText(profile.profileName());
    m_watchDirLineEdit->setText(profile.includeFiles());
    m_excludeDirLineEdit->setText(profile.excludeFiles());
    const QString optionstr = profile.profileOptions();
    QStringList options = optionstr.split('-');
    // 遍历options，设置对应的checkbox
    for (const auto& option : options)
    {
	    switch (option.toInt())
	    {
	    case 1:
			m_fileNameCheckBox->setChecked(true);
		    break;
	    case 2:
            m_dirNameCheckBox->setChecked(true);
            break;
	    case 3:
            m_fileAttributeCheckBox->setChecked(true);
            break;
	    case 4:
            m_fileSizeCheckBox->setChecked(true);
            break;
	    case 5:
            m_fileLastWriteCheckBox->setChecked(true);
            break;
	    case 6:
            m_fileLastVisitCheckBox->setChecked(true);
            break;
	    case 7:
			m_fileCreateCheckBox->setChecked(true);
            break;
	    case 8:
            m_fileSecurityCheckBox->setChecked(true);
            break;
	    case 9:
            m_fileSubtreeCheckBox->setChecked(true);
            break;
	    default: ;
	    }
	}
}

QString& KProfileEditDialog::getProfileOptions()
{
    m_profileOptions = "";
    if(m_fileNameCheckBox->isChecked())
		m_profileOptions += "1-";
    if(m_dirNameCheckBox->isChecked())
		m_profileOptions += "2-";
	if(m_fileAttributeCheckBox->isChecked())
		m_profileOptions += "3-";
    if(m_fileSizeCheckBox->isChecked())
		m_profileOptions += "4-";
    if(m_fileLastWriteCheckBox->isChecked())
		m_profileOptions += "5-";
    if(m_fileLastVisitCheckBox->isChecked())
		m_profileOptions += "6-";
    if(m_fileCreateCheckBox->isChecked())
		m_profileOptions += "7-";
	if(m_fileSecurityCheckBox->isChecked())
		m_profileOptions += "8-";
	if(m_fileSubtreeCheckBox->isChecked())
		m_profileOptions += "9-";
    return m_profileOptions;
}

void KProfileEditDialog::retranslateUi()
{
    setWindowTitle(QApplication::translate("KProfileEditDialog", "Dialog", Q_NULLPTR));
    m_contentToWatchGroupBox->setTitle(QApplication::translate("KProfileEditDialog", "\347\233\221\346\216\247\351\200\211\351\241\271", Q_NULLPTR));
    m_dirNameCheckBox->setText(QApplication::translate("KProfileEditDialog", "\346\226\207\344\273\266\345\244\271\345\220\215\347\247\260", Q_NULLPTR));
    m_fileLastWriteCheckBox->setText(QApplication::translate("KProfileEditDialog", "\346\226\207\344\273\266\346\234\200\345\220\216\345\206\231\345\205\245", Q_NULLPTR));
    m_fileNameCheckBox->setText(QApplication::translate("KProfileEditDialog", "\346\226\207\344\273\266\345\220\215\347\247\260", Q_NULLPTR));
    m_fileLastVisitCheckBox->setText(QApplication::translate("KProfileEditDialog", "\346\226\207\344\273\266\346\234\200\345\220\216\350\256\277\351\227\256", Q_NULLPTR));
    m_fileCreateCheckBox->setText(QApplication::translate("KProfileEditDialog", "\346\226\207\344\273\266\345\210\233\345\273\272\346\227\266\351\227\264", Q_NULLPTR));
    m_fileSubtreeCheckBox->setText(QApplication::translate("KProfileEditDialog", "\347\233\221\346\216\247\345\255\220\347\233\256\345\275\225", Q_NULLPTR));
    m_fileSecurityCheckBox->setText(QApplication::translate("KProfileEditDialog", "\345\256\211\345\205\250\346\217\217\350\277\260\347\254\246", Q_NULLPTR));
    m_fileSizeCheckBox->setText(QApplication::translate("KProfileEditDialog", "\346\226\207\344\273\266\345\244\247\345\260\217", Q_NULLPTR));
    m_fileAttributeCheckBox->setText(QApplication::translate("KProfileEditDialog", "\346\226\207\344\273\266\345\261\236\346\200\247", Q_NULLPTR));
    m_dirToWatchGroupBox->setTitle(QApplication::translate("KProfileEditDialog", "\347\233\221\346\216\247\350\247\204\345\210\231", Q_NULLPTR));
    m_watchDirLabel->setText(QApplication::translate("KProfileEditDialog", "\347\233\221\346\216\247\346\226\207\344\273\266", Q_NULLPTR));
    m_watchDirLineEdit->setText(QApplication::translate("KProfileEditDialog", "*.exe hello.txt *.docx", Q_NULLPTR));
    m_excludeDirLabel->setText(QApplication::translate("KProfileEditDialog", "\346\216\222\351\231\244\346\226\207\344\273\266", Q_NULLPTR));
    m_excludeDirLineEdit->setText(QApplication::translate("KProfileEditDialog", "\346\226\260\345\273\272\346\226\207\346\234\254\346\226\207\346\241\243.txt *\345\211\257\346\234\254.txt", Q_NULLPTR));
    m_profileNameLabel->setText(QApplication::translate("KProfileEditDialog", "\351\205\215\347\275\256\346\226\207\344\273\266\345\220\215\347\247\260", Q_NULLPTR));
    m_profileNameLineEdit->setText(QApplication::translate("KProfileEditDialog", "test", Q_NULLPTR));
}

void KProfileEditDialog::accept()
{
    // 生成配置文件
    KProfile profile;
    // 设置ID
	profile.setId(m_id);
    // 设置配置文件名
    profile.setProfileName(m_profileNameLineEdit->text());
    // 设置监控目录
    profile.setIncludeFiles(m_watchDirLineEdit->text());
    // 设置排除目录
    profile.setExcludeFiles(m_excludeDirLineEdit->text());
    // 设置配置选项
    profile.setProfileOptions(getProfileOptions());
    emit profileFinishEdited(profile);
	QDialog::accept();
}

void KProfileEditDialog::reject()
{
	QDialog::reject();
}
