// -------------------------------------------------------
// kquerypage.h
// 创建者： xie tingyu
// 创建时间： 2022/08/11
// 功能描述： 搜索页面
// Copyright 2013 Kingsoft
// --------------------------------------------------------

// ReSharper disable All
#ifndef _K_QUERYPAGE_H_
#define _K_QUERYPAGE_H_

#include "kglobaldata.h"

#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QDateTime>
#include <QApplication>

class KQueryPage final : public QWidget
{
	Q_OBJECT

public:
	KQueryPage(QWidget *parent);
	~KQueryPage() override;
	void initPage();
	void initValue() const;
	void retranslateUi();

    QComboBox* sortContentComboBox() const { return m_sortContent; }
    QComboBox* sortTypeComboBox() const { return m_sortType; }
    QComboBox* operationTypeComboBox() const { return m_operationType; }
    QPushButton* queryBtn() const { return m_queryBtn; }

private slots:
    void startDateTimeChanged(const QDateTime& datetime) const;
    void endDateTimeChanged(const QDateTime& datetime) const;
    void fileNameChanged() const;
    void ownerChanged() const;

private:
	QComboBox* m_sortContent{};
    QComboBox* m_sortType{};
    QComboBox* m_operationType{};

	QGridLayout* gridLayout_2{};
    QGridLayout* gridLayout{};

    QLabel* m_sortLabel{};
    QLabel* m_operationLabel{};
    QLabel* m_startLabel{};
    QLabel* m_endLabel{};
    QLabel* m_fuzzyLabel{};
    QLabel* m_fileNameLabel{};
    QLabel* m_ownerLabel{};

    QHBoxLayout* m_sortHorizontalLayout{};
    QHBoxLayout* m_operationHorizontalLayout{};
    QHBoxLayout* m_startHorizontalLayout{};
    QHBoxLayout* m_endHorizontalLayout{};
    QHBoxLayout* horizontalLayout{};
    QHBoxLayout* m_fileNameHorizontalLayout{};
    QHBoxLayout* m_ownerHorizontalLayout{};
    
    QVBoxLayout* m_sortVerticalLayout{};
    QVBoxLayout* m_operationVerticalLayout{};
    QVBoxLayout* m_startVerticalLayout{};
    QVBoxLayout* m_endVerticalLayout{};
    QVBoxLayout* verticalLayout{};

    QDateTimeEdit* m_startDateTimeEdit{};
    QDateTimeEdit* m_endDateTimeEdit{};

    QLineEdit* m_fileNameLineEdit{};
    QLineEdit* m_ownerLineEdit{};

    QPushButton* m_queryBtn{};

    KGlobalData* m_pGlobalData = KGlobalData::getGlobalDataInstance();
};

#endif