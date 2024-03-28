#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Ball.h"
#include "Global.h" // for windowWidth and windowHeight
#include "Paddle.h"
#include "Brick.h"
#include "LifeIndicator.h"
#include "Particle.cpp"
#include "Powerup.h"
#include <iostream>
#include <random>
#include "Laser.h"

int windowWidth{ 800 }, windowHeight{ 600 };


sf::SoundBuffer paddleHitBuffer;
sf::Sound paddleHit;
sf::SoundBuffer brickHitBuffer;
sf::Sound brickHit;
int score = 0;
sf::Text scoreText;
int level = 0;
sf::Text levelText;
int particlesSize = 0;
sf::Text pressSpaceText;
bool gameStopped = true;
sf::Clock blinkClock;
sf::Clock laserClock;
sf::Text laserText;

int numberOfLives = 3;
std::vector<LifeIndicator> lifeIndicators;

std::mt19937 mt(std::random_device{}());








// Bricks broken particle vector
std::vector<Particle> particles;
sf::Texture particleTexture;
sf::Texture ballTexture;
std::vector<Powerup> powerups;
std::vector<Ball> balls;
bool lasersActivated = true;
std::vector<Laser> lasers;



// Dealing with collisions: let's define a generic function
// to check if two shapes are intersecting (colliding).
template <class T1, class T2>
bool isIntersecting(T1& mA, T2& mB)
{
    return mA.right() >= mB.left() && mA.left() <= mB.right() &&
        mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

// Let's define a function that deals with paddle/ball collision.
void testCollision(Paddle& mPaddle, Ball& mBall)
{
    // If there's no intersection, get out of the function.
    if (!isIntersecting(mPaddle, mBall)) return;

    // Otherwise let's "push" the ball upwards.
    mBall.velocity.y = -mBall.ballVelocity;

    // And let's direct it dependently on the position where the
    // paddle was hit.
    if (mBall.x() < mPaddle.x()) 
        mBall.velocity.x = -mBall.ballVelocity - (rand() % 2);
    else
        mBall.velocity.x = mBall.ballVelocity + (rand() % 2);

    if (!paddleHitBuffer.loadFromFile("./sounds/paddleHit.flac"))
    {
        // error...
    }
    paddleHit.setBuffer(paddleHitBuffer);
    paddleHit.setVolume(50);
    paddleHit.play();
}

// Test collision for powerups
void testCollision(Powerup& mPowerUp, Paddle& mPaddle) {
    	if (!isIntersecting(mPowerUp, mPaddle)) return;
	// Powerup collected
	mPowerUp.destroyed = true;
    if (!paddleHitBuffer.loadFromFile("./sounds/powerup.flac"))
    {
		// error...
	}
	paddleHit.setBuffer(paddleHitBuffer);
	paddleHit.setVolume(50);
	paddleHit.play();
	// Increase paddle size
    if (mPowerUp.powerupType == 0) {
        mPaddle.shape.setSize({ mPaddle.paddleWidth * 1.5f, mPaddle.paddleHeight });
        mPaddle.shape.setOrigin(mPaddle.paddleWidth * 1.5f / 2.f, mPaddle.paddleHeight / 2.f);
    }
    // Decrease paddle size
    if (mPowerUp.powerupType == 1) {
		mPaddle.shape.setSize({ mPaddle.paddleWidth / 1.5f, mPaddle.paddleHeight });
		mPaddle.shape.setOrigin(mPaddle.paddleWidth / 1.5f / 2.f, mPaddle.paddleHeight / 2.f);
	}
    if (mPowerUp.powerupType == 2) {
		// Add ball
		Ball ball(windowWidth / 2, windowHeight / 2, ballTexture);
		balls.push_back(ball);
    }
    if (mPowerUp.powerupType == 3) {
        lasersActivated = true;
        laserClock.restart();        
    }

}

// Here's the most complex part of our game: ball-brick collision.
void testCollision(Brick& mBrick, Ball& mBall, std::map<int, sf::Texture>& powerupTextures)
{
    // If there's no intersection, get out of the function.
    if (!isIntersecting(mBrick, mBall)) return;

    // Otherwise, the brick has been hit!
    if (mBrick.hp > 1) {
		mBrick.updateHp(mBrick.hp - 1);
	}
    else if (mBrick.hp == 1) {
        mBrick.hp = 0;
        mBrick.destroyed = true;
    }

    score += 100; // increase score

    // Let's calculate how much the ball intersects the brick
    // in every direction.
    float overlapLeft{ mBall.right() - mBrick.left() };
    float overlapRight{ mBrick.right() - mBall.left() };
    float overlapTop{ mBall.bottom() - mBrick.top() };
    float overlapBottom{ mBrick.bottom() - mBall.top() };

    // If the magnitude of the left overlap is smaller than the
    // right one we can safely assume the ball hit the brick
    // from the left.
    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));

    // We can apply the same idea for top/bottom collisions.
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    // Let's store the minimum overlaps for the X and Y axes.
    float minOverlapX{ ballFromLeft ? overlapLeft : overlapRight };
    float minOverlapY{ ballFromTop ? overlapTop : overlapBottom };

    // If the magnitude of the X overlap is less than the magnitude
    // of the Y overlap, we can safely assume the ball hit the brick
    // horizontally - otherwise, the ball hit the brick vertically.

    // Then, upon our assumptions, we change either the X or Y velocity
    // of the ball, creating a "realistic" response for the collision.
    if (abs(minOverlapX) < abs(minOverlapY))
        mBall.velocity.x = ballFromLeft ? -mBall.ballVelocity : mBall.ballVelocity;
    else
        mBall.velocity.y = ballFromTop ? -mBall.ballVelocity : mBall.ballVelocity;

    // Create particles

    if (!particleTexture.loadFromFile("./images/default_particle.png"))
    {
        // error...
    }

    particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), true, particleTexture, mBrick.hp ));
	particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), false, particleTexture, mBrick.hp));
    particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), true, particleTexture, mBrick.hp));
    particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), false, particleTexture, mBrick.hp));
    // Used to track how many particles are on the screen to make them fall higher each time for better effect
    particlesSize = particles.size();

    if (!brickHitBuffer.loadFromFile("./sounds/brickHit.ogg"))
    {
        // error...
    }
    brickHit.setBuffer(brickHitBuffer);
    brickHit.setVolume(50);
    brickHit.play();

    int powerupChance = mt() % 100; 
    std::cout << powerupChance << std::endl;
    if (powerupChance < 20) {
       
        // Randomly choose powerup type
        int powerupType = rand() % 4;
		powerups.push_back(Powerup(mBrick.x(), mBrick.y(), powerupType, powerupTextures[powerupType]));
	}
}

