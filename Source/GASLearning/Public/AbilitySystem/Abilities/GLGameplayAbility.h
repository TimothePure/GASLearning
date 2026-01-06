// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GLGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GASLEARNING_API UGLGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug") 
	bool bDrawDebugs = false;
};
