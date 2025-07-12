#include <SFML/Graphics.hpp>
#include <iostream>
#define font_path "C:\\Users\\mniek\\source\\repos\\tictactoe\\f.ttf"


sf::Sprite captureScreen(sf::RenderWindow& window)
{
	sf::Texture texture(sf::Vector2u(window.getSize().x, window.getSize().y));
	texture.update(window);
	sf::Sprite sprite(texture);
	return sprite;
}

void game()
{
	sf::Font font(font_path);
	sf::Text text(font);
	text.setString("Game Over!");
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(80);
	text.setStyle(sf::Text::Bold);

	sf::Text text2(font);
	text2.setString("Press Space to Reset");
	text2.setFillColor(sf::Color::White);
	text2.setCharacterSize(40);


	std::vector<sf::Sprite> wins;
	int player = 1;
	auto window = sf::RenderWindow(sf::VideoMode({ 1200u, 700u }), "CMake SFML Project");
	float size = 100;
	window.setFramerateLimit(144);
	std::vector<std::vector<int>> grid(3, std::vector<int>(3, 0));

	sf::Color backgroundColor(233, 224, 201);
	std::vector<sf::RectangleShape> rectangles;
	sf::Vector2f rectangleSize(size, size);
	for (float x = 0; x <= 2 * rectangleSize.x; x += rectangleSize.x) {
		for (float y = 0; y <= 2 * rectangleSize.y; y += rectangleSize.y) {
			sf::RectangleShape rectangle(rectangleSize);

			rectangle.setPosition({ x + window.getSize().x / 3, y + window.getSize().y / 3 });
			rectangle.setFillColor(backgroundColor);
			rectangle.setOutlineColor(sf::Color::Black);
			rectangle.setOutlineThickness(2.f);
			rectangles.push_back(rectangle);
		}
	}
	text.setPosition({ static_cast<float_t>(window.getSize().x / 2 - 300), static_cast<float_t>(window.getSize().y / 2 - 300) });
	text2.setPosition({ static_cast<float_t>(window.getSize().x / 2 - 235), static_cast<float_t>(window.getSize().y / 2 - 200) });
	sf::RenderTexture renderTexture({ static_cast<unsigned int>(size),static_cast<unsigned int>(size) });
	sf::VertexArray lines(sf::PrimitiveType::Lines);
	sf::Vertex start;
	start.position = { 0.f, 0.f };
	start.color = sf::Color::Black;
	lines.append(start);
	sf::Vertex end;
	end.position = { size, size };
	end.color = sf::Color::Black;
	lines.append(end);

	sf::RectangleShape thickline({ 2 * size,2 });
	thickline.setFillColor(sf::Color::Black);
	thickline.setOutlineColor(sf::Color::Black);
	thickline.setOutlineThickness(2.f);
	thickline.setOrigin({ 0, 1 });
	thickline.setRotation(sf::degrees(45));
	//
	//thickline.setPosition({ size/2.0f, size / 2.0f });

	renderTexture.clear(sf::Color::Transparent);
	renderTexture.draw(thickline);
	thickline.setRotation(sf::degrees(135));
	thickline.setPosition({ size - 2, 0 });
	renderTexture.draw(thickline);
	renderTexture.draw(lines);
	renderTexture.display();

	bool finish = false;
	float r = size / 2.2f;
	sf::RenderTexture renderTexture2({ static_cast<unsigned int>(size),static_cast<unsigned int>(size) });
	sf::CircleShape circle(r);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(4.f);
	circle.setOrigin({ r, r });
	circle.setPosition({ size / 2.0f, size / 2.0f });

	renderTexture2.clear(sf::Color::Transparent);
	renderTexture2.draw(circle);
	renderTexture2.display();
	sf::Sprite o_sprite(renderTexture2.getTexture());
	o_sprite.setOrigin({ size / 2.0f, size / 2.0f });
	o_sprite.setPosition({ size + size / 2.0f, size + size / 2.0f });
	o_sprite.scale({ 0.9f, 0.9f });

	sf::Sprite x_sprite(renderTexture.getTexture());
	x_sprite.setOrigin({ size / 2.0f, size / 2.0f });
	x_sprite.setPosition({ size / 2.0f, size / 2.0f });
	x_sprite.scale({ 0.9f, 0.9f });
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		sf::Vector2i mousepos = sf::Mouse::getPosition(window);
		std::pair<int, int> gridpos = { (mousepos.x - window.getSize().x / 3) / static_cast<int>(size), (mousepos.y - window.getSize().y / 3) / static_cast<int>(size) };
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && gridpos.first >= 0 && gridpos.first < 3 && gridpos.second >= 0 && gridpos.second < 3) {
			if (grid[gridpos.second][gridpos.first] == 0) {
				grid[gridpos.second][gridpos.first] = player;
				player *= -1;
			}
		}
		window.clear({ 100,100,100 });
		for (const auto& rectangle : rectangles)
		{
			window.draw(rectangle);
		}
		for (auto vector : grid) {
			std::cout << vector[0] << " " << vector[1] << " " << vector[2] << std::endl;
		}
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (grid[i][j] == 1) {
					o_sprite.setPosition({ j * size + size / 2.0f + window.getSize().x / 3, i * size + size / 2.0f + window.getSize().y / 3 });
					window.draw(o_sprite);
				}
				else if (grid[i][j] == -1) {
					x_sprite.setPosition({ j * size + size / 2.0f + window.getSize().x / 3, i * size + size / 2.0f + window.getSize().y / 3 });
					window.draw(x_sprite);
				}
			}
		}
		std::cout << "-------------" << std::endl;

		if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != 0) {
			std::cout << "Diagonal Win!" << std::endl;
			finish = true;
		}
		if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != 0) {
			std::cout << "Diagonal Win!" << std::endl;
			finish = true;
		}
		for (int i = 0; i < 3; ++i) {
			if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != 0) {
				std::cout << "Row " << i << " Win!" << std::endl;
				finish = true;
			}
			if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != 0) {
				std::cout << "Column " << i << " Win!" << std::endl;
				finish = true;
			}
		}
		if (finish) {
			std::cout << "Game Over!" << std::endl;
			if (player == 1) {
				text.setString("Player 2 Wins!");
			}
			else {
				text.setString("Player 1 Wins!");
			}
			window.draw(text);
			window.draw(text2);
			window.display();
			while (1) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
					grid = std::vector<std::vector<int>>(3, std::vector<int>(3, 0));
					finish = false;
					break;
				}
			}
			//return grid;
		}
		if (std::all_of(grid.begin(), grid.end(), [](const std::vector<int>& row) {
			return std::all_of(row.begin(), row.end(), [](int cell) { return cell != 0; });
			})) {
			std::cout << "It's a draw!" << std::endl;
			text.setString("It's a draw!");
			text.move({ 40, 0 });
			window.draw(text);
			window.draw(text2);
			window.display();
			while (1) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
					grid = std::vector<std::vector<int>>(3, std::vector<int>(3, 0));
					finish = false;
					break;
				}
			}
			//return grid;
		}
		//window.draw(o_sprite);
		//window.draw(x_sprite);
		window.display();
	}
}
void test1()
{
	sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), "Test Window");
	window.setFramerateLimit(60);
	sf::RectangleShape rectangle(sf::Vector2f(100.f, 100.f));
	rectangle.setFillColor(sf::Color::Red);

	sf::CircleShape circle(50.f);
	circle.setFillColor(sf::Color::Green);
	bool first = true;
	circle.setPosition({ 350.f, 250.f });
	std::cout << "This is a test function." << std::endl;
	sf::Texture fullTexture(sf::Vector2u(window.getSize().x, window.getSize().y));

	sf::Image image;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
		image = fullTexture.copyToImage();
		window.clear(sf::Color::Black);
		window.draw(circle);
		window.draw(rectangle);
		window.display();

	}
	// You can add more test code here if needed.

}
int main()
{
	std::cout << "Welcome to Tic Tac Toe!" << std::endl;
	std::cout << "Player 1 is O and Player 2 is X." << std::endl;
	std::cout << "Click on the grid to place your mark." << std::endl;
	//test1();
	game();
	return 0;
}


