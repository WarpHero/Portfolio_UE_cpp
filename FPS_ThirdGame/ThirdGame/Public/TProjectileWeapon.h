//// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TWeapon.h"
#include "TProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class THIRDGAME_API ATProjectileWeapon : public ATWeapon
{
	GENERATED_BODY()

protected:

	virtual void Fire(); //override ���ִϱ� �ǳ� �� �׷���?

	UPROPERTY(EditDefaultsOnly, Category="ProjectileWeapon")
	TSubclassOf<AActor>ProjectileClass;
	
};
