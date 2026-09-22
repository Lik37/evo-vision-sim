// g++ learn.cpp -o learn -lsfml-system -lsfml-window
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <thread> 

#include <vector>
#include <optional>
#include <cstdint>

using namespace std;


namespace sys
{
    void angle() {
        sf::Angle angle1 = sf::degrees(90);
        sf::Angle angle2 = sf::radians(3.14f);

        cout << sf::degrees(540).wrapUnsigned().asRadians() << '\n';
    }

    void time() {
        sf::Time time1 = sf::seconds(1);
        sf::Time time2 = sf::milliseconds(1'000);
        sf::Time time3 = sf::microseconds(1'000'000);

        cout << time1.asMilliseconds() << ' ' << (time1.asMilliseconds() == time3.asMilliseconds()) << '\n';

        sf::Clock clock;
        cout << "Time0: " << clock.restart().asSeconds() << "\n";

        cout << "passed0 " << clock.getElapsedTime().asSeconds() << " sec\n";
        std:chrono::duration sleepTime = std::chrono::seconds(1);
        std::this_thread::sleep_for(sleepTime);
        cout << "passed1 " << clock.getElapsedTime().asSeconds() << " sec\n";
        clock.stop();
        std::this_thread::sleep_for(sleepTime);
        cout << "passedStop " << clock.getElapsedTime().asSeconds() << " sec\n";
        clock.start();
        std::this_thread::sleep_for(sleepTime);
        cout << "passedStart " << clock.getElapsedTime().asSeconds() << " sec\n";

    }
};


namespace windowAndEvents
{
    void simple() {
        sf::Window window; //(sf::VideoMode({800, 600}), "SFML window");
        window.create(sf::VideoMode({800, 600}), "SFML window");
        
        window.setKeyRepeatEnabled(false); // важно

        window.setPosition({0, 0});
        window.setSize({400, 400});
        window.setTitle("ABUNGA");
        
        sf::Vector2u size = window.getSize();
        auto [windowWidth, windowHeight] = size;
        bool focus = window.hasFocus();

        window.setVerticalSyncEnabled(true); //window.setFramerateLimit(60);

        
        while (window.isOpen()) {

            while (std::optional event = window.pollEvent()) {
                
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                } 
                else if (event->is<sf::Event::FocusLost>())
                {
                    cout << "бе\n";
                }
                else if (event->is<sf::Event::FocusGained>()) 
                {
                    cout << "hello\n";
                }
                else if (const auto* resized = event->getIf<sf::Event::Resized>())
                {
                    cout << "new size: " << resized->size.x << " " << resized->size.y << "\n";
                }
                else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) 
                {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                        window.close();
                        std::cout << "the escape key was pressed" << std::endl;
                        std::cout << "scancode: " << static_cast<int>(keyPressed->scancode) << std::endl;
                        std::cout << "code: " << static_cast<int>(keyPressed->code) << std::endl;
                        std::cout << "control: " << keyPressed->control << std::endl;
                        std::cout << "alt: " << keyPressed->alt << std::endl;
                        std::cout << "shift: " << keyPressed->shift << std::endl;
                        std::cout << "system: " << keyPressed->system << std::endl;
                        std::cout << "description: " << sf::Keyboard::getDescription(keyPressed->scancode).toAnsiString() << std::endl;
                        std::cout << "localize: " << static_cast<int>(sf::Keyboard::localize(keyPressed->scancode)) << std::endl;
                        std::cout << "delocalize: " << static_cast<int>(sf::Keyboard::delocalize(keyPressed->code)) << std::endl;
                    }
                }
                else if (const auto* textEntered = event->getIf<sf::Event::TextEntered>())
                {
                    if (textEntered->unicode < 128)
                        cout << "ASCII character typed " << static_cast<char>(textEntered->unicode) << "\n";
                }

