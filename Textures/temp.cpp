#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include<cmath>

using namespace std;
using namespace sf;

// Initializing Dimensions
const int resolutionX = 960;
const int resolutionY = 640;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; //30
const int gameColumns = resolutionY / boxPixelsY; //20

//////////////////////////////////////////////////////////////////////////Game Grid///////////////////////////////////////////////////////////////////////////////////////////////
int gameGrid[gameRows][gameColumns] = {};

// Function Declarations

void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void handleSprayLogic(int& currentSprays, int& currentCans, Sprite& playerSprite, Sprite& extraSprayCan1, Sprite& extraSprayCan2, bool& bullet_exists, float& bullet_x, float& bullet_y);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void moveBees(Sprite workerBees[], int beeAttributes[][3], Sprite honeycombs[], int gameGrid[][gameColumns], int numBees, Clock& moveClock);
void checkBulletCollision(Sprite workerBees[], int beeAttributes[][3], bool& bullet_exists, float& bullet_x, float& bullet_y, Sprite honeycombs[], int numBees);
void drawSprayCans(RenderWindow& window, Sprite& extraSprayCan1, Sprite& extraSprayCan2, int currentCans);
void moveHummingbirdToClosestHoneycomb(Sprite& hummingbird, int& hummingbirdX, int& hummingbirdY, Sprite honeycombs[], int beeAttributes[][3], int numBees, int gameGrid[][gameColumns]);
float calculateManhattanDistance(int x1, int y1, int x2, int y2);



void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite) {
    playerSprite.setPosition(player_x, player_y);
    window.draw(playerSprite);
}

///////////////////////////////////////////////////////////////////////// Manages bullet movement//////////////////////////////////////////////////////////////////////////////

void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock) {
    if (bulletClock.getElapsedTime().asMilliseconds() < 10)
        return;

    bulletClock.restart();
    bullet_y -= 10;
    if (bullet_y < -32)
        bullet_exists = false;
}

////////////////////////////////////////////////////////////////////// Draws the bullet sprite/////////////////////////////////////////////////////////////////////////////////

void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite) {
    bulletSprite.setPosition(bullet_x, bullet_y);
    window.draw(bulletSprite);
}

// ////////////////////////////////////////////////////////////////////Handles spray logic, including spray cans and shooting//////////////////////////////////////////////////////

