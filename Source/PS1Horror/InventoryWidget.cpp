// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "MainController.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{


}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bIsFocusable = true;
}

void UInventoryWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryWidget::ShowWidget() 
{
	this->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryWidget::HideWidget() 
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryWidget::LoadInventory(TArray<FItem*> _InventoryItems) 
{
	InventoryItems = _InventoryItems;
}

void UInventoryWidget::LoadItemList() 
{
	if (InventoryItems.Num() > 0) 
	{
		for (FItem* Item : InventoryItems) 
		{
			TArray<FText> Commands;
			ItemObject = NewObject<UInventoryItemObject>(UInventoryItemObject::StaticClass());
			ItemObject->SetID(Item->id);
			ItemObject->SetName(Item->name);
			ItemObject->SetDescription(Item->description);
			ItemObject->SetCommandNameList(Item->commands);
			ItemObject->SetCommandIndexList(Item->commands_index);
			ItemList->AddItem(ItemObject);
		}
	}
}

void UInventoryWidget::ClearItemList() 
{
	InventoryItems = TArray<FItem*>();
	ItemObject = nullptr;
	ItemList->ClearListItems();
}

void UInventoryWidget::ItemSelect(UInventoryItemObject* ItemObj)
{
	CommandList->SetUserFocus(GetWorld()->GetFirstPlayerController());
	if(ItemObj)
	{
		if (SelectedItemObject != ItemObj) 
		{
			SelectedItemObject = ItemObj;
			ItemObj->GetItemName();
			ItemDescriptionTxt->SetText(ItemObj->GetItemDescription());
			CommandList->ClearListItems();
			for (EItemCommands CmdIndex : ItemObj->CommandIndexList) 
			{
				CommandObject = NewObject<UItemCommandObject>(UItemCommandObject::StaticClass());
				FString CommandName;
				switch (CmdIndex) 
				{
					case EItemCommands::Equip:
						CommandName = FString("Equip");
						CommandObject->CommandDelegate.AddDynamic(this, &UInventoryWidget::Equip);
						break;
					case EItemCommands::Use:
						CommandName = FString("Use");
						CommandObject->CommandDelegate.AddDynamic(this, &UInventoryWidget::Use);
						break;
					case EItemCommands::Combine:
						CommandName = FString("Combine");
						CommandObject->CommandDelegate.AddDynamic(this, &UInventoryWidget::Combine);
						break;
					case EItemCommands::Examine:
						CommandName = FString("Examine");
						CommandObject->CommandDelegate.AddDynamic(this, &UInventoryWidget::Examine);
						break;
				}
				CommandObject->SetCommandName(CommandName);
				CommandList->AddItem(CommandObject);
			}
		}
	}
}

void UInventoryWidget::Equip(UItemCommandObject* CommandObj)
{
	UE_LOG(LogTemp, Warning, TEXT("Equip called"));
	AMainController* chr = Cast<AMainController>(GetWorld()->GetFirstPlayerController());
	if (chr) 
	{
		chr->EquipWeapon(SelectedItemObject->GetItemID().ToString());
		CommandObj->SetCommandName(FString("Unequip"));
	}
}

void UInventoryWidget::Use(UItemCommandObject* CommandObj)
{
	UE_LOG(LogTemp, Warning, TEXT("Use Called"));
}

void UInventoryWidget::Combine(UItemCommandObject* CommandObj)
{
	UE_LOG(LogTemp, Warning, TEXT("Combine Called"));
}

void UInventoryWidget::Examine(UItemCommandObject* CommandObj)
{
	UE_LOG(LogTemp, Warning, TEXT("Examine Called"));
}

void UInventoryWidget::CommandSelect(UItemCommandObject* CommandObj) 
{
	if (CommandObj) 
	{
		if (CommandObj->GetCommandDelegate().IsBound()) 
		{
			CommandObj->CommandDelegate.Broadcast(CommandObj);
		}
	}
}

void UInventoryWidget::UpdateItemDescription(FString ItemDescription) 
{
	//ItemDescriptionTxt->SetText(FText(ItemDescription));
}