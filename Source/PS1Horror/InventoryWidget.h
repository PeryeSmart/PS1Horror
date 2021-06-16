// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemObject.h"
#include "ItemCommandObject.h"
//#include "MainController.h"
#include "Components/Button.h" 
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */

UCLASS()
class PS1HORROR_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	public: 	
		UInventoryWidget(const FObjectInitializer& ObjectInitializer);
		virtual void NativeConstruct() override;
		virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

		UFUNCTION(BlueprintCallable)
			void ItemSelect(UInventoryItemObject* ItemObj);

		UFUNCTION(BlueprintCallable)
			void CommandSelect(UItemCommandObject* CommandObj);

	protected:

	private:
		friend class AGameHUD;
		void ShowWidget();
		void HideWidget();
		void LoadItemList();
		void LoadInventory(TArray<FItem*> _InventoryItems);
		void ClearItemList();
		void UpdateItemDescription(FString ItemDescription);

		UFUNCTION()
			void Equip(UItemCommandObject* CommandObj);
		UFUNCTION()
			void Use(UItemCommandObject* CommandObj);
		UFUNCTION()
			void Combine(UItemCommandObject* CommandObj);
		UFUNCTION()
			void Examine(UItemCommandObject* CommandObj);

	private:
		UInventoryItemObject* ItemObject;
		UInventoryItemObject* SelectedItemObject;
		UItemCommandObject* CommandObject;

		TArray<FItem*> InventoryItems;

		UPROPERTY(EditAnywhere, meta = (BindWidget))
			URichTextBlock* ItemDescriptionTxt;

		UPROPERTY(EditAnywhere, meta = (BindWidget))
			UListView* ItemList;

		UPROPERTY(EditAnywhere, meta = (BindWidget))
			UListView* CommandList;
};
