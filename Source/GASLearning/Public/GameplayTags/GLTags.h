#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GLTags
{
	namespace GLAbilities
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tertiary);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Death);
	}
	
	namespace Events
	{
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
		}
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary);
		}
	}
}
