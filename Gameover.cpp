#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
using namespace std;
using namespace sf;

bool show_game_over(RenderWindow& window)
{
	RectangleShape gameoverbox(Vector2f(500, 300));          //game over box size intialization
	gameoverbox.setPosition(150, 120);
	gameoverbox.setFillColor(Color::Transparent);

	Font font;
	if (!font.loadFromFile("font.ttf"))
		cout << "Failed to load font file";
	Text gameovertext;
	gameovertext.setFont(font);
	gameovertext.setFillColor(Color::Black);
	gameovertext.setString("\t\t\t\tGAME OVER!\nPRESS SPACE TO RESTART\n\t\tPRESS ESC TO EXIT");
	gameovertext.setCharacterSize(80);
	gameovertext.setPosition(220, 210);

	Music music;
	if (!music.openFromFile("music.ogg"))
		cout << "Failed to load music";
	music.setLoop(true);
	music.setVolume(100);
	music.play();
	while (window.isOpen())
	{
		Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == Event::Closed) {
				window.close();
			}
			else if (evnt.type == Event::KeyPressed) {
				if (evnt.key.code == Keyboard::Space) {                //when space is pressed it returns true value to main function and restarts 
					cout << "Restarting..." << endl;
					return true;
				}
				else if (evnt.key.code == Keyboard::Escape) {          //when escape is pressed it returns false to main function and exits
					cout << "Exiting..." << endl;
					return false;
				}
			}
		}
		window.clear(Color::White);
		window.draw(gameoverbox);
		window.draw(gameovertext);
		window.display();
	}
	return false;
}

