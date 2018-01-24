// Copyright David Lovi, 2018.

using UnrealBuildTool;
using System.Collections.Generic;

public class hello_world_2dEditorTarget : TargetRules
{
	public hello_world_2dEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "hello_world_2d" } );
	}
}
