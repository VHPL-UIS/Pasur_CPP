#include "MenuScene.h"
#include "GameScene.h"

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
		"green_button.png",
		"green_button.png",
		CC_CALLBACK_1(MenuScene::menu1vsCpuCallback, this));

	if (menu1vsCpuItem == nullptr ||
		menu1vsCpuItem->getContentSize().width <= 0 ||
		menu1vsCpuItem->getContentSize().height <= 0)
	{
		problemLoading("'green_button.png'");
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

	auto gameTitle = Label::createWithTTF("Pasur", "fonts/Marker Felt.ttf", 24);
	gameTitle->setTextColor(Color4B::WHITE);
	if (gameTitle == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		gameTitle->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - gameTitle->getContentSize().height));
		this->addChild(gameTitle, 1);
	}

	/*auto sprite = Sprite::create("HelloWorld.png");
	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x,
			visibleSize.height / 2 + origin.y));
		this->addChild(sprite, 0);
	}*/

	return true;
}


void MenuScene::menu1vsCpuCallback(Ref* pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}