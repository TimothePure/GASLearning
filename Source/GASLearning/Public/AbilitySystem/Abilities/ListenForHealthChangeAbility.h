// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GLGameplayAbility.h"
#include "ListenForHealthChangeAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASLEARNING_API UListenForHealthChangeAbility : public UGLGameplayAbility
{
	GENERATED_BODY()
	
public:
	UListenForHealthChangeAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	virtual void ClearOngoingTasks() override;

private:
	UFUNCTION()
	void OnHealthChanged(FGameplayAttribute Attribute, float NewValue, float OldValue);
	
	class UGLAttributeChangedTask* HealthAttributeChangedTask;
};
