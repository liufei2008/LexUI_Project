// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LexUI_ProjectTarget : TargetRules
{
	//=== ASan 编译开关 ===
	//true = 启用 AddressSanitizer。注意：
	//1. 官方(Launcher)引擎 + ASan 打包会链接失败(LNK2019 FRDGAllocator::AcquireAccess/ReleaseAccess)，
	//   因为引擎 DLL 未带 ASan 编译；ASan 打包请使用源码引擎(G:\UE5.7.4_Src)。
	//2. ASan 会强制 StaticAllocator=Ansi，与 UnrealGame 共享构建环境的 Binned2 冲突，
	//   因此开启时同时设置 bOverrideBuildEnvironment=true 跳过该检查。
	private const bool bUseAddressSanitizer = false;

	public LexUI_ProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		if (bUseAddressSanitizer)
		{
			WindowsPlatform.bEnableAddressSanitizer = true;
			//可选：源码引擎下若打包后运行时秒退（Win11 24H2 上 Clang 动态 ASan runtime 的
			//interception_win 问题），改回 MSVC ASan 可去掉下面这行注释。
			// WindowsPlatform.Compiler = WindowsCompiler.Clang;
			bOverrideBuildEnvironment = true;
		}
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		LinkType = TargetLinkType.Monolithic;
		
		ExtraModuleNames.Add("LexUI_Project");
	}
}
