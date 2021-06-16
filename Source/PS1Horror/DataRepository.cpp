// Fill out your copyright notice in the Description page of Project Settings.


#include "DataRepository.h"

DataRepository::DataRepository()
{
}

DataRepository::DataRepository (
	UDataTable* _DialogsDataTable, 
	UDataTable* _DialogChoicesDataTable, 
	UDataTable* _ItemDataTable, 
	UDataTable* _WeaponDataTable
)
{
	DialogsDataTable = _DialogsDataTable;
	DialogChoicesDataTable = _DialogChoicesDataTable;
	ItemDataTable = _ItemDataTable;
	WeaponDataTable = _WeaponDataTable;
}

FDialogs* DataRepository::GetDialogsRow(FString RowID) 
{
	if (DialogsDataTable) 
	{
		return DialogsDataTable->FindRow<FDialogs>(FName(RowID), RowID);
	}
	return nullptr;
}

FDialogChoices* DataRepository::GetDialogChoicesRow(FString RowID)
{
	if (DialogChoicesDataTable)
	{
		return DialogChoicesDataTable->FindRow<FDialogChoices>(FName(RowID), RowID);
	}
	return nullptr;
}

FWeapon* DataRepository::GetWeaponRow(FString RowID)
{
	if (WeaponDataTable)
	{
		return WeaponDataTable->FindRow<FWeapon>(FName(RowID), RowID);
	}
	return nullptr;
}

FItem* DataRepository::GetItemRow(FString RowID) 
{
	if (ItemDataTable)
	{
		return ItemDataTable->FindRow<FItem>(FName(RowID), RowID);
	}
	return nullptr;
}

DataRepository::~DataRepository()
{
}
