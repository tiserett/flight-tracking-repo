#include <iostream>
#include <string>
#include <fstream>

std::fstream file;
std::ofstream file_out;

struct Node {
	std::string destination_place;
	int flight_number;
	std::string surname;
	std::string initials;
	int departure_date[3];

	Node* left, * right;
};
Node* tree = nullptr;

void push(std::string destination_place, int flight_number, std::string surname, std::string initials, int* departure_date, Node** tree)
{
	if ((*tree) == nullptr) {
		(*tree) = new Node;
		(*tree)->destination_place = destination_place;
		(*tree)->flight_number = flight_number;
		(*tree)->surname = surname;
		(*tree)->initials = initials;
		for (int i = 0; i < 3; ++i) {
			(*tree)->departure_date[0] = departure_date[0];
			(*tree)->departure_date[1] = departure_date[1];
			(*tree)->departure_date[2] = departure_date[2];
		}
		(*tree)->left = (*tree)->right = nullptr;
		return;
	}

	if (flight_number > (*tree)->flight_number) {
		push(destination_place, flight_number, surname, initials, departure_date, &(*tree)->right);
	}
	else {
		push(destination_place, flight_number, surname, initials, departure_date, &(*tree)->left);
	}
}

void print(Node* tree, int size)
{
	if (tree == nullptr) {
		return;
	}
	else
	{
		print(tree->left, ++size);
		for (int i = 0; i < size; ++i) {
			std::cout << '|';
		}
		std::cout << "destination_place: " << tree->destination_place
		<< "\tflight_number: " << tree->flight_number
		<< "\tfull name: " << tree->surname << ' ' << tree->initials
		<< "\t    departure_date: " << tree->departure_date[0] << '/' << tree->departure_date[1] << '/' << tree->departure_date[2] << std::endl;
		--size;
	}
	print(tree->right, ++size);
}

Node* delete_element(Node*& tree, int flight_number) {
	if (tree == nullptr) {
		return tree;
	}

	if (flight_number == tree->flight_number) {

		Node* new_node;
		if (tree->right == nullptr) {
			new_node = tree->left;
		}
		else {
			Node* ptr = tree->right;
			if (ptr->left == nullptr) {
				ptr->left = tree->left;
				new_node = ptr;
			}
			else {

				Node* min_ptr = ptr->left;
				while (min_ptr->left != nullptr) {
					ptr = min_ptr;
					min_ptr = ptr->left;
				}
				ptr->left = min_ptr->right;
				min_ptr->left = tree->left;
				min_ptr->right = tree->right;
				new_node = min_ptr;
			}
		}
		delete tree;
		return new_node;
	}
	else if (flight_number < tree->flight_number)
		tree->left = delete_element(tree->left, flight_number);
	else
		tree->right = delete_element(tree->right, flight_number);
	return tree;
}

Node* find_element(Node* tree, int flight_number) {
	if (tree == nullptr) {
		return tree;
	}

	if (flight_number == tree->flight_number) {
		std::cout
		<< "destination_place: " << tree->destination_place
		<< "\t  flight_number: " << tree->flight_number
		<< "\tfull name: " << tree->surname << ' ' << tree->initials
		<< "\tdeparture_date: " << tree->departure_date[0] << '/' << tree->departure_date[1] << '/' << tree->departure_date[2] << std::endl;
	}
	else if (flight_number < tree->flight_number)
		tree->left = find_element(tree->left, flight_number);
	else
		tree->right = find_element(tree->right, flight_number);
	return tree;
}

void read_from_file(Node*& tree) {
	std::string destination_place;
	int flight_number;
	std::string surname;
	std::string initials;
	int departure_date[3];

	while (file >> destination_place) {
		file >> flight_number;
		file >> surname >> initials;
		file >> departure_date[0] >> departure_date[1] >> departure_date[2];
		push(destination_place, flight_number, surname, initials, departure_date, &tree);
	}
}

void add_to_file(Node* tree)
{
	if (tree == nullptr) {
		return;
	}
	else {
		add_to_file(tree->left);
		file_out << tree->destination_place << '\t' << tree->flight_number << '\t' << tree->surname << ' ' << tree->initials << '\t' << tree->departure_date[0] << '/' << tree->departure_date[1] << '/' << tree->departure_date[2] << '\n';
	}
	add_to_file(tree->right);
}

int main()
{
	int choose_action = 0;
	file.open("information.txt", std::fstream::in);
	file_out.open("information_out.txt");
	while (true) {
		std::cout << "Read information from file or no? \t1 - yes \tany other digit - no   ";
		std::cin >> choose_action;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else {
			break;
		}
	}
	if (choose_action == 1) {
		std::cout << "reading from file";
		read_from_file(tree);
	}

	do {
		std::cin.ignore(32767, '\n');
		std::cout << "\n\n\nList of available functions\nChoose action\n1)Add flight\n2)Print all flights\n3)Delete element\n4)Find and delete\n5)Close program\n\n";
		std::cin >> choose_action;
		if (choose_action == 1) {
			std::string destination_place;
			int flight_number;
			std::string surname;
			std::string initials;
			int departure_date[3];

			std::cout << "\n\n\nEnter destination place: ";
			std::cin >> destination_place;
			std::cin.clear();
			std::cin.ignore(32767, '\n');

			std::cout << "\nEnter flight number: ";
			std::cin >> flight_number;
			std::cin.clear();
			std::cin.ignore(32767, '\n');

			std::cout << "\nEnter surname: ";
			std::cin >> surname;
			std::cin.clear();
			std::cin.ignore(32767, '\n');

			std::cout << "\nEnter initials(M.R. I.V.): ";
			std::cin >> initials;
			std::cin.clear();
			std::cin.ignore(32767, '\n');

			std::cout << "\nEnter departure date \n";
			std::cout << "Day: ";
			std::cin >> departure_date[0];
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Month: ";
			std::cin >> departure_date[1];
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Year: ";
			std::cin >> departure_date[2];
			std::cin.clear();
			std::cin.ignore(32767, '\n');

			push(destination_place, flight_number, surname, initials, departure_date, &tree);
		}
		else if (choose_action == 2) {
			if (tree == nullptr) {
				std::cout << "there are no flights in our list";
			}
			else {
				std::cout << "printing flights\n";
				print(&(*tree), 0);
			}
		}
		else if (choose_action == 3) {

			if (tree == nullptr) {
				std::cout << "there are no flights in our list";
			}
			else {
				std::cout << "Enter flight_number you want to delete: ";
				int flight_number;
				std::cin >> flight_number;
				if (tree->flight_number == flight_number) {
					std::cout << "you can't delete root";
					continue;
				}
				delete_element(tree, flight_number);
			}
		}
		else if (choose_action == 4) {
			if (tree == nullptr) {
				std::cout << "there are no flights in our list";
			}
			else {
				std::cout << "enter flight number: ";
				int flight_number;
				std::cin >> flight_number;
				find_element(tree, flight_number);
				if (tree->flight_number == flight_number) {
					std::cout << "you can't delete root";
					continue;
				}
				delete_element(tree, flight_number);
			}
		}
		else if (choose_action == 5) {
			std::cout << "PROGRAM IS CLOSED";
			break;
		}
		else {
			std::cin.clear(), std::cin.ignore(32767, '\n');
		}
	} while (choose_action != 5);
	add_to_file(tree);
	return 0;
}
