// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GLAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GASLEARNING_API UGLAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	/** Health Attribute **/ 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attribute")
	FGameplayAttributeData Health;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	ATTRIBUTE_ACCESSORS(ThisClass, Health); 
	
	/** MaxHealth Attribute **/ 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attribute")
	FGameplayAttributeData MaxHealth;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth); 
	
	/** Mana Attribute **/ 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Attribute")
	FGameplayAttributeData Mana;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);
	
	ATTRIBUTE_ACCESSORS(ThisClass, Mana); 
	
	/** MaxMana Attribute **/ 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attribute")
	FGameplayAttributeData MaxMana;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);
	
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana); 
};
