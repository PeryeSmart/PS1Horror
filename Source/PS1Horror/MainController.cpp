// Fill out your copyright notice in the Description page of Project Settings.
#include "MainController.h"

AMainController::AMainController() 
{
	SceneCaptureComp = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComp"));
}

// Called every frame
void AMainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainController::BeginPlay()
{
	DataRepo = DataRepository(DialogsDataTable, DialogChoicesDataTable, ItemsDataTable, WeaponDataTable);

	Character = Cast<AMainCharacter>(GetPawn());
	if (Character)
	{
		this->Possess(Character);
		UpdatePlayerState(EPlayerState::InGame);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("FAILED"));
}

// Called to bind functionality to input
void AMainController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent) 
	{
		InputComponent->BindAxis("MoveForward", this, &AMainController::MoveForward);
		InputComponent->BindAxis("TurnLeft", this, &AMainController::TurnLeft);
		InputComponent->BindAction("Run", IE_Pressed, this, &AMainController::Walk);
		InputComponent->BindAction("Run", IE_Released, this, &AMainController::Walk);
		InputComponent->BindAction("Interact", IE_Pressed, this, &AMainController::Interact);
		InputComponent->BindAction("ShowInventory", IE_Pressed, this, &AMainController::ShowInventory);
		InputComponent->BindAction("Crouch", IE_Pressed, this, &AMainController::Crouch);
		InputComponent->BindAction("Back", IE_Pressed, this, &AMainController::Back).bExecuteWhenPaused = true;
	}
}

void AMainController::UpdatePlayerState(EPlayerState NewPlayerState)
{
	LatestPlayerState = PlayerState;
	PlayerState = NewPlayerState;
	UE_LOG(LogTemp, Warning, TEXT("PlayerState has changed from %d to %d"), LatestPlayerState, PlayerState);
}

void AMainController::MoveForward(float Axis)
{
	if (Character && Axis != 0.f)
	{
		switch (PlayerState) 
		{
			case EPlayerState::InGame:
				Character->MoveForward(Axis);
				break;
			case EPlayerState::Interacting:
				GameHUD = Cast<AGameHUD>(GetHUD());
				if (GameHUD->GetIsInDialogChoice()) 
				{
					if(Axis == 1.0f)
						GameHUD->MoveChoiceUp();
					else
						GameHUD->MoveChoiceDown();				
				}
				else 
				{
					ResetInteraction();
					Character->MoveForward(Axis);
				}
				break;
			case EPlayerState::Paused:
				break;
			case EPlayerState::InMenu:
				break;
		}
	}
}

void AMainController::TurnLeft(float Axis)
{
	if (Character && Axis != 0.f)
	{
		switch (PlayerState)
		{
			case EPlayerState::InGame:
				Character->TurnLeft(Axis);
				break;
			case EPlayerState::Interacting:
				GameHUD = Cast<AGameHUD>(GetHUD());
				if (!GameHUD->GetIsInDialogChoice())
				{
					ResetInteraction();
					Character->TurnLeft(Axis);
				}
				break;
			case EPlayerState::Paused:
				break;
			case EPlayerState::InMenu:
				break;
		}
	}
}

void AMainController::Walk()
{
	if (Character)
	{
		Character->Walk();
	}
}

void AMainController::Crouch()
{
	SetPause(false);
}

void AMainController::Interact()
{
	if (Character)
	{
		FString InteractableID;

		switch (PlayerState)
		{
			case EPlayerState::InGame:
				LatestCameraReference = GetViewTarget();
				Character->BeforeInteract(InteractableID);
				if (!InteractableID.IsEmpty() && DialogsDataTable)
				{
					DialogsDataObject = DataRepo.GetDialogsRow(InteractableID);
					if (DialogsDataObject) 
					{
						GameHUD = Cast<AGameHUD>(GetHUD());
						if (GameHUD) 
						{
							UpdatePlayerState(EPlayerState::Interacting);
							GameHUD->FeedDialogHUD(DialogsDataObject->dialog);
							if (DialogsDataObject->choice) 
							{
								DialogChoicesDataObject = DataRepo.GetDialogChoicesRow(InteractableID);
								if (DialogChoicesDataObject) 
								{
									GameHUD->FeedDialogChoicesHUD(
										DialogChoicesDataObject->dialog,
										DialogChoicesDataObject->confirmation,
										DialogChoicesDataObject->choices
									);
								}
							}
						}
					}
					else
						break;
				}
				else
					break;
			case EPlayerState::Interacting:
				if (GameHUD->GetDialogUpdating()) 
				{
					GameHUD->Confirmed();
					if (!GameHUD->GetDialogUpdating()) 
					{
						if (GameHUD->GetSelectedChoice() || !DialogsDataObject->choice )
						{
							Character->Interact();
							GameHUD->Confirmed();
						}
						else
						{
							ResetInteraction();
						}
					}
				}
				else 
				{
					ResetInteraction();
				}
				break;
			case EPlayerState::Paused:
				break;
			case EPlayerState::InMenu:
				break;
		}
	}
}

