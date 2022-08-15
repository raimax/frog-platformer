#pragma once
#include "Scene.h"
#include <any>
#include <unordered_map>

enum VideoSettingsMenuItem {
	FULLSCREEN,
	WINDOW_SIZE,
	MAX_FPS,
	APPLY_VIDEO_SETTINGS,
	BACK_TO_SETTINGS
};

typedef struct Resolution {
	Resolution(std::string name, int width, int height) {
		this->name = name;
		this->width = width;
		this->height = height;
	}
	std::string name;
	int width;
	int height;
} Resolution;

class VideoSettingsScene : public Scene
{
private:
	std::vector<Resolution> windowSizes = {
		Resolution("720x480", 720, 480), 
		Resolution("960x540", 960, 540), 
		Resolution("1280x720", 1280, 720), 
		Resolution("1366x768", 1366, 768),
		Resolution("1600x900", 1600, 900),
		Resolution("1920x1080", 1920, 1080),
		Resolution("2560x1440", 2560, 1440),
		Resolution("3200x1800", 3200, 1800),
		Resolution("3840x2160", 3840, 2160),
	};
	std::vector<std::string> fullscreenOptions = {
		"off", "on", "borderless"
	};
	std::vector<std::string> maxFps = {
		"60", "75", "144", "240", "unlimited"
	};
	std::vector<std::string> menuItems = {
		{"FULLSCREEN"},
		{"WINDOW SIZE"},
		{"MAX FPS"},
		{"APPLY"},
		{"BACK"},
	};
	int selectedMenuItem = 0;
	int selectedWindowSize = 2;
	int selectedFullscreenOption = 0;
	int selectedMaxFps = 0;
	void drawOption(std::string option, int index);
public:
	void drawScene() override;
	void updateScene() override;
};

