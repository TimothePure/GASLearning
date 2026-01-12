// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GLGameplayAbility.h"
#include "GLPrimaryAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASLEARNING_API UGLPrimaryAbility : public UGLGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	TArray<AActor*> HitBoxOverlapTest();
	
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SendHitReactEventToActors(const TArray<AActor*>& HitActors);
	
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ApplyDamageEffectToActors(const TArray<AActor*>& HitActors);
	
private:
	void DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const;
	
	UFUNCTION()
	void OnMontageFinished();
	
	UFUNCTION()
	void OnGameplayEventReceived(FGameplayEventData Payload);
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	float HitBoxRadius = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	float HitBoxForwardOffset = 200.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	float HitBoxElevationOffset = 20.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TArray<UAnimMontage*> AttackAnimMontages;
	
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DamageEffect;
	
	bool bFlipFlop;
	bool FlipFlop();
	
	UPROPERTY()
	class UAbilityTask_WaitGameplayEvent* WaitEventTask;

	UPROPERTY()
	class UAbilityTask_PlayMontageAndWait* MontageTask;
};
