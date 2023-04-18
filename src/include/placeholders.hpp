#pragma once

#include <unordered_map>

#include <co/fastring.h>

struct placeholders {
    std::unordered_map<fastring, fastring> holders {
            {"auth_player_name", ""},
            {"version_name", ""},
            {"game_directory", ""},
            {"assets_root", ""},
            {"assets_index_name", ""},
            {"auth_uuid", ""},
            {"auth_access_token", ""},
            {"clientid", ""},
            {"auth_xuid", ""},
            {"user_type", ""},
            {"version_type", ""},
            {"natives_directory",""},
            {"launcher_name", ""},
            {"launcher_version", ""},
            {"classpath", ""},
            {"path", ""},
            {"classpath_separator", ""},
            {"library_directory", ""},
            {"javaw_app_path", ""}
    };
};