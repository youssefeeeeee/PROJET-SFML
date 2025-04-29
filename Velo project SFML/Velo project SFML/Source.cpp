#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Parallax Example",
        sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Texture texture;
    if (!texture.loadFromFile("./assets/bgr.png"))
        return EXIT_FAILURE;
    texture.setRepeated(true);
    sf::Sprite sprite(texture);
    sprite.setPosition(0, 0);
    sprite.setColor(sf::Color(255, 255, 255, 200));

    sf::Shader parallaxShader;
    parallaxShader.loadFromMemory(
        "uniform float offset;"

        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;" // magic
        "    gl_FrontColor = gl_Color;"
        "}"
        , sf::Shader::Vertex);

    float offset = 0.f;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        // I set an arbitrary value as the offset, you'd calculate this based on camera position
        parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() / 10);

        window.clear();
        window.draw(sprite, &parallaxShader);
        window.display();
    }

    return EXIT_SUCCESS;
}