                else if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
                {
                    switch (mouseWheelScrolled->wheel)
                    {
                        case sf::Mouse::Wheel::Vertical:
                            std::cout << "wheel type: vertical" << std::endl;
                            break;
                        case sf::Mouse::Wheel::Horizontal:
                            std::cout << "wheel type: horizontal" << std::endl;
                            break;
                    }
                    std::cout << "wheel movement: " << mouseWheelScrolled->delta << std::endl;
                    std::cout << "mouse x: " << mouseWheelScrolled->position.x << std::endl;
                    std::cout << "mouse y: " << mouseWheelScrolled->position.y << std::endl;
                }
                else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    std::cout << "the mouse button was pressed" << std::endl;
                    std::cout << "button: ";
                    switch (mouseButtonPressed->button)
                    {
                        case sf::Mouse::Button::Left:
                            std::cout << "Left\n";
                            break;
                        case sf::Mouse::Button::Right:
                            std::cout << "Right\n";
                            break;
                        case sf::Mouse::Button::Middle:
                            std::cout << "Middle\n";
                            break;
                        case sf::Mouse::Button::Extra1:
                            std::cout << "Extra1\n";
                            break;
                        case sf::Mouse::Button::Extra2:
                            std::cout << "Extra2\n";
                            break;
                    }
                    std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
                    std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;
                }
                else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonReleased>())
                {
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                    {
                        std::cout << "the right button was released" << std::endl;
                        std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
                        std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;
                    }
                }
                // else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
                // {
                //     std::cout << "new mouse x: " << mouseMoved->position.x << std::endl;
                //     std::cout << "new mouse y: " << mouseMoved->position.y << std::endl;
                // }
                // else if (const auto* mouseMovedRaw = event->getIf<sf::Event::MouseMovedRaw>())
                // {
                //     std::cout << "new mouse x: " << mouseMovedRaw->delta.x << std::endl;
                //     std::cout << "new mouse y: " << mouseMovedRaw->delta.y << std::endl;
                // }
                else if (event->is<sf::Event::MouseEntered>())
                    std::cout << "the mouse cursor has entered the window" << std::endl;
                else if (event->is<sf::Event::MouseLeft>())
                    std::cout << "the mouse cursor has left the window" << std::endl;
            }
        }
    }
};


namespace keyboard
{
    void simple() {
        sf::Window window; //(sf::VideoMode({800, 600}), "SFML window");
        window.create(sf::VideoMode({800, 600}), "SFML window");
        
        window.setKeyRepeatEnabled(false); // важно

        window.setVerticalSyncEnabled(true); //window.setFramerateLimit(60);


        // get the global mouse position (relative to the desktop)
        sf::Vector2i globalPosition = sf::Mouse::getPosition();
        // get the local mouse position (relative to a window)
        sf::Vector2i localPosition = sf::Mouse::getPosition(window); // window is a sf::Window
        std::cout << "global/window: (" << globalPosition.x << " " << globalPosition.y << ") / (" << localPosition.x << " " << localPosition.y << ")\n";

        // set the mouse position globally (relative to the desktop)
        // sf::Mouse::setPosition({10, 50});
        // set the mouse position locally (relative to a window)
        sf::Mouse::setPosition({10, 10}, window); // window is a sf::Window

        
        while (window.isOpen()) {

            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                std::cout << "key pressed: left\n";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
            {
                std::cout << "key pressed: right\n";
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                std::cout << "mouse pressed: Left\n";
            }
        }
    }

};