//Test laser and brick collision
void testCollision(Laser& mLaser, Brick& mBrick) {
	if (!isIntersecting(mLaser, mBrick)) return;
    score += 100 * mBrick.hp;
	mBrick.hp = 0;
	mBrick.destroyed = true;
    mLaser.destroyed = true;

    if (!brickHitBuffer.loadFromFile("./sounds/brickHit.ogg"))
    {
		// error...
	}
	brickHit.setBuffer(brickHitBuffer);
	brickHit.setVolume(50);
	brickHit.play();
	// Create particles
    if (!particleTexture.loadFromFile("./images/default_particle.png"))
    {
		// error...
	}
	particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), true, particleTexture, mBrick.hp));
	particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), false, particleTexture, mBrick.hp));
	particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), true, particleTexture, mBrick.hp));
	particles.push_back(Particle::Particle(sf::Vector2f(mBrick.x(), mBrick.y()), false, particleTexture, mBrick.hp));
	// Used to track how many particles are on the screen to make them fall higher each time for better effect
	particlesSize = particles.size();
}


void changeMusic(sf::Music& music1, sf::Music& music2, sf::Music& music3) {
    if (music1.getStatus() == sf::Music::Playing) {
		music1.stop();
		music2.play();
	}
    else if (music2.getStatus() == sf::Music::Playing) {
		music2.stop();
		music3.play();
	}
    else if (music3.getStatus() == sf::Music::Playing) {
		music3.stop();
		music1.play();
    }
    else {
        music1.play();	
    }
}


