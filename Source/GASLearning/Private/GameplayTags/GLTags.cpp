#include "GameplayTags/GLTags.h"

namespace GLTags
{
	namespace GLAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "GLTags.GLAbilities.ActivateOnGiven", "Tag for abilities that should activate immediately once given.");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GLTags.GLAbilities.Primary", "Tag for the Primary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "GLTags.GLAbilities.Secondary", "Tag for the Secondary Ability");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "GLTags.GLAbilities.Tertiary", "Tag for the Tertiary Ability");
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, "GLTags.GLAbilities.Death", "Tag for the Death Ability");
	}
	
	namespace Events
	{
		  UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "GLTags.Events.KillScored", "Tag for the KillScored Event");
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GLTags.Events.Enemy.HitReact", "Tag for the enemy HitReact Event");
		}
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GLTags.Events.Player.Primary", "Tag for the player Primary attack Event");
		}
	}
	
	namespace Status
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dead, "GLTags.Status.Dead", "Tag for the dead status of a character.");
	}
}