void handleSprayLogic(int& currentSprays, int& currentCans, Sprite& playerSprite, Sprite& extraSprayCan1, Sprite& extraSprayCan2, bool& bullet_exists, float& bullet_x, float& bullet_y) {
    if (currentSprays <= 0) {
        if (currentCans > 0) {
            currentSprays = 56;
            currentCans--;
            if (currentCans == 2) {
                extraSprayCan2.setPosition(-100, -100);
            } else if (currentCans == 1) {
                extraSprayCan1.setPosition(-100, -100);
            }
        } else {
            cout << "Game Over!" << endl;
            bullet_exists = false;
            exit(0);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        if (currentSprays > 0 && !bullet_exists) {
            bullet_exists = true;
            bullet_x = playerSprite.getPosition().x + boxPixelsX / 2;
            bullet_y = playerSprite.getPosition().y;
            currentSprays--;
        }
    }
}

///////////////////////////////////////////////////////////////////////// Moves bees and updates their positions////////////////////////////////////////////////////////////

void moveBees(Sprite workerBees[], int beeAttributes[][3], Sprite honeycombs[], int gameGrid[][gameColumns], int numBees, Clock& moveClock) {
    if (moveClock.getElapsedTime().asMilliseconds() < 20)
        return;

    moveClock.restart();

    for (int i = 0; i < numBees; i++) {
        int& beeX = beeAttributes[i][0];
        int& beeY = beeAttributes[i][1];
        int& direction = beeAttributes[i][2];

        if (beeAttributes[i][2] == 0) continue;

        if (beeX >= 0 && beeX < resolutionX && beeY >= 0 && beeY < resolutionY) {
            gameGrid[beeX / boxPixelsX][beeY / boxPixelsY] = 0;
        }

        beeX += direction * 5;

        if (beeX <= 0 || beeX >= resolutionX - boxPixelsX) {
            direction *= -1;
            beeY += boxPixelsY;
        }

        if (beeX >= 0 && beeX < resolutionX && beeY >= 0 && beeY < resolutionY) {
            gameGrid[beeX / boxPixelsX][beeY / boxPixelsY] = 1;
        }

        workerBees[i].setPosition(beeX, beeY);
    }
}

///////////////////////////////////////////////////////////////// Checks for bullet collisions with bees and honeycombs////////////////////////////////////////////////////

void checkBulletCollision(Sprite workerBees[], int beeAttributes[][3], bool& bullet_exists, float& bullet_x, float& bullet_y, Sprite honeycombs[], int numBees) {
    for (int i = 0; i < numBees; i++) {
        if (beeAttributes[i][2] == 0) continue; // Skip inactive bees

        float beeX = workerBees[i].getPosition().x;
        float beeY = workerBees[i].getPosition().y;

        // Check if bullet collides with bee
        if (bullet_exists && bullet_x >= beeX && bullet_x <= beeX + boxPixelsX && bullet_y >= beeY && bullet_y <= beeY + boxPixelsY) {
            // Mark the bee as inactive (destroy it)
            beeAttributes[i][2] = 0;

            // Create a honeycomb at the bee's position
            honeycombs[i].setPosition(beeX, beeY);

           
            bullet_exists = false;
        }
    }

 
    for (int i = 0; i < numBees; i++) {
        float honeycombX = honeycombs[i].getPosition().x;
        float honeycombY = honeycombs[i].getPosition().y;

        if (bullet_exists && bullet_x >= honeycombX && bullet_x <= honeycombX + boxPixelsX && bullet_y >= honeycombY && bullet_y <= honeycombY + boxPixelsY) {
           
            honeycombs[i].setPosition(-100, -100);

            // Destroy the bullet
            bullet_exists = false;
        }
    }
}

///////////////////////////////////////////////////////////////// Draws spray cans//////////////////////////////////////////////////////////////////////////////////////////////

void drawSprayCans(RenderWindow& window, Sprite& extraSprayCan1, Sprite& extraSprayCan2, int currentCans) {
    if (currentCans >= 1) {
        window.draw(extraSprayCan1);
    }
    if (currentCans >= 2) {
        window.draw(extraSprayCan2);
    }
}
///////////////////////////////////////////////////////////////manhattan distance//////////////////////////////////////////////////////////////////////////////////////////

float calculateManhattanDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}
/////////////////////////////////////////////////////////////////hummingbird movement///////////////////////////////////////////////////////////////////////////////////////////

void moveHummingbirdToClosestHoneycomb(Sprite& hummingbird, Sprite honeycombs[], int beeAttributes[][3], int numBees) {
    if (hummingbird.getPosition().x == -100 && hummingbird.getPosition().y == -100) {
        // If hummingbird is not placed yet, place it at a starting position
        hummingbird.setPosition(resolutionX / 2, resolutionY / 2);
    }

    // Find the closest honeycomb based on Manhattan distance
    int closestHoneycombIndex = -1;
    int minDistance = 100000;

    // Loop through all honeycombs to find the closest one
    for (int i = 0; i < numBees; i++) {
        // Skip if honeycomb is already eaten (position is off-screen)
        if (honeycombs[i].getPosition().x == -100 && honeycombs[i].getPosition().y == -100)
            continue;

        int honeycombX = honeycombs[i].getPosition().x;
        int honeycombY = honeycombs[i].getPosition().y;

        // Calculate Manhattan distance from the hummingbird to the honeycomb
        int distance = abs(hummingbird.getPosition().x - honeycombX) + abs(hummingbird.getPosition().y - honeycombY);

        if (distance < minDistance) {
            minDistance = distance;
            closestHoneycombIndex = i;
        }
    }

    // If we found the closest honeycomb
    if (closestHoneycombIndex != -1) {
        // Move the hummingbird toward the closest honeycomb
        int targetX = honeycombs[closestHoneycombIndex].getPosition().x;
        int targetY = honeycombs[closestHoneycombIndex].getPosition().y;

        // Calculate direction vector to move hummingbird towards target
        float deltaX = targetX - hummingbird.getPosition().x;
        float deltaY = targetY - hummingbird.getPosition().y;
        float distance = sqrt(deltaX * deltaX + deltaY * deltaY);  // Get distance to the target

        if (distance > 1) {  // If the hummingbird hasn't reached the honeycomb yet
            // Normalize the movement vector and move the hummingbird
            float speed = 0.05f;
            hummingbird.move(speed * (deltaX / distance), speed * (deltaY / distance));
        } else {
            // Once the hummingbird reaches the honeycomb, remove the honeycomb from the grid
            honeycombs[closestHoneycombIndex].setPosition(-100, -100);  // Move honeycomb off-screen
        }
    }
}
/////////////////////////////////////////////////////////////////////draw a honeycomb////////////////////////////////////////////////////////////////////////////////////////////

