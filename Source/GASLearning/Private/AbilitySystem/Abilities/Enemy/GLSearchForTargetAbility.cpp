// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Enemy/GLSearchForTargetAbility.h"

#include "Characters/GLBaseCharacter.h"
#include "GameplayTags/GLTags.h"
#include "Utils/GLGameplayStaticsLibrary.h"

UGLSearchForTargetAbility::UGLSearchForTargetAbility()
{
	SetAssetTags(FGameplayTagContainer(GLTags::GLAbilities::ActivateOnGiven));
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void UGLSearchForTargetAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	FClosestActorWithTagResult Result = UGLGameplayStaticsLibrary::FindClosestActorWithTag(AvatarActor, AvatarActor->GetActorLocation(), GLTags::Player);
	
	DrawDebugSphere(GetWorld(), Result.Actor->GetActorLocation(), 10.f, 12, FColor::Red, false, 10.f);
}
