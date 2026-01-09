// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/GLAttributeSet.h"
#include "GameFramework/Character.h"
#include "GLBaseCharacter.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
class UGameplayEffect;
class UAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class GASLEARNING_API AGLBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGLBaseCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const;
	
	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;
	
	UFUNCTION(BlueprintCallable, Category = "Death")
	virtual void HandleRespawn();
	
protected:
	void GiveStartupAbilities();
	void InitializeAttributes() const;
	
	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);
	virtual void HandleDeath();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;
	
	
	UPROPERTY(BlueprintReadOnly, Replicated, meta = (AllowPrivateAccess = true))
	bool bAlive = true;
	
public:
	FORCEINLINE bool IsAlive() const { return bAlive; }
	FORCEINLINE void SetAlive(bool bAliveStatus) { bAlive = bAliveStatus; }
};
