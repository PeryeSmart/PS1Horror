// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemObject.h"

UInventoryItemObject::UInventoryItemObject() 
{

}

UInventoryItemObject::UInventoryItemObject(FString _ItemName)
{
	ItemName = _ItemName;
}

void UInventoryItemObject::SetDescription(FString _ItemDescription) 
{
	ItemDescription = _ItemDescription;
}

void UInventoryItemObject::SetID(FString _ItemID)
{
	ItemID = _ItemID;
}

void UInventoryItemObject::SetName(FString _ItemName) 
{
	ItemName = _ItemName;
}

void UInventoryItemObject::SetCommandNameList(TArray<FString> _CommandNameList) 
{
	CommandNameList = _CommandNameList;
}

void UInventoryItemObject::SetCommandIndexList(TArray<EItemCommands> _CommandIndexList) 
{
	CommandIndexList = _CommandIndexList;
}