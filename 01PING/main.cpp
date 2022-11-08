#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
int main()
{

    double x=10,y=250,xx=455,yy=250,speed=5,speed2=5,speed3=5,speed4=0;
    double xxx=250,yyy=250,f=0;

    RenderWindow mywindow(VideoMode(500,500),"my Game");
    mywindow.setFramerateLimit(100);

    Texture img;
    img.loadFromFile("./images/img.jpg");

    RectangleShape wallpaper(Vector2f(500,500));
    wallpaper.setPosition(0,0);
    wallpaper.setTexture(&img);

    RectangleShape rec1(Vector2f(30,120));
    rec1.setFillColor(Color(0,0,100));
    rec1.setPosition(x,y);

    RectangleShape rec2(Vector2f(30,120));
    rec2.setFillColor(Color(500,0,0));
    rec2.setPosition(xx,yy);

    CircleShape cshape(100);
    cshape.setPosition(mywindow.getSize().x/2,mywindow.getSize().y/2);
    cshape.setRadius(15);
    cshape.setFillColor(Color(0,255,0));
    cshape.setOrigin(50,50);

    srand(time(0));
    while(mywindow.isOpen()){
        Event ev;
        while(mywindow.pollEvent(ev)){
            if(ev.type==Event::Closed) mywindow.close();

        }
        //rec1
        if(y<10 ||y>(mywindow.getSize().y)-130 )speed*=-1;
        if(y<10 && f)speed+=0.1;

        y+=speed;

        //rec2
        if(Keyboard::isKeyPressed(Keyboard::Up)){
            if(yy>=10)yy-=speed2;

        }
        if(Keyboard::isKeyPressed(Keyboard::Down)){
            if(yy<(mywindow.getSize().y)-130 )yy+=speed2;

        }

        //Circle
        if(xxx<30 || xxx>(mywindow.getSize().x))speed3*=-1,speed4*=-1;

        xxx+=speed3;
        yyy+=speed4;



        //intersection
        if(cshape.getGlobalBounds().intersects(rec1.getGlobalBounds())){
            speed3*=-1;
            xxx+=2*speed3;
            speed4=(rand()%3)*(speed4<0?1:-1);

        }
        if(cshape.getGlobalBounds().intersects(rec2.getGlobalBounds())){
            speed3*=-1;
            xxx+=2*speed3;
            speed4*=-1;
            f=1;
        }

        //Update the position
        rec1.setPosition(x,y);
        rec2.setPosition(xx,yy);
        cshape.setPosition(xxx,yyy);

        //Draw
        mywindow.clear();
        mywindow.draw(wallpaper);
        mywindow.draw(rec1);
        mywindow.draw(rec2);
        mywindow.draw(cshape);
        mywindow.display();

    };



    return EXIT_SUCCESS;
}
