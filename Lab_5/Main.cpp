#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

// ��������� ��� �������� ���������� � �����
struct Book {
    std::string id, author, title;
    int pages;

    // ���������� ��������� ����� ��� ������ ����� �� ������
    friend std::istream& operator>>(std::istream& is, Book& book) {
        is >> book.id >> book.author >> book.title >> book.pages;
        return is;
    }

    // ���������� ��������� ������ ��� ������ ����� � �����
    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << book.id << " " << book.author << " " << book.title << " " << book.pages;
        return os;
    }
};

// ��������� ��� �������� �������
struct Matrix {
    std::vector<std::vector<int>> data;
};

// ������� ��� ���������� ����� ����� � ������ � ����
void addBook(std::vector<Book>& books, const Book& newBook) {
    std::ofstream outBook("Book.txt", std::ios::app);
    if (!outBook.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������" << std::endl;
        return;
    }
    books.push_back(newBook); // ��������� ����� � ������
    outBook << newBook << std::endl; // ���������� ����� � ����
    outBook.close();
}

// ������� ��� ������ ���� ���� �� �����
void viewBooks() {
    std::vector<Book> books;
    std::ifstream inFile("Book.txt");
    if (!inFile.is_open()) {
        std::cerr << "�� ������� ������� ����" << std::endl;
        return;
    }
    Book book;
    while (inFile >> book) {
        books.push_back(book); // ������ ����� �� ����� � ������
    }
    inFile.close();

    // ������� ��� �����
    for (const auto& book : books) {
        std::cout << book.id << " " << book.author << " " << book.title << " " << book.pages << std::endl;
    }
}

// ������� ��� �������� ����� �� ��������������
void deleteBook(const std::string& id) {
    std::vector<Book> books;
    std::ifstream inFile("Book.txt");
    if (!inFile.is_open()) {
        std::cerr << "�� ������� ������� ����" << std::endl;
        return;
    }
    Book book;
    while (inFile >> book) {
        books.push_back(book); // ������ ����� �� ����� � ������
    }
    inFile.close();

    // ������� ����� � �������� ���������������
    books.erase(std::remove_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; }), books.end());

    // �������������� ���� ��� ��������� �����
    std::ofstream outFile("Book.txt");
    if (!outFile.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������" << std::endl;
        return;
    }
    for (const auto& book : books) {
        outFile << book << std::endl;
    }
    outFile.close();
}

// ������� ��� ������ ����� �� ��������
void searchBook(const std::string& title) {
    std::vector<Book> books;
    std::ifstream inFile("Book.txt");
    if (!inFile.is_open()) {
        std::cerr << "�� ������� ������� ����" << std::endl;
        return;
    }
    Book book;
    while (inFile >> book) {
        books.push_back(book); // ������ ����� �� ����� � ������
    }
    inFile.close();

    // ���� ����� � �������� ���������
    auto it = std::find_if(books.begin(), books.end(), [&title](const Book& book) { return book.title == title; });
    if (it != books.end()) {
        std::cout << it->id << " " << it->author << " " << it->title << " " << it->pages << std::endl;
    }
    else {
        std::cout << "����� �� �������." << std::endl;
    }
}

// ������� ��� �������������� ���������� � ����� �� ��������������
void editBook(const std::string& id, const Book& updatedBook) {
    std::vector<Book> books;
    std::ifstream inFile("Book.txt");
    if (!inFile.is_open()) {
        std::cerr << "�� ������� ������� ����" << std::endl;
        return;
    }
    Book book;
    while (inFile >> book) {
        books.push_back(book); // ������ ����� �� ����� � ������
    }
    inFile.close();

    // ���� � ��������� ����� � �������� ���������������
    auto it = std::find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        *it = updatedBook;
    }
    else {
        std::cout << "����� � ����� ID �� �������." << std::endl;
        return;
    }

    // �������������� ���� � ����������� ����������� � �����
    std::ofstream outFile("Book.txt");
    if (!outFile.is_open()) {
        std::cerr << "�� ������� ������� ���� ��� ������" << std::endl;
        return;
    }
    for (const auto& book : books) {
        outFile << book << std::endl;
    }
    outFile.close();
}

// ������� ��� ������ ������� � ����
void writeMatrixToFile(const std::string& filename, const Matrix& matrix) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ����" << std::endl;
        return;
    }

    // ���������� ������ ������ ������� � ����
    for (const auto& row : matrix.data) {
        for (int value : row) {
            file << value << ' ';
        }
        file << '\n';
    }

    file.close();
}

// ������� ��� ������ ������� �� �����
Matrix readMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ����" << std::endl;
        return Matrix{};
    }

    Matrix matrix;
    std::string line;
    // ������ ������ ������ ����� � ��������� � �������
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::vector<int> row;
        int value;
        while (stream >> value) {
            row.push_back(value);
        }
        matrix.data.push_back(row);
    }

    file.close();
    return matrix;
}

// ������� ��� �������� ���������� ��������� ��������� ����� � ��������� �����
int countWordOccurrences(const std::string& filename, const std::string& word) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ����" << std::endl;
        return -1;
    }

    std::string line;
    int count = 0;
    // ���� �������� ����� � ������ ������ �����
    while (std::getline(file, line)) {
        size_t pos = 0;
        while ((pos = line.find(word, pos)) != std::string::npos) {
            ++count;
            pos += word.length();
        }
    }

    file.close();
    return count;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<Book> books;
    std::ifstream file("books.txt");
    if (file.is_open()) {
        Book book;
        while (file >> book) {
            books.push_back(book); // ������ ����� �� ����� � ������ ��� ������� ���������
        }
        file.close();
    }

    int choice;
    do {
        std::cout << "�������� ��������:\n"
            << "1. �������� �����\n"
            << "2. ���������� ��� �����\n"
            << "3. ������� �����\n"
            << "4. ����� ����\n"
            << "5. ������������� �����\n"
            << "6. ���������� ���������� ���� � �����\n"
            << "7. �����\n"
            << "��������: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            Book newBook;
            std::cout << "������� �������������, ������, �������� � ���������� �������: ";
            std::cin >> newBook.id >> newBook.author >> newBook.title >> newBook.pages;
            addBook(books, newBook);
            break;
        }
        case 2:
            viewBooks();
            break;
        case 3: {
            std::string id;
            std::cout << "������� ������������� �����, ������� ����� �������: ";
            std::cin >> id;
            deleteBook(id);
            break;
        }
        case 4: {
            std::string title;
            std::cout << "������� �������� ����� ��� ������: ";
            std::cin >> title;
            searchBook(title);
            break;
        }
        case 5: {
            std::string id;
            Book updatedBook;
            std::cout << "������� ������������� ����� ��� ��������������: ";
            std::cin >> id;
            std::cout << "������� ����� ������: ";
            std::cin >> updatedBook.id >> updatedBook.author >> updatedBook.title >> updatedBook.pages;
            editBook(id, updatedBook);
            break;
        }
        case 6: {
            std::string filename, word;
            std::cout << "������� ��� ����� � ������� �����: ";
            std::cin >> filename >> word;
            int occurrences = countWordOccurrences(filename, word);
            std::cout << "����� '" << word << "' ����������� " << occurrences << " ���(�)." << std::endl;
            break;
        }
        case 7:
            std::cout << "����� �� ���������." << std::endl;
            break;
        default:
            std::cout << "������������ �����. ���������� ��� ���." << std::endl;
            break;
        }
    } while (choice != 7);

    return 0;
}
