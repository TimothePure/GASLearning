// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GLGameplayAbility.h"
#include "GLSearchForTargetAbility.generated.h"

class AAIController;
class AGLEnemyCharacter;
/**
 * 
 */
UCLASS()
class GASLEARNING_API UGLSearchForTargetAbility : public UGLGameplayAbility
{
	GENERATED_BODY()
public:
	UGLSearchForTargetAbility();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
protected:
	virtual void ClearOngoingTasks() override;
	
	void StartSearch();
	
	UFUNCTION()
	void SearchAndMoveToClosestTarget();
	
private:
	UPROPERTY(VisibleAnywhere)
	AGLEnemyCharacter* OwningEnemy;
	
	UPROPERTY(VisibleAnywhere)
	AAIController* OwningAIController;
	
	UPROPERTY()
	class UAbilityTask_WaitDelay* WaitTask;
};
