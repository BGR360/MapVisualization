using UnrealBuildTool;

public class OpenStreetMapModule : ModuleRules
{
    public OpenStreetMapModule( TargetInfo Target )
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "Engine", "CoreUObject", "XmlParser", "UnrealEd" });
        PrivateDependencyModuleNames.AddRange( new string[] { "RenderCore" } );
    }
}