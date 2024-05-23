#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

// Структура для хранения информации о книге
struct Book {
    std::string id, author, title;
    int pages;

    // Перегрузка оператора ввода для чтения книги из потока
    friend std::istream& operator>>(std::istream& is, Book& book) {
        is >> book.id >> book.author >> book.title >> book.pages;
        return is;
    }

    // Перегрузка оператора вывода для записи книги в поток
    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << book.id << " " << book.author << " " << book.title << " " << book.pages;
        return os;
    }
};

// Структура для хранения матрицы
struct Matrix {
    std::vector<std::vector<int>> data;
};

// Функция для добавления новой книги в вектор и файл
void addBook(std::vector<Book>& books, const Book& newBook) {
    std::ofstream outBook("Book.txt", std::ios::app);
    if (!outBook.is_open()) {
        std::cerr << "Не удалось открыть файл для записи" << std::endl;
        return;
    }
    books.push_back(newBook); // Добавляем книгу в вектор
    outBook << newBook << std::endl; // Записываем книгу в файл
    outBook.close();
}

// Функция для вывода всех книг из файла
void viewBooks() {
    std::vector<Book> books;
    std::ifstream inFile("Book.txt");
    if (!inFile.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    Book book;
    while (inFile >> book) {
        books.push_back(book); // Читаем книги из файла в вектор
    }
    inFile.close();

    // Выводим все книги
    for (const auto& book : books) {
        std::cout << book.id << " " << book.author << " " << book.title << " " << book.pages << std::endl;
    }
}

// Функция для удаления книги по идентификатору
void deleteBook(const std::string& id) {
    std::vector<Book> books;
    std::ifstream inFile("Book.txt");
    if (!inFile.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    Book book;
    while (inFile >> book) {
        books.push_back(book); // Читаем книги из файла в вектор
    }
    inFile.close();

    // Удаляем книгу с заданным идентификатором
    books.erase(std::remove_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; }), books.end());

    // Перезаписываем файл без удаленной книги
    std::ofstream outFile("Book.txt");
    if (!outFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи" << std::endl;
        return;
    }
    for (const auto& book : books) {
        outFile << book << std::endl;
    }
    outFile.close();
}

// Функция для поиска книги по названию
void searchBook(const std::string& title) {
    std::vector<Book> books;
    std::ifstream inFile("Book.txt");
    if (!inFile.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    Book book;
    while (inFile >> book) {
        books.push_back(book); // Читаем книги из файла в вектор
    }
    inFile.close();

    // Ищем книгу с заданным названием
    auto it = std::find_if(books.begin(), books.end(), [&title](const Book& book) { return book.title == title; });
    if (it != books.end()) {
        std::cout << it->id << " " << it->author << " " << it->title << " " << it->pages << std::endl;
    }
    else {
        std::cout << "Книга не найдена." << std::endl;
    }
}

// Функция для редактирования информации о книге по идентификатору
void editBook(const std::string& id, const Book& updatedBook) {
    std::vector<Book> books;
    std::ifstream inFile("Book.txt");
    if (!inFile.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    Book book;
    while (inFile >> book) {
        books.push_back(book); // Читаем книги из файла в вектор
    }
    inFile.close();

    // Ищем и обновляем книгу с заданным идентификатором
    auto it = std::find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        *it = updatedBook;
    }
    else {
        std::cout << "Книга с таким ID не найдена." << std::endl;
        return;
    }

    // Перезаписываем файл с обновленной информацией о книге
    std::ofstream outFile("Book.txt");
    if (!outFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи" << std::endl;
        return;
    }
    for (const auto& book : books) {
        outFile << book << std::endl;
    }
    outFile.close();
}

// Функция для записи матрицы в файл
void writeMatrixToFile(const std::string& filename, const Matrix& matrix) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }

    // Записываем каждую строку матрицы в файл
    for (const auto& row : matrix.data) {
        for (int value : row) {
            file << value << ' ';
        }
        file << '\n';
    }

    file.close();
}

// Функция для чтения матрицы из файла
Matrix readMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return Matrix{};
    }

    Matrix matrix;
    std::string line;
    // Читаем каждую строку файла и добавляем в матрицу
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

// Функция для подсчета количества появлений заданного слова в текстовом файле
int countWordOccurrences(const std::string& filename, const std::string& word) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return -1;
    }

    std::string line;
    int count = 0;
    // Ищем заданное слово в каждой строке файла
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
            books.push_back(book); // Читаем книги из файла в вектор при запуске программы
        }
        file.close();
    }

    int choice;
    do {
        std::cout << "Выберите действие:\n"
            << "1. Добавить книгу\n"
            << "2. Посмотреть все книги\n"
            << "3. Удалить книгу\n"
            << "4. Поиск книг\n"
            << "5. Редактировать книгу\n"
            << "6. Подсчитать количество слов в файле\n"
            << "7. Выход\n"
            << "Выберите: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            Book newBook;
            std::cout << "Введите идентификатор, автора, название и количество страниц: ";
            std::cin >> newBook.id >> newBook.author >> newBook.title >> newBook.pages;
            addBook(books, newBook);
            break;
        }
        case 2:
            viewBooks();
            break;
        case 3: {
            std::string id;
            std::cout << "Введите идентификатор книги, которую нужно удалить: ";
            std::cin >> id;
            deleteBook(id);
            break;
        }
        case 4: {
            std::string title;
            std::cout << "Введите название книги для поиска: ";
            std::cin >> title;
            searchBook(title);
            break;
        }
        case 5: {
            std::string id;
            Book updatedBook;
            std::cout << "Введите идентификатор книги для редактирования: ";
            std::cin >> id;
            std::cout << "Введите новые данные: ";
            std::cin >> updatedBook.id >> updatedBook.author >> updatedBook.title >> updatedBook.pages;
            editBook(id, updatedBook);
            break;
        }
        case 6: {
            std::string filename, word;
            std::cout << "Введите имя файла и искомое слово: ";
            std::cin >> filename >> word;
            int occurrences = countWordOccurrences(filename, word);
            std::cout << "Слово '" << word << "' встречается " << occurrences << " раз(а)." << std::endl;
            break;
        }
        case 7:
            std::cout << "Выход из программы." << std::endl;
            break;
        default:
            std::cout << "Неправильный выбор. Попробуйте еще раз." << std::endl;
            break;
        }
    } while (choice != 7);

    return 0;
}
