#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;
bool show_game_over(RenderWindow& window);
int N = 53, M = 30;
int size;                                                                  //dimension of each cell

float timer = 1, delay = 0.1;                                              // delay , delays event timing
int dir, snakeSize = 2, score = 0, highestScore = 0;
bool gameOver = false;
bool show_main_menu = true;
struct Snake {
    int x, y;
};

struct Fruit {
    int x, y;
};

Snake s[100];

Fruit f;
  
void update()                                               //updates the movement of snake and checks for collision
{
    for (int i = snakeSize; i > 0; --i) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    if (dir == 0) s[0].y += 1;
    if (dir == 1) s[0].x -= 1;
    if (dir == 2) s[0].x += 1;
    if (dir == 3) s[0].y -= 1;

    if (s[0].x >= N || s[0].x < 0 || s[0].y >= M || s[0].y < 0) {
        gameOver = true;
        return;
    }

    for (int i = 1; i < snakeSize; i++) {
        if (s[0].x == s[i].x && s[0].y == s[i].y) {
            gameOver = true;
            return;
        }
    }
}


int main() {
    srand(time(0));                                                      // seed rand is with time that it randomizes time               

    int screenWidth = 1280;
    int screenHeight = 720;
    size = screenWidth / N;                          // determining grid size;


    RenderWindow window(VideoMode(screenWidth, screenHeight), "Snake Game!");

    Texture t1, t2, t3;                    //declaring textures and loading it form file
    t1.loadFromFile("white.png"); 
    t2.loadFromFile("purple.png");
    t3.loadFromFile("green.png");

    //Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);

    //sprite1.setScale((float)size / t1.getSize().x + 100, (float)size / t1.getSize().y);
    sprite2.setScale((float)size / t2.getSize().x, (float)size / t2.getSize().y);
    sprite3.setScale((float)size / t3.getSize().x, (float)size / t3.getSize().y);


    Font font;
    font.loadFromFile("font.ttf");

    Text scoreText, HighestScoreText;
    scoreText.setFont(font);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(400, 10);
    scoreText.setCharacterSize(30);
    scoreText.setString("Current Score: 0");

    HighestScoreText.setFont(font);
    HighestScoreText.setFillColor(Color::Black);
    HighestScoreText.setPosition(800, 10);
    HighestScoreText.setCharacterSize(30);
    HighestScoreText.setString("Highest Score: 0");

    Clock clock;

    f.x = rand() % (N);
    f.y = rand() % (M);

    Music music, beep;                     //declaring and intializing music and beep sound
    music.openFromFile("music.ogg"); 
    beep.openFromFile("beep.ogg");
    music.setLoop(true);
    music.setVolume(100);
    beep.setVolume(100);
    music.play();

    while (window.isOpen()) {                          //game loop is started when window is open()
        music.setVolume(100);
        //..........
        if (gameOver) {                                //when the player has lost
            music.setVolume(0);
            if (!show_game_over(window))               //calls the funtion to check if the game should restart or exited
                break;
            else {
                snakeSize = 2;
                score = 0;
                delay = 0.1;
                dir = 0;
                gameOver = false;                              //it resets all variable except highscore
                for (int i = 0; i < 100; ++i) {
                    s[i] = { 0, 0 };
                }
                s[0] = { N / 2, M / 2 };
                f.x = rand() % (N);
                f.y = rand() % (M);
           
            }
        }

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
           if (e.type == Event::Closed) window.close();
        }

        if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && dir != 2) dir = 1;
        if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && dir != 1) dir = 2;
        if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && dir != 0) dir = 3;
        if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && dir != 3) dir = 0;


        if (timer > delay) {                                                                  //condition for updating the function
            timer = 0;
            update();
        }

        scoreText.setString("Current Score: " + std::to_string(score));                      //set string updates string
        HighestScoreText.setString("Highest Score: " + std::to_string(highestScore));        //to string converts scores ( int ) into string

        if ((s[0].x == f.x) && (s[0].y == f.y)) {                                            //when the snake eats up the fruit
            beep.play();
            snakeSize++;
            score++;
            if (score > highestScore) highestScore = score;
            if (score % 3 == 0 && score != 0) delay -= 0.01;
            f.x = rand() % (N);
            f.y = rand() % (M);
        }

        window.clear(Color::White);                                                          //the backgroud will be clear 
          
        /* 
         for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                sprite1.setPosition(i*size, j* size);                                        //other way for giving up textures on screen
                window.draw(sprite1);
            }
        }*/
         
        for (int i = 0; i < snakeSize; i++)                                                  //sets position of sprite2 , which is for snake
        {
            sprite2.setPosition(s[i].x * size, s[i].y * size);
            window.draw(sprite2);
        }

        sprite3.setPosition(f.x * size, f.y * size);                                           //sets position for sprite3 , which is for fruit
        window.draw(sprite3);

        window.draw(scoreText);
        window.draw(HighestScoreText);

        window.display();
    }
    return 0;
}
