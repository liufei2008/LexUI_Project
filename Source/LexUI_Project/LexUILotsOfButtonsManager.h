

#pragma once

#include "CoreMinimal.h"
#include "Core/LexUIBehaviour.h"

#include "LexUILotsOfButtonsManager.generated.h"

class ULexText;
class ULexUIPrefab;
/**
 * 
 */
UCLASS(ClassGroup = (LGUI), Blueprintable, meta = (BlueprintSpawnableComponent))
class LEXUI_PROJECT_API ULexUILotsOfButtonsManager : public ULexUIBehaviour
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	int32 ButtonCount = 1000;
	UPROPERTY(EditAnywhere)
	TObjectPtr<ULexUIPrefab> ButtonPrefab;
	UPROPERTY(EditAnywhere)
	TObjectPtr<ULexText> FpsText;
	UPROPERTY(EditAnywhere)
	TObjectPtr<ULexText> DrawCallCountText;
	UPROPERTY(EditAnywhere)
	TObjectPtr<ULexWidget> ButtonRoot;
	UPROPERTY(EditAnywhere)
	float RotateSpeed = 10;
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> UMGLevel;
	
	float RotateAngle = 0;

	TArray<TWeakObjectPtr<ULexWidget>> ButtonArray;
	
	virtual void Awake() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void LoadUMG();
};