int main()
{
    srand((unsigned)time(NULL));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Super Arkanoid!", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(60);
    auto icon = sf::Image();
    if (!icon.loadFromFile("./images/ballBlue.png")) {
		// error...
	}
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


    sf::Font font;
    if (!font.loadFromFile("./fonts/kenvector_future.ttf")) {
        // handle error...
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(18); // choose appropriate size
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(windowWidth - 170, 8); // adjust position as needed

    levelText.setFont(font);
    levelText.setCharacterSize(18); // choose appropriate size
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(8, 8); // adjust position as needed

    // Show text press space to start

    pressSpaceText.setFont(font);
    pressSpaceText.setCharacterSize(24);
    pressSpaceText.setFillColor(sf::Color::White);
    pressSpaceText.setString("Press space to start");
    pressSpaceText.setPosition(windowWidth / 2 - 165, windowHeight / 2);

    laserText.setFont(font);
    laserText.setCharacterSize(14);
    laserText.setFillColor(sf::Color::Red);
    laserText.setString("Lasers activated, press UP to shoot");
    laserText.setPosition(windowWidth - 420, windowHeight - 20);




    // Powerups
    sf::Texture powerupTexture;
    sf::Texture powerupTexture2;
    sf::Texture powerupTexture3;
    sf::Texture powerupTexture4;
    powerupTexture.setSmooth(true);
    powerupTexture2.setSmooth(true);
    powerupTexture3.setSmooth(true);
    powerupTexture4.setSmooth(true);

    // Powerup spawn
    if (!powerupTexture.loadFromFile("./images/coins/coin_01.png"))
    {
        // error...
    }
    // Load powerup texture2

    if (!powerupTexture2.loadFromFile("./images/coins/coin_04.png"))
    {
        // error...
    }
    if (!powerupTexture3.loadFromFile("./images/coins/coin_03.png"))
    {
        // error...
    }
    if (!powerupTexture4.loadFromFile("./images/coins/coin_05.png"))
    {
        // error...
    }

    std::map<int, sf::Texture> powerupTextures;
    powerupTextures[0] = powerupTexture;
    powerupTextures[1] = powerupTexture2;
    powerupTextures[2] = powerupTexture3;
    powerupTextures[3] = powerupTexture4;

    if (!ballTexture.loadFromFile("./images/ballBlue.png"))
    {
        // error...
    }




    Ball ball(windowWidth / 2, windowHeight / 2, ballTexture);
    balls.push_back(ball);

    Paddle paddle(windowWidth / 2, windowHeight - 50 );
	sf::Texture paddleTextureBlue;
    if (!paddleTextureBlue.loadFromFile("./images/paddleBlue.png"))
    {
		// error...
	}
    paddleTextureBlue.setSmooth(true);
    sf::Texture paddleTextureRed;
    if (!paddleTextureRed.loadFromFile("./images/paddleRed.png"))
    {
        // error...
    }
    paddleTextureRed.setSmooth(true);

    sf::Music music1;
    if (!music1.openFromFile("./sounds/backgroundMusic1.ogg"))
        return -1; // error
    music1.setLoop(true);
    music1.setVolume(40.f);

    sf::Music music2;
    if (!music2.openFromFile("./sounds/backgroundMusic2.wav"))
        return -1; // error
    music2.setLoop(true);
    music2.setVolume(40.f);

    sf::Music music3;
    if (!music3.openFromFile("./sounds/backgroundMusic3.ogg"))
        return -1; // error
    music3.setPitch(0.90f);
    music3.setLoop(true);
    music3.setVolume(40.f);

    // We will use an `std::vector` to contain any number
    // of `Brick` instances.
    std::vector<Brick> bricks;




    // Load brick texture only once
    sf::Texture texture;
    if (!texture.loadFromFile("./images/default_block.png"))
    {
        // print the error to console
    }
    texture.setSmooth(true);





    // Load life indicator texture
    sf::Texture lifeIndicatorTexture;
    lifeIndicatorTexture.setSmooth(true);

    if (!lifeIndicatorTexture.loadFromFile("./images/paddleRed.png"))
    {
        // error...
    }

    for (int i = 0; i < numberOfLives; ++i) {
        lifeIndicators.push_back(LifeIndicator(50 + i * 60, windowHeight - 10, lifeIndicatorTexture));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
            {
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up && lasersActivated) {
                    lasers.push_back(Laser(paddle.x(), paddle.y()));
                    // Play laser sound
                    if (!brickHitBuffer.loadFromFile("./sounds/laser.wav"))
                    {
						// error...
					}
                    brickHit.setBuffer(brickHitBuffer);
                    brickHit.setVolume(50);
                    brickHit.play();


                }
            }

			
        }

        if (lasersActivated) {
            //Show text in lower right corner that lasers are activated
            paddle.shape.setTexture(&paddleTextureRed);
            if (laserClock.getElapsedTime().asSeconds() > 4) {
                lasersActivated = false;
                
            }
        }
        else {
           paddle.shape.setTexture(&paddleTextureBlue);
        }

        window.clear(sf::Color(30, 41, 59));

        if (gameStopped) {
            float time = blinkClock.getElapsedTime().asSeconds();
            int alpha = 127.5f * (1 + sin(2 * 3.14159f * time / 2)); // 2 seconds period
            pressSpaceText.setFillColor(sf::Color(255, 255, 255, alpha));

			window.draw(pressSpaceText);    
            // Show level text above the space to start text
            levelText.setPosition(windowWidth / 2 - 20, windowHeight / 2 - 50);

            
        }
        else {
            levelText.setPosition(8, 8);
        }

        // New level
        if (bricks.empty()) {
            balls.clear();
            balls.push_back(Ball(windowWidth / 2, windowHeight / 2, ballTexture));
            paddle.reset();
            powerups.clear();
            lasers.clear();
            lasersActivated = false;

            changeMusic(music3, music1, music2);
			level++;
            gameStopped = true;
            
            // We fill vector with random number of bricks
            int numberOfBricksX = rand() % 7 + 4;
            int numberOfBricksY = rand() % 3 + 2;
            int padLeft = 0;
            if (numberOfBricksX < 11) {
                 padLeft = (11 - numberOfBricksX) / 2;
            }
            for (int iX{ 0 }; iX < numberOfBricksX + padLeft; ++iX)
                for (int iY{ 0 }; iY < numberOfBricksY; ++iY) {
                    Brick newBrick = Brick((iX + 1) * (Brick::blockWidth + 3) + 22, (iY + 2) * (Brick::blockHeight + 3), texture, 1);
                    if (iX < padLeft) {
						newBrick.destroyed = true;
					}
                    // Randomly destroy some bricks or set their hp to 2 or 3
                    int random = rand() % 100;
                    if (random < 12) {
						newBrick.destroyed = true;
					}
                    if (random > 12 && random < 30) {
                        newBrick.updateHp(2);
                    }
                    if (random > 30 && random < 42) {
						newBrick.updateHp(3);
					}
                    if (random > 42 && random < 48) {
                        newBrick.updateHp(4);
                    }
                    bricks.push_back(newBrick);
                }         
            

     }



        // Update paddle
        paddle.update();

        // Test if ball has gone out of bounds

        if (balls.empty()) {
			balls.push_back(Ball(windowWidth / 2, windowHeight / 2, ballTexture));
            powerups.clear();
			paddle.reset();
			numberOfLives--;
			lifeIndicators.pop_back();
            gameStopped = true;
            if (numberOfLives == 0) {
				// Game over
				// Show game over text
                sf::Text gameOverText;
                gameOverText.setFont(font);
                gameOverText.setCharacterSize(36);
                gameOverText.setFillColor(sf::Color::White);
                gameOverText.setString("Game Over");
                gameOverText.setPosition(windowWidth / 2 - 100, windowHeight / 2 - 50);
                levelText.setPosition(windowWidth / 2 - 20, windowHeight / 2);
                window.draw(levelText);
                scoreText.setPosition(windowWidth / 2 - 50, windowHeight / 2 + 30);
                
                window.draw(scoreText);
                window.draw(gameOverText);
                window.display();
                sf::sleep(sf::seconds(4));
                window.close();
			}
		}




        // Update ball
        for (Ball& ball : balls) {
			ball.update();
            // Let's test the collision every game loop iteration.
            testCollision(paddle, ball);
		}

        // Update lasers
        for (Laser& laser : lasers) {
            laser.update();
        }




        // Test collision for powerup
        for (auto& powerup : powerups) testCollision(powerup, paddle);

        // Tests collision for lasers
        for (auto& laser : lasers) {
            for (auto& brick : bricks) {
				testCollision(laser, brick);
			}
		}

        // We use another C++11 foreach loop to test collisions
        // between the ball and EVERY brick.
        for (auto& brick : bricks) {
            for (auto& ball : balls)
            testCollision(brick, ball, powerupTextures);
        }

        // And we use the "erase-remove idiom" to remove all `destroyed`
        // blocks from the block vector - using a cool C++11 lambda!
        bricks.erase(remove_if(begin(bricks), end(bricks),
            [](const Brick& mBrick)
            {
                return mBrick.destroyed;
            }),
            end(bricks));

        // Erase powerups that are out of bounds
        powerups.erase(std::remove_if(powerups.begin(), powerups.end(), [](const Powerup& p) {

            return p.destroyed;
            }), powerups.end());

        // Erase lasers that are destroyed
        lasers.erase(std::remove_if(lasers.begin(), lasers.end(), [](const Laser& l) {
			return l.destroyed;
			}), lasers.end());

        for (Ball& ball : balls) {
            if (ball.y() > windowHeight) {
                ball.destroyed = true;
                balls.erase(std::remove_if(balls.begin(), balls.end(), [](const Ball& b) {
					return b.destroyed;
					}), balls.end());
            }
        }            



        
        window.draw(paddle.shape);

        for (Ball& ball : balls) {
            window.draw(ball.shape);
        }

        for (auto& brick : bricks) window.draw(brick.shape);

        // Update particles
        for (Particle& p : particles) {
            p.update(2);
        }

        //Update powerups
        for (Powerup& powerup : powerups) {
			powerup.update();
		}

		// Draw particles
        for (const Particle& p : particles) {
			window.draw(p.shape);
		}

        //Draw powerups
        for (const Powerup& powerup : powerups) {
            window.draw(powerup.shape);
        }

        //Draw lasers
        for (const Laser& laser : lasers) {
			window.draw(laser.shape);
		}


        // Remove particles that are out of bounds
        particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& p) {
			return p.shape.getPosition().y > windowHeight;
			}), particles.end());
        particlesSize = particles.size();

        // Update score
        scoreText.setString("Score: " + std::to_string(score));
		window.draw(scoreText);
        // Update level
        levelText.setString("Level: " + std::to_string(level));
        window.draw(levelText);

        // Draw life indicators
        for (LifeIndicator& lifeIndicator : lifeIndicators) {
			window.draw(lifeIndicator.lifeIndicatorShape);
		}

        if (lasersActivated) {
            window.draw(laserText);
        }

        window.display();
    }

    return 0;
}