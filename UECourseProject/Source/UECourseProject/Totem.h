// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Totem.generated.h"

UCLASS()
class UECOURSEPROJECT_API ATotem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATotem();
	UPROPERTY(EditAnywhere)
		TArray<UStaticMesh*> TotemPieces;
	UPROPERTY(EditDefaultsOnly)
		TArray<UStaticMesh*> RandomTotemPieces;
	UPROPERTY(EditAnywhere)
		bool IsRandom;
	UPROPERTY(EditAnywhere)
		bool IsReversed;
	UPROPERTY(EditAnywhere)
		int RandomPiecesAMount;
	UPROPERTY(EditAnywhere)
		bool IsColored;
	UPROPERTY(EditAnywhere)
		UMaterial* DefaultTotemMaterial;
	UPROPERTY(EditAnywhere)
		UMaterialInstance* InstancedTotemMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SpawnTotemPieces(TArray<UStaticMesh*> Pieces);
	virtual TArray<UStaticMesh*> CreateRandomPieces();
	virtual void SetPieceMaterial(UStaticMeshComponent* Piece);
	virtual void DestroyTotemPieces();
	virtual void SetRandomColor(UMaterialInstanceDynamic* TargetMatInstance);
	virtual float SpawnLoopedPiece(UStaticMesh* PieceToSpawn, float TotemHeight);
};
