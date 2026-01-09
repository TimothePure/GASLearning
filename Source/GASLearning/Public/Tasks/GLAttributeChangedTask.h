// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GLAttributeChangedTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

struct FOnAttributeChangeData;

UCLASS(Blueprinttype, meta = (ExposedAsyncProxy = AsyncTask))
class GASLEARNING_API UGLAttributeChangedTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UGLAttributeChangedTask* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);

	UFUNCTION(BlueprintCallable)
	void EndTask();

	TWeakObjectPtr<UAbilitySystemComponent> ASC;
	FGameplayAttribute AttributeToListenFor;
	
	void AttributeChanged(const FOnAttributeChangeData& Data);
};
