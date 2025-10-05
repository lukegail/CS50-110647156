# Harvard's CS50x: Introduction to Computer Science

This repository contains my coursework and solutions for Harvard University's CS50x course, which I completed in 2023. It includes my work on problem sets covering topics from C and Python to SQL and web development.

## The CS50 Development Environment

All projects in this repository were developed within the CS50 Codespace, a cloud-based Linux environment tailored for the course. This ecosystem provides pre-configured software for all assignments, from C and Python to SQL and web development. The early C programs are especially dependent on this setup, as they rely on a custom `cs50.h` library and a compiler toolchain that links it automatically. For this reason, the C code will not compile "out-of-the-box" on a standard system, and all projects herein are best understood as products of this specific, managed environment.

---

## Highlighted Projects

While this repository contains all my weekly assignments, the projects below are the ones I'm most proud of. They showcase my ability to tackle complex logical problems.

### 1. Tideman (Week 3)
* **Location:** [`wk3/tideman/`](https://github.com/lukegail/CS50-110647156/blob/main/wk3/tideman/)
* **Description:** This program simulates the "Tideman" ranked-pairs voting method. The core challenge was to lock in pairs of candidates to a directed graph without creating cycles. To solve this, I implemented a recursive depth-first search (DFS) algorithm to detect cycles before locking in an edge.
* **Skills Demonstrated:** Algorithmic thinking (recursion, depth-first search), data structures (directed graphs), complex logical problem-solving, and systematic debugging.

### 2. Speller (Week 5)
* **Location:** [`/wk5/speller/`](https://github.com/lukegail/CS50-110647156/blob/main/wk5/speller/)
* **Description:** A command-line spell-checking program written in C. The program's core task is to load a large dictionary file into memory efficiently and then check an input text file for misspelled words at high speed. To achieve this, I implemented a hash table data structure from scratch to store and look up dictionary words.
* **Skills Demonstrated:** Data structures (hash tables, linked lists), memory management in C, performance optimization, and file I/O. This project was a practical exercise in choosing the right data structure to solve a performance-critical problem.

### 3. Filter (Week 4)

  * **Location:** [`/wk4/filter-more/`](https://www.google.com/search?q=%5Bhttps://github.com/lukegail/CS50-110647156/blob/main/wk4/filter-more/helpers.c%5D\(https://github.com/lukegail/CS50-110647156/blob/main/wk4/filter-more/)
  * **Description:** A command-line program written in C that applies various filters to BMP image files by directly manipulating their pixel data. I implemented several image processing algorithms from scratch, including grayscale, reflection, box blur, and a more complex edge detection filter that uses the Sobel operator.
  * **Skills Demonstrated:** **Image processing algorithms**, low-level **memory management** (`malloc`, `free`), **2D array manipulation**, and implementing **convolutional kernels** (Sobel operator) for edge detection. This project required careful handling of edge cases and an understanding of binary file formats.

### 4. Finance (Week 9)

* **Location:** [`/wk9/finance/`](https://www.google.com/search?q=%5Bhttps://github.com/lukegail/CS50-110647156/blob/main/wk9/finance/app.py%5D\(https://github.com/lukegail/CS50-110647156/blob/main/wk9/finance/)
* **Description:** A full-stack web application that simulates a stock trading platform. I built the back end using Python and the Flask framework, with a SQLite database to manage user data, portfolios, and transaction histories. The application features full user authentication (registration, login/logout), real-time stock quoting by fetching data from the Yahoo Finance API, and the ability to "buy" and "sell" stocks.
* **Skills Demonstrated:** **Full-stack web development**, back-end programming (**Python, Flask**), database management (**SQL**), third-party **API integration**, front-end templating (**HTML, CSS, Jinja**), and session management for user authentication.
