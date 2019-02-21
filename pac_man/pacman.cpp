#include "pacman.h"
#include "cmp_player_movement.h"
#include "cmp_ghost_movement.h"
#include "cmp_ghost_ai.h"
#define GHOSTS_COUNT 4

using namespace sf;
using namespace std;

vector<shared_ptr<Entity>> ghosts;
shared_ptr<Entity> player;

MenuScene::MenuScene()
{
}

void MenuScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	_font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(_font);
	text.setCharacterSize(24);
	text.setString("Almost Pacman");
	text.setPosition((800 * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
}

void GameScene::respawn()
{
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(150.f);

	auto ghost_spawns = ls::findTiles(ls::ENEMY);
	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		ghosts[i]->setPosition(ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
		ghosts[i]->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.0f);
	}
}

void GameScene::update(double dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}

	for (auto g : ghosts) {
		if (length(player->getPosition() - g->getPosition()) < 25.0f)
			respawn();
	}

	Scene::update(dt);
}

void GameScene::render() {
	ls::render(Renderer::getWindow());
	Scene::render();
}

void GameScene::load() {

	ls::loadLevelFile("assets/levels/pacman.txt", 25.0f);

	{
		auto pl = make_shared<Entity>();

		auto s = pl->addComponent<ShapeComponent>();
		pl->addComponent<PlayerMovementComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		_ents.list.push_back(pl);
		player = pl;
	}

	const sf::Color ghost_cols[]{ { 208, 62, 25 },    // red Blinky
	{ 219, 133, 28 },   // orange Clyde
	{ 70, 191, 238 },   // cyan Inky
	{ 234, 130, 229 } }; // pink Pinky


	for (int i = 0; i < GHOSTS_COUNT; ++i) {
		auto ghost = make_shared<Entity>();
		auto s = ghost->addComponent<ShapeComponent>();
		ghost->addComponent<GhostAIComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(ghost_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));

		_ents.list.push_back(ghost);
		ghosts.push_back(ghost);
	}

	respawn();
}