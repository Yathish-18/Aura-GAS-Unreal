// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};


UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(blueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(blueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyEffectOnRemoval = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InstantApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy DurationApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
		
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InfiniteApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Applied Effects")
	float ActorLevel= 1.f;
};