namespace graphic
{
    void simple() {
        sf::RenderWindow window; //(sf::VideoMode({800, 600}), "SFML window");
        window.create(sf::VideoMode({800, 600}), "SFML window");
        
        window.setKeyRepeatEnabled(false); // важно

        window.setVerticalSyncEnabled(true); //window.setFramerateLimit(60);

        
        while (window.isOpen()) {

            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }
            

            // clear the window with black color
            window.clear(sf::Color::Black);

            // draw everything here...
            // create a 500x500 render-texture
            sf::RenderTexture renderTexture({500, 500});

            // drawing uses the same functions
            renderTexture.clear(sf::Color::Blue);
            // renderTexture.draw(sprite); // or any other drawable
            renderTexture.display();

            // get the target texture (where the stuff has been drawn)
            const sf::Texture& texture = renderTexture.getTexture();

            // draw it to the window
            sf::Sprite sprite(texture);
            window.draw(sprite);

            // end the current frame
            window.display();
        }
    }



    void renderingThread(sf::RenderWindow* window) {
        // activate the window's context
        if (!window->setActive(true)) {
            std::cerr << "Ошибка: Не удалось активировать контекст в контексте графики!\n";
            return;
        }
        // the rendering loop
        while (window->isOpen())
        {
            window->clear(sf::Color::Black);
            sf::RenderTexture renderTexture({500, 500});
            renderTexture.clear(sf::Color::Blue);
            renderTexture.display();
            const sf::Texture& texture = renderTexture.getTexture();
            sf::Sprite sprite(texture);
            window->draw(sprite);
            // end the current frame
            window->display();
        }
    }
    void multiThread()
    {
        // create the window (remember: it's safer to create it in the main thread due to OS limitations)
        sf::RenderWindow window(sf::VideoMode({800, 600}), "OpenGL");

        // deactivate its OpenGL context
        if (!window.setActive(false)) {
            std::cerr << "Ошибка: Не удалось деактивировать контекст в главном потоке!\n";
            return;
        }
        // launch the rendering thread
        std::thread thread(&renderingThread, &window);

        // the event/logic/whatever loop
        while (window.isOpen())
        {
            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }
        }

        thread.join();
    }


    void textureAndSprite1() 
    {
        sf::RenderWindow window; //(sf::VideoMode({800, 600}), "SFML window");
        window.create(sf::VideoMode({800, 600}), "SFML window");
        
        window.setKeyRepeatEnabled(false); // важно

        window.setVerticalSyncEnabled(true); //window.setFramerateLimit(60);

        
        while (window.isOpen()) {

            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }
            

            // clear the window with black color
            window.clear(sf::Color::Black);

            // create a 500x500 render-texture
            sf::RenderTexture renderTexture({500, 500});

            // drawing uses the same functions
            renderTexture.clear(sf::Color::Blue);
            // renderTexture.draw(sprite); // or any other drawable
            renderTexture.display();

            // get the target texture (where the stuff has been drawn)
            const sf::Texture& texture = renderTexture.getTexture();

            // sf::Texture texture("image.png", false, sf::IntRect({10, 10}, {32, 32})); // Throws sf::Exception if an error occurs
            // OR
            // sf::Texture texture;
            // if (!texture.loadFromFile("image.png", false, sf::IntRect({10, 10}, {32, 32}))) {} // error...

            // sf::Texture texture(sf::Vector2u(200, 200)); // Throws sf::Exception if an error occurs
            // // OR
            // if (!texture.resize({200, 200})) {} // error...
            
            // update a texture from an array of pixels
            // auto [width, height] = texture.getSize();
            // std::vector<std::uint8_t> pixels(width * height * 4); // * 4 because pixels have 4 components (RGBA)
            // ...
            // texture.update(pixels.data());

            // // update a texture from a sf::Image
            // sf::Image image;
            // ...
            // texture.update(image);

            // // update the texture from the current contents of the window
            // sf::RenderWindow window;
            // ...
            // texture.update(window);

            // texture.setSmooth(true); // сглаживание
            // texture.setRepeated(true); // повторение (текстура кирпича -> стена из кирпичей)

            // sf::Sprite sprite(texture);
            // sprite.setTextureRect(sf::IntRect({10, 10}, {32, 32}));

            // sprite.setColor(sf::Color(0, 255, 0)); // green
            // sprite.setColor(sf::Color(255, 255, 255, 128)); // half transparent

            // // position
            // sprite.setPosition({10.f, 50.f}); // absolute position
            // sprite.move({5.f, 10.f}); // offset relative to the current position
            // // rotation
            // sprite.setRotation(sf::degrees(90)); // absolute angle
            // sprite.rotate(sf::degrees(14)); // offset relative to the current angle
            // // scale
            // sprite.setScale({0.5f, 2.f}); // absolute scale factor
            // sprite.scale({1.5f, 3.f}); // factor relative to the current scale
            // // starting point
            // sprite.setOrigin({25.f, 25.f});
            
            // ERRORS:
            // sf::Sprite loadSprite(const std::filesystem::path& filename)
            // {
            //     sf::Texture texture;
            //     texture.loadFromFile(filename);

            //     return sf::Sprite(texture);
            // } // error: the texture is destroyed here
            // RELLOCATE
            // std::vector<sf::Texture> textures;
            // auto& texture1 = textures.emplace_back("image1.png");
            // sf::Sprite sprite1(texture1);
            // auto& texture2 = textures.emplace_back("image2.png"); // This may reallocate!
            // sf::Sprite sprite2(texture2);


            // draw it to the window
            sf::Sprite sprite(texture);
            window.draw(sprite);

            // end the current frame
            window.display();
        }
    }
    

    void textureAndSprite() 
    {
        // ==========================================
        // ЗОНА 1: ИНИЦИАЛИЗАЦИЯ (Выполняется строго 1 раз)
        // ==========================================
        sf::RenderWindow window;
        window.create(sf::VideoMode({800, 600}), "SFML window");
        
        window.setKeyRepeatEnabled(false); 
        window.setVerticalSyncEnabled(true); 

        // 1. Работа с RenderTexture (Холст в памяти)
        sf::RenderTexture renderTexture({500, 500});
        renderTexture.clear(sf::Color::Blue);
        renderTexture.display();

        // 2. Получение текстуры из холста
        const sf::Texture& textureFromCanvas = renderTexture.getTexture();

        // 3. Создание отдельной текстуры и изменение её размера
        sf::Texture texture;
        if (!texture.resize({200, 200})) 
        {
            std::cerr << "Ошибка изменения размера текстуры!\n";
            return;
        }

        // 4. Настройка свойств текстуры (Сглаживание и Повторение)
        texture.setSmooth(true); 
        texture.setRepeated(true); 

        // 5. Обновление текстуры через массив сырых пикселей (RGBA)
        auto [width, height] = texture.getSize();
        std::vector<std::uint8_t> pixels(width * height * 4, 255); // Заполняем белым цветом (255)
        texture.update(pixels.data());

        // 6. Обновление текстуры через объект sf::Image
        // 6. Обновление текстуры через объект sf::Image
        sf::Image image;
        image.resize({width, height}, sf::Color::Red); // Метод просто создает красную картинку (возвращает void)
        texture.update(image);                         // Спокойно обновляем текстуру


        // 7. Создание спрайта и привязка к текстуре
        sf::Sprite sprite(texture);

        // 8. Тонкая настройка геометрии и внешнего вида спрайта
        sprite.setTextureRect(sf::IntRect({10, 10}, {32, 32})); // Вырезаем кусок текстуры
        sprite.setColor(sf::Color(255, 255, 255, 128));       // Делаем полупрозрачным

        // Настройка начальной точки (Центр вращения и масштабирования)
        sprite.setOrigin({16.f, 16.f}); 

        // Начальные трансформации (Абсолютные значения)
        sprite.setPosition({400.f, 300.f}); // Ставим по центру экрана
        sprite.setRotation(sf::degrees(90)); // Поворачиваем на 90 градусов
        sprite.setScale({2.f, 2.f});         // Увеличиваем в 2 раза

        // ==========================================
        // ЗОНА 2: ИГРОВОЙ ЦИКЛ (Выполняется по кругу)
        // ==========================================
        while (window.isOpen()) 
        {
            // 2.1 Обработка событий
            while (std::optional event = window.pollEvent()) 
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }
            
            // 2.2 Динамические трансформации спрайта (Относительные смещения каждый кадр)
            sprite.move({0.5f, 0.f});            // Плавно двигаем вправо
            sprite.rotate(sf::degrees(1));       // Плавно вращаем по часовой стрелке
            sprite.scale({0.999f, 0.999f});      // Крошечное плавное уменьшение масштаба

            // Обновление текстуры из текущего кадра окна (команда из комментариев)
            // texture.update(window); // Если раскомментировать, будет эффект "зеркала в зеркале"

            // 2.3 Отрисовка
            window.clear(sf::Color::Black);

            // Рисуем настроенный спрайт на экран
            window.draw(sprite);

            window.display();
        }
    }

};



int main() {
    graphic::multiThread();
}
