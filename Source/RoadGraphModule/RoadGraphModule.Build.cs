using UnrealBuildTool;

public class RoadGraphModule : ModuleRules
{
    public RoadGraphModule(TargetInfo Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "Engine", "CoreUObject" });
        PrivateDependencyModuleNames.AddRange( new string[] { "RenderCore" } );
    }
}