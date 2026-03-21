// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PoCCloThang : ModuleRules
{
	public PoCCloThang(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"PoCCloThang",
			"PoCCloThang/Variant_Platforming",
			"PoCCloThang/Variant_Platforming/Animation",
			"PoCCloThang/Variant_Combat",
			"PoCCloThang/Variant_Combat/AI",
			"PoCCloThang/Variant_Combat/Animation",
			"PoCCloThang/Variant_Combat/Gameplay",
			"PoCCloThang/Variant_Combat/Interfaces",
			"PoCCloThang/Variant_Combat/UI",
			"PoCCloThang/Variant_SideScrolling",
			"PoCCloThang/Variant_SideScrolling/AI",
			"PoCCloThang/Variant_SideScrolling/Gameplay",
			"PoCCloThang/Variant_SideScrolling/Interfaces",
			"PoCCloThang/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
