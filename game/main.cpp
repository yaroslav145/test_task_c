#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <ctime>


const int winW = 1000;
const int winH = 1000;
const int playerFeeldBotBorderHeight = 40;


using namespace std;


float dist(const sf::Vector2f& a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}


float dot(const sf::Vector2f& a,  const sf::Vector2f& b)
{
    return(a.x*b.x + a.y*b.y);
}


sf::Vector2f projV1toV2(const sf::Vector2f& a,  const sf::Vector2f& b)
{
    float len = dist(b);

    if(len == 0)
        len = 0.001;

    sf::Vector2f p = b*(dot(a, b) / (len*len)) ;

    return  p;
}


bool collideBallRect(sf::CircleShape& circ, const sf::RectangleShape& rect, sf::Vector2f& ballv)
{
    float vectx = circ.getPosition().x - rect.getPosition().x;
    float vecty = circ.getPosition().y - rect.getPosition().y;

    float wx = abs(vectx);
    float wy = abs(vecty);

    float distx = wx - rect.getSize().x/2;
    float disty = wy - rect.getSize().y/2;

    float inx = distx - circ.getRadius();
    float iny = disty - circ.getRadius();

    if((inx < 0) && (iny < 0))
    {
        if(disty < distx)
        {
            if(disty < 0)
            {
                if(vectx * ballv.x < 0)
                ballv.x *= -1;

                if(vectx > 0)
                {
                    circ.move(sf::Vector2f(-inx, 0));
                }
                else
                {
                    circ.move(sf::Vector2f(inx, 0));
                }

                return true;
            }
        }
        else
        {
            if(distx < 0)
            {
                if(vecty * ballv.y < 0)
                ballv.y *= -1;

                if(vecty > 0)
                {
                    circ.move(sf::Vector2f(0, -iny));
                }
                else
                {
                    circ.move(sf::Vector2f(0, iny));
                }

                return true;
            }
        }

        if(dist(sf::Vector2f(distx, disty)) < circ.getRadius())
        {
            sf::Vector2f temp;

            if(vectx < 0)
                distx *= -1;

            if(vecty < 0)
                disty *= -1;

            sf::Vector2f toCorner = sf::Vector2f(distx, disty);

            temp = projV1toV2(ballv, toCorner);

            if(dot(ballv, toCorner) <= 0)
            {
               ballv -= temp * 2.f;
            }
            else
            {
                circ.move(temp);
            }

            return true;
        }
    }

    return false;
}


bool collidePointRectangle(const sf::Vector2f& v, const sf::Vector2f& pos, const sf::Vector2f& size)
{
    sf::Vector2f temp = v - pos;

    if((abs(temp.x) - size.x < 0) && (abs(temp.y) - size.y < 0))
        return true;

    return false;
}


class Block {
    public:
        sf::RectangleShape rect;
        bool status;
        int hp;
        int scorePoints;

        Block(){}
        Block(sf::RectangleShape _rect, bool _status, int _hp, int _scorePoints) :
            rect(_rect), status(_status), hp(_hp), scorePoints(_scorePoints) {}

        void setBlockColorByHp()
        {
            if(hp == 1)
                rect.setFillColor(sf::Color::Green);

            if(hp == 2)
                rect.setFillColor(sf::Color::Yellow);

            if(hp == 3)
                rect.setFillColor(sf::Color::Red);

            if(hp == 4)
                rect.setFillColor(sf::Color::Blue);

            if(hp == 5)
                rect.setFillColor(sf::Color::Magenta);
        }
};


class Mouse
{
        sf::RenderWindow* window;
    public:
        bool cursorInWindow = false;
        bool leftButtonPresed = false;
        sf::Vector2f pos;


        void setWindow(sf::RenderWindow* window)
        {
            this->window = window;
        }


        void updateMousePosition()
        {
            if(cursorInWindow)
            {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
                pos = window->mapPixelToCoords(pixelPos);
            }
        }
};


class Platform
{
    public:
        float platformSpeed;
        sf::Vector2f platformSize;
        sf::RectangleShape rect;


        Platform()
        {
            setDefault();
        }


        void movePlatformLeft()
        {
            if(rect.getPosition().x - rect.getSize().x/2 > 0)
                rect.move(sf::Vector2f(-platformSpeed, 0));
        }


        void movePlatformRight()
        {
            if(rect.getPosition().x + rect.getSize().x/2 < winW)
                rect.move(sf::Vector2f(platformSpeed, 0));
        }


