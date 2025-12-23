#include <SFML/Graphics.hpp>
#include "Library.h"
#include "SimpleUI.h"
#include <iostream>
#include <vector>

enum AppState {
    MENU,
    ADD_BOOK,
    DISPLAY_BOOKS,
    SEARCH_BOOK,
    BORROW_BOOK,
    RETURN_BOOK,
    HISTORY,
    SORT_BOOKS,
    CATEGORY,
    HUFFMAN
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Library Management System");
    window.setFramerateLimit(60);

    Library lib;
    // Pre-populate
    // Programming & Algorithms
    lib.addBook(101, "The C++ Programming Language", "Bjarne Stroustrup", 2013, "Programming");
    lib.addBook(105, "Introduction to Algorithms", "Cormen", 2009, "Algorithms");
    lib.addBook(106, "Data Structures and Algorithms in C++", "Goodrich", 2011, "Algorithms");
    lib.addBook(107, "Effective C++", "Scott Meyers", 2005, "Programming");
    
    // Software Engineering
    lib.addBook(102, "Clean Code", "Robert C. Martin", 2008, "Software Engineering");
    lib.addBook(104, "Design Patterns", "Erich Gamma", 1994, "Software Engineering");
    lib.addBook(103, "The Pragmatic Programmer", "Andrew Hunt", 1999, "Software Engineering");
    lib.addBook(108, "Refactoring", "Martin Fowler", 1999, "Software Engineering");

    // Artificial Intelligence
    lib.addBook(201, "Artificial Intelligence: A Modern Approach", "Russell & Norvig", 2020, "AI");
    lib.addBook(202, "Deep Learning", "Ian Goodfellow", 2016, "AI");
    lib.addBook(203, "Pattern Recognition and Machine Learning", "Christopher Bishop", 2006, "AI");

    // Databases
    lib.addBook(301, "Database System Concepts", "Silberschatz", 2019, "Databases");
    lib.addBook(302, "Designing Data-Intensive Applications", "Martin Kleppmann", 2017, "Databases");

    // Operating Systems
    lib.addBook(401, "Operating System Concepts", "Silberschatz", 2018, "OS");
    lib.addBook(402, "Modern Operating Systems", "Andrew S. Tanenbaum", 2014, "OS");

    // Networks
    lib.addBook(501, "Computer Networking: A Top-Down Approach", "Kurose & Ross", 2021, "Networks");

    // Category Graph Dependencies
    lib.addCategoryDependency("Computer Science", "Programming");
    lib.addCategoryDependency("Computer Science", "AI");
    lib.addCategoryDependency("Computer Science", "Databases");
    lib.addCategoryDependency("Computer Science", "OS");
    lib.addCategoryDependency("Computer Science", "Networks");
    
    lib.addCategoryDependency("Programming", "Algorithms");
    lib.addCategoryDependency("Programming", "Software Engineering");
    
    lib.addCategoryDependency("Software Engineering", "Design Patterns");
    lib.addCategoryDependency("Software Engineering", "Testing");
    
    lib.addCategoryDependency("AI", "Machine Learning");
    lib.addCategoryDependency("AI", "Robotics");
    
    lib.addCategoryDependency("Databases", "SQL");
    lib.addCategoryDependency("Databases", "NoSQL");

    sf::Font font;
    // Try to load a system font
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    AppState currentState = MENU;

    // --- UI Elements ---
    
    // Menu Buttons
    std::vector<Button> menuButtons;
    std::vector<std::string> menuLabels = {
        "Add Book", "Display Books", "Search Book", "Borrow Book", 
        "Return Book", "History", "Sort Books", "Category Analysis", "Compress History", "Exit"
    };

    for (size_t i = 0; i < menuLabels.size(); ++i) {
        Button btn(362, 100 + i * 60, 300, 50, menuLabels[i], font);
        menuButtons.push_back(btn);
    }

    // Back Button
    Button backBtn(20, 20, 100, 40, "Back", font);
    backBtn.setOnClick([&]() { currentState = MENU; });

    // Add Book Inputs
    InputBox idInput(300, 150, 400, 40, font, "Book ID");
    InputBox titleInput(300, 210, 400, 40, font, "Title");
    InputBox authorInput(300, 270, 400, 40, font, "Author");
    InputBox yearInput(300, 330, 400, 40, font, "Year");
    InputBox categoryInput(300, 390, 400, 40, font, "Category");
    Button submitAddBtn(300, 450, 200, 50, "Add Book", font);
    sf::Text addStatusText;
    addStatusText.setFont(font);
    addStatusText.setPosition(300, 520);
    addStatusText.setCharacterSize(20);