void AMainController::ResetInteraction()
{
	GameHUD = Cast<AGameHUD>(GetHUD());
	if (GameHUD) 
	{
		UpdatePlayerState(EPlayerState::InGame);
		GameHUD->ResetDialogHUD();
		SetViewTarget(LatestCameraReference);
	}
}

void AMainController::LoadLevel(FName LevelName, ULevelSequence * FadeOutSequence, ULevelSequence* FadeInSequence)
{	
	NextLevelName = LevelName;
	GameHUD = Cast<AGameHUD>(GetHUD());
	//Fade Out Animation
	PlayTransition(FadeOutSequence);
	// Load Level

}

void AMainController::OpenLevel() 
{
	IsOpenningLevel = true;
	GameHUD->ShowLoadingScreen(true);
	UGameplayStatics::OpenLevel(GetWorld(), NextLevelName);
	//Close LoadingHud
	GameHUD->ShowLoadingScreen(true);
	//Fade In Animation
	//PlayTransition(FadeInSequence);
}

void AMainController::PlayTransition(ULevelSequence * TransitionSequence)
{
	ALevelSequenceActor* CutsceneSequenceActor = GetWorld()->SpawnActor<ALevelSequenceActor>();
	CutsceneSequenceActor->SetSequence(TransitionSequence);
	ULevelSequencePlayer* CutscenePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
		GetWorld(),
		TransitionSequence,
		FMovieSceneSequencePlaybackSettings(),
		CutsceneSequenceActor
	);
	CutscenePlayer->Play();
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(
		handle,
		[this]() {
			if(!IsOpenningLevel)
			{
				OpenLevel();
			}
		},
		CutscenePlayer->GetFrameDuration() / CutscenePlayer->GetFrameRate().Numerator, false
	);
}

void AMainController::ShowInventory()
{
	CharInventory.Empty();
	switch (PlayerState)
	{
		case EPlayerState::InGame:
			Character->IsRunning = false;
			for (FString ItemID : Character->GetInventory()) 
			{
				CharInventory.Add(DataRepo.GetItemRow(ItemID));
			}
			GameHUD = Cast<AGameHUD>(GetHUD());
			if (GameHUD)
			{
				SetInputMode(FInputModeGameAndUI());
				SetShowMouseCursor(true);
				GameHUD->FeedInventoryHUD(CharInventory);
				UpdatePlayerState(EPlayerState::InMenu);
			}
			
		case EPlayerState::Interacting:
		case EPlayerState::Paused:
			//IntHUD = Cast<AInteractHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			//IntHUD->UpdateInteractDialog(InteractDialog.ToString());
		case EPlayerState::InMenu:

			//SetPause(true);
			break;
	}
}

void AMainController::Back()
{
	switch (PlayerState)
	{
		case EPlayerState::InGame:
			UpdatePlayerState(EPlayerState::Interacting);
			break;
		case EPlayerState::Interacting:
			UpdatePlayerState(EPlayerState::Paused);
			break;
		case EPlayerState::Paused:
			//IntHUD = Cast<AInteractHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			//IntHUD->UpdateInteractDialog(InteractDialog.ToString());
			SetPause(true);
			UpdatePlayerState(EPlayerState::InMenu);
			break;
		case EPlayerState::InMenu:
			SetPause(false);
			GameHUD = Cast<AGameHUD>(GetHUD());
			if (GameHUD)
			{
				GameHUD->ResetInventoryHUD();
			}
			UpdatePlayerState(LatestPlayerState);
			break;
	}
}

void AMainController::EquipWeapon(FString ItemID)
{
	WeaponDataObject = DataRepo.GetWeaponRow(ItemID);
	if (WeaponDataObject)
	{
		UE_LOG(LogTemp, Error, TEXT("EQUIPPING WEAPON"));
		Character->EquipWeapon(WeaponDataObject);
		if (EquipmentStudio) 
		{
			EquipmentStudio->SetWeaponMesh(WeaponDataObject->mesh);
		}
	}
}