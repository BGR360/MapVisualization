using UnrealBuildTool;

public class GeographicLibModule : ModuleRules
{
    public GeographicLibModule( TargetInfo Target )
    {
        PublicDependencyModuleNames.AddRange( new string[] { "Core", "Engine", "MapVisualization" } );
        PrivateDependencyModuleNames.AddRange( new string[] { "RenderCore" } );
    }
}