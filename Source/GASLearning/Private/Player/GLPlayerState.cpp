// Fill out your copyright notice in the Description page of Project Settings.


#include "GASLearning/Public/Player/GLPlayerState.h"
#include "AbilitySystemComponent.h"

AGLPlayerState::AGLPlayerState()
{
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AGLPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
