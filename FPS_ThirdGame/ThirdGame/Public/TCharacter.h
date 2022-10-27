//TCharacter.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TWeapon.h"
#include "GameFramework/Character.h"
#include "TCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class THIRDGAME_API ATCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveFoward(float Value);

	void MoveRight(float Value);

	void BeginCrouch();
	void EndCrouch();

	void BeginZoom();
	void EndZoom();



	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArmComp;

	//UPROPERTY(EditDefaultsOnly, Category = "Player")
	bool bWantsToZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		float ZoomedFOV;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.0, ClampMax = 100))
		float ZoomInterpSpeed;

	//default FOV set during begin play
	//UPROPERTY(EditDefaultsOnly, Category="Player")
	float DefaultFOV;

	//UPROPERTY(EditDefaultsOnly, Category = "Player")
	ATWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		TSubclassOf<ATWeapon> StarterWeaponClass;

	void Fire();

	//UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

	/*UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
	bool bIsCrouchPressDown;*/
};
