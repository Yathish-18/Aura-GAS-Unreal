// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag MessageTag = FGameplayTag();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);



/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependancies() override;
	
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Gas|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}