#include "kmessage.h"

#include <utility>
#include <QDebug>

KMessage::KMessage(): m_operation(KOperationFlag::All)
{
}

KMessage::KMessage(KOperationFlag operation, QString fileName, qreal filesize, QString owner)
{
	m_date = QDate::currentDate();
	m_time = QTime::currentTime();
	m_operation = operation;
	m_fileName = std::move(fileName);
	m_fileSize = filesize;
	m_owner = std::move(owner);
}

KMessage::KMessage(const KMessage& other)
{
	m_date = other.m_date;
	m_time = other.m_time;
	m_operation = other.m_operation;
	m_fileName = other.m_fileName;
	m_fileSize = other.m_fileSize;
	m_owner = other.m_owner;
}

KMessage& KMessage::operator=(const KMessage& other)
{
	this->m_date = other.m_date;
	this->m_time = other.m_time;
	this->m_operation = other.m_operation;
	this->m_fileName = other.m_fileName;
	this->m_fileSize = other.m_fileSize;
	this->m_owner = other.m_owner;
	return *this;
}

KMessage::~KMessage()
= default;

QString KMessage::title() const
{
	return "file change!";
}

QString KMessage::content() const
{
	QString content = m_fileName;
	switch (m_operation) {
	case KOperationFlag::BadData: 
		content.append(" error");
		break;
	case KOperationFlag::Added:
		content.append(" added");
		break;
	case KOperationFlag::Deleted:
		content.append(" deleted");
		break;
	case KOperationFlag::Modified:
		content.append(" modified");
		break;
	case KOperationFlag::RenamedFrom:
	case KOperationFlag::RenamedTo:
	case KOperationFlag::Renamed:
		content.append(" renamed");
		break;
	case KOperationFlag::All: break;
	default: break;
	}
	return content;
}

void KMessage::generateRow(QSqlTableModel* model) const
{
	const int rowToSet = model->rowCount();
	model->insertRow(rowToSet);
	model->setData(model->index(rowToSet, 1), static_cast<int>(m_operation));
	model->setData(model->index(rowToSet, 2), m_date.toString("yyyy-MM-dd"));
	model->setData(model->index(rowToSet, 3), m_time.toString("hh:mm:ss"));
	model->setData(model->index(rowToSet, 4), m_fileName);
	model->setData(model->index(rowToSet, 5), m_fileSize);
	model->setData(model->index(rowToSet, 6), m_owner);
	model->submitAll();
}