    submitAddBtn.setOnClick([&]() {
        try {
            int id = std::stoi(idInput.getValue());
            int year = std::stoi(yearInput.getValue());
            lib.addBook(id, titleInput.getValue(), authorInput.getValue(), year, categoryInput.getValue());
            addStatusText.setString("Book Added Successfully!");
            addStatusText.setFillColor(sf::Color::Green);
            // Clear inputs
            idInput.setValue(""); titleInput.setValue(""); authorInput.setValue(""); yearInput.setValue(""); categoryInput.setValue("");
        } catch (...) {
            addStatusText.setString("Invalid Input!");
            addStatusText.setFillColor(sf::Color::Red);
        }
    });

    // Display Area
    TextArea displayArea(50, 80, 924, 600, font);

    // Search Inputs
    InputBox searchInput(300, 150, 400, 40, font, "Enter Title or ID");
    Button searchTitleBtn(300, 210, 190, 50, "Search Title", font);
    Button searchIdBtn(510, 210, 190, 50, "Search ID", font);
    
    searchTitleBtn.setOnClick([&]() {
        displayArea.setText(lib.searchByTitleString(searchInput.getValue()));
    });
    searchIdBtn.setOnClick([&]() {
        try {
            displayArea.setText(lib.searchByIDString(std::stoi(searchInput.getValue())));
        } catch (...) {
            displayArea.setText("Invalid ID format.");
        }
    });

    // Borrow/Return Inputs
    InputBox borrowReturnInput(300, 150, 400, 40, font, "Enter Book Title");
    Button borrowBtn(300, 210, 400, 50, "Borrow", font);
    Button returnBtn(300, 210, 400, 50, "Return", font);
    sf::Text actionStatusText;
    actionStatusText.setFont(font);
    actionStatusText.setPosition(300, 280);
    actionStatusText.setCharacterSize(20);

    borrowBtn.setOnClick([&]() {
        actionStatusText.setString(lib.borrowBookString(borrowReturnInput.getValue()));
    });
    returnBtn.setOnClick([&]() {
        actionStatusText.setString(lib.returnBookString(borrowReturnInput.getValue()));
    });

    // Sort Buttons
    Button sortTitleBtn(100, 20, 200, 40, "Sort by Title", font);
    Button sortYearBtn(320, 20, 200, 40, "Sort by Year", font);
    Button sortAuthorBtn(540, 20, 200, 40, "Sort by Author", font);

    sortTitleBtn.setOnClick([&]() { lib.sortByTitleQuickSort(); displayArea.setText(lib.getBooksString()); });
    sortYearBtn.setOnClick([&]() { lib.sortByYearMergeSort(); displayArea.setText(lib.getBooksString()); });
    sortAuthorBtn.setOnClick([&]() { lib.sortByAuthorHeapSort(); displayArea.setText(lib.getBooksString()); });

    // Category Inputs
    InputBox catInput(300, 150, 400, 40, font, "Start Category");
    Button bfsBtn(300, 210, 190, 50, "BFS Traversal", font);
    Button dfsBtn(510, 210, 190, 50, "DFS Traversal", font);

    bfsBtn.setOnClick([&]() {
        displayArea.setText(lib.getCategoryTraversalBFSString(catInput.getValue()));
    });
    dfsBtn.setOnClick([&]() {
        displayArea.setText(lib.getCategoryTraversalDFSString(catInput.getValue()));
    });


