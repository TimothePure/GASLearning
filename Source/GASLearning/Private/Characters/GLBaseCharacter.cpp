// Fill out your copyright notice in the Description page of Project Settings.


#include "GASLearning/Public/Characters/GLBaseCharacter.h"

#include "AbilitySystemComponent.h"


AGLBaseCharacter::AGLBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* AGLBaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AGLBaseCharacter::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void AGLBaseCharacter::InitializeAttributes() const
{
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect not set."));
	
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect, 1.f, EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
;}
