// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GLGameplayAbility.h"
#include "GLDeathAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASLEARNING_API UGLDeathAbility : public UGLGameplayAbility
{
	GENERATED_BODY()
public:	
	UGLDeathAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	virtual void ClearOngoingTasks() override;
	
	UFUNCTION()
	void OnMontageFinished();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY()
	class UAbilityTask_PlayMontageAndWait* MontageTask;
};
