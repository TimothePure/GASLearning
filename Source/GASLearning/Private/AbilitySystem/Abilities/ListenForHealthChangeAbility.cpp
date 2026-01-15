// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ListenForHealthChangeAbility.h"

#include "AbilitySystem/GLAttributeSet.h"
#include "GameplayTags/GLTags.h"
#include "Tasks/GLAttributeChangedTask.h"

UListenForHealthChangeAbility::UListenForHealthChangeAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
}

void UListenForHealthChangeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
                                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	HealthAttributeChangedTask = UGLAttributeChangedTask::ListenForAttributeChange(GetAbilitySystemComponentFromActorInfo(), UGLAttributeSet::GetHealthAttribute());
	
	if (HealthAttributeChangedTask)
	{
		HealthAttributeChangedTask->OnAttributeChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
	}
}

void UListenForHealthChangeAbility::OnHealthChanged(FGameplayAttribute Attribute, float NewValue, float OldValue)
{
	if (NewValue <= 0.f)
	{
		  GetAbilitySystemComponentFromActorInfo()->TryActivateAbilitiesByTag(FGameplayTagContainer(GLTags::GLAbilities::Death));
	}
}

void UListenForHealthChangeAbility::ClearOngoingTasks()
{
	if (HealthAttributeChangedTask)
	{
		HealthAttributeChangedTask->EndTask();
		HealthAttributeChangedTask = nullptr;
	}
}
