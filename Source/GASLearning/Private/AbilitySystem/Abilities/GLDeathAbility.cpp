// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GLDeathAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameplayTags/GLTags.h"

UGLDeathAbility::UGLDeathAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	SetAssetTags(FGameplayTagContainer(GLTags::GLAbilities::Death));
}

void UGLDeathAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName(TEXT("AttackMontage")), DeathAnimMontage);
	
	if (MontageTask)
	{
		MontageTask->OnCompleted.AddDynamic(this, &ThisClass::OnMontageFinished);
		MontageTask->OnCancelled.AddDynamic(this, &ThisClass::OnMontageFinished);
		MontageTask->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageFinished);
		MontageTask->OnBlendOut.AddDynamic(this, &ThisClass::OnMontageFinished);
		MontageTask->Activate();
	}
}

void UGLDeathAbility::ClearOngoingTasks()
{
	if (MontageTask)
	{
		MontageTask->EndTask();
		MontageTask = nullptr;
	}
}

void UGLDeathAbility::OnMontageFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
