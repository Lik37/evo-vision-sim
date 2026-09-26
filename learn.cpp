// g++ learn.cpp -o learn -lsfml-system -lsfml-window -lsfml-graphics
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

        // 3. Загрузка текстуры
        sf::Texture texture; // texture(("assets/cute_image.jpg", false, sf::IntRect({10, 10}, {32, 32}));
        if (!texture.loadFromFile("assets/cute_image.jpg", false, sf::IntRect({10, 10}, {32, 32})))
        {
            return; // Если файла нет, мягко выходим из функции
        }

        // 4. Настройка свойств текстуры (Сглаживание и Повторение)
        texture.setSmooth(true); 
        texture.setRepeated(true); 

        // 5. Изменение размера текстуры
        if (!texture.resize({200, 200})) 
        {
            std::cerr << "Ошибка изменения размера текстуры!\n";
            return;
        }

        // 6. Обновление текстуры через массив сырых пикселей (RGBA)
        auto [width, height] = texture.getSize();
        std::vector<std::uint8_t> pixels(width * height * 4, 255); // Заполняем белым цветом (255)
        texture.update(pixels.data());

        // 7. Обновление текстуры через объект sf::Image
        sf::Image image;
        image.resize({width, height}, sf::Color::Red); // Метод просто создает красную картинку (возвращает void)
        texture.update(image);                         // Спокойно обновляем текстуру


        // 8. Создание спрайта и привязка к текстуре
        sf::Sprite sprite(texture);

        // 9. Тонкая настройка геометрии и внешнего вида спрайта
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


    void textAndFonts() 
    {
        sf::Font font; // font("arial.ttf");
        if (!font.openFromFile("assets/LiberationSans-Regular.ttf")) {
            return;
        }

        sf::Text text(font); // a font is required to make a text object
        text.setString("Hello world"); // L"" широкая строка для кириллицы и тп.
        text.setCharacterSize(24); // in pixels, not points!
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);

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

            window.clear(sf::Color::Black);
            window.draw(text);
            window.display();
        }
    }


    class EllipseShape : public sf::Shape
    {
    public:
        explicit EllipseShape(sf::Vector2f radius = {0, 0}) : m_radius(radius)
        {
            update();
        }
        void setRadius(sf::Vector2f radius)
        {
            m_radius = radius;
            update();
        }
        sf::Vector2f getRadius() const
        {
            return m_radius;
        }
        std::size_t getPointCount() const override // нужно перепределить
        {
            return 30; // fixed, but could be an attribute of the class if needed
        }
        sf::Vector2f getPoint(std::size_t index) const override // нужно перепределить
        {
            static constexpr float pi = 3.141592654f;

            float angle = index * 2 * pi / getPointCount() - pi / 2;
            float x     = std::cos(angle) * m_radius.x;
            float y     = std::sin(angle) * m_radius.y;

            return m_radius + sf::Vector2f(x, y);
        }
    private:
        sf::Vector2f m_radius;
    };
    void shapes() 
    {   
        sf::ContextSettings settings;
        // settings.antiAliasingLevel = 8; // сглаживание
        std::cout << "settings.antiAliasingLevel: ";
        std::cin >> settings.antiAliasingLevel;
        std::cout << "settings.antiAliasingLevel = " << settings.antiAliasingLevel << "\n";
        sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML shapes", sf::Style::Default, sf::State::Windowed, settings);
        window.create(sf::VideoMode({800, 600}), "SFML window");
        window.setKeyRepeatEnabled(false); // важно
        window.setVerticalSyncEnabled(true); //window.setFramerateLimit(60);

        // sf::Color::Transparent - полностью прозрачный

        // circle
        sf::CircleShape circleShape(40.f);
        circleShape.setFillColor(sf::Color(100, 250, 50));
        circleShape.setRadius(50.f);
        circleShape.setPointCount(16);
        // outline
        circleShape.setOutlineThickness(-10.f);
        circleShape.setOutlineColor(sf::Color(250, 150, 100));
        // textureCircle
        sf::CircleShape textureCircle(50);
        sf::Texture cuteTexture("assets/cute_image.jpg");
        textureCircle.setTexture(&cuteTexture);
        textureCircle.setTextureRect(sf::IntRect({100, 0}, {200, 400})); // ({10, 10}, {100, 100})
        textureCircle.setPosition({100, 0});
        // rectangle
        sf::RectangleShape rectangle({120.f, 50.f});
        rectangle.setFillColor(sf::Color::Yellow);
        rectangle.setSize({100.f, 100.f});
        rectangle.setPosition({200, 0});
        // shape
        // create an empty shape
        sf::ConvexShape convex;
        convex.setPointCount(5);
        // define the points
        convex.setPoint(0, {0.f, 0.f});
        convex.setPoint(1, {150.f, 10.f});
        convex.setPoint(2, {120.f, 90.f});
        convex.setPoint(3, {30.f, 100.f});
        convex.setPoint(4, {0.f, 50.f});
        convex.setFillColor(sf::Color::Green);
        convex.setPosition({300, 0});
        // line with thickness
        sf::RectangleShape line1({150.f, 5.f});
        line1.rotate(sf::degrees(45));
        // line witout thickness
        std::array line2 =
        {
            sf::Vertex{sf::Vector2f(10.f, 10.f)},
            sf::Vertex{sf::Vector2f(150.f, 150.f)}
        };
        // ellipse
        EllipseShape ellipse = EllipseShape({25, 50});
        ellipse.setFillColor(sf::Color::Red);
        ellipse.setPosition({450, 0});


        
        while (window.isOpen()) {

            while (std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }
            }

            window.clear(sf::Color::Black);
            window.draw(circleShape);
            window.draw(textureCircle);
            window.draw(rectangle);
            window.draw(convex);
            window.draw(line1);
            window.draw(line2.data(), line2.size(), sf::PrimitiveType::Lines);
            window.draw(ellipse);
            window.display();
        }
        
    }

};



int main() {
    graphic::shapes();
}