        void setDefault()
        {
            platformSpeed = 10;
            platformSize = sf::Vector2f(150, 15);
            rect.setSize(platformSize);
            rect.setFillColor(sf::Color::Blue);
            rect.setPosition(sf::Vector2f(winW/2, winH - platformSize.y - playerFeeldBotBorderHeight));
            rect.setOrigin(platformSize / 2.f);
        }
};


class Player
{
    public:
        int life;
        int score;
        int highScore;


        Player() : highScore(0)
        {
            setDefault();
        }

        void setDefault()
        {
            life = 3;
            score = 0;
        }
};


class Ball
{
    public:
        float ballRadius;
        sf::Vector2f ballvector;
        sf::CircleShape circ;
        sf::Vector2f ballvectorStart;
        int damage;


    Ball()
    {
        setDefault();
        ballvectorStart = sf::Vector2f(3, -9);
    }


    void updateBall()
    {
        circ.move(ballvector);
    }


    void setDefault()
    {
        ballRadius = 10;
        ballvector = sf::Vector2f(0, 0);
        circ.setRadius(ballRadius);
        circ.setFillColor(sf::Color::Red);
        circ.setPosition(sf::Vector2f(winW/2, winH - playerFeeldBotBorderHeight - 30 - ballRadius));
        circ.setOrigin(sf::Vector2f(ballRadius, ballRadius));
        damage = 100;
    }


    void startBall()
    {
        if(ballvector == sf::Vector2f(0, 0))
            ballvector = ballvectorStart;
    }
};


class Font
{
    public:
        sf::Font f;

        Font()
        {
            f.loadFromFile("arial.ttf");
        }
}font;


class Text
{
    public:
        sf::Text text;
        int defaultSize = 60;

        Text()
        {
            text.setFont(font.f);
            text.setCharacterSize(defaultSize);
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);
        }


        void setTextOriginByK(float kw, float kh)
        {
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width * kw,
                            textRect.top  + textRect.height * kh);
        }


        bool collidePointText(const sf::Vector2f& point)
        {
            return collidePointRectangle(point, text.getPosition(),
                    sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height));
        }


        void increaseAndRepaint()
        {
            text.setFillColor(sf::Color::Red);
            text.setCharacterSize(defaultSize + 20);
            setTextOriginByK(0.5, 0.5);
        }

        void setDefault()
        {
            text.setCharacterSize(defaultSize);
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);
            setTextOriginByK(0.5, 0.5);
        }
};


class Level
{
    int cols;
    int rows;
    float intervalW;
    float intervalH;
    float blockH;
    float blockW;

    public:
        vector<Block> block;
        vector<Text> bonuses;

        int current;

        Level()
        {
            setDefault();
        }


        void setDefault()
        {
            current = 1;
            cols = 12;
            rows = 10;
            intervalW = 10;
            intervalH = 15;
            blockW = winW/cols - intervalW;
            blockH = (winH*0.5)/rows - intervalH;
        }


        void createBonus(const sf::Vector2f& pos)
        {
            bonuses.push_back(Text());

            int choice = rand()%7;

            if(choice == 0)
                bonuses.back().text.setString("P+");

            if(choice == 1)
                bonuses.back().text.setString("P-");

            if(choice == 2)
                bonuses.back().text.setString("R+");

            if(choice == 3)
                bonuses.back().text.setString("R-");

            if(choice == 4)
                bonuses.back().text.setString("S+");

            if(choice == 5)
                bonuses.back().text.setString("S-");

            if(choice == 6)
                bonuses.back().text.setString("L+");

            bonuses.back().text.setPosition(pos);
            bonuses.back().setTextOriginByK(0.5, 0.5);
            bonuses.back().text.setFillColor(sf::Color(255, 0, 238));
            bonuses.back().text.setCharacterSize(30);
        }


