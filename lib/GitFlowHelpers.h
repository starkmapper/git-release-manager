#pragma once
#include "Version.h"
/// Hotfix commands for git-flow
class Hotfix
{
public:
	/// Call git flow start hotfix using the specified version
	static void start(Version in);
};
