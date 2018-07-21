#include <SFML/Graphics.hpp>
#include <thread>
#include <windows.h>
#include <iostream>
#include<time.h>
#include <chrono>
#include <vector>

bool isOnGround(sf::Sprite s, sf::RectangleShape b[]);
sf::RectangleShape touchedThing(sf::Sprite s, sf::RectangleShape b[]);
void isTouchingEvilBob(sf::Sprite evil[]);
/*

	Global var declaration area.

*/
const float maxY = 50.0f;
const sf::Vector2f gravity(0.f, .5f);
sf::Vector2f velocity(0.f, 0.f);

sf::RectangleShape nullRect; // Used to say there is nothing found or that the tot was deleted.

bool dead = false; // If the player is dead

int boxsize = 10; // How many platforms you have. (Must be exact)
int treesize = 3; // How many trees you have. (Must be exact).
int collectablesize = 4; //How many tatertots there are. (Must be exact).
int evildudesize = 1; // How many enemys there are. (Must be exact).

int screenX = 1600;
int screenY = 900;
bool inJump = false; //If the player is in the middle of the jump.
sf::Sprite playerSprite; //The player sprite.

float currentTime;
float oldTime;
float deltaTime;

int scores = 0; //The score.



std::vector<sf::RectangleShape> usedCollect; //A vector to store used tatertots.

void jump(sf::Sprite p, sf::RectangleShape b[]) {  //Jump function
	if (isOnGround(p, b) && !inJump && !dead) {
		float acceleration = 0.3;
		float velocity = 0;
		std::cout << "fire" << std::endl;
		inJump = true;
		sf::Vector2f vel(0, 0);
		for (int i = 0; i < 50; i++) {
			if (velocity < 10)
				velocity -= acceleration;
			
			///vel.y -= 0.5 * deltaTime (Unused)
			playerSprite.move(0, velocity );
			
		}
		std::cout << "after loop" << std::endl;
		Sleep(20);
		sf::Vector2f vel2(0, 0);
		velocity = 0;
		acceleration = 0.5;
		while (!isOnGround(p, b)) {
			///Sleep(500);
			if (velocity < 6)
				velocity += acceleration * deltaTime;
			///vel2.y += 0.01 * deltaTime;
			playerSprite.move(0, velocity);
		}
		std::cout << "done" << std::endl;
		inJump = false;

	}
}


