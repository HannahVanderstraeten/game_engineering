#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Vector2f ballVelocity;
bool isPlayer1Serving = false;
int player1Score = 0;
int player2Score = 0;

Font font;
Text text;
const float initialVelocityX = 100.f;
const float initialVelocityY = 60.f;
const float velocityMultiplier = 1.1f;
const Keyboard::Key controls[4] = {
    Keyboard::A,
    Keyboard::Z,
    Keyboard::Up,
    Keyboard::Down
};
const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;

CircleShape ball;
RectangleShape paddles[2];

void Reset(){
    // Update Score Text
    text.setString(to_string(player1Score) + " - " + to_string(player2Score));
    // Keep Score Text Centered
    text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);
    // reset paddle position
    paddles[0].setPosition(Vector2f(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f));
    paddles[1].setPosition(Vector2f(gameWidth - (paddleOffsetWall + paddleSize.x) / 2.f, gameHeight / 2.f));
    // reset Ball Position
    ball.setPosition(Vector2f(gameWidth / 2.f, gameHeight / 2.f));

    ballVelocity = { (isPlayer1Serving ? initialVelocityX : -initialVelocityX), initialVelocityY };
}

void Load() {
    // Load font-face from res dir
    font.loadFromFile("fonts/RobotoMono-Medium.ttf");
    // Set text element to use font
    text.setFont(font);
    // set the character size to 24 pixels
    text.setCharacterSize(24);
    // Set size and origin of paddles
    for (auto& p : paddles) {
        p.setSize(paddleSize);
        p.setOrigin(paddleSize / 2.f);
    }
    // Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius, ballRadius); //Should be half the ball width and height

    Reset();

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

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    // handle paddle movement
    float direction = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
    paddles[0].move(Vector2f(0.f, direction * paddleSpeed * dt));

    // Clamp paddle 1 within screen bounds
    Vector2f paddle1Pos = paddles[0].getPosition();
    if (paddle1Pos.y - paddleSize.y / 2 < 0) {
        paddles[0].setPosition(paddle1Pos.x, paddleSize.y / 2);
    }
    else if (paddle1Pos.y + paddleSize.y / 2 > gameHeight) {
        paddles[0].setPosition(paddle1Pos.x, gameHeight - paddleSize.y / 2);
    }

    float direction2 = 0.0f;
    if (Keyboard::isKeyPressed(controls[2])) { // Player 2 up
        direction2 -= 1.0f;
    }
    if (Keyboard::isKeyPressed(controls[3])) { // Player 2 down
        direction2 += 1.0f;
    }
    paddles[1].move(Vector2f(0.f, direction2 * paddleSpeed * dt));

    // Clamp paddle 2 within screen bounds
    Vector2f paddle2Pos = paddles[1].getPosition();
    if (paddle2Pos.y - paddleSize.y / 2 < 0) {
        paddles[1].setPosition(paddle2Pos.x, paddleSize.y / 2);
    }
    else if (paddle2Pos.y + paddleSize.y / 2 > gameHeight) {
        paddles[1].setPosition(paddle2Pos.x, gameHeight - paddleSize.y / 2);
    }

    ball.move(ballVelocity * dt);

    // check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > gameHeight) { //bottom wall
        // bottom wall
        ballVelocity.x *= velocityMultiplier;
        ballVelocity.y *= -velocityMultiplier;
        ball.move(Vector2f(0.f, -10.f));
    }
    else if (by < 0) { //top wall
        // top wall
        ballVelocity.x *= velocityMultiplier;
        ballVelocity.y *= -velocityMultiplier;
        ball.move(Vector2f(0.f, 10.f));
    }
    else if (bx > gameWidth) {
        // right wall
        Reset();
    }
    else if (bx < 0) {
        // left wall
        Reset();
    }

    else if (
        //ball is inline or behind paddle AND
        bx < paddleSize.x + paddleOffsetWall &&
        //ball is below top edge of paddle AND
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        //ball is above bottom edge of paddle
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
    {
        //bounce off left paddle
        ballVelocity.x *= -velocityMultiplier;
        ballVelocity.y *= velocityMultiplier;
        ball.move(Vector2f(10.f, 0.f));
    }
    else if (
        bx + ballRadius > gameWidth - paddleSize.x - paddleOffsetWall && // Ball near/behind paddle
        by > paddles[1].getPosition().y - paddleSize.y / 2 && // Ball below top of paddle
        by < paddles[1].getPosition().y + paddleSize.y / 2)  {
        // bounce off right paddle
        ballVelocity.x *= -velocityMultiplier;
        ballVelocity.y *= velocityMultiplier;
        ball.move(Vector2f(-10.f, 0.f));
    }

    // Check if ball goes off screen (left or right)
    if (bx > gameWidth) {
        player1Score++;
        isPlayer1Serving = false;
        Reset();
    }
    else if (bx < 0) {
        player2Score++;
        isPlayer1Serving = true;
        Reset();
    }
}

void Render(RenderWindow& window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
    window.draw(text);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();
    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}