void drawHoneycombs(RenderWindow& window, Sprite honeycombs[], int numHoneycombs) {
    for (int i = 0; i < numHoneycombs; i++) {
        window.draw(honeycombs[i]);  // Draw each honeycomb sprite
    }
}



////////////////////////////////////////////////////////////////////movekillerbees//////////////////////////////////////////////////////////////////////////////////////////////

void moveKillerBees(Sprite& killerBee, int& killerBeeX, int& killerBeeY, bool& killerBeeActive) {
    if (!killerBeeActive) return; // If the killer bee is not active, don't move it

    static int direction = 1; // 1 for right, -1 for left
    killerBeeX += 1.0* direction;  // Move faster than regular bees

    // When the Killer Bee reaches the screen's edges, reverse its direction
    if (killerBeeX >= resolutionX - boxPixelsX || killerBeeX <= 0) {
        direction *= -1;  // Reverse direction
        killerBeeY += boxPixelsY;  // Move downwards when hitting the edge
    }

    killerBee.setPosition(killerBeeX, killerBeeY);
}

///////////////////////////////////////////////////////////////////check killer bee collision////////////////////////////////////////////////////////////////////////////////////

void checkKillerBeeCollision(Sprite& killerBee, int& killerBeeX, int& killerBeeY, bool& bullet_exists, float& bullet_x, float& bullet_y, bool& killerBeeActive, Sprite& redHoneycomb) {
    // Check if the bullet hits the Killer Bee
    if (bullet_exists && bullet_x >= killerBeeX && bullet_x <= killerBeeX + boxPixelsX && bullet_y >= killerBeeY && bullet_y <= killerBeeY + boxPixelsY) {
        bullet_exists = false;  // Bullet hit the Killer Bee
        killerBeeActive = false;  // Mark it inactive
        killerBee.setPosition(-100, -100); // Move Killer Bee off-screen

        // Spawn a red honeycomb at the position of the killer bee
        redHoneycomb.setPosition(killerBeeX, killerBeeY);
    }
}

/////////////////////////////////////////////////////////////check bee collision with green rectangle and create flowers///////////////////////////////////////////////////////

void checkBeeCollisionAndCreateFlowers(Sprite workerBees[], int& numBees, double flowerGrid[20][3], int& total_flowers, double resolutionX) {
    double greenRectY = 500;  // The Y position of the ground or rectangle

    // Loop through each bee to check for collision and create flowers
    for (int i = 0; i < numBees; i++) {
        float beeX = workerBees[i].getPosition().x;  // Get the X position of the current bee
        float beeY = workerBees[i].getPosition().y;  // Get the Y position of the current bee

        // Debugging message to check bee's current position
        cout << "Checking bee " << i << " at position (" << beeX << ", " << beeY << ")\n";
        // Check if the bee reaches the ground or the rectangle at greenRectY
        if (beeY >= greenRectY && beeX >= 0 ) {  
        	for(int x=0;x<total_flowers;x++){
        		if(flowerGrid[x][2]==0){
				flowerGrid[x][0]=beeX;
				flowerGrid[x][1]=beeY;
				flowerGrid[x][2]=1;
				cout << "Flower created at (" << beeX << ", " << beeY << ")\n";  // Log flower creation
				
				break;
				
			}
			
			
		}
		workerBees[i].setPosition(0,0);
	
	}
	else{
		
		flowerGrid[i][0] = 0;
		flowerGrid[i][1] = 0;
		flowerGrid[i][2] = 0;  // InActive flower
			 
        		
        	
   
    	}
     }
}
///////////////////////////////////////////////////////////////draw flowers//////////////////////////////////////////////////////////////////////////////////////////////////

