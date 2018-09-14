// Copyright (c) 2018 Vaei. MIT License.

#include "MessageLogger.h"

#define LOCTEXT_NAMESPACE "FMessageLoggerModule"

void FMessageLoggerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FMessageLoggerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMessageLoggerModule, MessageLogger)