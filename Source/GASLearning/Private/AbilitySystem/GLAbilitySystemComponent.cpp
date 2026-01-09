// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GLAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/GLGameplayAbility.h"
#include "GameplayTags/GLTags.h"


UGLAbilitySystemComponent::UGLAbilitySystemComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;
}

void UGLAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	
	if (!IsValid(AbilitySpec.Ability)) return;
	
	HandleAutoActivatedAbility(AbilitySpec);
}

void UGLAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		HandleAutoActivatedAbility(AbilitySpec);
	}
}

void UGLAbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 NewLevel)
{
	if (!IsValid(GetAvatarActor()) || !GetAvatarActor()->HasAuthority()) return;
	
	if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass))
	{
		AbilitySpec->Level = NewLevel;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UGLAbilitySystemComponent::IncrementAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 LevelToAdd)
{
	if (!IsValid(GetAvatarActor()) || !GetAvatarActor()->HasAuthority()) return;
	
	if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass))
	{
		AbilitySpec->Level += LevelToAdd;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UGLAbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	for (const FGameplayTag& Tag : AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTagExact(GLTags::GLAbilities::ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);
			return;
		}
	}
}
