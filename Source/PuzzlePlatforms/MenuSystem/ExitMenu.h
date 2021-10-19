// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "ExitMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UExitMenu : public UMenuWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;

	UFUNCTION()
	void Cancel();

	UFUNCTION()
	void BackToMenu();

protected:

	virtual bool Initialize() override;
};
