// Some copyright should be here...

using System.IO;
using UnrealBuildTool;

public class VirtuSphereClient : ModuleRules
{
	public VirtuSphereClient(ReadOnlyTargetRules Target) : base(Target)
	{
		bUsePrecompiled = true;
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);

        PublicAdditionalLibraries.AddRange(
			new string[]
			{
                Path.Combine(PluginDirectory, "Source", "ThirdParty", "nethost", "nethost.lib")
            }
			);

        //RuntimeDependencies.Add("$(TargetOutputDir)/nethost.dll", Path.Combine(PluginDirectory, "Source/ThirdParty/nethost/nethost.dll"));
        //RuntimeDependencies.Add("$(TargetOutputDir)/VirtuSphereClient.dll", Path.Combine(PluginDirectory, "Source/ThirdParty/VirtuSphereClient/VirtuSphereClient.dll"));
        //RuntimeDependencies.Add("$(TargetOutputDir)/VirtuSphereClient.runtimeconfig.json", Path.Combine(PluginDirectory, "Source/ThirdParty/VirtuSphereClient/VirtuSphereClient.runtimeconfig.json"));


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
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
