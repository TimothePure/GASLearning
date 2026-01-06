// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GLBaseCharacter.h"
#include "GLEnemyCharacter.generated.h"


class UGLAbilitySystemComponent;

UCLASS()
class GASLEARNING_API AGLEnemyCharacter : public AGLBaseCharacter
{
	GENERATED_BODY()

public:
	AGLEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGLAbilitySystemComponent> AbilitySystemComponent;
};
