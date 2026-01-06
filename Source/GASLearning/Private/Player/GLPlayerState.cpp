// Fill out your copyright notice in the Description page of Project Settings.


#include "GASLearning/Public/Player/GLPlayerState.h"
#include "AbilitySystem/GLAbilitySystemComponent.h"
#include "AbilitySystem/GLAttributeSet.h"

AGLPlayerState::AGLPlayerState()
{
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UGLAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UGLAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGLPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
