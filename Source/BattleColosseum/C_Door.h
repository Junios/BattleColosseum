// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Components/BoxComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Public/Math/UnrealMathUtility.h"
#include "ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "C_Door.generated.h"

UCLASS()
class BATTLECOLOSSEUM_API AC_Door : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Door();

protected:
	// 컴포넌트들.
	class UBoxComponent* Collision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* StaticDoor;
	class UBoxComponent* BoxTrig;

	// 변수들.
	float Speed;
	bool IsOpen;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 함수들.
	UFUNCTION(BlueprintCallable)
	void DoorOpen();
	UFUNCTION(BlueprintCallable)
	void DoorClose();

	UFUNCTION(BlueprintCallable)
	void BoxTrigBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION(BlueprintCallable)
	void BoxTrigEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
