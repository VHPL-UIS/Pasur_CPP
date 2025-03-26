#include "MenuScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menu1vsCpuItem = MenuItemImage::create(
		"buttons\green_button.png",
		"buttons\green_button.png",
		CC_CALLBACK_1(MenuScene::menu1vsCpuCallback, this));

	if (menu1vsCpuItem == nullptr ||
		menu1vsCpuItem->getContentSize().width <= 0 ||
		menu1vsCpuItem->getContentSize().height <= 0)
	{
		problemLoading("'buttons\green_button.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + visibleSize.height / 2;
		menu1vsCpuItem->setPosition(Vec2(x, y));
	}

	auto menu = Menu::create(menu1vsCpuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}


void MenuScene::menu1vsCpuCallback(Ref* pSender)
{
	//GameManager::getInstance().changeState(std::make_unique<GameState1vsCpu>());
}