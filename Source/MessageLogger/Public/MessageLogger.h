// Copyright (c) 2018 Vaei

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMessageLoggerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
