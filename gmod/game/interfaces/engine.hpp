#pragma once

#include "interface_define.hpp"

#include "../math/math.hpp"

#include <d3d9.h>

using button_code_t = int;
using color32_s = float;

#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1
#define MAX_FLOWS		2		// in & out

class i_net_channel_info {
public:
	virtual void nop0() = 0;
	virtual const char* get_ip_address() = 0;
	virtual void nop2() = 0;
	virtual void nop3() = 0;
	virtual void nop4() = 0;
	virtual void nop5() = 0;
	virtual void nop6() = 0;
	virtual void nop7() = 0;
	virtual void nop8() = 0;
	virtual float get_latency(int a2) = 0;
	virtual float get_avg_latency(int a2) = 0;
};

class i_material;
class c_audio_source;
class i_material_system;

struct model_t;
struct text_message_t;

typedef struct player_info_s {
	char name[128];
	int userID; // local server user ID, unique while server is running <- THIS IS NOT STEAMID
	char guid[33]; // that is Steamid
	unsigned int friendsid;
	char friendsname[128];
	bool fakeplayer; // true, if player is a bot controlled by game.dll
	bool ishltv;
	unsigned int customfiles[4]; // custom files CRC for this player
	unsigned char filesdownloaded; // this counter increases each time the server downloaded a new file
} player_info_t;

class c_engine_client {
public:
	virtual int get_interesting_surfaces(model_t* model, float* vector_center, const float radius, bool only_visible, void* infos, int max_infos) = 0;
	virtual c_vector* get_light_for_point(const float* pos, int clamp) = 0;
	virtual void* trace_line_material_and_lighting(c_vector& start, c_vector& end, c_vector& defuse_light, c_vector& base_color) = 0;
	virtual const char* parse_file(const char* data, char* token, size_t max_size) = 0;
	virtual int copy_file(const char* name, char* token) = 0;
	virtual void get_screen_size(int& x, int& y) = 0;
	virtual void server_cmd() = 0;
	virtual void client_cmd() = 0;
	virtual void get_player_info(int ent_id, player_info_t* storage) = 0;
	virtual int get_player_for_user_id(int user_id) = 0;
	virtual text_message_t* get_text_message(const char* name) = 0; //10
	virtual bool console_is_visible() = 0;
	virtual int get_local_player() = 0;
	virtual model_t* load_model(const char* name, bool is_prop = false) = 0;
	virtual float get_time_stamp_from_start() = 0;
	virtual float get_last_time_stamp() = 0;
	virtual void* get_sentence(const char* name) = 0;
	virtual float get_sentence_len(c_audio_source* source) = 0;
	virtual bool is_streaming(c_audio_source* source) = 0;
	virtual void get_view_angles(c_vector& in) = 0;
	virtual void set_view_angles(c_vector& new_ang) = 0; //20
	virtual int get_max_clients(void) = 0;
	virtual void key_lookup_binding() = 0;
	virtual void key_binding_for_key() = 0;
	virtual void start_key_trap_mode() = 0;
	virtual void check_done_key_trapping() = 0;
	virtual bool is_in_game() = 0;
	virtual bool is_connected() = 0;
	virtual bool is_drawing_loading_image() = 0;
	virtual void con_print_f(int pos, const char* fmt, ...) = 0;
	virtual void con_print_f(const struct con_nprint_s* info, const char* fmt, ...) = 0; //30
	virtual bool is_box_visible(c_vector& dst, c_vector& src) = 0;
	virtual void is_box_in_view_cluster() = 0;
	virtual void cull_box() = 0;
	virtual void sound_extra_update() = 0;
	virtual const char* get_game_directory() = 0;
	virtual const D3DMATRIX& get_world_to_screen_matrix() = 0;
	virtual const D3DMATRIX& get_world_to_view_matrix() = 0;
	virtual int game_lump_version(int idx) = 0;
	virtual int game_lump_size(int idx) = 0;
	virtual int load_game_lump(int id, void* buffer, int size) = 0; //40
	virtual int level_leaf_count() = 0;
	virtual void* get_bsp_tree_query() = 0;
	virtual void linear_to_gamma(float* linear, float* gamma) = 0;
	virtual float light_style_value(int style) = 0;
	virtual void compute_dynamic_lighting(c_vector&, c_vector&, c_vector&) = 0;
	virtual void get_ambient_light_color(c_vector& color) = 0;
	virtual int get_dx_support_level() = 0;
	virtual bool support_hdr() = 0;
	virtual void mat_stub(i_material_system& matsys) = 0;
	virtual void get_chapter_name(char* buf, int max_len) = 0; //50
	virtual const char* get_level_name() = 0;
	virtual int get_level_version() = 0;
	virtual struct i_voice_tweak_s* get_voice_tweak_api() = 0;
	virtual void engine_stats_begin_frame() = 0;
	virtual void engine_stats_end_frame() = 0;
	virtual void fire_events() = 0; //FIXME
	virtual void get_leaves_area(int* ptr_leaves, int num_leaves) = 0;
	virtual void does_box_touch_area_frustum(c_vector& mins, c_vector& maxs, int area) = 0;
	virtual void set_audio_state(void* state) = 0;
	virtual void sentence_group_pick() = 0; //60
	virtual void sentence_group_pick_sequential() = 0;
	virtual void sentence_index_from_name() = 0;
	virtual void sentence_name_from_index() = 0;
	virtual void sentence_group_index_from_name() = 0;
	virtual void sentence_group_name_from_index() = 0;
	virtual void sentence_length() = 0;
	virtual void compute_lighting() = 0;
	virtual void activate_occluder() = 0;
	virtual bool is_occluded() = 0;
	virtual void* save_alloc_memory(int num, int size) = 0; //70
	virtual void* save_free_memory() = 0;
	virtual i_net_channel_info* get_net_channel_info() = 0;
	virtual void debug_draw_phys_collide() = 0; //FIXME
	virtual void check_point(const char* name) = 0;
	virtual void draw_portals() = 0;
	virtual bool is_playing_demo() = 0;
	virtual bool is_recording_demo() = 0;
	virtual bool is_playing_time_demo() = 0;
	virtual float get_demo_recording_tick() = 0;
	virtual float get_demo_playback_tick() = 0; //80
	virtual float get_demo_playback_start_tick() = 0;
	virtual float get_demo_playback_time_scale() = 0;
	virtual float get_demo_playback_total_ticks() = 0;
	virtual bool is_paused() = 0;
	virtual float get_time_scale() = 0;
	virtual bool is_taking_screenshot() = 0;
	virtual bool is_hltv() = 0;
	virtual bool is_level_main_menu_background() = 0;
	virtual void get_video_modes() = 0;
	virtual void set_occlusion_parameters() = 0; //90
	virtual void  get_ui_language() = 0;
	virtual bool is_skybox_visible_from_point() = 0;
	virtual const char* get_map_entities_string() = 0;
	virtual bool is_in_edit_mode(void) = 0;
	virtual float get_screen_aspect_ratio() = 0;
	virtual bool removed_steam_refresh_login(const char* password, bool isSecure) = 0;
	virtual bool removed_steam_process_call(bool& finished) = 0;
	virtual unsigned int get_engine_build_number() = 0;
	virtual const char* get_product_version_string() = 0;
	virtual void grab_pre_color_corrected_frame(int x, int y, int width, int height) = 0; //100
	[[nodiscard]] virtual bool is_hammer_running() const = 0;
	virtual void execute_client_cmd(const char* cmd) = 0;
};

INITIALIZE_INTERFACE(engine, c_engine_client, memory::engine_module, "VEngineClient015");