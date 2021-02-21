// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Kismet\KismetArrayLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Super_unit.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PROJECT_002_API ASuper_unit : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		FString unit_ID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		FString unit_type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		FString country;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		FString name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int requisition_cost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int train_type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		float health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int weight_type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int volume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int hide;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int ground_investigation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int helo_investigation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int plane_investigation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int sead_investigation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		float auto_seek_time;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int investigation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		float dynamic_friction_coefficient;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		float cross_country_speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		float cross_road_speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		float amphibious;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int informatization;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		float morale;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		int morale_type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		float morale_reflex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		float noise;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		FVector my_location;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		float tp_distance_for_sort;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		FVector now_speed_vector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Unit_Information")
		bool is_self_dead = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
		int unit_status_enum;//ground_helo_plane

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
		bool is_player_self;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
		bool is_AI_control;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Components")
		int camp_in_game;

public:
	// Sets default values for this pawn's properties
	ASuper_unit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Super_unit")
		void set_tp_distance_for_sort(FVector location);

	UFUNCTION(BlueprintCallable, Category = "Super_unit")
		void set_my_location();

	UFUNCTION(BlueprintPure, Category = "investigation_hide")
		void distance_sort_unit_list(TArray<ASuper_unit*>& out_sorted_array, TArray<ASuper_unit*> unit_list, FVector self_location);

	UFUNCTION(BlueprintPure, Category = "NavMesh")
		FVector get_next_nav_point(ASuper_unit* target_enemy_unit, FVector target_location, bool is_target_unit);
};
