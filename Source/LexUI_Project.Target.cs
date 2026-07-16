// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LexUI_ProjectTarget : TargetRules
{
	public LexUI_ProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		WindowsPlatform.bEnableAddressSanitizer = true;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		LinkType = TargetLinkType.Monolithic;
		
		ExtraModuleNames.Add("LexUI_Project");
	}
}