        void initBlocks()
        {
            Block temp;
            block.clear();
            bonuses.clear();

            for(int i = 0; i < rows; ++i)
            {
                for(int j = 0; j < cols; ++j)
                {
                    temp.rect.setPosition(sf::Vector2f((intervalW + blockW)/2 + j*(intervalW + blockW), 100 + blockH/2 + i*(intervalH + blockH)));
                    temp.rect.setOrigin(sf::Vector2f(blockW, blockH) / 2.f);
                    temp.rect.setSize(sf::Vector2f(blockW, blockH));
                    temp.status = true;
                    temp.hp = 1;
                    temp.scorePoints = temp.hp;
                    temp.setBlockColorByHp();
                    block.push_back(temp);
                }
            }


            if(current == 1)
            {
                for(int i = 0; i < block.size(); ++i)
                {
                    if(dist(sf::Vector2f(block.at(i).rect.getPosition().x - winW/2, block.at(i).rect.getPosition().y - winH/2)) > 410)
                        block.at(i).status = false;

                    if(abs(block.at(i).rect.getPosition().x - winW/2) > 350)
                    {
                        block.at(i).hp = 2;
                        block.at(i).setBlockColorByHp();
                        block.at(i).scorePoints = 2;
                    }
                }
            }


            if(current == 2)
            {
                for(int i = 0; i < cols; ++i)
                {
                    block.at((rows - 1) * cols + i).hp = 5;
                    block.at((rows - 1) * cols + i).setBlockColorByHp();
                    block.at((rows - 1) * cols + i).scorePoints = 5;

                    block.at((rows/2) * cols + i).hp = 2;
                    block.at((rows/2) * cols + i).setBlockColorByHp();
                    block.at((rows/2) * cols + i).scorePoints = 2;

                    block.at((rows/2 - 1) * cols + i).hp = 3;
                    block.at((rows/2 - 1) * cols + i).setBlockColorByHp();
                    block.at((rows/2 - 1) * cols + i).scorePoints = 3;
                }
            }
        }


        bool checkLevelComplete()
        {
            for(vector<Block>::iterator it = block.begin(); it != block.end(); it++)
            {
                if(it->status == true)
                    return false;
            }

            return true;
        }
};


class Keyboard
{
    public:
        bool left;
        bool right;
        bool space;

        Keyboard() : left(0), right(0), space(0) {}
};


class Scene
{
    public:
        sf::RenderWindow window;
        Platform platform;
        Ball ball;
        Mouse mouse;
        Player player;
        Level level;
        Keyboard keyboard;

        int currentScene;

        Text buttonStart;
        Text buttonExit;
        Text highscore;
        Text score;
        Text life;
        Text levelLabel;

        Scene()
        {
            window.create(sf::VideoMode(winW, winH, sf::Style::Resize), "Game");
            window.setSize(sf::Vector2u(800, 800));
            window.setFramerateLimit(60);
            mouse.setWindow(&window);
            srand(unsigned(time(0)));
            setCurrentScene(0);
        }


        void initNewLevel()
        {
            ball.setDefault();
            platform.setDefault();

            level.initBlocks();
        }


        void setCurrentScene(int num)
        {
            if(num == 0)
            {
                currentScene = 0;
                buttonStart.text.setString("Start");
                buttonStart.text.setPosition(sf::Vector2f(winW/2, winH*1/4));
                buttonStart.setTextOriginByK(0.5, 0.5);
                buttonStart.text.setFillColor(sf::Color::White);
                buttonExit.text.setString("Exit");
                buttonExit.text.setPosition(sf::Vector2f(winW/2, winH*3/5));
                buttonExit.setTextOriginByK(0.5, 0.5);
                highscore.text.setPosition(sf::Vector2f(winW/2, winH*0.9));
            }

            if(num == 1)
            {
                currentScene = 1;
                score.text.setPosition(sf::Vector2f(0, winH));
                score.text.setCharacterSize(40);
                life.text.setPosition(sf::Vector2f(winW/2, winH));
                life.text.setCharacterSize(40);
                levelLabel.text.setPosition(sf::Vector2f(winW, winH));
                levelLabel.text.setCharacterSize(40);

                player.setDefault();
                level.setDefault();

                initNewLevel();
            }

            if(num == 2)
            {
                currentScene = 2;
            }
        }


        void decrementLife()
        {
            ball.setDefault();
            platform.setDefault();
            player.life--;

            if(player.life <= 0)
            {
                setCurrentScene(2);

                if(player.score > player.highScore)
                    player.highScore = player.score;
            }

        }


        void collisionWall()
        {
            if(ball.circ.getPosition().x - ball.circ.getRadius() < 0)
                ball.ballvector.x *= -1;

            if(ball.circ.getPosition().x + ball.circ.getRadius() > winW)
                ball.ballvector.x *= -1;

            if(ball.circ.getPosition().y - ball.circ.getRadius() < 0)
                ball.ballvector.y *= -1;

            if(ball.circ.getPosition().y + ball.circ.getRadius() > winH - playerFeeldBotBorderHeight)
                decrementLife();
        }


        sf::String intToString(int num)
        {
            ostringstream os;
            os << num;
            return os.str();
        }


        void updateHighscoreString()
        {
            highscore.text.setString("Highscore: " + intToString(player.highScore));
            highscore.setTextOriginByK(0.5, 0.5);
        }


