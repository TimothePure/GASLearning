// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Enemy/GLHitReactAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameplayTags/GLTags.h"

void UGLHitReactAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
                                         const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// UAbilityTask_WaitGameplayEvent* WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, GLTags::Events::Enemy::HitReact);
	//
	// if (WaitEventTask)
	// {
	// 	WaitEventTask->EventReceived.AddDynamic(this, &UGLHitReactAbility::OnHitReactEventReceived);
	// 	WaitEventTask->ReadyForActivation();
	// }
}

void UGLHitReactAbility::OnHitReactEventReceived(FGameplayEventData Payload)
{
	
}

void UGLHitReactAbility::CacheHitDirectionVectors(AActor* Instigator)
{
	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	
	const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector InstigatorLocation = Instigator->GetActorLocation();
	
	ToInstigator = InstigatorLocation - AvatarLocation;
	ToInstigator.Normalize();
}
