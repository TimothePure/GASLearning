// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GLWidgetComponent.h"

#include "AbilitySystem/GLAbilitySystemComponent.h"
#include "AbilitySystem/GLAttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/GLBaseCharacter.h"
#include "UI/GLAttributeWidget.h"


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
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject() , Pair); // for checking the owned widget object
		
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}

void UGLWidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	UGLAttributeWidget* AttributeWidget = Cast<UGLAttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget) || !AttributeWidget->MatchesAttributes(Pair)) return;
		
	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get());
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get());
	});
}