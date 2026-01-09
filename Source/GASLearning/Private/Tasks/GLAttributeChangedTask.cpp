// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/GLAttributeChangedTask.h"
#include "AbilitySystemComponent.h"

UGLAttributeChangedTask* UGLAttributeChangedTask::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	if (!IsValid(AbilitySystemComponent)) return nullptr;
	
	UGLAttributeChangedTask* WaitForAttributeChangeTask = NewObject<UGLAttributeChangedTask>();
	WaitForAttributeChangeTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangeTask->AttributeToListenFor = Attribute;
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangeTask, &UGLAttributeChangedTask::AttributeChanged);
	
	return WaitForAttributeChangeTask;
}

void UGLAttributeChangedTask::EndTask()
{
	if (ASC.IsValid())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}
	
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UGLAttributeChangedTask::AttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