    // Menu Button Actions
    menuButtons[0].setOnClick([&]() { currentState = ADD_BOOK; addStatusText.setString(""); });
    menuButtons[1].setOnClick([&]() { currentState = DISPLAY_BOOKS; displayArea.setText(lib.getBooksString()); });
    menuButtons[2].setOnClick([&]() { currentState = SEARCH_BOOK; displayArea.setText(""); searchInput.setValue(""); });
    menuButtons[3].setOnClick([&]() { currentState = BORROW_BOOK; actionStatusText.setString(""); borrowReturnInput.setValue(""); });
    menuButtons[4].setOnClick([&]() { currentState = RETURN_BOOK; actionStatusText.setString(""); borrowReturnInput.setValue(""); });
    menuButtons[5].setOnClick([&]() { currentState = HISTORY; displayArea.setText(lib.getHistoryString()); });
    menuButtons[6].setOnClick([&]() { currentState = SORT_BOOKS; displayArea.setText(lib.getBooksString()); });
    menuButtons[7].setOnClick([&]() { currentState = CATEGORY; displayArea.setText(""); catInput.setValue(""); });
    menuButtons[8].setOnClick([&]() { currentState = HUFFMAN; displayArea.setText(lib.getCompressedHistoryString()); });
    menuButtons[9].setOnClick([&]() { window.close(); });


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                
                if (currentState == MENU) {
                    for (auto& btn : menuButtons) btn.isClicked(mousePos);
                } else {
                    if (backBtn.isClicked(mousePos)) continue;

                    if (currentState == ADD_BOOK) {
                        idInput.setFocus(idInput.contains(mousePos));
                        titleInput.setFocus(titleInput.contains(mousePos));
                        authorInput.setFocus(authorInput.contains(mousePos));
                        yearInput.setFocus(yearInput.contains(mousePos));
                        categoryInput.setFocus(categoryInput.contains(mousePos));
                        submitAddBtn.isClicked(mousePos);
                    } else if (currentState == SEARCH_BOOK) {
                        searchInput.setFocus(searchInput.contains(mousePos));
                        searchTitleBtn.isClicked(mousePos);
                        searchIdBtn.isClicked(mousePos);
                    } else if (currentState == BORROW_BOOK) {
                        borrowReturnInput.setFocus(borrowReturnInput.contains(mousePos));
                        borrowBtn.isClicked(mousePos);
                    } else if (currentState == RETURN_BOOK) {
                        borrowReturnInput.setFocus(borrowReturnInput.contains(mousePos));
                        returnBtn.isClicked(mousePos);
                    } else if (currentState == SORT_BOOKS) {
                        sortTitleBtn.isClicked(mousePos);
                        sortYearBtn.isClicked(mousePos);
                        sortAuthorBtn.isClicked(mousePos);
                    } else if (currentState == CATEGORY) {
                        catInput.setFocus(catInput.contains(mousePos));
                        bfsBtn.isClicked(mousePos);
                        dfsBtn.isClicked(mousePos);
                    }
                }
            }

            if (event.type == sf::Event::TextEntered) {
                if (currentState == ADD_BOOK) {
                    idInput.handleEvent(event);
                    titleInput.handleEvent(event);
                    authorInput.handleEvent(event);
                    yearInput.handleEvent(event);
                    categoryInput.handleEvent(event);
                } else if (currentState == SEARCH_BOOK) {
                    searchInput.handleEvent(event);
                } else if (currentState == BORROW_BOOK || currentState == RETURN_BOOK) {
                    borrowReturnInput.handleEvent(event);
                } else if (currentState == CATEGORY) {
                    catInput.handleEvent(event);
                }
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        
        // Update hover states
        if (currentState == MENU) {
            for (auto& btn : menuButtons) btn.update(mousePos);
        } else {
            backBtn.update(mousePos);
            if (currentState == ADD_BOOK) submitAddBtn.update(mousePos);
            if (currentState == SEARCH_BOOK) { searchTitleBtn.update(mousePos); searchIdBtn.update(mousePos); }
            if (currentState == BORROW_BOOK) borrowBtn.update(mousePos);
            if (currentState == RETURN_BOOK) returnBtn.update(mousePos);
            if (currentState == SORT_BOOKS) { sortTitleBtn.update(mousePos); sortYearBtn.update(mousePos); sortAuthorBtn.update(mousePos); }
            if (currentState == CATEGORY) { bfsBtn.update(mousePos); dfsBtn.update(mousePos); }
        }

        window.clear(sf::Color(20, 20, 20));

        if (currentState == MENU) {
            sf::Text title("Library Management System", font, 40);
            title.setPosition(250, 30);
            title.setFillColor(sf::Color::Cyan);
            window.draw(title);
            for (auto& btn : menuButtons) btn.draw(window);
        } else {
            backBtn.draw(window);

            if (currentState == ADD_BOOK) {
                idInput.draw(window);
                titleInput.draw(window);
                authorInput.draw(window);
                yearInput.draw(window);
                categoryInput.draw(window);
                submitAddBtn.draw(window);
                window.draw(addStatusText);
            } else if (currentState == DISPLAY_BOOKS || currentState == HISTORY || currentState == HUFFMAN) {
                displayArea.setPosition(50, 80); // Default position
                displayArea.draw(window);
            } else if (currentState == SEARCH_BOOK) {
                searchInput.draw(window);
                searchTitleBtn.draw(window);
                searchIdBtn.draw(window);
                displayArea.setPosition(50, 300); // Move down
                displayArea.draw(window); 
            } else if (currentState == BORROW_BOOK) {
                borrowReturnInput.draw(window);
                borrowBtn.draw(window);
                window.draw(actionStatusText);
            } else if (currentState == RETURN_BOOK) {
                borrowReturnInput.draw(window);
                returnBtn.draw(window);
                window.draw(actionStatusText);
            } else if (currentState == SORT_BOOKS) {
                sortTitleBtn.draw(window);
                sortYearBtn.draw(window);
                sortAuthorBtn.draw(window);
                displayArea.setPosition(50, 80);
                displayArea.draw(window);
            } else if (currentState == CATEGORY) {
                catInput.draw(window);
                bfsBtn.draw(window);
                dfsBtn.draw(window);
                displayArea.setPosition(50, 300);
                displayArea.draw(window);
            }
        }

        window.display();
    }

    return 0;
}
