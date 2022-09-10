#include "kprofileutil.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>

KProfileUtil::KProfileUtil(QObject *parent)
	: QObject(parent)
{}

KProfileUtil::~KProfileUtil()
= default;

void KProfileUtil::toJson(KProfile& profile, QString& json)
{
	json.clear();
	QJsonObject jsonObject;
	jsonObject.insert(QStringLiteral("id"), profile.id());
	jsonObject.insert(QStringLiteral("name"), profile.profileName());
	jsonObject.insert(QStringLiteral("includes"), profile.includeFiles());
	jsonObject.insert(QStringLiteral("excludes"), profile.excludeFiles());
	jsonObject.insert(QStringLiteral("options"), profile.profileOptions());
	jsonObject.insert(QStringLiteral("watchdirs"), profile.watchDirs());
	json.append(QJsonDocument(jsonObject).toJson());
}

void KProfileUtil::parseJson(KProfile& profile, const QString& json)
{
	QJsonParseError error{};
	const QJsonDocument& document = QJsonDocument::fromJson(json.toUtf8(), &error);
	if (QJsonParseError::NoError == error.error)
	{
		const QJsonObject& jsonObject = document.object();
		profile.setId(jsonObject.value(QStringLiteral("id")).toInt());
		profile.setProfileName(jsonObject.value(QStringLiteral("name")).toString());
		profile.setIncludeFiles(jsonObject.value(QStringLiteral("includes")).toString());
		profile.setExcludeFiles(jsonObject.value(QStringLiteral("excludes")).toString());
		profile.setProfileOptions(jsonObject.value(QStringLiteral("options")).toString());
		profile.setWatchDirs(jsonObject.value(QStringLiteral("watchdirs")).toString());
	}
}
