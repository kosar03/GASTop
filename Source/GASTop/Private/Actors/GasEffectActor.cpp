// Belong to kosar 


#include "Actors/GasEffectActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/GasAttributeSet.h"


// Sets default values
AGasEffectActor::AGasEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGasEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGasEffectActor::OnBeginOverlapFunc);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AGasEffectActor::OnEndOverlapFunc);


}

void AGasEffectActor::OnBeginOverlapFunc(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if (ASCInterface)
	{
		const UGasAttributeSet* AttributeSet = Cast<UGasAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UGasAttributeSet::StaticClass()));

		UGasAttributeSet* MutableAttributeSet = const_cast<UGasAttributeSet*>(AttributeSet);
		MutableAttributeSet->SetHealth(MutableAttributeSet->GetHealth() + 10.0f);
		Destroy();
	}
}

void AGasEffectActor::OnEndOverlapFunc(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{

}
