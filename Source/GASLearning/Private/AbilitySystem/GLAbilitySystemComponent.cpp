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
