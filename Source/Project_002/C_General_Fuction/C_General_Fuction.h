// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "..\Source\Project_002\Super_unit\Super_unit.h"
#include "C_General_Fuction.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_002_API UC_General_Fuction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:

public:
	UFUNCTION(BlueprintPure, Category = "Damage")
		static float KE_health_cal(float KE, int32 range, float distance, int attack_location, int ERA_strengh
			, TArray<int> self_ERA_list, TArray<int> self_Armor_list, float ERA_revise);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static float CE_health_cal(float CE, int attack_location, int ERA_strengh, TArray<int> self_ERA_list
			, TArray<int> self_Armor_list, float self_armor_conversion_coefficient, float ERA_revise);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static float HE_health_cal(float HE, float HE_self_distance, int attack_location, TArray<int> self_Armor_list);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static float KE_ERA_cal(float KE, int ERA_strengh);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static float CE_ERA_cal(float CE, float ERA_strength);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static float HE_ERA_cal(float HE, float ERA_strength, float HE_self_distance);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static float ERA_revise_cal(float ERA_health, float const_ERA_health);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static void vehicle_module_health_cal(TArray<float>& out_vehicle_module_health, TArray<float> vehicle_module_health, int vehicle_module_attacked_enum, float damage);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static int vehicle_attack_location_to_module_attacked_enum(int attack_location, float module_hurt);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static void attacked_cal(TArray<float>& out_vehicle_module_health, float& out_health, float& out_ERA_health, float& out_ERA_revise, bool& is_morale_cal, float health, float ERA_health, float const_ERA_health,
			float KE, float CE, float HE, float HE_self_distance, int ERA_strength, int32 range, int32 distance, int attack_location, TArray<int> self_ERA_list, TArray<float> vehicle_module_health,
			TArray<int> self_Armor_list, float self_armor_conversion_coefficient, float ERA_revise);

	UFUNCTION(BlueprintPure, Category = "Vector")
		static float Vector_distance_cal(FVector a, FVector b);

	UFUNCTION(BlueprintPure, Category = "Morale")
		static int32 morale_to_morale_type(float const_morale, float morale_now);

	UFUNCTION(BlueprintPure, Category = "War_zone")
		static void is_war_zone_caped(bool& is_cap, int& cap_camp, TArray<int>& out, TArray<int> unit_in_war_zone_list);

	UFUNCTION(BlueprintCallable, Category = "War_Zone")
		static void unit_in_out_war_cone(bool& is_cap, int& cap_camp, TArray<int>& out, bool in, int unit_camp, TArray<int> unit_in_war_zone_list);

	UFUNCTION(BlueprintCallable, Category = "War_Zone")
		static void add_score_list_parse(int& out_camp, int& out_add_score, TArray<int> tp_add_list);

	UFUNCTION(BlueprintPure, Category = "Morale")
		static float morale_reflex(float morale_now, float morale_reflex, float const_morale);

	UFUNCTION(BlueprintCallable, Category = "Supply")
		static void weapon_supply_cal(TArray<float>& out_temp_weapon_sup, TArray<int>& out_weapon_sup_result, TArray<float> temp_weapon_sup, TArray<float> weapon_sup_cost);

	UFUNCTION(BlueprintCallable, Category = "Supply")
		static void vehicle_onlyself_supply_cal(bool& is_vehicle_sup_over, float& now_health, float& now_ERA_health, float& now_oil,
			float& now_APS_number, float& now_smoke_number, TArray<float>& out_temp_sup_list_self, float health, float const_health,
			float per_health_sup_time, float ERA_health, float const_ERA_health, float per_ERA_health_sup_time, float oil, float const_oil,
			float per_10_oil_sup_time, float APS_num, float const_APS_num, float per_APS_sup_time, float smoke_num, float const_smoke_num, float per_smoke_sup_time,
			TArray<float> temp_sup_list_self);

	UFUNCTION(BlueprintCallable, Category = "Supply")
		static void helo_onlyself_supply_cal(bool& is_helo_sup_over, float& now_health, float& now_oil,
			float& now_hot_bait_number, TArray<float>& out_temp_sup_list_self, float health, float const_health, float per_health_sup_time, float oil, float const_oil,
			float per_10_oil_sup_time, float hot_bait_num, float const_hot_bait_num, float per_hot_bait_sup_time, TArray<float> temp_sup_list_self);

	UFUNCTION(BlueprintCallable, Category = "Supply")
		static void vehicle_general_sup(float& out_property, float& temp_sup_list_increment, bool& is_property_sup_over, float property,
			float const_property, float per_property_sup_time, int sup_multiplier, TArray<float> temp_sup_list_self, int index);

	UFUNCTION(BlueprintPure, Category = "Fire")
		static void Boardwalk_radius_cal(FVector& random_boardwalk, float speed, float boardwalk_radius, int range, float X_multi, float Y_multi, float Z_multi);

	UFUNCTION(BlueprintPure, Category = "CROWS_Control")
		static void high_performance_CROWS_rotate_control(bool& is_over, float& CROWS_rotate, float& CROWS_gun_barrel_rotate, float aiming_z_CROWS, float aiming_x_CROWS_gun_barrel,
			float z_CROWS, float x_CROWS_gun_barrel);

	UFUNCTION(BlueprintPure, Category = "CROWS_Control")
		static float high_performance_CROWS_rotate_cal_function(float aiming_rotation, float now_rotation);

	UFUNCTION(BlueprintPure, Category = "Fire")
		static int set_now_salvo(bool can_fire_all, int const_bullet_in_magazine, int now_salvo, int salvo);

	UFUNCTION(BlueprintPure, Category = "camp")
		static bool is_in_same_camp(int self_camp, int other_camp);

	UFUNCTION(BlueprintPure, Category = "get_on_vehicle")
		static bool can_vehicle_load_soldier(int vehicle_type);

	UFUNCTION(BlueprintPure, Category = "get_on_vehicle")
		static bool can_get_on(int vehicle_type, int self_camp, int other_camp);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static void attacked_cal_person(TArray<int>& out_body_armor_list, TArray<float>& out_body_health_list, float& out_health, float health, int enemy_anti_person, int attack_location,
			int enemy_range, int enemy_distance, int body_armor_loss_revise, TArray<int> self_body_armor_list, TArray<float> self_body_health_list, TArray<float> damage_multiplier_list);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static int real_anti_person_cal(int enemy_anti_person, int enemy_range, int enemy_distance);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static void person_armor_cal_and_update(TArray<int>& out_armor_list, int out_health_hurt, int real_anti_person, int attack_location, int body_armor_loss_revise, TArray<int> self_armor_list);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static void person_health_cal_and_update(TArray<float>& out_body_health_list, float& total_health_hurt, float health_hurt, int attack_location, TArray<float> body_health_list,
			TArray<float> damage_multiplier_list);

	UFUNCTION(BlueprintPure, Category = "Bullet_behavior")
		static bool ricochet_static_mesh(FVector bullet_vector, FVector hit_normal, float KE, int anti_person);

	UFUNCTION(BlueprintPure, Category = "Bullet_behavior")
		static bool ricochet_vehicle(FVector bullet_vector, FVector hit_normal, float KE, int hit_armor);

	UFUNCTION(BlueprintPure, Category = "Bullet_behavior")
		static bool ricochet_helo(FVector bullet_vector, FVector hit_normal, float KE, int hit_armor);

	UFUNCTION(BlueprintPure, Category = "Bullet_behavior")
		static bool ricochet_person(FVector bullet_vector, FVector hit_normal, float KE, int anti_person, int hit_body_armor);

	UFUNCTION(BlueprintPure, Category = "Bullet_behavior")
		static bool ricochet_general_cal(float angle, float ricochet_angle);

	UFUNCTION(BlueprintPure, Category = "Abnormal_status_cal")
		static void abnormal_status_cal(FString& out_status_string, TArray<float> vehicle_module_health, TArray<float> const_vehicle_module_health, TArray<FString> vehicle_abnormal_status_rate_list);

	UFUNCTION(BlueprintPure, Category = "Enum_map")
		static FString enum_index_to_fstring(int m);

	UFUNCTION(BlueprintPure, Category = "Enum_map")
		static int enum_index_fstring_to_int(FString str);

	UFUNCTION(BlueprintCallable, Category = "Abnormal_status_cal")
		static void abnormal_status_cal_check(FString& out_status, bool& have_new, FString& new_status, FString now_status,
			TArray<float> vehicle_module_health, TArray<float> const_vehicle_module_health, TArray<FString> vehicle_abnormal_status_rate_list);

	UFUNCTION(BlueprintPure, Category = "Exp_cal")
		static void Exp_cal(float& prograss, int& max_exp, int now_exp, int level);

	UFUNCTION(BlueprintPure, Category = "int_to_string")
		static void large_int_normalize_to_string(FString& out_normalize_string, int input);

	UFUNCTION(BlueprintPure, Category = "sundry")
		static void helo_close_engine_decline_buoyancy(float& out_buoyancy, int in_index);

	UFUNCTION(BlueprintCallable, Category = "FOV")
		static void set_camera_FOV(float& out_FOV, int& aiming_multipiler, float now_FOV, TArray<float> FOV_list, bool is_add);

	UFUNCTION(BlueprintPure, Category = "FOV")
		static void get_now_aiming_multipiler(int& out_multipiler, float now_FOV);

	UFUNCTION(BlueprintPure, Category = "Damage")
		static void attacked_comp_to_location(int& attack_loaction, FString comp_name);

	UFUNCTION(BlueprintPure, Category = "ATGM_check")
		static void is_ATGM_FoF(bool& out_bool, FString ATGM_property);

	UFUNCTION(BlueprintPure, Category = "AI_vehicle")
		static float high_performance_AI_standby_CROWS_rotate(int total_index, int now_index, int stop_duration, float rotate_speed);

	UFUNCTION(BlueprintPure, Category = "IO_initial")
		static void magazine_array_parse(int& out_magazine_number,bool& is_rewrite_bullet_number,int& rewrite_per_magazine_bullet_number,TArray<int> origin_data);

	UFUNCTION(BlueprintPure, Category = "Unit_type")
		static void unit_type_to_unit_status_enum(int& out_status_enum, FString unit_type);

	UFUNCTION(BlueprintCallable, Category = "Turret_Control")
		static void high_performance_turret_rotate_to_degrees(float& out_axis, bool& is_turret_rotate_rdy, FVector enemy_location, FVector my_location, float now_turret_degrees,
			float pre_aim_turret_rotate);

	UFUNCTION(BlueprintPure, Category = "Turret_Control")
		static void high_performance_turret_rotate_only_degrees(float& out_axis, bool& is_rotate_over, float now_turret_rotate, float now_target_rotate);

	UFUNCTION(BlueprintCallable, Category = "Barrel_Control")
		static void high_performance_barrel_rotate_to_degrees(float& out_axis, bool& is_barrel_rotate_rdy, float pre_aim_turret_rotate, float now_barrel_degrees);

	UFUNCTION(BlueprintCallable, Category = "Aim_Control")
		static void auto_advance_cal_after_rotate(float& turret_advance_rotate_z, float& barrel_advance_rotate_y, FVector enemy_location
			, FVector enemy_speed, FVector my_location, float my_pitch, float bullet_speed);

	UFUNCTION(BlueprintPure, Category = "Aim_Control")
		static void time_advance_cal(float& tadv, float distance, FVector enemy_speed, int bullet_speed);

	UFUNCTION(BlueprintPure, Category = "Aim_Control")
		static void barrel_pitch_cal(float& out_pitch, FVector enemy_adv_location, FVector my_location, float my_pitch, float bullet_speed, float TADV);

	UFUNCTION(BlueprintCallable, Category = "Nav_ponit_to_move")
		static void vehicle_nav_ponit_to_move(float& out_forward_move, float& out_right_move, float now_forward_move, float now_right_move,
			FVector next_nav_point, FVector my_location, float my_rotate, float speed_multiplier, float delta_time);

	UFUNCTION(BlueprintPure, Category = "UI_color")
		static void unit_in_map_icon_color_set(FLinearColor& out_Linear_color, int camp, int camp_and_friend_enum);

	UFUNCTION(BlueprintPure, Category = "UI_Map")
		static void worldlocation_to_map_location(FVector2D& out_unit_map_location, FVector unit_location, float map_size_x, float map_size_y, float map_ui_size);

	UFUNCTION(BlueprintCallable, Category = "RTS_Camera")
		static void camera_height_switch_cal(float& out_height_switch, float& out_axis, float axis, float now_height, float lower_limit, float upper_limit, 
			float height_multiplier, float deltatime, float last_axis);

	UFUNCTION(BlueprintCallable, Category = "RTS_Camera")
		static void camera_translation_switch_cal(float& out_translation_switch, float& out_axis, float axis, float now_height, float lower_limit, float upper_limit,
			float translation_multiplier, float deltatime, float last_axis);
};