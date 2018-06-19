// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_LobbyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API AC_LobbyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AC_LobbyCharacter();

public: // ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTextRenderComponent* UserID;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCameraComponent* Camera;

	// RunningState, �ٱ� �Ҹ���.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code", Replicated)
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

public: // �Լ�

	virtual void BeginPlay() override;

	// �Է� ���� �ൿ �Լ�
	UFUNCTION(BlueprintCallable)
		void MoveForward(float Value);						// ������ ����
	UFUNCTION(BlueprintCallable)
		void MoveRight(float Value);						// ������ ����
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
		void ActiveSprint();								// �ٱ� Ȱ��ȭ
	UFUNCTION(BlueprintCallable, Server, reliable, WithValidation)
		void DeActiveSprint();								// �ٱ� ��Ȱ��ȭ
	UFUNCTION()
		void SwitchView();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	void Jumpp();
	
	
};
