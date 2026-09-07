// Fill out your copyright notice in the Description page of Project Settings.


#include "AddShadowToAllVisual.h"

#include "Core/Components/LexVisualBatchMesh.h"
#include "Core/Components/LexWidget.h"
#include "MeshModifier/LexMeshModifierShadow.h"

void UAddShadowToAllVisual::OnRegister()
{
	Super::OnRegister();
	AddShadow();	
}

void UAddShadowToAllVisual::OnUnregister()
{
	Super::OnUnregister();
	RemoveShadow();
}

#if WITH_EDITOR
void UAddShadowToAllVisual::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
	AddShadow();
	UpdateParams();
}
#endif

void UAddShadowToAllVisual::AddShadow()
{
	struct LOCAL
	{
		static void CollectVisual(ULexWidget* Widget, TArray<TObjectPtr<ULexVisualBatchMesh>>& Visuals)
		{
			if (auto VisualBatchMesh = Widget->GetVisualAs<ULexVisualBatchMesh>())
			{
				Visuals.Add(VisualBatchMesh);
			}
			for (auto Child : Widget->GetChildren())
			{
				CollectVisual(Child, Visuals);
			}
		}
	};
	
	AllShadowCollection.Empty();
	TArray<TObjectPtr<ULexVisualBatchMesh>> Visuals;
	LOCAL::CollectVisual(this->GetWidget(), Visuals);
	for (auto Visual : Visuals)
	{
		auto ShadowComp = Visual->GetWidget()->GetComponent<ULexMeshModifierShadow>();
		if (!ShadowComp)
		{
			ShadowComp = Visual->GetWidget()->AddComponent<ULexMeshModifierShadow>();
			ShadowComp->SetFlags(EObjectFlags::RF_Transient);
		}
		AllShadowCollection.AddUnique(ShadowComp);
	}
	
	UpdateParams();
}

void UAddShadowToAllVisual::UpdateParams()
{
	for (auto Shadow : AllShadowCollection)
	{
		if (!IsValid(Shadow))continue;
		Shadow->SetShadowColor(this->ShadowColor);
		Shadow->SetMultiplySourceAlpha(this->bMultiplySourceColor);
		Shadow->SetMultiplySourceAlpha(this->bMultiplySourceAlpha);
		Shadow->SetShadowOffset(this->ShadowOffset);
	}
}

void UAddShadowToAllVisual::RemoveShadow()
{
	for (auto Shadow : AllShadowCollection)
	{
		if (!IsValid(Shadow))continue;
		Shadow->DestroyComponent();
	}
	AllShadowCollection.Empty();
}
