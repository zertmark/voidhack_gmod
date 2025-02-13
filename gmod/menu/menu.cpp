#include "menu.hpp"

#include "content.hpp"

#include "../input.hpp"
#include "../hooks.hpp"

#include <Windows.h>

using namespace menu;

enum class EMenuState {
	Closed,
	Opened
};

struct MenuContext {
	EMenuState state = EMenuState::Closed;
	float fadeAnimation = 0.f;
};

inline auto& GetMenuContext() {
	static MenuContext context;
	return context;
}

bool menu::MenuOpen() {
	return GetMenuContext().state == EMenuState::Opened || GetMenuContext().fadeAnimation > 0.f;
}

static bool StyleSetuped = false;

void menu::render_menu() {
	using namespace ImGui;

	GetMenuContext().fadeAnimation = GetMenuContext().state == EMenuState::Opened ? 
		ImMin(GetMenuContext().fadeAnimation + GetIO().DeltaTime * 2.f, 1.f) : ImMax(GetMenuContext().fadeAnimation - GetIO().DeltaTime * 2.f, 0.f);

	if (menu::MenuOpen()) {
		if (interfaces::surface->is_cursor_visible() && !ImGui::GetIO().MouseDrawCursor) {
			GetIO().MouseDrawCursor = true;
		}
		PushStyleVar(ImGuiStyleVar_Alpha, GetMenuContext().fadeAnimation);

		PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.06f, 0.06f, 0.06f, 0.4f));
		PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
		PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
		PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, { 5, 5 });

		SetNextWindowSize(GetIO().DisplaySize);
		SetNextWindowPos({ 0, 0 });
		Begin("##TABS", (bool*)0, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDecoration
				| ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);

		for (auto& i : Tabs()) {
			TabSelector(i.name.c_str(), &i.state);
		}

		End();
		PopStyleColor();
		PopStyleVar(4);

		for (auto& i : Tabs()) {
			if (i.state || i.animationState) {
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImMin(i.animationState, GetMenuContext().fadeAnimation));
				i.drawFunction();
				ImGui::PopStyleVar();
			}

			i.animationState = i.state ? ImMin(i.animationState + GetIO().DeltaTime * 2.f, 1.f) : ImMax(i.animationState - GetIO().DeltaTime * 2.f, 0.f);
		}

	} else if (GetIO().MouseDrawCursor) {
		GetIO().MouseDrawCursor = false;
	}
}

bool LockCursorHandler() {
	return menu::MenuOpen();
}

void menu::InitializeMenu() {
	settings::CreateVariable<int>("OpenMenuKey", VK_INSERT);

	hooks::add_listener(hooks::e_hook_type::lock_cursor, LockCursorHandler);
	input::add_handler({"MenuOpen", settings::GetVariablePointer<int>("OpenMenuKey"), [&](input::EKeyState state) {
		if (state == input::EKeyState::Released)
			GetMenuContext().state = GetMenuContext().state == EMenuState::Closed ? EMenuState::Opened : EMenuState::Closed;
		}}
	);
}

void menu::AddElementToCategory(EMenuCategory category, std::shared_ptr<MenuElement> element) {
	for (auto& i : Tabs()) {
		if (i.tabContent.tabID == category) {
			i.tabContent.elements.emplace_back(element);
			std::sort(i.tabContent.elements.begin(), i.tabContent.elements.end(), [](decltype(i.tabContent.elements)::value_type& v1,
				decltype(i.tabContent.elements)::value_type& v2) { return v1->GetId() < v2->GetId(); });
		}
	}
}

decltype(MenuTabContent::elements)& menu::GetElementsForCategory(EMenuCategory category) {
	for (auto& i : Tabs()) {
		if (i.tabContent.tabID == category) {
			return i.tabContent.elements;
		}
	}
}
