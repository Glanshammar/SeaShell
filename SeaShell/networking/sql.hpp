#pragma once

#include "../global.hpp"
#include <sqlite3.h>
#include "../files/filesystem.hpp"

void CreateSettingsDB();
void LoadSettingsDB();
string SettingValue(const string& settingName);