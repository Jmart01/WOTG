#pragma once
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "ShintoAbilitySystemComp.h"
#include "CharacterBase.generated.h"
UCLASS()
class SHINTO_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ACharacterBase();
	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void BP_HealthUpdated(float newValue, float maxVaue);

	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void BP_Death();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//TSubclassOf<class UMainInGameUI> InGameUIClass;


	//UFUNCTION()
		//void SpawnInGameUI();

	//Components that will be attached to the character base
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* PlayerEye;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UShintoAbilitySystemComp* AbilitySystemComp;

	UPROPERTY()
	class USetActorAttributes* Attributes;


	//functions that deal with movement
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float amount);
	void MoveRight(float amount);
	void Turn(float amount);
	void LookUp(float amount);

	//functions that give the player attributes and abilities
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	virtual void GiveAbilities();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
		TArray<TSubclassOf<class UGameplayAbilityBase>> DefaultAbilities;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void HealthUpdated(const FOnAttributeChangeData& attributeData);
};
