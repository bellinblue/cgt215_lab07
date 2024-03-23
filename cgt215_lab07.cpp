// cgt215_lab07.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Draws four rectangles that cage in ball; program ends once ball collides with center rectangle 3 times

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
	ball.setCenter(Vector2f(150, 100));
	ball.setRadius(20);
	ball.applyImpulse(Vector2f(0.4, 0.4));
	world.AddPhysicsBody(ball);

	//Create floor, ceiling, two vertical walls, & center wall
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 560));
	leftWall.setCenter(Vector2f(10, 300));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);

	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 560));
	rightWall.setCenter(Vector2f(790, 300));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	PhysicsRectangle centerWall;
	centerWall.setSize(Vector2f(150, 150));
	centerWall.setCenter(Vector2f(400, 300));
	centerWall.setStatic(true);
	world.AddPhysicsBody(centerWall);

	//Add to thud & bang counter 
	int thudCount(0);
	int bangCount(0);

	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount+1 << endl;
		thudCount++;
		};
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount+1 << endl;
		thudCount++;
		};
	leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount+1 << endl;
		thudCount++;
		};
	rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount+1 << endl;
		thudCount++;
		};
	centerWall.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount+1 << endl;
		if (bangCount >= 2) { exit(0); } else { bangCount++; }
		};

	//Set & get time
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		//Calculate milliseconds since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}

		//Draw window, rectangles, & ball
		window.clear(Color(0, 0, 0));
		window.draw(floor);
		window.draw(ceiling);
		window.draw(leftWall);
		window.draw(rightWall);
		window.draw(centerWall);
		window.draw(ball);
		window.display();
	}
}
