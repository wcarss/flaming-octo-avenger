default:
	gcc main.cpp -o flaming-octo-avenger -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -g

mac:
	clang++ main.cpp -o flaming-octo-avenger -framework sfml-graphics -framework sfml-audio -framework sfml-window -framework sfml-system -stdlib=libc++