int main()
{
	nullRect.setPosition(-900, -900); //set's null position to somewhere way offscreen where nothing can have the same position.

	sf::RenderWindow window(sf::VideoMode(screenX, screenY), "Bob the teleporter!");
	/* 
		Textures
	*/
	sf::Texture leftPlayerTex;
	leftPlayerTex.loadFromFile("Textures/PlayerDude_Left.png");
	sf::Texture rightPlayerTex;
	rightPlayerTex.loadFromFile("Textures/PlayerDude_Right.png");
	sf::Texture treeTex;
	treeTex.loadFromFile("Textures/Tree.png");
	sf::Font robotoItalics;
	robotoItalics.loadFromFile("Font/Roboto-Italic.ttf");
	sf::Texture evilDudeTex;
	evilDudeTex.loadFromFile("Textures/EvilDude.png");

	/*
		Camera
	*/
	sf::View camera(sf::Vector2f(50, 50), sf::Vector2f(100, 100));
	camera.setSize(screenX, screenY);
	camera.setCenter(150, 150);

	/*
		Player Sprite
	*/
	playerSprite.setTexture(leftPlayerTex);

	playerSprite.setOrigin(32, 32);
	playerSprite.setScale(0.4, 0.4);
	playerSprite.setPosition(450, 380);

	/*
		Enemies
	*/

	sf::Sprite evilDude;
	evilDude.setTexture(evilDudeTex);
	evilDude.setOrigin(32, 32);
	evilDude.setScale(0.2, 0.2);
	evilDude.setPosition(2200, 165);
	/*
		Trees
	*/
	sf::Sprite tree;
	tree.setTexture(treeTex);
	tree.setOrigin(32, 32);
	tree.setScale(0.7, 0.7);
	tree.setPosition(200, 330);
	sf::Sprite tree1;
	tree1.setTexture(treeTex);
	tree1.setOrigin(32, 32);
	tree1.setScale(0.7, 0.7);
	tree1.setPosition(1200, 150);
	sf::Sprite tree2;
	tree2.setTexture(treeTex);
	tree2.setOrigin(32, 32);
	tree2.setScale(0.7, 0.7);
	tree2.setPosition(3000, 350);

	/*
		Collectables (Tatertots)
	*/

	sf::RectangleShape collectable;
	collectable.setSize(sf::Vector2f(10, 10));
	collectable.setFillColor(sf::Color::Yellow);
	collectable.setPosition(1250, 730);

	sf::RectangleShape collectable2;
	collectable2.setSize(sf::Vector2f(10, 10));
	collectable2.setFillColor(sf::Color::Yellow);
	collectable2.setPosition(550, 250);

	sf::RectangleShape collectable3;
	collectable3.setSize(sf::Vector2f(10, 10));
	collectable3.setFillColor(sf::Color::Yellow);
	collectable3.setPosition(2500, 250);

	sf::RectangleShape collectable4;
	collectable4.setSize(sf::Vector2f(10, 10));
	collectable4.setFillColor(sf::Color::Yellow);
	collectable4.setPosition(2750, 600);
	/*
		Boxes.
		(Platforms or objects that the player can collide with (walk on)).
	*/
	sf::RectangleShape box1;
	box1.setSize(sf::Vector2f(1000, 15));
	box1.setPosition(500, 500);
	box1.setRotation(180.0f);
	box1.setFillColor(sf::Color::Green);
	sf::RectangleShape box2;
	box2.setSize(sf::Vector2f(250, 10));
	box2.setPosition(900, 500);
	box2.setRotation(180.0f);
	box2.setFillColor(sf::Color::Green);
	sf::RectangleShape box3;
	box3.setSize(sf::Vector2f(100, 15));
	box3.setPosition(600, 800);
	box3.setRotation(180.0f);
	box3.setFillColor(sf::Color::Red);
	sf::RectangleShape box4;
	box4.setSize(sf::Vector2f(100, 15));
	box4.setPosition(600, 300);
	box4.setRotation(180.0f);
	box4.setFillColor(sf::Color::Green);
	sf::RectangleShape box5;
	box5.setSize(sf::Vector2f(1650, 15));
	box5.setPosition(900, 300);
	box5.setRotation(0.0f);
	box5.setFillColor(sf::Color::Green);
	sf::RectangleShape box6;
	box6.setSize(sf::Vector2f(100, 15));
	box6.setPosition(1300, 800);
	box6.setRotation(180.0f);
	box6.setFillColor(sf::Color::Red);
	sf::RectangleShape box7; //Platform over the top evilbob.
	box7.setSize(sf::Vector2f(300, 15));
	box7.setPosition(2100, -100);
	box7.setRotation(0.f);
	box7.setFillColor(sf::Color::White);
	sf::RectangleShape box8;
	box8.setSize(sf::Vector2f(700, 15));
	box8.setPosition(2700, 500);
	box8.setRotation(0.0f);
	box8.setFillColor(sf::Color::Green);
	sf::RectangleShape box9; //Platform to get to box 8
	box9.setSize(sf::Vector2f(100, 15));
	box9.setPosition(2600, 5);
	box9.setRotation(0.f);
	box9.setFillColor(sf::Color::White);
	sf::RectangleShape box10; //Platform below box 8
	box10.setSize(sf::Vector2f(100, 15));
	box10.setPosition(2750, 700);
	box10.setRotation(0.f);
	box10.setFillColor(sf::Color::White);

	/*
		Texts
	*/

	sf::Text txt;
	sf::Font ft;
	ft.loadFromFile("Font/Roboto-Regular.ttf");
	txt.setString("Youz iz ded.");
	txt.setFillColor(sf::Color::Red);
	txt.setCharacterSize(100);
	txt.setPosition(500, 100);
	txt.setFont(ft);

	sf::Text info;
	info.setString("               Hello bob, Go on your adventure! \n                     Press W to teleport upward! \n Collect the yellow tatertots to increse your score!");
	info.setFillColor(sf::Color::Black);
	info.setCharacterSize(40);
	info.setPosition(150, 50);
	info.setFont(ft);

	sf::Text evilBob;
	evilBob.setString("This is evil bob! He wants your tatertots. \n              Find a way around him!");
	evilBob.setFillColor(sf::Color::Black);
	evilBob.setCharacterSize(40);
	evilBob.setPosition(1900, 20);
	evilBob.setFont(ft);

	sf::Text thanks;
	thanks.setString("Thanks for playing my demo! \n              Creator: Ryan");
	thanks.setFillColor(sf::Color::Black);
	thanks.setCharacterSize(40);
	thanks.setPosition(2800, 200);
	thanks.setFont(ft);

	sf::Text invis;
	invis.setString("What's This? Invisable Platforms?");
	invis.setFillColor(sf::Color::Black);
	invis.setCharacterSize(40);
	invis.setPosition(1900, -400);
	invis.setFont(ft);
	/*
		UI Elements
	*/
	sf::Text score;
	score.setString("Tatertots: xxx");
	score.setFillColor(sf::Color::Black);
	score.setCharacterSize(30);
	score.setPosition(1000, 20);
	score.setFont(robotoItalics);

	sf::Texture tatertotTex;
	tatertotTex.loadFromFile("Textures/tatertot.png");
	sf::Sprite tatertot;
	tatertot.setTexture(tatertotTex);
	tatertot.setOrigin(32, 32);
	tatertot.setScale(0.05, 0.05);
	tatertot.setPosition(450, 380);


	bool movingUp = false; // Controls moving
	bool movingLeft = false;
	bool movingRight = false;
	bool movingDown = false;

	/*
		This is used so items can be added in with little editing of code. The size of the array can not be smaller than the number
		of items inside.
	*/
	sf::RectangleShape boxes[10] = { box1, box2, box3, box4, box5, box6, box7, box8, box9, box10 }; //platforms
	sf::Sprite trees[3] = { tree, tree1, tree2 }; //trees
	sf::RectangleShape collectables[4] = { collectable, collectable2, collectable3, collectable4 }; //collectables (tots)
	sf::Sprite evilDudes[1] = { evilDude }; //Enemies
	//Main Loop:
	while (window.isOpen())
	{
		//Unused. Delta time is currently broken in this version.
		clock_t t;
		t = clock();
		oldTime = currentTime;
		currentTime = t;
		deltaTime = currentTime - oldTime;
		//Events
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					///movingUp = true;
					std::thread t1(jump, playerSprite, boxes); //Fire the jump function.
					t1.join();
				}
				if (event.key.code == sf::Keyboard::A) {
					movingLeft = true;
					playerSprite.setTexture(leftPlayerTex);
				}
				if (event.key.code == sf::Keyboard::D) {
					movingRight = true;
					playerSprite.setTexture(rightPlayerTex);
				}
				if (event.key.code == sf::Keyboard::S) {
					movingDown = true;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::W) {
					movingUp = false;
				}
				if (event.key.code == sf::Keyboard::A) {
					movingLeft = false;
				}
				if (event.key.code == sf::Keyboard::D) {
					movingRight = false;
				}
				if (event.key.code == sf::Keyboard::S) {
					movingDown = false;
				}
			}
		}

		isTouchingEvilBob(evilDudes); //Checks to see if the player is touching any evil bob (the enemies).

		for (int i = 0; i < collectablesize; i++) {
			if (collectables[i].getPosition() != nullRect.getPosition()) {
				collectables[i].setRotation(collectables[i].getRotation() + 1); //Rotates the collectables if it exists still.
			}
		}

		sf::RectangleShape tempRS; //Used for temp storage.
		tempRS = touchedThing(playerSprite, collectables);
		if (tempRS.getPosition() != nullRect.getPosition()) {
			for (int i = 0; i < collectablesize; i++) {
				if (tempRS.getPosition() == collectables[i].getPosition()) {
					collectables[i] = nullRect; //Sets used collectables to nullRect so they no longer appear and are collectable.
					break;
				}
			}
		}
		/*
			Movement handler
		*/
		sf::Vector2f movement(0, 0);
		if (!dead) {
			
			if (movingUp) {
				movement.y -= 2.5f;
			}
			if (movingDown) {
				movement.y += 0.5f;
			}
			if (movingRight) {
				movement.x += 0.5f;
			}
			if (movingLeft) {
				movement.x -= 0.5f;
			}
		}
		/*
			Moves the camera with the player. Moved the is dead text so it spawns where the player is when they die.
		*/
		if (!(playerSprite.getPosition().y > screenY) || dead) {
			camera.setCenter(playerSprite.getPosition());
			txt.setPosition(playerSprite.getPosition());
		}
		else {
			camera.setCenter(500, 100); //resets the camera when the player dies.
		}
		/*
			UI handler. This handles the UI so it always stays on screen in the same position.
		*/
		score.setPosition(camera.getCenter().x + 600, camera.getCenter().y - 450); // Set the score position so it moves with the camera.
		score.setString("Tatertots: " + std::to_string(scores)); //set the score
		tatertot.setPosition(camera.getCenter().x + 550, camera.getCenter().y - 440);

		/* 
			Gravity Handler
		*/
		if (!isOnGround(playerSprite, boxes) && !inJump)
		{

			playerSprite.move(velocity);
			if (velocity.y < maxY) velocity += gravity;
		}
		

		
		playerSprite.move(movement); //Applies the movement the the sprite so the player moves.


		window.clear(sf::Color::White); //Clears the screen and sets the background white.
		for (int i = 0; i < treesize; i++) {
			window.draw(trees[i]); //Draws all the trees.
		}
		for (int i = 0; i < collectablesize; i++) {
			if (collectables[i].getPosition() != nullRect.getPosition()) {
				window.draw(collectables[i]); //Draws all the collectables. (Except the collected ones).
			}
		}
		window.draw(info);
		window.draw(evilBob); //Draws the text named evilbob;
		for (int i = 0; i < evildudesize; i++) {
			window.draw(evilDudes[i]); //Draws all of the enemies.
		}
		if (!dead) {
			window.draw(playerSprite); //Draws the player sprite if it is not dead.
		}
		for (int i = 0; i < boxsize; i++) {
			window.draw(boxes[i]); //Draws all of the boxes. (Platforms)
		}
		window.draw(invis);
		window.draw(thanks);
		if (playerSprite.getPosition().y > screenY || dead) {
			window.draw(txt); //Draws the dead text if the player is dead.
		}
		if(!(playerSprite.getPosition().y > screenY))
			window.setView(camera); //Sets the view window the the camera.
		window.draw(score);
		window.draw(tatertot);
		
		window.display(); //Displays the window.
	}
	
}
/*
	Checks if the player is on a platform.
*/
bool isOnGround(sf::Sprite s, sf::RectangleShape b[]) {
	for (int i = 0; i < boxsize; i++) {
		if (s.getGlobalBounds().intersects(b[i].getGlobalBounds()))
			return true;
	}
	return false;
}
/*
	Checks if the player touched any collectables.
*/
sf::RectangleShape touchedThing(sf::Sprite s, sf::RectangleShape b[]) {
	for (int i = 0; i < collectablesize; i++) {
		if (s.getGlobalBounds().intersects(b[i].getGlobalBounds())) {
			usedCollect.push_back(b[i]);
			scores++;
			return b[i];
		}
			
	}
	return nullRect;
}
/*
	Checks if the player touched evil bob.
*/
void isTouchingEvilBob(sf::Sprite evil[]) {
	for (int i = 0; i < evildudesize; i++) {
		if (playerSprite.getGlobalBounds().intersects(evil[i].getGlobalBounds())) {
			dead = true;
		}
	}
}