void drawFlowers(RenderWindow& window, Texture& flowerTexture, double flowerGrid[20][3], int total_flowers) {
    // Loop through the flower grid and draw active flowers
    for (int i = 0; i < 20; i++) {
        if (flowerGrid[i][2] == 1) {  // Check if the flower is active
            Sprite flowerSprite(flowerTexture);
            flowerSprite.setPosition(flowerGrid[i][0], flowerGrid[i][1]);
            window.draw(flowerSprite);
            cout << "Drawing flower at (" << flowerGrid[i][0] << ", " << flowerGrid[i][1] << ")\n";  // Log flower drawing
         
        }
    }
}



/////////////////////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    srand(time(0));

    RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);
    window.setPosition(Vector2i(500, 200));

    Music bgMusic;
    if (!bgMusic.openFromFile("Music/Music3.ogg")) {
        cout << "Warning: Could not load music file. Game will run without music." << endl;
    } else {
        bgMusic.setVolume(50);
        bgMusic.setLoop(true);
        bgMusic.play();
    }

    float player_x = (gameRows / 2) * boxPixelsX;
    float player_y = (gameColumns - 4) * boxPixelsY;

    Texture playerTexture;
    Sprite playerSprite;
    playerTexture.loadFromFile("Textures/spray.png");
    playerSprite.setTexture(playerTexture);

    Texture bulletTexture;
    Sprite bulletSprite;
    bulletTexture.loadFromFile("Textures/bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setScale(2, 2);

    Texture beeTexture, honeycombTexture;
    beeTexture.loadFromFile("Textures/Regular_bee.png");
    honeycombTexture.loadFromFile("Textures/honeycomb.png");
   
   
     Sprite redHoneycomb;
     Texture redHoneycombTexture;
     redHoneycombTexture.loadFromFile("Textures/honeycomb_red.png");
     redHoneycomb.setTexture(redHoneycombTexture);
     redHoneycomb.setPosition(-100, -100); // Initially off-screen


    Texture flowerTexture;
    flowerTexture.loadFromFile("Textures/obstacles.png");

    int numBees = 20;
    Sprite workerBees[numBees], honeycombs[numBees];
    int beeAttributes[numBees][3];

    for (int i = 0; i < 3; i++) {
        int randX = rand() % gameRows * boxPixelsX;
        int randY = rand() % (gameColumns / 4) * boxPixelsY;
        honeycombs[i].setTexture(honeycombTexture);
        honeycombs[i].setPosition(randX, randY);
    }

    for (int i = 0; i < numBees; i++) {
        workerBees[i].setTexture(beeTexture);
        honeycombs[i].setTexture(honeycombTexture);
        beeAttributes[i][0] = rand() % gameRows * boxPixelsX;
        beeAttributes[i][1] = rand() % (gameColumns / 4) * boxPixelsY;
        beeAttributes[i][2] = 1; // All bees are active initially
    }



    int currentSprays = 56, currentCans = 3;
    bool bullet_exists = false;
    float bullet_x = player_x, bullet_y = player_y;
    Sprite extraSprayCan1, extraSprayCan2;
    extraSprayCan1.setTexture(playerTexture);

    extraSprayCan2.setTexture(playerTexture);

    extraSprayCan1.setPosition(10, resolutionY - 120);
    extraSprayCan2.setPosition(50, resolutionY - 120);

    Clock bulletClock;
    Clock moveClock;
    int currentLevel = 10;

    // Green bottom block (ground rectangle)
    RectangleShape groundRectangle(Vector2f(960, 64));
    groundRectangle.setPosition(0, resolutionY - 64);  // Place it at the bottom
    groundRectangle.setFillColor(Color::Green);

    // Timer to spawn hummingbird after 10 seconds
    Clock gameClock;
    bool hummingbirdAppeared = false;
    Sprite hummingbird;
    Texture hummingbirdTexture;
    hummingbirdTexture.loadFromFile("Textures/hummingbird.gif");
    hummingbird.setTexture(hummingbirdTexture);
    hummingbird.setPosition(-100, -100);  // Initially off-screen
    hummingbird.setScale(1.0f, 1.0f);

    // Killer Bee logic
    Sprite killerBee;
    Texture killerBeeTexture;
    killerBeeTexture.loadFromFile("Textures/Fast_bee.png");
    killerBee.setTexture(killerBeeTexture);
    int killerBeeX = resolutionX / 2;  // Start in the center
    int killerBeeY = resolutionY / 2;
    bool killerBeeActive = true;  // Start the Killer Bee as active
   
   
    double flowerGrid[20][3];
    int total_flowers=20;
     int state=0;
for (int i = 0; i < 20; ++i) {
   for (int j = 0; j < 3; ++j) {
flowerGrid[i][j] = 0;
   }
}

/////////////////////////////////////////////////////////////////////GAME LOOP///////////////////////////////////////////////////////////////////////////////////

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                bgMusic.stop();
                return 0;
            }
        }

        // Handle player movement
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (player_x > 0) player_x -= 0.5;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (player_x < resolutionX - boxPixelsX) player_x += 0.5;
        }

        handleSprayLogic(currentSprays, currentCans, playerSprite, extraSprayCan1, extraSprayCan2, bullet_exists, bullet_x, bullet_y);
        moveBullet(bullet_y, bullet_exists, bulletClock);

        window.clear(Color(20, 20, 20));

        drawPlayer(window, player_x, player_y, playerSprite);
        drawSprayCans(window, extraSprayCan1, extraSprayCan2, currentCans);
        drawBullet(window, bullet_x, bullet_y, bulletSprite);
        moveBees(workerBees, beeAttributes, honeycombs, gameGrid, numBees, moveClock);
        checkBulletCollision(workerBees, beeAttributes, bullet_exists, bullet_x, bullet_y, honeycombs, numBees);

        // Draw hummingbird if it appears
        if (hummingbirdAppeared) {
            moveHummingbirdToClosestHoneycomb(hummingbird, honeycombs, beeAttributes, numBees);
            window.draw(hummingbird);
        }

        drawHoneycombs(window, honeycombs, 3);

