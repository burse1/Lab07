#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
// Create our window and world with gravity 0,1
RenderWindow window(VideoMode(800, 600), "Bounce");
World world(Vector2f(0, 1));
// Create the ball
PhysicsCircle ball;
ball.setCenter(Vector2f(100, 100));
ball.setRadius(20);
world.AddPhysicsBody(ball);
ball.applyImpulse(Vector2f(.1,-.4));

// Create the floor
PhysicsRectangle floor;
floor.setSize(Vector2f(800, 20));
floor.setCenter(Vector2f(400, 590));
floor.setStatic(true);
world.AddPhysicsBody(floor);
int thudCount(0);
floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
cout << "thud " << thudCount << endl;
thudCount++;
};

// Create the roof
PhysicsRectangle roof;
roof.setSize(Vector2f(800, 20));
roof.setCenter(Vector2f(400, 10));
roof.setStatic(true);
world.AddPhysicsBody(roof);
roof.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
	cout << "thud " << thudCount << endl;
	thudCount++;
};

// Create the walls
PhysicsRectangle wallLeft;
wallLeft.setSize(Vector2f(20, 560));
wallLeft.setCenter(Vector2f(10, 300));
wallLeft.setStatic(true);
world.AddPhysicsBody(wallLeft);
wallLeft.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
	cout << "thud " << thudCount << endl;
	thudCount++;
};

PhysicsRectangle wallRight;
wallRight.setSize(Vector2f(20, 560));
wallRight.setCenter(Vector2f(790, 300));
wallRight.setStatic(true);
world.AddPhysicsBody(wallRight);
wallRight.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
	cout << "thud " << thudCount << endl;
	thudCount++;
};
//Create center Rectangle
PhysicsRectangle centerRect;
centerRect.setSize(Vector2f(200, 200));
centerRect.setCenter(Vector2f(400, 300));
centerRect.setStatic(true);
world.AddPhysicsBody(centerRect);
int bangCount(1);
centerRect.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
	cout << "bang " << bangCount << endl;
	bangCount++;
};

Clock clock;
Time lastTime(clock.getElapsedTime());
while (true) {
// calculate MS since last frame
Time currentTime(clock.getElapsedTime());
Time deltaTime(currentTime - lastTime);
int deltaTimeMS(deltaTime.asMilliseconds());
if (deltaTimeMS > 0) {
world.UpdatePhysics(deltaTimeMS);
lastTime = currentTime;
}
window.clear(Color(0, 0, 0));
window.draw(ball);
window.draw(floor);
window.draw(roof);
window.draw(wallLeft);
window.draw(wallRight);
window.draw(centerRect);
window.display();
if (bangCount == 4) {
	window.close();
	return(0);

}

}
}
