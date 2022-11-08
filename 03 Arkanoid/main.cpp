#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include<string>
using namespace sf;
using namespace std;
int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(620, 550), "Arkanoid!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3, t4, t5;

    t1.loadFromFile("images/block02.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");
    t5.loadFromFile("images/block03.png");

    Font fon;
    fon.loadFromFile("Avara.otf");
    Text text1, scr;
    text1.setFont(fon);
    text1.setString("Game Over!");
    text1.setCharacterSize(50);
    text1.setFillColor(Color(1000, 1000, 1000));
    text1.setStyle(Text::Bold);
    text1.setPosition(100, 150);

    scr.setFont(fon);
    scr.setString("Score");
    scr.setCharacterSize(20);
    scr.setFillColor(Color(0, 0, 0));
    scr.setStyle(Text::Bold);
    scr.setPosition(10, 10);

    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sBackground.scale(0.3, 0.3);
    sBall.scale(1.5, 1.5);

    sPaddle.scale(1.5, 1.5);
    sPaddle.setPosition(300, 520);

    Sprite block[201];

    int n = 0, f = 0, k = 1, cnt = 0;
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 12; j++) {
            if (f)   block[n].setTexture(t1);
            else block[n].setTexture(t5);
            block[n].setPosition(j * 45, (i + 1) * 25);   // fill row by row
            n++;
        }
        f = !f;
    }

    float dx = 8, dy = 8;
    float x = 300, y = 500;


    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        //moving ball
        x += dx;
        y += dy;

        for (int i = 0; i < n; i++)
            if (FloatRect(x, y, 12, 12).intersects(block[i].getGlobalBounds())) {
                block[i].setPosition(0, 600);
                cnt++;
                dx = -dx;
                dy = ((rand() % 4) + k);
            }


        if (x < 0 || x>610)  dx = -dx;
        if (y < 0)  dy = -dy;


        //moving the paddle
        if (Keyboard::isKeyPressed(Keyboard::Right)) if (sPaddle.getPosition().x < 490)sPaddle.move(11, 0);
        if (Keyboard::isKeyPressed(Keyboard::Left))  if (sPaddle.getPosition().x > 5)sPaddle.move(-11, 0);
        if (Keyboard::isKeyPressed(Keyboard::R)) {
            cnt = 0, y = 310, x = 300;
            sPaddle.setPosition(300, 540);
            int x = 0;
            for (int i = 1; i <= 10; i++) {
                for (int j = 1; j <= 12; j++) {
                    if (f)   block[x].setTexture(t1);
                    else block[x].setTexture(t5);
                    block[x].setPosition(j * 45, (i + 1) * 25);   // fill row by row
                    x++;
                }
                f = !f;
            }

        }
        //move the ball with a random movment
        if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) dy = -((rand() % 4) + k), k += 0.5;

        //update position of the ball
        sBall.setPosition(x, y);

        app.clear();

        //display
        app.draw(sBackground);

        if (y > 550) {
            text1.setString("Game Over\n your score is " + to_string(cnt) + "\nClick R to Repeat");
            text1.setFillColor(Color(255, 0, 0));
            app.draw(text1);

        }
        else if (cnt == n) {
            text1.setString("    You Won\n your score is " + to_string(cnt) + "\nClick R to Repeat");
            text1.setFillColor(Color(0, 255, 0));
            app.draw(text1);
            y = 540;

        }
        else {
            for (int i = 0; i < n; i++)
                app.draw(block[i]);

            scr.setString("Score: " + to_string(cnt));
            app.draw(sPaddle);
            app.draw(sBall);
            app.draw(scr);

        }


        app.display();
    }

    return 0;
}
