#include "Geode/binding/LevelTools.hpp"
#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <utility>

#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/LevelTools.hpp>

namespace eclipse::hacks::Creator {

    class LevelEdit : public hack::Hack {
        void init() override {
            auto tab = gui::MenuTab::find("Creator");
            tab->addToggle("Level Edit", "creator.leveledit")
                ->handleKeybinds()
                ->setDescription("Allows you to access the level editor from the pause menu in any level.");
        }

        [[nodiscard]] const char* getId() const override { return "Level Edit"; }
    };

    REGISTER_HACK(LevelEdit)

    class $modify(PauseLayer) {
        static void onModify(auto& self) {
            SAFE_PRIORITY("PauseLayer::customSetup");
            SAFE_PRIORITY("PauseLayer::onEdit");
        }

        void customSetup() override {
            auto level = PlayLayer::get()->m_level;
            auto levelType = level->m_levelType;

            if (config::get<bool>("creator.leveledit", false))
                level->m_levelType = GJLevelType::Editor;

            PauseLayer::customSetup();
            level->m_levelType = levelType;
        }

        void onEdit(cocos2d::CCObject* sender) {
            auto level = PlayLayer::get()->m_level;
            auto levelType = level->m_levelType;

            if (config::get<bool>("creator.leveledit", false))
                level->m_levelType = GJLevelType::Editor;

            PauseLayer::onEdit(sender);
            level->m_levelType = levelType;
        }
    };

// due to some mysterious reason, this will crash in Debug mode
#ifdef NDEBUG
    class $modify(LevelTools) {
        static void onModify(auto& self) {
            SAFE_PRIORITY("LevelTools::verifyLevelIntegrity");
        }

        static bool verifyLevelIntegrity(gd::string levelString, int levelID) {
            if (LevelTools::verifyLevelIntegrity(std::move(levelString), levelID))
                return true;

            return config::get<bool>("creator.leveledit", false);
        }
    };
#endif
}