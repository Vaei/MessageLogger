// Copyright (c) 2018 Vaei

using UnrealBuildTool;

public class MessageLogger : ModuleRules
{
	public MessageLogger(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
            );
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "CoreUObject",
                "Engine",
                "UnrealEd",
				// ... add private dependencies that you statically link with here ...	
			}
			);
	}
}
