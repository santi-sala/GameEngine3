// Fill out your copyright notice in the Description page of Project Settings.


#include "Totem.h"
#include "Engine/StaticMesh.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"


// Sets default values
ATotem::ATotem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATotem::BeginPlay()
{
	Super::BeginPlay();
	if (IsRandom)
	{
		if (RandomTotemPieces.Num() != 0)
		{
			SpawnTotemPieces(CreateRandomPieces());
			//SpawnTotemPieces(TotemPieces);
		}
	}
	else
	{
		if (TotemPieces.Num() != 0)
		{
			SpawnTotemPieces(TotemPieces);
		}
	}
	
}

// Called every frame
void ATotem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATotem::SpawnTotemPieces(TArray<UStaticMesh*> Pieces)
{
	float CurrentTotemHeight = 0;
	
	if (IsReversed)
	{
		for (auto i = Pieces.Num(); i--;)
		{
			CurrentTotemHeight = SpawnLoopedPiece(Pieces[i], CurrentTotemHeight);
			
		}
	}
	else
	{
		for (size_t i = 0; i < Pieces.Num(); i++)
		{
			CurrentTotemHeight = SpawnLoopedPiece(Pieces[i], CurrentTotemHeight);
		}
	}
}

TArray<UStaticMesh*> ATotem::CreateRandomPieces()
{
	TArray<UStaticMesh*> Pieces;
	for (size_t i = 0; i < RandomPiecesAMount; i++)
	{
		Pieces.Add(RandomTotemPieces[FMath::RandRange(0, (RandomTotemPieces.Num() - 1))]);
	}
	return Pieces;
}

void ATotem::SetPieceMaterial(UStaticMeshComponent* Piece)
{
	if (IsColored)
	{
		UMaterialInstanceDynamic* DynamicTotemMaterial = UMaterialInstanceDynamic::Create(InstancedTotemMaterial, this);
		SetRandomColor(DynamicTotemMaterial);
		Piece->SetMaterial(0, DynamicTotemMaterial);
	}
	else
	{
		Piece->SetMaterial(0, DefaultTotemMaterial);
	}
}

void ATotem::DestroyTotemPieces()
{
	TArray<AActor*> TobeDestroyedActors;
	this->GetAttachedActors(TobeDestroyedActors);
	for (size_t i = 0; i < TobeDestroyedActors.Num(); i++)
	{
		TobeDestroyedActors[i]->Destroy();
	}
}

void ATotem::SetRandomColor(UMaterialInstanceDynamic* TargetMatInstance)
{
	FLinearColor RandomColor = FLinearColor(FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f),FMath::RandRange(0.0f, 1.0f), 1.0f);
	TargetMatInstance->SetVectorParameterValue("WoodColor", RandomColor);
}

float ATotem::SpawnLoopedPiece(UStaticMesh* PieceToSpawn, float TotemHeight)
{
	float CurrentTotemHeight = TotemHeight;	

	FVector SpawnLocation(GetActorLocation().X, GetActorLocation().Y, (GetActorLocation().Z + CurrentTotemHeight));
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	AStaticMeshActor* SpawnedMesh = GetWorld()->SpawnActor < AStaticMeshActor>(SpawnLocation, Rotation, SpawnInfo);
	SetPieceMaterial(SpawnedMesh->GetStaticMeshComponent());
	SpawnedMesh->SetMobility(EComponentMobility::Movable);
	SpawnedMesh->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	SpawnedMesh->GetStaticMeshComponent()->SetStaticMesh(PieceToSpawn);
	CurrentTotemHeight = (PieceToSpawn->GetBounds().BoxExtent.Z * 2 + TotemHeight);
	return CurrentTotemHeight;
}

