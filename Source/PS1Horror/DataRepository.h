// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DialogChoicesRepository.h"
#include "ItemRepository.h"
#include "WeaponRepository.h"
#include "CoreMinimal.h"

/**
 * 
 */
class PS1HORROR_API DataRepository
{
	public:
		DataRepository ();
		DataRepository (
			UDataTable* _DialogsDataTable,
			UDataTable* _DialogChoicesDataTable, 
			UDataTable* _ItemDataTable, 
			UDataTable* _WeaponDataTable
		);
		~DataRepository();

		FDialogs* GetDialogsRow(FString RowID);
		FDialogChoices* GetDialogChoicesRow(FString RowID);
		FWeapon* GetWeaponRow(FString RowID);
		FItem* GetItemRow(FString RowID);

		template <typename T>
		T* GetRow(FString RowID)
		{
			return nullptr;
		};
	private:

		UDataTable* DialogsDataTable;
		UDataTable* DialogChoicesDataTable;
		UDataTable* ItemDataTable;
		UDataTable* WeaponDataTable;
};
