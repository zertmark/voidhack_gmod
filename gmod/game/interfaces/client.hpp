#pragma once

#include "interface_define.hpp"
#include "../misc/c_client_class.hpp"

class c_view_setup;

struct rect_t {
	int x, y;
	int width, height;
};

struct vrect_t {
	int				x, y, width, height;
	vrect_t* pnext;
};

enum render_view_info_t {
	RENDERVIEW_UNSPECIFIED = 0,
	RENDERVIEW_DRAWVIEWMODEL = (1 << 0),
	RENDERVIEW_DRAWHUD = (1 << 1),
	RENDERVIEW_SUPPRESSMONITORRENDERING = (1 << 2),
};

enum class e_frame_stage {
	frame_undefined = -1, 
	frame_start = 0, 
	frame_render_start = 5, 
	frame_render_end = 6 
};

class chl_client {
public:
	virtual void init(void) = 0;
	virtual void post_init(void) = 0;
	virtual void shutdown(void) = 0;
	virtual void unk1(void) = 0;
	virtual void reply_post_init(void) = 0;
	virtual void level_init_pre_entity() = 0;
	virtual void level_init_post_entity() = 0;
	virtual void level_shutdown() = 0;
	virtual c_client_class* get_all_classes() = 0;

	bool get_player_view(c_view_setup* setup) {
		using fn = bool(__fastcall*)(void*, c_view_setup* out);
		return (*(fn**)this)[59](this, setup);
	}

	void render_view(const c_view_setup& setup, const int clear_flags, const int what_to_draw) {
		using fn = void(__fastcall*)(void*, const c_view_setup&, int, int);
		return (*reinterpret_cast<fn**>(this))[27](this, setup, clear_flags, what_to_draw);
	}
};

INITIALIZE_INTERFACE(client, chl_client, memory::client_module, "VClient017");