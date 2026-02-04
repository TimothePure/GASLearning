// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Enemy/GLSearchForTargetAbility.h"

#include "Characters/GLBaseCharacter.h"
#include "Characters/GLEnemyCharacter.h"
#include "GameplayTags/GLTags.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
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
	
	StartSearch();
}

void UGLSearchForTargetAbility::ClearOngoingTasks()
{
	if (WaitTask)
	{
		WaitTask->EndTask();
		WaitTask = nullptr;
	}
}

void UGLSearchForTargetAbility::StartSearch()
{
	OwningEnemy = Cast<AGLEnemyCharacter>(GetAvatarActorFromActorInfo());
	if (OwningEnemy == nullptr) StartSearch();
	OwningAIController = Cast<AAIController>(OwningEnemy->GetController());
	
	const float WaitDuration = FMath::FRandRange(OwningEnemy->MinAttackDelay, OwningEnemy->MaxAttackDelay);
	
	WaitTask = UAbilityTask_WaitDelay::WaitDelay(this, WaitDuration);
	
	if (WaitTask != nullptr)
	{
		WaitTask->OnFinish.AddDynamic(this, &ThisClass::SearchAndMoveToClosestTarget);
		WaitTask->Activate();
	}
}

void UGLSearchForTargetAbility::SearchAndMoveToClosestTarget()
{
	FClosestActorWithTagResult ClosestTargetResult = UGLGameplayStaticsLibrary::FindClosestActorWithTag(OwningEnemy, OwningEnemy->GetActorLocation(), GLTags::Player);
	DrawDebugSphere(GetWorld(), ClosestTargetResult.Actor->GetActorLocation(), 10.f, 12, FColor::Red, false, 10.f);
	
	OwningAIController->MoveToActor(ClosestTargetResult.Actor.Get(), OwningEnemy->AcceptanceRadius);
}
