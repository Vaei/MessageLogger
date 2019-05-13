// Copyright (c) 2018 Vaei

#pragma once

#include "CoreMinimal.h"
#include "ModuleInterface.h"

class FMessageLoggerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
