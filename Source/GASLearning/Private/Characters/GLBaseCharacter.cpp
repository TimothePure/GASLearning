// Fill out your copyright notice in the Description page of Project Settings.


#include "GASLearning/Public/Characters/GLBaseCharacter.h"


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
