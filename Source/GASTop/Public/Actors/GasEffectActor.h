// Belong to kosar 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GasEffectActor.generated.h"

UCLASS()
class GASTOP_API AGasEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGasEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	virtual void OnBeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
