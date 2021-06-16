// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
//#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameHUD.h"
#include "MainCharacter.h"
#include "Engine/Level.h"
#include "EquipmentStudio.h"
#include "InventoryStudio.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "Runtime/LevelSequence/Public/LevelSequenceActor.h"
#include "MainController.generated.h"

UENUM()
enum class EPlayerState : uint8
{
	InGame,
	Interacting,
	Paused,
	InMenu,
};
/**
 * 
 */
UCLASS()
class PS1HORROR_API AMainController : public APlayerController
{
	GENERATED_BODY()
	public:

		AMainController();
		// Called every frame
		virtual void Tick(float DeltaTime) override;
		// Called to bind functionality to input
		virtual void SetupInputComponent() override;
		virtual void BeginPlay() override;
		void MoveForward(float Axis);
		void EquipWeapon(FString ItemID);
	public:
	private:
		UPROPERTY(EditAnywhere, Category = "Items Studio")
			TSoftObjectPtr<AEquipmentStudio> EquipmentStudio;
		UPROPERTY(EditAnywhere, Category = "Items Studio")
			TSoftObjectPtr<AInventoryStudio> InventoryStudio;
		UPROPERTY(EditAnywhere, Category = "Dialogs DataTables")
			UDataTable* DialogsDataTable;
		UPROPERTY(EditAnywhere, Category = "Dialogs DataTables")
			UDataTable* DialogChoicesDataTable;
		UPROPERTY(EditAnywhere, Category = "Item DataTables")
			UDataTable* ItemsDataTable;
		UPROPERTY(EditAnywhere, Category = "Weapon DataTables")
			UDataTable* WeaponDataTable;
		UPROPERTY(EditAnywhere, Category = "Texture")
			UTextureRenderTarget2D* GameViewRenderTarget;
		FItem* ItemDataObject;
		FWeapon* WeaponDataObject;
		FDialogs* DialogsDataObject;
		FDialogChoices* DialogChoicesDataObject;

		TArray<FItem*> CharInventory;

		DataRepository DataRepo;
		bool IsOpenningLevel = false;
		FName NextLevelName;
		AActor* LatestCameraReference;
		AMainCharacter* Character;
		AGameHUD* GameHUD;
		EPlayerState PlayerState;
		EPlayerState LatestPlayerState;

		USceneCaptureComponent2D* SceneCaptureComp;
	private:
		friend class ACutsceneTrigger;
		friend class ASingleDoor;
		void UpdatePlayerState(EPlayerState NewPlayerState);
		void TurnLeft(float Axis);
		void Interact();
		void ResetInteraction();
		void Walk();
		void Crouch();
		void ShowInventory();
		void Back();
		void LoadLevel(FName LevelName, ULevelSequence * FadeOutSequence, ULevelSequence* FadeInSequence);
		void PlayTransition(ULevelSequence * TransitionSequence);
		void OpenLevel();
		//void FocusCameraOnInteractable();
		//void AddToInventory(ACollectible* Collectible);
};
