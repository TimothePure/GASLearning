// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GLBaseCharacter.generated.h"

class UAbilitySystemComponent;

UCLASS(Abstract)
class GASLEARNING_API AGLBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGLBaseCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
