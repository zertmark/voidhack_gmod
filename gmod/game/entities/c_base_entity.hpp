#pragma once

#include "../misc/netvars.hpp"
#include "../../interfaces.hpp"

#include "i_client_entity.hpp"

#include <map>

#define CHECK_THIS if (!this) return

class c_collidable
{
public:
	virtual void unknown_0() = 0;
	virtual c_vector& mins() = 0;
	virtual c_vector& maxs() = 0;
};

static inline std::map<std::string, std::vector<std::string>> entity_bones_by_class {
	{"head", {"ValveBiped.Bip01_Head", "ValveBiped.Bip01_Neck1"}},
	{"pelvis", {"ValveBiped.Bip01_Pelvis"}},
	{"body", {"ValveBiped.Bip01_Spine", "ValveBiped.Bip01_Spine2",
			"ValveBiped.Bip01_Spine3", "ValveBiped.Bip01_Spine4"}},
	{"arm", {"ValveBiped.Bip01_L_UpperArm", "ValveBiped.Bip01_L_Forearm", "ValveBiped.Bip01_L_Hand"
	         "ValveBiped.Bip01_R_UpperArm", "ValveBiped.Bip01_R_Forearm", "ValveBiped.Bip01_R_Hand"}},
	{"foot", {"ValveBiped.Bip01_L_Thigh", "ValveBiped.Bip01_L_Calf", "ValveBiped.Bip01_L_Foot", "ValveBiped.Bip01_L_Toe0",
			  "ValveBiped.Bip01_R_Thigh", "ValveBiped.Bip01_R_Calf", "ValveBiped.Bip01_R_Foot", "ValveBiped.Bip01_R_Toe0"}}
};

class c_base_player;

class c_base_entity : public i_client_entity
{
public:
	netvar("DT_BaseEntity", "m_vecOrigin", get_origin, c_vector);
	netvar("DT_GMOD_Player", "m_angEyeAngles[0]", get_angles, c_vector);
	netvar("DT_BaseEntity", "m_nModelIndex", get_model_index, int);
	netvar("DT_BaseEntity", "m_iTeamNum", get_team_num, int);
	netvar("DT_BasePlayer", "m_vecViewOffset[0]", get_view_offset, c_vector);
	netvar("DT_BaseEntity", "m_flAnimTime", get_anim_time, float);
	netvar("DT_BaseEntity", "m_flSimulationTime", get_simulation_time, float);
	netvar("DT_BaseEntity", "m_angRotation", get_rotation, c_vector);
	netvar("DT_BaseEntity", "m_hOwnerEntity", get_owner_entity_handle, uintptr_t);
	netvar("DT_BaseEntity", "m_iHealth", get_health, int);
	netvar("DT_BaseEntity", "m_iMaxHealth", get_max_health, int);

	c_vector get_eye_pos() { return this->get_origin() + this->get_view_offset(); }

	c_collidable* get_collidable_ptr() {
		using original_fn = c_collidable * (__thiscall*)(void*);
		return (*(original_fn**)this)[3](this);
	}

	bool is_alive() {
		using original_fn = bool(__fastcall*)(void*);
		return (*(original_fn**)this)[129](this);
	}

	bool is_player() {
		using original_fn = bool(__fastcall*)(void*);
		return (*(original_fn**)this)[130](this);
	}

	//https://imgur.com/bK6cNdu 
	void push_entity() {
		using original_fn = void(__fastcall*)(void*);
		return (*(original_fn**)this)[172](this);
	}

	bool is_use_lua() {
		using fn = bool(__fastcall*)(void*);
		return (*(fn**)this)[170](this);
	}

	//B8 AA 2A 4D 00 C3	client.dll 
	const char* get_lua_script_name() {
		using fn = const char* (__fastcall*)(void*);
		return (*(fn**)this)[183](this);
	}

	c_vector get_bone(int bone) {
		CHECK_THIS{};
		matrix3x4_t bone_matrix[128];
		if (!setup_bones(bone_matrix, 128, 0x00000100, interfaces::engine->get_last_time_stamp()))
			return {};
		auto hitbox = bone_matrix[bone];
		return { hitbox[0][3], hitbox[1][3], hitbox[2][3] };
	}

	inline c_base_player* as_player() const {
		return (c_base_player*)this;
	}

	inline c_base_entity* as_entity() const {
		return (c_base_entity*)this;
	}

	__forceinline bool equal(c_base_entity* other) const {
		return other->get_index() == this->get_index();
	}

	int get_health_procentage() {
		return 100 / get_max_health() * get_health();
	}
};

__forceinline c_base_entity* get_entity_by_index(const int i)
{
	return static_cast<c_base_entity*>(interfaces::entity_list->get_client_entity(i));
}