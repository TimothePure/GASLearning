// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GLBaseCharacter.h"
#include "GLEnemyCharacter.generated.h"


class UGLAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class GASLEARNING_API AGLEnemyCharacter : public AGLBaseCharacter
{
	GENERATED_BODY()

public:
	AGLEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float AcceptanceRadius = 500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float MinAttackDelay = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float MaxAttackDelay = 0.5f;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGLAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
