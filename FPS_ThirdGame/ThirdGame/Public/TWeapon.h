//TWeapon.h

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TWeapon.generated.h"

class USkeletalMeshComponent;
class UDamageType;

UCLASS()
class THIRDGAME_API ATWeapon : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ATWeapon();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* MeshComp;

	/*UFUNCTION(BlueprintCallable, Category = "Weapon")
		void Fire();*/

	/*UFUNCTION(BlueprintCallable, Category = "Weapon")
		void PlayFireEffect();*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<UDamageType>DamageType;
	//UDamageType* DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		FName TracerTargetName;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* TracerEffect;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};