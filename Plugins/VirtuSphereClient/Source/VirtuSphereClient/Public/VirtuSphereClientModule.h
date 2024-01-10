// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class VirtuSphereDllHost;

class FVirtuSphereClientModule : public IModuleInterface
{
private:
	VirtuSphereDllHost* dllHost;

public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	VirtuSphereDllHost* getDllHost() { return dllHost; }
};
