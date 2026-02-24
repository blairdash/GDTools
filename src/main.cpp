#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <Geode/modify/MenuLayer.hpp>

class ToolsLayer : public CCLayer {
public:
	static ToolsLayer* create() {
		auto ret = new ToolsLayer();
		if (ret->init()) {
			ret->autorelease();
			return ret;
		}
		delete ret;
		return nullptr;
	}

	bool init() override {
		if (!CCLayer::init())
			return false;

		setKeypadEnabled(true);

		auto bg = CCLayerColor::create({0, 0, 0, 120});
		this->addChild(bg);

		auto menu = CCMenu::create();

		auto title = CCLabelBMFont::create("Tools", "bigFont.fnt");
		title->setPosition({160, 240});
		this->addChild(title);

		auto toolBtn1 = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("GDDL"),
			this,
			menu_selector(ToolsLayer::onGDDL)
		);
		toolBtn1->setPosition({160, 180});
		menu->addChild(toolBtn1);

		auto toolBtn2 = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("AREDL"),
			this,
			menu_selector(ToolsLayer::onAREDL)
		);
		toolBtn2->setPosition({160, 120});
		menu->addChild(toolBtn2);

		auto closeBtn = CCMenuItemSpriteExtra::create(
			ButtonSprite::create("Close"),
			this,
			menu_selector(ToolsLayer::onClose)
		);
		closeBtn->setPosition({160, 60});
		menu->addChild(closeBtn);

		menu->setPosition({0, 0});
		this->addChild(menu);

		return true;
	}

	void onClose(CCObject*) {
		this->removeFromParent();
	}

	void onGDDL(CCObject*) {
		CCApplication::sharedApplication()->openURL("https://gdladder.com");
	}

	void onAREDL(CCObject*) {
		CCApplication::sharedApplication()->openURL("https://aredl.net");
	}

	void keyBackClicked() override {
		onClose(nullptr);
	}
};

class $modify(HookedMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init())
			return false;

		auto spr = ButtonSprite::create("Tools");
		auto menu = CCMenu::create();
		
		auto btn = CCMenuItemSpriteExtra::create(
			spr,
			this,
			menu_selector(HookedMenuLayer::onToolsButton)
		);
		menu->addChild(btn);
		menu->setPosition({100, 100});
		this->addChild(menu);

		return true;
	}

	void onToolsButton(CCObject*) {
		auto toolsLayer = ToolsLayer::create();
		CCScene::get()->addChild(toolsLayer, 1000);
	}
};