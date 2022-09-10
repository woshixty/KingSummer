#include "kmsgfilter.h"

#include <tchar.h>

bool KMsgFilter::filter(const KMessage& msg)
{
	// 当前活跃配置文件
	KProfile profile = KGlobalData::getGlobalDataInstance()->activeProfile();
	bool successFlag = true;
	QList<QString> includeList = profile.includeFilesList();
	QList<QString> excludeList = profile.excludeFilesList();
	//只要存在include规则，那么不匹配的都会被淘汰
	if (!includeList.empty())
		successFlag = false;

	QString fileName = msg.filename().split("/").last();
	const auto szfileName = reinterpret_cast<LPCTSTR>(fileName.data());

	for (auto include_rule : includeList)
	{
		const auto szinclude_rule = reinterpret_cast<LPCTSTR>(include_rule.data());
		const bool ok = wildcmp(szfileName, szinclude_rule);
		if (ok)
		{
			successFlag = true;
			break;
		}
	}
	if (!successFlag)return false;

	for (auto exclude_rule : excludeList)
	{
		const auto szexclude_rule = reinterpret_cast<LPCTSTR>(exclude_rule.data());
		if (const bool ok = wildcmp(szfileName, szexclude_rule))
		{
			successFlag = false;
			break;
		}
	}
	if (!successFlag)return false;

	return successFlag;
}

bool STDAPICALLTYPE KMsgFilter::wildcmp(LPCTSTR string, LPCTSTR wild)
{
	const TCHAR* mp;
	const TCHAR* cp = mp = nullptr;
	while (*string && *wild != _T('*'))
	{
		if (_toupper(*wild) != _toupper(*string) && *wild != _T('?'))
			return false;
		wild++;
		string++;
	}
	while (*string)
	{
		if (*wild == _T('*'))
		{
			if (!*++wild)
				return true;
			mp = wild;
			cp = string + 1;
		}
		else
			if (_toupper(*wild) == _toupper(*string) || *wild == _T('?'))
			{
				wild++;
				string++;
			}
			else
			{
				wild = mp;
				string = cp++;
			}
	}
	while (*wild == _T('*'))
		wild++;
	return (!*wild) ? true : false;
}
