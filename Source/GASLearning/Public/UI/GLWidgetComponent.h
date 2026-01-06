// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GLWidgetComponent.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;
class UGLAttributeSet;
class UGLAbilitySystemComponent;
class AGLBaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASLEARNING_API UGLWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UGLWidgetComponent();

protected:
	virtual void BeginPlay() override;

private:
	TWeakObjectPtr<AGLBaseCharacter> GLCharacter;
	TWeakObjectPtr<UGLAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UGLAttributeSet> AttributeSet;
	
	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAttributeDelegate();
	
	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	UFUNCTION()
	void BindToAttributeChanges();
};
