// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/LexUIBehaviour.h"
#include "AddShadowToAllVisual.generated.h"

class ULexMeshModifierShadow;
/**
 * This will add Shadow component to all children widget which has visual
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class LEXUI_PROJECT_API UAddShadowToAllVisual : public ULexUIBehaviour
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "LGUI")
	FColor ShadowColor = FColor::Black;
	UPROPERTY(EditAnywhere, Category = "LGUI")
	bool bMultiplySourceColor = false;
	UPROPERTY(EditAnywhere, Category = "LGUI")
	bool bMultiplySourceAlpha = true;
	UPROPERTY(EditAnywhere, Category = "LGUI")
	FVector3f ShadowOffset = FVector3f(0, 1, -1);
	
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<ULexMeshModifierShadow>> AllShadowCollection;
	
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
#if WITH_EDITOR
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif
	
	void AddShadow();
	void UpdateParams();
	void RemoveShadow();
public:
	
};
