#include <SFML/Graphics.hpp>
#include "ecm.h"
#include "game.h"
#include "LevelSystem.h"
#include "system_renderer.h"
#include "pacman.h"


using namespace sf;
using namespace std;




void Load() {
    // Load Scene-Local Assets
    gameScene.reset(new GameScene());
    menuScene.reset(new MenuScene());
    gameScene->load();
    menuScene->load();
    // Start at main menu
    activeScene = menuScene;
}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    // check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }

    activeScene->update(dt);


    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

}

void Render(RenderWindow& window) {
    activeScene->render();
    // flush to screen
    Renderer::render();
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Pacman");
    Renderer::initialise(window);
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}