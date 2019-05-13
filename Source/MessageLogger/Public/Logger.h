// Copyright (c) 2018 Vaei

#pragma once

#include "CoreMinimal.h"
#include "Logger.generated.h"

UENUM(BlueprintType)
enum class ELoggerCategories : uint8
{
	LC_AssetTools					UMETA(DisplayName = "Asset Tools"),
	LC_BuildAndSubmitErrors			UMETA(DisplayName = "Build and Submit Errors"),
	LC_SourceControl				UMETA(DisplayName = "Source Control"),
	LC_BlueprintLog					UMETA(DisplayName = "Blueprint Log"),
	LC_PlayInEditor					UMETA(DisplayName = "Play In Editor"),
	LC_AutomationTestingLog			UMETA(DisplayName = "Automation Testing Log"),
	LC_LocalizationService			UMETA(DisplayName = "Localization Service"),
	LC_AssetReimport				UMETA(DisplayName = "Asset Reimport"),
	LC_LightingResults				UMETA(DisplayName = "Lighting Results"),
	LC_MapCheck						UMETA(DisplayName = "Map Check"),
	LC_LoadErrors					UMETA(DisplayName = "Load Errors"),
	LC_EditorErrors					UMETA(DisplayName = "Editor Errors"),
	LC_PackagingResults				UMETA(DisplayName = "Packaging Results"),
	LC_AssetCheck					UMETA(DisplayName = "Asset Check"),
	LC_SlateStyleLog				UMETA(DisplayName = "Slate Style Log"),
};

UENUM(BlueprintType)
enum class ELoggerSeverity : uint8
{
	LS_CriticalError				UMETA(DisplayName = "Critical Error"),
	LS_Error						UMETA(DisplayName = "Error"),
	LS_PerformanceWarning			UMETA(DisplayName = "Performance Warning"),
	LS_Warning						UMETA(DisplayName = "Warning"),
	LS_Info							UMETA(DisplayName = "Info"),
};

/**
 * 
 */
UCLASS(meta = (DisplayName = "Logger"))
class MESSAGELOGGER_API ULogger : public UObject
{
	GENERATED_BODY()
	
public:
	/**
	 * Add a category to the message log
	 * @param LogName Name of the log to add
	 * @param LogLabel The label to use in the message log
	 * @param bShowFilters Whether to show the filters menu
	 * @param bShowPages Whether to initially show the pages widget; setting this to false will allow the user to manually clear the log
	 * @param bAllowClear Whether to allow the user to clear this log
	 * @param bDiscardDuplicates Whether to check for duplicate messages and discard them
	 * @param MaxPageCount The maximum number of pages this log can hold; pages are managed on a first in, last out basis
	 * @param bShowInLogWindow Whether to show this log in the main log window
	 */
	UFUNCTION(BlueprintCallable, Category = MessageLogger, meta = (DevelopmentOnly, DisplayName = "Add Message Log Category"))
	static void AddLogCategory(const FName LogName, const FName LogLabel, const bool bShowFilters = false, const bool bShowPages = false, const bool bAllowClear = true, const bool bDiscardDuplicates = false, const int32 MaxPageCount = 20, const bool bShowInLogWindow = true);

	/**
	 * Remove a category from the message log
	 * @param LogName Name of the log to remove
	 */
	UFUNCTION(BlueprintCallable, Category = MessageLogger, meta = (DevelopmentOnly, DisplayName = "Remove Message Log Category"))
	static void RemoveLogCategory(const FName LogName);

	/**
	 * Log a message to a pre-existing category
	 * @param InfoString The message to write to the log
	 * @param Log The category to write the message to
	 * @param Severity The severity of the message
	 */
	UFUNCTION(BlueprintCallable, Category = MessageLogger, meta = (DevelopmentOnly))
	static void MessageLog(const FString InfoString, const ELoggerCategories Log = ELoggerCategories::LC_PlayInEditor, const ELoggerSeverity Severity = ELoggerSeverity::LS_Info);

	/**
	 * Log a message to the "play in editor" category and close play in editor
	 * Particularly useful for avoiding otherwise fatal errors that would crash the editor
	 * @param InfoString The message to write to the log
	 */
	UFUNCTION(BlueprintCallable, Category = MessageLogger, meta = (DevelopmentOnly))
	static void MessageLogEndPlay(const FString InfoString);

	/**
	 * Log a message to any specified category
	 * @param InfoString The message to write to the log
	 * @param LogName The name of the log to write the message to
	 * @param Severity The severity of the message
	 */
	UFUNCTION(BlueprintCallable, Category = MessageLogger, meta = (DevelopmentOnly))
	static void MessageLogByName(const FString InfoString, const FName LogName, const ELoggerSeverity Severity = ELoggerSeverity::LS_Info);

private:
	static FName GetLogNameFromCategory(const ELoggerCategories& Category)
	{
		switch (Category)
		{
		case ELoggerCategories::LC_AssetTools:
			return TEXT("AssetTools");
		case ELoggerCategories::LC_BuildAndSubmitErrors:
			return TEXT("BuildAndSubmitErrors");
		case ELoggerCategories::LC_SourceControl:
			return TEXT("SourceControl");
		case ELoggerCategories::LC_BlueprintLog:
			return TEXT("BlueprintLog");
		case ELoggerCategories::LC_PlayInEditor:
			return TEXT("PIE");
		case ELoggerCategories::LC_AutomationTestingLog:
			return TEXT("AutomationTestingLog");
		case ELoggerCategories::LC_LocalizationService:
			return TEXT("LocalizationService");
		case ELoggerCategories::LC_AssetReimport:
			return TEXT("AssetReimport");
		case ELoggerCategories::LC_LightingResults:
			return TEXT("LightingResults");
		case ELoggerCategories::LC_MapCheck:
			return TEXT("MapCheck");
		case ELoggerCategories::LC_LoadErrors:
			return TEXT("LoadErrors");
		case ELoggerCategories::LC_EditorErrors:
			return TEXT("EditorErrors");
		case ELoggerCategories::LC_PackagingResults:
			return TEXT("PackagingResults");
		case ELoggerCategories::LC_AssetCheck:
			return TEXT("AssetCheck");
		case ELoggerCategories::LC_SlateStyleLog:
			return TEXT("SlateStyleLog");
		}
		return NAME_None;
	}
};
