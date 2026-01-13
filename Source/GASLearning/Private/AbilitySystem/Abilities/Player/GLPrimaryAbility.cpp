// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Player/GLPrimaryAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Engine/OverlapResult.h"
#include "GameplayTags/GLTags.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UGLPrimaryAbility::UGLPrimaryAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UGLPrimaryAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (AttackAnimMontages.Num() > 1)
	{
		if (FlipFlop())
		{
			MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName(TEXT("AttackMontage")), AttackAnimMontages[0]);
		} else
		{
			MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName(TEXT("AttackMontage")), AttackAnimMontages[1]);
		}
	} else
	{
		
		if (IsValid(AttackAnimMontages[0]))
		{
			MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName(TEXT("AttackMontage")), AttackAnimMontages[0]);
		}
	}
	
	if (MontageTask)
	{
		MontageTask->OnCompleted.AddDynamic(this, &ThisClass::OnMontageFinished);
		MontageTask->OnCancelled.AddDynamic(this, &ThisClass::OnMontageFinished);
		MontageTask->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageFinished);
		MontageTask->OnBlendOut.AddDynamic(this, &ThisClass::OnMontageFinished);
		MontageTask->Activate();
	}
	
	WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag(GLTags::Events::Player::Primary));
	
	if (WaitEventTask)
	{
		WaitEventTask->Activate();
		WaitEventTask->EventReceived.AddDynamic(this, &ThisClass::OnGameplayEventReceived);
	}
}

TArray<AActor*> UGLPrimaryAbility::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	
	// Ensure that the overlap test ignores the Avatar actor
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);
	
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
	
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(0.f, 0.f, HitBoxElevationOffset);
	
	GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Visibility, Sphere, QueryParams, ResponseParams);
	
	
	TArray<AActor*> HitActors;
	
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (!IsValid(Result.GetActor())) continue;
		
		HitActors.Add(Result.GetActor());
	}
	
	if (bDrawDebugs)
	{
		DrawHitBoxOverlapDebugs(OverlapResults, HitBoxLocation);
	}
	
	return HitActors;
}

void UGLPrimaryAbility::SendHitReactEventToActors(const TArray<AActor*>& HitActors)
{
	for (AActor* HitActor : HitActors)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, GLTags::Events::Enemy::HitReact, Payload);
	}
}

void UGLPrimaryAbility::ApplyDamageEffectToActors(const TArray<AActor*>& HitActors)
{
	FGameplayAbilityTargetDataHandle TargetData;
	FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffect,  GetAbilityLevel());
	
	for (auto HitActor : HitActors)
	{
		FGameplayAbilityTargetData_ActorArray* Data = new FGameplayAbilityTargetData_ActorArray();
		Data->TargetActorArray.Add(HitActor);
		TargetData.Add(Data);
	}
	
	ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, EffectSpecHandle, TargetData);
}

void UGLPrimaryAbility::ClearOngoingTasks()
{
	if (WaitEventTask)
	{
		WaitEventTask->EndTask();
		WaitEventTask = nullptr;
	}

	if (MontageTask)
	{
		MontageTask->EndTask();
		MontageTask = nullptr;
	}
}

void UGLPrimaryAbility::DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const
{
	DrawDebugSphere(GetWorld(), HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);
	
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (IsValid(Result.GetActor()))
		{
			FVector DebugLocation = Result.GetActor()->GetActorLocation();
			DebugLocation.Z += 100.f;
			DrawDebugSphere(GetWorld(), DebugLocation, 30.f, 10, FColor::Green, false, 3.f);
		}
	}
}

void UGLPrimaryAbility::OnMontageFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UGLPrimaryAbility::OnGameplayEventReceived(FGameplayEventData Payload)
{
	TArray<AActor*> HitActors = HitBoxOverlapTest();
	SendHitReactEventToActors(HitActors);
	ApplyDamageEffectToActors(HitActors);
}

bool UGLPrimaryAbility::FlipFlop()
{
	return bFlipFlop = !bFlipFlop;
}