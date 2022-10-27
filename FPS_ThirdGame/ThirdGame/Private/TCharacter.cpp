//TCharacter.cpp

// Fill out your copyright notice in the Description page of Project Settings.


#include "TCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
ATCharacter::ATCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->bUsePawnControlRotation = true; //"Camera/CameraComponent.h" include½ÃÄÑÁà¾ß ÇÔ
	CameraComp->SetupAttachment(SpringArmComp);

	SpringArmComp->TargetArmLength = 200.0f;
	ZoomedFOV = 65.0f;


}

// Called when the game starts or when spawned
void ATCharacter::BeginPlay()
{
	Super::BeginPlay();


	DefaultFOV = CameraComp->FieldOfView;

	//Spawn a default weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon = Cast<ATWeapon>(GetWorld()->SpawnActor<AActor>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams));
	if (CurrentWeapon) {
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "WeaponAttachSocketName");
	}
}

void ATCharacter::MoveFoward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void ATCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void ATCharacter::Fire()
{
	if (CurrentWeapon) {

		CurrentWeapon->Fire();
	}
}

// Called every frame
void ATCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;

	float NewFOV = FMath::FInterpTo(CameraComp->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);
	CameraComp->SetFieldOfView(TargetFOV);

}

// Called to bind functionality to input
void ATCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveFoward", this, &ATCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ATCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ATCharacter::AddControllerYawInput);


	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ATCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ATCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ATCharacter::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &ATCharacter::EndZoom);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATCharacter::Jump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATCharacter::Fire);


}

FVector ATCharacter::GetPawnViewLocation() const
{
	if (CameraComp) {

		return CameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

void ATCharacter::BeginCrouch()
{
	//bIsCrouchPressDown = true;
	Crouch();
}

void ATCharacter::EndCrouch()
{
	//bIsCrouchPressDown = false;
	UnCrouch();
}

void ATCharacter::BeginZoom()
{
	bWantsToZoom = true;
}

void ATCharacter::EndZoom()
{
	bWantsToZoom = false;
}
