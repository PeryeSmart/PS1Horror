// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleDoor.h"

// Sets default values
ASingleDoor::ASingleDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorRootComponent	=	CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	DoorFrame			=	CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame Mesh"));
	Door				=	CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorCollider		=	CreateDefaultSubobject<UBoxComponent>(TEXT("Door Collider"));

	DoorCollider->SetupAttachment(Door);
	Door->SetupAttachment(DoorFrame);
	DoorFrame->SetupAttachment(DoorRootComponent);
}

// Called when the game starts or when spawned
void ASingleDoor::BeginPlay()
{
	Super::BeginPlay();
	if (IsDoorOpen) 
	{
		OpenDoor();
	}
}

// Called every frame
void ASingleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsOpenning)
	{
		OpenDoor();
	}
}

// Implements Method derived from InteractInterface
void ASingleDoor::Interact()
{
	if (!IsDoorLocked) 
	{
		if (LoadLevelOnOpen) 
		{
			OpenDoor();
			//Load Referenced Level
		}
		else
		{
			bool _IsDoorOpen;
			if (IsDoorOpen) 
			{
				CloseDoor();
				_IsDoorOpen = false;
			}
			else
			{
				IsOpenning = true;
				_IsDoorOpen = true;
			}
			SetDoorOpen(_IsDoorOpen);
		}
	}
}

bool ASingleDoor::GetIsFocusEnable() 
{
	return IsFocusEnable;
}

void ASingleDoor::UnlockDoor()
{
	
}

void ASingleDoor::OpenDoor()
{
	if (LoadLevelOnOpen)
	{
		AMainController* Ctrl = Cast<AMainController>(GetWorld()->GetFirstPlayerController());
		if (Ctrl)
		{
			Ctrl->LoadLevel(LevelToLoad, DoorInCutsceneSequence, DoorOutCutsceneSequence);
		}
		//Load Referenced Level
	}
	else 
	{
		//Door->AddWorldRotation(FQuat(FRotator(0.f, DoorOpeningAngle, 0.f)));
		if (Door->GetRelativeRotation().Yaw != DoorOpeningAngle)
			Door->AddRelativeRotation(FMath::Lerp(FQuat(FRotator(0.f, 0.f, 0.f)), FQuat(FRotator(0.f, DoorOpeningAngle, 0.f)), 0.01));
		else 
		{
			IsOpenning = false;
			UE_LOG(LogTemp, Warning, TEXT("DOOR IS CLOSED"));
		}
	}
}

void ASingleDoor::CloseDoor()
{
	Door->AddWorldRotation(FQuat(FRotator(0.f, -DoorOpeningAngle, 0.f)));
}

bool ASingleDoor::GetIsDoorOpen()
{
	return IsDoorOpen;

}

bool ASingleDoor::GetIsDoorLocked()
{
	return IsDoorLocked;

}

void ASingleDoor::SetDoorLocked(bool _IsDoorLocked)
{
	IsDoorLocked = _IsDoorLocked;
}

void ASingleDoor::SetDoorOpen(bool _IsDoorOpen)
{
	IsDoorOpen = _IsDoorOpen;
}

