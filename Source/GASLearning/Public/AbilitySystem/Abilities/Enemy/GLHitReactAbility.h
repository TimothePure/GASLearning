// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GLGameplayAbility.h"
#include "GLHitReactAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASLEARNING_API UGLHitReactAbility : public UGLGameplayAbility
{
	GENERATED_BODY()
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly, Category = "Abilities");
	FVector AvatarForward;
	
	UPROPERTY(BlueprintReadOnly, Category = "Abilities");
	FVector ToInstigator;
	
protected:
	UFUNCTION()
	void OnHitReactEventReceived(FGameplayEventData Payload);
};
