#include "LexUILotsOfButtonsManager.h"

#include "LTweenBPLibrary.h"
#include "Core/Components/LexCanvas.h"
#include "Core/Components/LexText.h"
#include "Core/Components/LexWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PrefabSystem/LexUIPrefab.h"

void ULexUILotsOfButtonsManager::Awake()
{
	Super::Awake();
	for (int i = 0; i < ButtonCount; i++)
	{
		if (auto Button = ButtonPrefab->LoadPrefab(this->GetWorld(), ButtonRoot))
		{
			ButtonArray.Add(Button);
		}
	}
	auto RenderCanvas = this->GetWidget()->GetRenderCanvas();
	ULTweenBPLibrary::RepeatCall(this, [this, RenderCanvas]() {
		if (IsValid(FpsText))
		{
			FpsText->SetText(FText::FromString(FString::Printf(TEXT("FPS: %.2f"), 1.0f / GetWorld()->GetDeltaSeconds())));
		}
		if (IsValid(DrawCallCountText))
		{
			DrawCallCountText->SetText(FText::FromString(FString::Printf(TEXT("DrawCalls: %d"), RenderCanvas->GetDrawCallCount())));
		}
	}, 0.5f, 1.0f, -1);
}

void ULexUILotsOfButtonsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateAngle += RotateSpeed * DeltaTime;
	auto Rotation = FRotator(0, 0, RotateAngle).Quaternion();
	for (int i = 0; i < ButtonCount; i++)
	{
		ButtonArray[i]->SetRelativeRotation(Rotation);
	}
}

void ULexUILotsOfButtonsManager::LoadUMG()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, UMGLevel);
}