moveBees(workerBees, beeAttributes, honeycombs, gameGrid, numBees, moveClock);
        checkBulletCollision(workerBees, beeAttributes, bullet_exists, bullet_x, bullet_y, honeycombs, numBees);

        // Move Killer Bee and handle collision with bullet
        moveKillerBees(killerBee, killerBeeX, killerBeeY, killerBeeActive);
        checkKillerBeeCollision(killerBee, killerBeeX, killerBeeY, bullet_exists, bullet_x, bullet_y,killerBeeActive, redHoneycomb);

        // Draw Killer Bee if active
        if (killerBeeActive) {
            window.draw(killerBee);
        }


// Draw all regular bees
for (int i = 0; i < numBees; i++) {
   if (beeAttributes[i][2] != 0) {  // If bee is active
window.draw(workerBees[i]);  // Draw each active bee
   }
}

if (redHoneycomb.getPosition().x != -100) {
    window.draw(redHoneycomb);
}
// Draw all honeycombs
for (int i = 0; i < numBees; i++) {
   if (honeycombs[i].getPosition().x != -100 && honeycombs[i].getPosition().y != -100) {
window.draw(honeycombs[i]);  // Draw each honeycomb if it's not off-screen
   }
}

checkBeeCollisionAndCreateFlowers(workerBees, numBees, flowerGrid, total_flowers, resolutionX);
drawFlowers(window,flowerTexture, flowerGrid,total_flowers);

        window.draw(groundRectangle);

        window.display();
    }

    return 0;
}
