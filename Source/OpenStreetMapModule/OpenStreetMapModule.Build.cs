using UnrealBuildTool;

public class OpenStreetMapModule : ModuleRules
{
    public OpenStreetMapModule( TargetInfo Target )
    {
        PublicDependencyModuleNames.AddRange( new string[] { "Core", "Engine" } );
        PrivateDependencyModuleNames.AddRange( new string[] { "RenderCore" } );
    }
}