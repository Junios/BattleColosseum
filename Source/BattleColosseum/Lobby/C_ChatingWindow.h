// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_ChatingWindow.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECOLOSSEUM_API UC_ChatingWindow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

public: // ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UEditableTextBox* ChattingInput;

public: // �Լ�
	UFUNCTION(BlueprintCallable)
		void SetFocusTextbox(APlayerController* A);
	
	
};
