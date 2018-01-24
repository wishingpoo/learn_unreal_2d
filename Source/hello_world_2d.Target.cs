// Copyright David Lovi, 2018.

using UnrealBuildTool;
using System.Collections.Generic;

public class hello_world_2dTarget : TargetRules
{
	public hello_world_2dTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "hello_world_2d" } );
	}
}