        void updateScoreString()
        {
            score.text.setString("Score: " + intToString(player.score));
            score.setTextOriginByK(0, 1);
            life.text.setCharacterSize(40);
        }


        void updateLifeString()
        {
            life.text.setString("Life: " + intToString(player.life));
            life.setTextOriginByK(0.5, 1);
        }


        void updateLevelString()
        {
            levelLabel.text.setString("Level: " + intToString(level.current) + " ");
            levelLabel.setTextOriginByK(1, 1);
        }



        void drawBlocks()
        {
            for(vector<Block>::iterator it = level.block.begin(); it != level.block.end(); it++)
            {
                if(it->status == true)
                    window.draw(it->rect);
            }
        }


        void drawBonuses()
        {
            for(vector<Text>::iterator it = level.bonuses.begin(); it != level.bonuses.end(); it++)
            {
                window.draw(it->text);
            }
        }


        void updateBonuses()
        {
            for(vector<Text>::iterator it = level.bonuses.begin(); it != level.bonuses.end(); it++)
            {
                it->text.setPosition(sf::Vector2f(it->text.getPosition().x, it->text.getPosition().y + 4));

                if(it->text.getPosition().y > winH - playerFeeldBotBorderHeight)
                {
                    level.bonuses.erase(it);
                    break;
                }

                if(abs(it->text.getPosition().x - platform.rect.getPosition().x) -  platform.rect.getSize().x / 2 < 0)
                    if(abs(it->text.getPosition().y - platform.rect.getPosition().y) -  (platform.rect.getSize().y) / 2 < 0)
                {
                    if(it->text.getString() == "P+")
                    {
                        if(platform.rect.getSize().x <= 300)
                        {
                            platform.rect.setSize(sf::Vector2f(platform.rect.getSize().x + 50, platform.rect.getSize().y));
                            platform.rect.setOrigin(platform.rect.getSize()/2.f);
                        }
                    }

                    if(it->text.getString() == "P-")
                    {
                        if(platform.rect.getSize().x >= 100)
                        {
                            platform.rect.setSize(sf::Vector2f(platform.rect.getSize().x - 50, platform.rect.getSize().y));
                            platform.rect.setOrigin(platform.rect.getSize()/2.f);
                        }
                    }

                    if(it->text.getString() == "R+")
                    {
                        if(ball.circ.getRadius() <= 30)
                        {
                            ball.circ.setRadius(ball.circ.getRadius() * 1.2f);
                            ball.circ.setOrigin(sf::Vector2f(ball.circ.getRadius(), ball.circ.getRadius()));
                        }
                    }

                    if(it->text.getString() == "R-")
                    {
                        if(ball.circ.getRadius() >= 8)
                        {
                            ball.circ.setRadius(ball.circ.getRadius() / 1.2f);
                            ball.circ.setOrigin(sf::Vector2f(ball.circ.getRadius(), ball.circ.getRadius()));
                        }
                    }

                    if(it->text.getString() == "S+")
                    {
                        platform.platformSpeed *= 1.5f;
                    }

                    if(it->text.getString() == "S-")
                    {
                        platform.platformSpeed /= 1.5f;
                    }

                    if(it->text.getString() == "L+")
                    {
                        player.life++;
                    }

                    level.bonuses.erase(it);
                    break;
                }
            }
        }



        void drawGame()
        {
            window.clear();

            window.draw(platform.rect);
            window.draw(ball.circ);
            drawBlocks();
            window.draw(score.text);
            window.draw(life.text);
            window.draw(levelLabel.text);
            drawBonuses();

            window.display();
        }


        void drawMenu()
        {
            window.clear();

            window.draw(buttonStart.text);
            window.draw(buttonExit.text);
            window.draw(highscore.text);

            window.display();
        }


