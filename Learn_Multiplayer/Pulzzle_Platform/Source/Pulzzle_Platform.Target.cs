// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Pulzzle_PlatformTarget : TargetRules
{
	public Pulzzle_PlatformTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("Pulzzle_Platform");
	}
}
