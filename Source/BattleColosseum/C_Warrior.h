// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/CharacterMovementComponent.h"
#include "Classes/Components/CapsuleComponent.h"
#include "ConstructorHelpers.h"
#include "C_Warrior.generated.h"


UCLASS()
class BATTLECOLOSSEUM_API AC_Warrior : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Warrior();

protected:
	// ������Ʈ.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code")
	class USpringArmComponent* springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code")
	class UCameraComponent* cam;

	// ������.

	// RunningState, �ٱ� �Ҹ���.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code")
	bool IsSprinting;		
	//  Run Rate, �ٱ� ����.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Code")
	float SprintRate;	
	// OriginSpeed, ���� �ӵ�.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Code")
	float Ori_Speed;	
	// SprintSpeed, ���� �ӵ�. 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Code")
	float Sprint_Speed;		
	// Look Over Right Shoulder, �����ʾ���� �����ִ�. 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code")
	bool RightView;										
	// if set true, Be Man, Nor Be Woman.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	bool SexMan;										
	// ����(�⺻�� : ����).
	class USkeletalMesh* ManMesh;
	class USkeletalMesh* WomanMesh;

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// �Լ���
	// �Է� ���� �ൿ �Լ�
	void MoveForward(float Value);						// ������ ����
	void MoveRight(float Value);						// ������ ����
	void ActiveSprint();								// �ٱ� Ȱ��ȭ
	void DeActiveSprint();								// �ٱ� ��Ȱ��ȭ
	void SwitchView();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
