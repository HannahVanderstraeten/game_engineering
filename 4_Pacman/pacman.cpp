//pacman.cpp
#include "pacman.h"
#include "system_renderer.h"
#include "ecm.h"
#include <SFML/Graphics.hpp>
#include "cmp_sprite.h"
#include "cmp_actor_movement.h"
#include "cmp_enemyai_movement.h"
#include "cmp_player_movement.h"
#include "LevelSystem.h"
#include <iostream>
#define GHOSTS_COUNT 4

std::shared_ptr<Scene> gameScene;     // Definition of gameScene
std::shared_ptr<Scene> menuScene;     // Definition of menuScene
std::shared_ptr<Scene> activeScene;
std::vector<std::shared_ptr<Entity>> ghosts;
std::shared_ptr<Entity> player;


void Scene::render() { 

        _ents.render(Renderer::getWindow()); // Call render with the window reference
    
}

void Scene::update(double dt) {


    for (const auto& entity : _ents.list) {
        if (entity) {
            entity->update(dt);
        }

    }

}


void MenuScene::update(double dt) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        activeScene = gameScene;
    }
    Scene::update(dt);

}

void MenuScene::render() {
	Renderer::queue(&text);
	Scene::render();
}

void MenuScene::load() {
	// Set up the text element
    font.loadFromFile("res/fonts/RobotoMono-Medium.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text.setString("Press Enter to Start");
	text.setPosition(100, 100); // Adjust position as needed
}

void GameScene::render() {
    ls::Render(Renderer::getWindow());
    Renderer::queue(&text);
    Scene::render();
}

void GameScene::load() {
    ls::loadLevelFile("res/levels/pacman.txt", 25.0f);
    // Load the font for text (example)
    font.loadFromFile("res/fonts/RobotoMono-Medium.ttf");
    

    auto pl = std::make_shared<Entity>();
    auto s = pl->addComponent<ShapeComponent>();
    
    s->setShape<sf::CircleShape>(12.f);
    s->getShape().setFillColor(sf::Color::Yellow);
    s->getShape().setOrigin(sf::Vector2f(0.f, 0.f));
    pl->addComponent<PlayerMovementComponent>();
    //pl->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

    _ents.list.push_back(pl);
    player = pl;
    std::cout << "Added player entity!" << std::endl;  // Debug print

    const sf::Color ghost_cols[]{ {208, 62, 25},    // red Blinky
                                 {219, 133, 28},   // orange Clyde
                                 {70, 191, 238},   // cyan Inky
                                 {234, 130, 229} }; // pink Pinky

    for (int i = 0; i < GHOSTS_COUNT; ++i) {
        auto ghost = std::make_shared<Entity>();
        auto s = ghost->addComponent<ShapeComponent>();
        
        s->setShape<sf::CircleShape>(12.f);
        s->getShape().setFillColor(ghost_cols[i % 4]);
        s->getShape().setOrigin(sf::Vector2f(0.f, 0.f));

        ghost->addComponent<EnemyAIMovementComponent>();

        _ents.list.push_back(ghost);
        ghosts.push_back(ghost);
    }

    respawn();

}


void GameScene::update(double dt) {


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        activeScene = menuScene;
    }
    Scene::update(dt);

    for (auto& g : ghosts) {
        if (length(g->getPosition() - player->getPosition()) < 30.0f) {
            respawn();
        }
    }


}

void GameScene::respawn() {
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    player->GetCompatibleComponent<ActorMovementComponent>()[0]
        ->setSpeed(150.f);

    auto ghost_spawns = ls::findTiles(ls::ENEMY);
    for (auto& g : ghosts) {
        g->setPosition(
            ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
        g->GetCompatibleComponent<ActorMovementComponent>()[0]->setSpeed(100.0f);
    }
    
}
