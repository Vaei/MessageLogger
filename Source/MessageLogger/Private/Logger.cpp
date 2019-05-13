// Copyright (c) 2018 Vaei

#include "Logger.h"

#if WITH_EDITOR
#include "Editor.h"
#include "ModuleManager.h"
#include "MessageLog.h"
#include "MessageLog/Public/MessageLogModule.h"
#endif  // WITH_EDITOR

void ULogger::AddLogCategory(
	const FName LogName, 
	const FName LogLabel,
	const bool bShowFilters /*= false*/, 
	const bool bShowPages /*= false*/,
	const bool bAllowClear /*= true*/,
	const bool bDiscardDuplicates /*= false*/,
	const int32 MaxPageCount /*= 20*/, 
	const bool bShowInLogWindow /*= true*/
)
{
#if WITH_EDITOR
	FMessageLogInitializationOptions LogOptions = FMessageLogInitializationOptions();
	LogOptions.bShowFilters = bShowFilters;
	LogOptions.bShowPages = bShowPages;
	LogOptions.bAllowClear = bAllowClear;
	LogOptions.bDiscardDuplicates = bDiscardDuplicates;
	LogOptions.MaxPageCount = MaxPageCount;
	LogOptions.bShowInLogWindow = bShowInLogWindow;

	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	MessageLogModule.RegisterLogListing(LogName, FText::FromName(LogLabel), LogOptions);
#endif  // WITH_EDITOR
}

void ULogger::RemoveLogCategory(const FName LogName)
{
#if WITH_EDITOR
	FMessageLogModule& MessageLogModule = FModuleManager::LoadModuleChecked<FMessageLogModule>("MessageLog");
	MessageLogModule.UnregisterLogListing(LogName);
#endif  // WITH_EDITOR
}

void ULogger::MessageLog(const FString InfoString, const ELoggerCategories Log /*= ELoggerCategories::LC_PlayInEditor*/, const ELoggerSeverity Severity /*= ELoggerSeverity::LS_Info*/)
{
#if WITH_EDITOR
	MessageLogByName(InfoString, GetLogNameFromCategory(Log), Severity);
#endif  // WITH_EDITOR
}

void ULogger::MessageLogEndPlay(const FString InfoString)
{
#if WITH_EDITOR
	MessageLogByName(InfoString, GetLogNameFromCategory(ELoggerCategories::LC_PlayInEditor), ELoggerSeverity::LS_CriticalError);
	if (GEditor)
	{
		GEditor->RequestEndPlayMap();
	}
#endif  // WITH_EDITOR
}

void ULogger::MessageLogByName(const FString InfoString, const FName LogName, const ELoggerSeverity Severity /*= ELoggerSeverity::LS_Info*/)
{
#if WITH_EDITOR
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
#endif  // WITH_EDITOR
}
