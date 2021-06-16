// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemRepository.h"
#include "InventoryItemObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PS1HORROR_API UInventoryItemObject : public UObject
{
	GENERATED_BODY()
	public:
		UInventoryItemObject();
		UInventoryItemObject(FString _ItemName);
		void SetID(FString _ItemID);
		void SetName(FString _ItemName);
		void SetDescription(FString _ItemDescription);
		void SetCommandNameList(TArray<FString> _CommandNameList);
		void SetCommandIndexList(TArray<EItemCommands> _CommandIndexList);
		UFUNCTION(BlueprintCallable)
			FText GetItemID() { return FText::FromString(ItemID); };

		UFUNCTION(BlueprintCallable)
			FText GetItemName() { return FText::FromString(ItemName); };

		UFUNCTION(BlueprintCallable)
			FText GetItemDescription() { return FText::FromString(ItemDescription); };

		UFUNCTION(BlueprintCallable)
			TArray<FString> GetCommandNameList() { return CommandNameList; };

		UFUNCTION(BlueprintCallable)
			TArray<EItemCommands> GetCommandIndexList() { return CommandIndexList; };

		TArray<FString> CommandNameList;
		TArray<EItemCommands> CommandIndexList;
private:
		FString ItemID;
		FString ItemName;
		FString ItemDescription;
};