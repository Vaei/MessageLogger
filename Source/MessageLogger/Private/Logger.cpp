// Copyright (c) 2018 Vaei. MIT License.

#include "Logger.h"
#include "MessageLog/Public/MessageLogModule.h"
#include "MessageLog.h"
#include "Editor.h"

void ULogger::AddLogCategory(
	const FName LogName, 
	const FText LogLabel,
	const bool bShowFilters /*= false*/, 
	const bool bShowPages /*= false*/,
	const bool bAllowClear /*= true*/,
	const bool bDiscardDuplicates /*= false*/,
	const int32 MaxPageCount /*= 20*/, 
	const bool bShowInLogWindow /*= true*/
)
{
	FMessageLogInitializationOptions LogOptions = FMessageLogInitializationOptions();
	LogOptions.bShowFilters = bShowFilters;
	LogOptions.bShowPages = bShowPages;
	LogOptions.bAllowClear = bAllowClear;
	LogOptions.bDiscardDuplicates = bDiscardDuplicates;
	LogOptions.MaxPageCount = MaxPageCount;
	LogOptions.bShowInLogWindow = bShowInLogWindow;

	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	MessageLogModule.RegisterLogListing(LogName, LogLabel, LogOptions);
}

void ULogger::RemoveLogCategory(const FName LogName)
{
	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	MessageLogModule.UnregisterLogListing(LogName);
}

void ULogger::MessageLog(const FString InfoString, const ELoggerCategories Log /*= ELoggerCategories::LC_PlayInEditor*/, const ELoggerSeverity Severity /*= ELoggerSeverity::LS_Info*/)
{
	MessageLogByName(InfoString, GetLogNameFromCategory(Log), Severity);
}

void ULogger::MessageLogEndPlay(const FString InfoString)
{
	MessageLogByName(InfoString, GetLogNameFromCategory(ELoggerCategories::LC_PlayInEditor), ELoggerSeverity::LS_CriticalError);
	if (GEditor)
	{
		GEditor->RequestEndPlayMap();
	}
}

void ULogger::MessageLogByName(const FString InfoString, const FName LogName, const ELoggerSeverity Severity /*= ELoggerSeverity::LS_Info*/)
{
	FMessageLog MessageLog{ LogName };
	const FText MessageText = FText::FromString(InfoString);

	switch (Severity)
	{
		case ELoggerSeverity::LS_Info:
		{
			MessageLog.Info(MessageText);
			break;
		}
		case ELoggerSeverity::LS_Warning:
		{
			MessageLog.Warning(MessageText);
			break;
		}
		case ELoggerSeverity::LS_PerformanceWarning:
		{
			MessageLog.PerformanceWarning(MessageText);
			break;
		}
		case ELoggerSeverity::LS_Error:
		{
			MessageLog.Error(MessageText);
			break;
		}
		case ELoggerSeverity::LS_CriticalError:
		{
			MessageLog.Error(MessageText);
			break;
		}
	}
}
