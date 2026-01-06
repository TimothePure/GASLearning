// Fill out your copyright notice in the Description page of Project Settings.


#include "GASLearning/Public/Player/GLPlayerState.h"
#include "AbilitySystem/GLAbilitySystemComponent.h"

AGLPlayerState::AGLPlayerState()
{
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UGLAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AGLPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
