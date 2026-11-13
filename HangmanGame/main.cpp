#include <iostream>
#include <string>
#include <array>

constexpr int LOST{ 1 };
constexpr int WON{ 0 };
constexpr int ERR{ -1 };

enum class stickman
{
	none = 0, head, body, left_arm, right_arm, left_leg, dead = 6
};

int main()
{
	srand(time(0));
	std::array<std::string, 2> word_list{ "DOG", "CAT" };
	std::string word{ word_list.at(rand() % word_list.size()) };
	size_t word_size = { word.size() };
	bool* is_guessed = new bool[word_size] {false};
	bool won{ false };

	std::array<char, 26> alphabet{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	constexpr size_t alphabet_size{ 26 };
	std::array<bool, 26> is_letter{ false };

	stickman life{ stickman::none };
	char guess{}; // '\0'
	std::cout << "Welcome to Hangman! Try to guess the word, one letter at a time! \n";

	while (!won)
	{
		//Output current stickman
		switch (life)
		{
		using enum stickman;
		case none:
			std::cout << "_____________________\n|  /                |\n| /                 |\n|/		    |\n|\n|\n|\n|\n|\n|\n|\n\n";
			break;
		case head:
			std::cout << "_____________________\n|  /                |\n| /                 |\n|/		   _|_\n|		  /   \\\n|		  \\___/\n|\n|\n|\n|\n|\n\n";
			break;
		case body:
			std::cout << "_____________________\n|  /                |\n| /                 |\n|/		   _|_\n|		  /   \\\n|		  \\___/\n|		    |\n|		    |\n|\n|\n|\n\n";
			break;
		case left_arm:
			std::cout << "_____________________\n|  /                |\n| /                 |\n|/		   _|_\n|		  /   \\\n|		  \\___/\n|		   /|\n|		  / |\n|\n|\n|\n\n";
			break;
		case right_arm:
			std::cout << "_____________________\n|  /                |\n| /                 |\n|/		   _|_\n|		  /   \\\n|		  \\___/\n|		   /|\\\n|		  / | \\\n|\n|\n|\n\n";
			break;
		case left_leg:
			std::cout << "_____________________\n|  /                |\n| /                 |\n|/		   _|_\n|		  /   \\\n|		  \\___/\n|		   /|\\\n|		  / | \\\n|		   /\n|		  /\n|\n\n";
			break;
		case dead:
			std::cout << "_____________________\n|  /                |\n| /     YOU         |\n|/      HAVE        |\n|	LOST!	  /x x\\\n|		  \\_-_/\n|		   /|\\\n|		  / | \\\n|		   / \\\n|		  /   \\\n|\n\n";
			/**/std::cout << "\n\nThe word was " << word << '\n';
			delete[] is_guessed;
			return LOST;
			break;
		default:
			std::cout << "ERROR: Stickman state not found in switch! Aborting program...\n\n";
			delete[] is_guessed;
			return ERR;
			break;
		}

		//Output the word
		for (size_t i{ 0 }; i < word_size; ++i)
		{
			if (!is_guessed[i])
				std::cout << "_ ";
			else
				std::cout << word[i] << ' ';
		}
		std::cout << "\n\n";

		//Output all letters
		for (size_t i{ 0 }; i < alphabet_size; ++i)
		{
			if (!is_letter[i])
			{
				std::cout << alphabet[i] << ' ';
			}
			else
			{
				std::cout << "\033[9m\033[3m\033[90m" << alphabet[i] << "\033[0m "; //strike-through, italic, and gray, then reset
			}
		}
		std::cout << "\n\n\nGuess a letter >> ";

		//Guess check

		std::cin >> guess;
		if (guess >= 'a' && guess <= 'z')
			guess -= 32; //a -> A
		if (guess < 'A' || (guess > 'Z' && guess < 'a') || guess > 'z')
		{
			std::cout << "Your input is not a letter!!!\n";
			continue;
		}
		if (is_letter.at(static_cast<int>(guess) - 65) == true)
		{
			std::cout << "You have already guessed this letter!\n\n";
			continue;
		}
		else
		{
			bool hang{ true };
			for (size_t i{ 0 }; i < word_size; ++i)
			{
				if (word[i] == guess)
				{
					hang = false;
					is_guessed[i] = true;
				}
			}
			if (hang)
				life = static_cast<stickman>(static_cast<int>(life) + 1); //++
		}
		is_letter.at(static_cast<int>(guess) - 65) = true; //'A' - 65 == alphabet[0] == 'A'
		
		//Check if you have won: TO DO

	}
	return WON;
	delete[] is_guessed;
}