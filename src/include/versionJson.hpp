#pragma once

#include <co/json.h>
#include <co/fastring.h>
#include <co/fs.h>

#include "osInfo.hpp"
#include "placeholders.hpp"

class versionJson {
    json::Json version;
    fastring launchString;
    placeholders phs;

    auto loadJvmArgsPart() -> void {
        launchString += "${javaw_app_path} ";

        json::Json jvmPartJson(version.get("arguments").get("jvm"));

        for (auto const & e : jvmPartJson) {
            if (e.is_object() && e.has_member("value")) {
                json::Json rulesArray(e.get("rules"));

                bool apply {true};

                for (auto const & rule : rulesArray) {
                    if (rule.get("action").as_string() != "allow") {
                        continue;
                    }

                    json::Json osRequirements(rule.get("os"));

                    for (auto it {osRequirements.begin()}; it != osRequirements.end(); ++it) {
                        if (!osInfoType::ref().satisfy(it.key(), it.value().as_string())) {
                            apply = false;

                            break;
                        }
                    }

                    if (!apply) {
                        break;
                    }
                }

                if (apply) {
                    if (e.get("value").is_array()) {
                        for (auto const & eachValue : e.get("value")) {
                            launchString += eachValue.as_string();
                            launchString += ' ';
                        }
                    } else {
                        launchString += e.get("value").as_string();
                        launchString += ' ';
                    }
                }
            } else if (e.is_string()) {
                launchString += e.as_string();
                launchString += ' ';
            }
        }
    }

    auto loadExtraJvmArgsPart() -> void {
        launchString += "-XX:+UnlockExperimentalVMOptions ";
        launchString += "-XX:+UseG1GC ";
        launchString += "-XX:G1NewSizePercent=20 ";
        launchString += "-XX:G1ReservePercent=20 ";
        launchString += "-XX:MaxGCPauseMillis=50 ";
        launchString += "-XX:G1HeapRegionSize=32M ";
    }

    auto loadLogArgsPart() -> void {
        launchString += version.get("logging").get("client").get("argument").as_string();
        launchString += ' ';
    }

    auto loadGameArgsPart() -> void {
        launchString += version.get("mainClass").as_string();
        launchString += ' ';

        json::Json gamePartJson(version.get("arguments").get("game"));

        for (auto const & e : gamePartJson) {
            if (e.is_string()) {
                launchString += e.as_string();
                launchString += ' ';
            }
        }
    }

    auto replaceGameArgsPart() -> void {

    }

    auto replaceLogArgsPart() -> void {

    }

    auto replaceJvmArgsPart() -> void {

    }
public:
    explicit
    versionJson(fastring const & versionJsonFilePath) {
        if (!fs::exists(versionJsonFilePath)) {
            return;
        }

        fs::file versionJsonFile(versionJsonFilePath, 'r');

        if (!versionJsonFile) {
            return;
        }

        version.parse_from(versionJsonFile.read(versionJsonFile.size()));
    }

    auto healthy() const -> bool {
        return !version.is_null();
    }

    auto loadLaunchString() -> void {
        loadJvmArgsPart();
        loadExtraJvmArgsPart();
        loadLogArgsPart();
        loadGameArgsPart();
    }

    auto fixPlaceHolders() -> void {

    }

    auto replaceLaunchString() -> void {

    }
};