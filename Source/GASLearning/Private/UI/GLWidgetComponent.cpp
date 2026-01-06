// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GLWidgetComponent.h"

#include "AbilitySystem/GLAbilitySystemComponent.h"
#include "AbilitySystem/GLAttributeSet.h"
#include "Characters/GLBaseCharacter.h"


UGLWidgetComponent::UGLWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGLWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	InitAbilitySystemData();
	
	if (!IsASCInitialized())
	{
		GLCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}
	
	InitializeAttributeDelegate();
}

void UGLWidgetComponent::InitAbilitySystemData()
{
	GLCharacter = Cast<AGLBaseCharacter>(GetOwner());
	AttributeSet = Cast<UGLAttributeSet>(GLCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UGLAbilitySystemComponent>(GLCharacter->GetAbilitySystemComponent());
}

bool UGLWidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UGLWidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UGLAbilitySystemComponent>(ASC);
	AttributeSet = Cast<UGLAttributeSet>(AS);
	
	if (!IsASCInitialized()) return;
	
	InitializeAttributeDelegate();
}

void UGLWidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributeInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
	} else
	{
		BindToAttributeChanges();
	}
}

void UGLWidgetComponent::BindToAttributeChanges()
{
	
}