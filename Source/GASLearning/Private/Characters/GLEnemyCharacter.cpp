// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GLEnemyCharacter.h"

#include "AbilitySystem/GLAbilitySystemComponent.h"
#include "AbilitySystem/GLAttributeSet.h"


AGLEnemyCharacter::AGLEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UGLAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UGLAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGLEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AGLEnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void AGLEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	if (HasAuthority())
	{
		GiveStartupAbilities();
		InitializeAttributes();
	}
}

