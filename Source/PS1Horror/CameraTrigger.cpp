// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTrigger.h"

// Sets default values
ACameraTrigger::ACameraTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraTriggerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	CameraTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Camera Trigger"));

	CameraTrigger->SetupAttachment(CameraTriggerRoot);
}

// Called when the game starts or when spawned
void ACameraTrigger::BeginPlay()
{
	Super::BeginPlay();
	CameraTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACameraTrigger::OnColliderOverlapBegin);
	if (CameraRef) 
	{
		CameraLocation = CameraRef->GetActorLocation();
	}
	if(IsCameraActive)
	{
		ToggleCamera();
	}
}

// Called every frame
void ACameraTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CameraRef && HittingActor && HittingActor->GetActorLocation() != PlayerActorLocation)
	{
		if (GetWorld()->GetFirstPlayerController()->GetViewTarget() == CameraRef) 
		{
			UpdateCamera();
		}
	}
}

void ACameraTrigger::OnColliderOverlapBegin(
	UPrimitiveComponent* Comp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherIndex, 
	bool bFromSweep, 
	const FHitResult & SweepResult)
{
	ToggleCamera();
	HittingActor = OtherActor;
}

void ACameraTrigger::ToggleCamera() 
{
	if (CameraRef)
	{
		if (!IsBlendingEnable) 
			GetWorld()->GetFirstPlayerController()->SetViewTarget(CameraRef);
		else
			GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(CameraRef, BlendingTime, BlendingFunction, BlendingExponent);
	}
}

void ACameraTrigger::UpdateCamera() 
{
	if (EnableFollowing)
	{
		FVector NewLocation;

		PlayerActorLocation != FVector(0.f, 0.f, 0.f) 
			? NewLocation = HittingActor->GetActorLocation() - PlayerActorLocation
			: NewLocation = FVector(0.f, 0.f, 0.f);

		switch (FollowingAxisEnum)
		{
			case AxisEnum::X:
				CameraLocation = FVector(NewLocation.X, 0.f, 0.f);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *CameraLocation.ToString());
				break;
			case AxisEnum::Y:
				CameraLocation = FVector(0.f, NewLocation.Y, 0.f);
				break;
			case AxisEnum::Z:
				CameraLocation = FVector(0.f, 0.f, NewLocation.Z);
				break;
			case AxisEnum::XY:
				CameraLocation = FVector(NewLocation.X, NewLocation.Y, 0.f);
				break;
			case AxisEnum::XZ:
				CameraLocation = FVector(NewLocation.X, 0.f, NewLocation.Z);
				break;
			case AxisEnum::YZ:
				CameraLocation = FVector(0.f, NewLocation.Y, NewLocation.Z);
				break;
			case AxisEnum::XYZ:
				CameraLocation = FVector(NewLocation.X, NewLocation.Y, NewLocation.Z);
				break;
		}
		PlayerActorLocation = HittingActor->GetActorLocation();
		CameraRef->AddActorWorldTransform(FTransform(CameraLocation), true);
	}

	if (EnableTracking)
	{
		PlayerActorLocation = HittingActor->GetActorLocation();
		CameraLocation = CameraRef->GetActorLocation();
		CameraRotation = UKismetMathLibrary::FindLookAtRotation(CameraLocation, PlayerActorLocation);
		CameraRef->SetActorRotation(FQuat(CameraRotation));
	}
}
