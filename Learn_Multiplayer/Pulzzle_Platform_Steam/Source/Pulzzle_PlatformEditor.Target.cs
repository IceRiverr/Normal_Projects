// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Pulzzle_PlatformEditorTarget : TargetRules
{
	public Pulzzle_PlatformEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("Pulzzle_Platform");
	}
}
