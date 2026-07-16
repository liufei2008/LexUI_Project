// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LexUI_ProjectEditorTarget : TargetRules
{
	public LexUI_ProjectEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		// WindowsPlatform.bEnableAddressSanitizer = true;
		// LinkType = TargetLinkType.Monolithic;
		
		ExtraModuleNames.Add("LexUI_Project");
	}
}