        void updateEvents()
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    window.close();
                    break;
                }


                if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                        break;
                    }

                    if(event.key.code == sf::Keyboard::Space)
                    {
                        keyboard.space = true;
                    }


                    if((event.key.code == sf::Keyboard::Left) ||  (event.key.code == sf::Keyboard::A))
                    {
                        keyboard.left = true;
                    }


                    if((event.key.code == sf::Keyboard::Right) ||  (event.key.code == sf::Keyboard::D))
                    {
                        keyboard.right = true;
                    }
                }


                if(event.type == sf::Event::KeyReleased)
                {
                    if(event.key.code == sf::Keyboard::Space)
                    {
                        keyboard.space = false;
                    }


                    if((event.key.code == sf::Keyboard::Left) ||  (event.key.code == sf::Keyboard::A))
                    {
                        keyboard.left = false;
                    }


                    if((event.key.code == sf::Keyboard::Right) ||  (event.key.code == sf::Keyboard::D))
                    {
                        keyboard.right = false;
                    }
                }


                if(event.type == sf::Event::MouseEntered)
                {
                    mouse.cursorInWindow = true;
                    break;
                }


                if(event.type == sf::Event::MouseLeft)
                {
                    mouse.cursorInWindow = false;
                    break;
                }


                if(event.type == sf::Event::MouseMoved)
                {
                    mouse.updateMousePosition();
                    break;
                }


                if(event.type == sf::Event::MouseButtonPressed)
                {
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        mouse.leftButtonPresed = true;
                    }

                    break;
                }


                if(event.type == sf::Event::MouseButtonReleased)
                {
                    mouse.leftButtonPresed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
                }
            }
        }


        void platformControlKeyboard()
        {
            if(mouse.cursorInWindow == false)
            {
                if(keyboard.left)
                    platform.movePlatformLeft();


                if(keyboard.right)
                    platform.movePlatformRight();
            }
        }


        void platformControlMouse()
        {
            if(mouse.cursorInWindow == true)
            {
                if(platform.rect.getPosition().x > mouse.pos.x)
                    platform.movePlatformLeft();

                if(platform.rect.getPosition().x < mouse.pos.x)
                    platform.movePlatformRight();
            }
        }


        void updateStartBall()
        {
            if(ball.ballvector == sf::Vector2f(0,0))
            {
                ball.circ.setPosition(sf::Vector2f(platform.rect.getPosition().x, ball.circ.getPosition().y));

                if(keyboard.space == true)
                    if(currentScene == 1)
                        ball.startBall();
            }
        }


        void collisionButtonsAndCursor()
        {
            if(buttonStart.collidePointText(mouse.pos))
            {
                buttonStart.increaseAndRepaint();

                if(mouse.leftButtonPresed)
                {
                    setCurrentScene(1);
                }
            }
            else
            {
                buttonStart.setDefault();
            }


            if(buttonExit.collidePointText(mouse.pos))
            {
                buttonExit.increaseAndRepaint();

                if(mouse.leftButtonPresed)
                {
                    window.close();
                }
            }
            else
            {
                buttonExit.setDefault();
            }
        }


        void updateLevelComplete()
        {
            if(!level.checkLevelComplete())
                return;

            level.current++;

            initNewLevel();
        }



        void collideBlocksAndBall()
        {
            collideBallRect(ball.circ, platform.rect, ball.ballvector);

            for(vector<Block>::iterator it = level.block.begin(); it != level.block.end(); it++)
            {
                if(it->status == true)
                {
                    if(collideBallRect(ball.circ, it->rect, ball.ballvector))
                    {
                        player.score += it->scorePoints;

                        it->hp--;
                        it->scorePoints = it->hp;
                        if(it->hp <= 0)
                        {
                            it->status = false;

                            if(rand()%10 == 0)
                                level.createBonus(it->rect.getPosition());
                        }
                        it->setBlockColorByHp();
                    }
                }
            }
        }



        void drawGameOver()
        {
            window.clear();

            window.draw(score.text);
            window.draw(highscore.text);

            window.display();
        }


        void updateGameOver()
        {
            updateHighscoreString();
            score.text.setString("Score: " + intToString(player.score));
            score.setTextOriginByK(0.5, 0.5);
            score.text.setPosition(sf::Vector2f(winW/2, winH/2));
            score.text.setCharacterSize(60);

            if(mouse.leftButtonPresed)
            {
                setCurrentScene(0);
                mouse.leftButtonPresed = 0;
            }

        }
};



int main()
{
    Scene scene;

    while(scene.window.isOpen())
    {
        scene.updateEvents();

        if(scene.currentScene == 0)
        {
            scene.updateHighscoreString();
            scene.collisionButtonsAndCursor();
            scene.drawMenu();
        }

        if(scene.currentScene == 1)
        {
            scene.platformControlMouse();
            scene.platformControlKeyboard();
            scene.updateStartBall();
            scene.ball.updateBall();
            scene.collisionWall();
            scene.collideBlocksAndBall();
            scene.updateLevelComplete();
            scene.updateScoreString();
            scene.updateLifeString();
            scene.updateLevelString();
            scene.updateBonuses();
            scene.drawGame();
        }

        if(scene.currentScene == 2)
        {
            scene.updateGameOver();
            scene.drawGameOver();
        }
    }

    return 0;
}
