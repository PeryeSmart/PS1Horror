// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsInteracting = false;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	InteractCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact Collider"));
	CharacterMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh Component"));
	WeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh Component"));
	FPSCamera = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("FPS Camera"));

	InteractCollider->SetupAttachment(GetCapsuleComponent());
	FPSCamera->SetupAttachment(CharacterMeshComp);
	CharacterMeshComp->SetupAttachment(GetCapsuleComponent());
	WeaponMeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	InteractCollider->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnInteractOverlapBegin);
	InteractCollider->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnInteractOverlapEnd);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AMainCharacter::Walk);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharacter::Crouch);*/
	PlayerInputComponent->BindAction("FightingStance", IE_Pressed, this, &AMainCharacter::EnterFightingStance);
	PlayerInputComponent->BindAction("FightingStance", IE_Released, this, &AMainCharacter::LeaveFightingStance);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainCharacter::Attack);
}

void AMainCharacter::OnInteractOverlapBegin(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult & SweepResult)
{
	InteractableObject = Cast<IInteractInterface>(OtherActor);
}

void AMainCharacter::OnInteractOverlapEnd(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	InteractableObject = nullptr;
}

void AMainCharacter::Attack() 
{
	if (IsInFightingStance && IsWeaponEquipped)
	{
		if (EquippedWeapon->mag_ammo_count != 0) 
		{
			if (EquippedWeapon->fire_sound)
			{
				UGameplayStatics::PlaySoundAtLocation(WeaponMeshComp, EquippedWeapon->fire_sound, GetActorLocation());
			}

			if (EquippedWeapon->char_fire_anim)
			{
				CharacterMeshComp->PlayAnimation(EquippedWeapon->char_fire_anim, false);
			}

			if (EquippedWeapon->fire_anim)
			{
				WeaponMeshComp->PlayAnimation(EquippedWeapon->fire_anim, false);
			}	
			EquippedWeapon->mag_ammo_count-- ;
		}
		else 
		{
			if (EquippedWeapon->empty_sound)
			{
				UGameplayStatics::PlaySoundAtLocation(WeaponMeshComp, EquippedWeapon->empty_sound, GetActorLocation());
			}
		}
	}
}

void AMainCharacter::EnterFightingStance()
{
	IsInFightingStance = true;
}

void AMainCharacter::LeaveFightingStance() 
{
	IsInFightingStance = false;
	if (EquippedWeapon->mag_ammo_count == 0) 
	{
		EquippedWeapon->mag_ammo_count = EquippedWeapon->mag_capacity;
	}
}

void AMainCharacter::MoveForward(float Axis) 
{
	AddMovementInput(GetActorForwardVector(), Axis);
	if (Axis == -1.f) 
	{
		IsMovingBackward = true;
	}
	else 
	{
		IsMovingBackward = false;
	}
}

void AMainCharacter::TurnLeft(float Axis)
{
	AddControllerYawInput(Axis);
}

void AMainCharacter::Walk() 
{
	if (!IsMovingBackward) 
	{
		if (!IsRunning && !IsInFightingStance) 
		{
			IsRunning = true;
			GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		}
		else 
		{
			IsRunning = false;
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		}	
	}
}

void AMainCharacter::Crouch() 
{

}

void AMainCharacter::BeforeInteract(FString& InteractableID)
{
	InteractableObject = Cast<IInteractInterface>(InteractableObject);
	if (InteractableObject)
	{
		if (InteractableObject->GetIsFocusEnable())
		{
			FocusCameraOnInteractable();
		}
		InteractableID = InteractableObject->GetInteractableID();
	}
}

void AMainCharacter::Interact()
{
	InteractableObject = Cast<IInteractInterface>(InteractableObject);
	if (InteractableObject) 
	{
		InteractableObject->Interact();
		ACollectible * Collectible = Cast<ACollectible>(InteractableObject);
		if (Collectible)
			AddToInventory(Collectible, InteractableObject->GetInteractableID());
	}
}

void AMainCharacter::FocusCameraOnInteractable()
{
	if (InteractableObject)
	{
		FVector InteractableActorLocation = Cast<AActor>(InteractableObject)->GetActorLocation();
		FVector CameraLocation = FPSCamera->GetComponentLocation();
		FRotator CameraRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation, InteractableActorLocation);
		FPSCamera->SetWorldRotation(FQuat(CameraRotation), true);
		GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	}
}

void AMainCharacter::EquipWeapon(FWeapon* WeaponToEquip)
{
	if (WeaponToEquip) 
	{
		EquippedWeapon = WeaponToEquip;
		if (EquippedWeapon->skeletal_mesh)
		{
			WeaponMeshComp->SetSkeletalMesh(EquippedWeapon->skeletal_mesh);
			WeaponMeshComp->AttachToComponent(
				CharacterMeshComp, 
				FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), 
				EquippedWeapon->socket_name
			);
			IsWeaponEquipped = true;
		}
	}
}

void AMainCharacter::AddToInventory(ACollectible* Collectible, FString ItemID)
{
	/*Collect Item and Destroy it in the World*/
	Inventory.Add(ItemID);
	Collectible->DestroyItem();
}
