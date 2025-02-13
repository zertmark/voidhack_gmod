#pragma once

#include "interface_define.hpp"

class i_panel {
public:
	/*0*/	virtual void* destr() = 0;
	/*1*/	virtual void* init(unsigned int, void*) = 0;
	/*2*/	virtual void* set_pos(unsigned int, int, int) = 0;
	/*3*/	virtual void* get_pos(unsigned int, int&, int&) = 0;
	/*4*/	virtual void* set_size(unsigned int, int, int) = 0;
	/*5*/	virtual void* get_size(unsigned int, int&, int&) = 0;
	/*6*/	virtual void* set_minimum_size(unsigned int, int, int) = 0;
	/*7*/	virtual void* get_minimum_size(unsigned int, int&, int&) = 0;
	/*8*/	virtual void* set_z_pos(unsigned int, int) = 0;
	/*9*/	virtual void* get_z_pos(unsigned int) = 0;
	/*10*/	virtual void* get_abs_pos(unsigned int, int&, int&) = 0;
	/*11*/	virtual void* get_clip_rect(unsigned int, int&, int&, int&, int&) = 0;
	/*12*/	virtual void* set_inset(unsigned int, int, int, int, int) = 0;
	/*13*/	virtual void* get_inset(unsigned int, int&, int&, int&, int&) = 0;
	/*14*/	virtual void* set_visible(unsigned int, bool) = 0;
	/*15*/	virtual void* is_visible(unsigned int) = 0;
	/*16*/	virtual void* set_parent(unsigned int, unsigned int) = 0;
	/*17*/	virtual void* get_child_count(unsigned int) = 0;
	/*18*/	virtual void* get_child(unsigned int, int) = 0;
	/*19*/	virtual void* get_children(unsigned int) = 0;
	/*20*/	virtual void* get_parent(unsigned int) = 0;
	/*21*/	virtual void* move_to_front(unsigned int) = 0;
	/*22*/	virtual void* move_to_back(unsigned int) = 0;
	/*23*/	virtual void* has_parent(unsigned int, unsigned int) = 0;
	/*24*/	virtual void* is_popup(unsigned int) = 0;
	/*25*/	virtual void* set_popup(unsigned int, bool) = 0;
	/*26*/	virtual void* is_fully_visible(unsigned int) = 0;
	/*27*/	virtual void* get_scheme(unsigned int) = 0;
	/*28*/	virtual void* is_proportional(unsigned int) = 0;
	/*29*/	virtual void* is_auto_delete_set(unsigned int) = 0;
	/*30*/	virtual void* delete_panel(unsigned int) = 0;
	/*31*/	virtual void* set_key_board_input_enabled(i_panel* panel, bool) = 0;
	/*32*/	virtual void* set_mouse_input_enabled(i_panel* panel, bool) = 0;
	/*33*/	virtual bool is_key_board_input_enabled(i_panel* panel) = 0;
	/*34*/	virtual void* is_mouse_input_enabled(unsigned int) = 0;
	/*35*/	virtual void* solve(unsigned int) = 0;
	/*36*/	virtual const char* get_name(void*) = 0;
	/*37*/	virtual const char* get_class_name(unsigned int) = 0;
	/*38*/	virtual void* send_message(unsigned int, void*, unsigned int) = 0;
	/*39*/	virtual void* think(unsigned int) = 0;
	/*40*/	virtual void* perform_apply_scheme_settings(unsigned int) = 0;
	/*41*/	virtual void* paint_traverse(unsigned int, bool, bool) = 0;
	/*42*/	virtual void* repaint(unsigned int) = 0;
	/*43*/	virtual void* is_within_traverse(unsigned int, int, int, bool) = 0;
	/*44*/	virtual void* on_child_added(unsigned int, unsigned int) = 0;
	/*45*/	virtual void* on_size_changed(unsigned int, int, int) = 0;
	/*46*/	virtual void* internal_focus_changed(unsigned int, bool) = 0;
	/*47*/	virtual void* request_info(unsigned int, void*) = 0;
	/*48*/	virtual void* request_focus(unsigned int, int) = 0;
	/*49*/	virtual void* request_focus_prev(unsigned int, unsigned int) = 0;
	/*50*/	virtual void* request_focus_next(unsigned int, unsigned int) = 0;
	/*51*/	virtual void* get_current_key_focus(unsigned int) = 0;
	/*52*/	virtual void* get_tab_position(unsigned int) = 0;
	/*53*/	virtual void* plat(unsigned int) = 0;
	/*54*/	virtual void* set_plat(unsigned int, void*) = 0;
	/*55*/	virtual void* get_panel(unsigned int, char const*) = 0;
	/*56*/	virtual void* is_enabled(unsigned int) = 0;
	/*57*/	virtual void* set_enabled(unsigned int, bool) = 0;
	/*58*/	virtual void* is_topmost_popup(unsigned int) = 0;
	/*59*/	virtual void* set_topmost_popup(unsigned int, bool) = 0;
	/*60*/	virtual void* set_sibling_pin(unsigned int, unsigned int, unsigned char, unsigned char) = 0;
	/*61*/	virtual void* popup_wants_front(unsigned int) = 0;
	/*62*/	virtual void* set_popup_wants_front(unsigned int, bool) = 0;
	/*63*/	virtual void* client(unsigned int) = 0;
	/*64*/	virtual void* get_module_name(unsigned int) = 0;
};

INITIALIZE_INTERFACE(panel, i_panel, memory::vgui_module, "VGUI_Panel009")