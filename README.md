# Eliza's Coffee Shop ☕

**C++20 | Object-Oriented Programming | Design Patterns | CMake | GoogleTest | GitHub Actions**

A console-based coffee shop management system developed as a university Object-Oriented Programming project. It models ordering, product customization, inventory, preparation queues, and business reporting across three user roles: **Customer**, **Barista**, and **Manager**.

This project focuses on maintainable C++ design, runtime polymorphism, reusable components, file-based persistence, and automated testing.

## Highlights

- **Role-based workflows:** separate menus for customers, baristas, and managers.
- **Extensible product hierarchy:** drinks, pastries, and sandwiches share an abstract product interface.
- **Customizable orders:** extra drink toppings and optional sandwich heating.
- **Inventory tracking:** stock consumption, restocking, expiry checks, and low-stock alerts.
- **Preparation queue:** baristas can inspect pending orders and process the oldest order.
- **Pricing policies:** switch between standard, Happy Hour, and weekend pricing at runtime.
- **Business reports:** sales history, cumulative profit, best-selling products, and peak hours.
- **Automated validation:** 21 GoogleTest unit tests and a GitHub Actions build-and-test workflow.

## Tech Stack

| Area | Technologies and concepts |
| --- | --- |
| Language | C++20, STL, templates, smart pointers |
| Architecture | OOP, abstract classes, inheritance, runtime polymorphism, NVI, SOLID principles |
| Design patterns | Singleton, Factory Method, Strategy |
| Build tooling | CMake, GCC / C++20-compatible compiler |
| Testing | GoogleTest, CTest, boundary-value and exception testing |
| CI | GitHub Actions (Ubuntu runner) |
| Storage | Text-file input and persistence |

## Features

### Customer

- Browse the complete menu or show only currently available items.
- Search products by name and inspect pricing, preparation time, and nutritional information.
- Filter options by dietary preferences (vegan, sugar-free, lactose-free) or included/excluded ingredients.
- Customize drinks with extra toppings and request sandwich heating when supported.
- Place orders and receive an order summary with pricing, timestamp, and a pickup reference.

### Barista

- View available products and inspect active orders.
- Process orders from the preparation queue in arrival order.
- View updated waiting-time information.
- Receive low-stock alerts for ingredients (**fewer than 5 units**) and prepared products (**fewer than 3 units**).

### Manager

- Review inventory and restock ingredients.
- Identify critical inventory levels and handle expired products.
- Inspect order history and business reports.
- View total accumulated profit, peak ordering hours, and best-selling products.
- Switch the global pricing policy while the application is running.

## Software Architecture

```text
                         Produs (abstract)
                        /        |        \
                   Bautura   Patiserie   Sandwich
                        \        |        /
                       ProdusFactory
                             |
                    Gestiune (Singleton)
                      /       |        \
               Ingredient   Comanda   StrategiePret
                   |                    /    |     \
                Depozit<T>       Standard  HappyHour  Weekend
```

*Conceptual overview; the code contains additional dependencies and helper classes.*

### Core classes

| Component | Responsibility |
| --- | --- |
| `Produs` | Abstract product API, polymorphic cloning, final-price and availability contracts, non-virtual display interface |
| `Bautura` | Recipe ingredients, optional toppings, nutrition and pricing |
| `Patiserie` | Prepared-item stock and expiry checks |
| `Sandwich` | Prepared-item stock, expiry checks and optional heating |
| `Ingredient` | Ingredient stock, pricing and dietary/nutritional attributes |
| `Comanda` | Shopping basket, order summary and finalization |
| `Gestiune` | Coordinates menu, inventory, order processing, persistence and reports |
| `Autentificare` | Role selection and password checks for staff menus |
| `Depozit<T>` | Generic container supporting insertion, clearing and element access |
| `ProdusFactory` | Creates products through a common factory interface |
| `StrategiePret` | Abstracts pricing calculations into interchangeable policies |

### Design patterns

**Singleton — `Gestiune`**  
Provides a single coordinating instance for the application's business state.

**Factory Method-style creation — `ProdusFactory`**  
Creates `Bautura`, `Patiserie`, or `Sandwich` objects through a common product interface.

**Strategy — `StrategiePret`**  
Supports configurable pricing rules:
- **Standard:** base price
- **Happy Hour:** 20% discount
- **Weekend:** 10% surcharge

The strategy can change without requiring separate pricing logic throughout the product hierarchy.

### C++ engineering concepts

- Runtime polymorphism via virtual methods and abstract classes.
- `std::shared_ptr` and polymorphic `clone()` operations where required.
- Non-Virtual Interface (NVI) for product display.
- Generic programming through `Depozit<T>`.
- Custom exceptions, including insufficient-stock handling.
- Modular organization into header and implementation files.
- Design informed by SOLID principles, especially separation of responsibilities and dependency on abstractions.

## Build & Run

### Requirements

- A C++20-compatible compiler
- CMake **3.14 or newer**
- Internet access during the first configuration if GoogleTest has not yet been downloaded by CMake

From the repository root:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Run the main program from the **repository root** so its relative `.txt` data-file paths can be resolved:

**Linux / macOS**
```bash
./build/cafenea_tema_3
```

**Windows (single-config generators such as MinGW)**
```powershell
.\build\cafenea_tema_3.exe
```

For a multi-config generator such as Visual Studio, the executable may instead be under `build/Debug/`.

The application is menu-driven: choose Customer, Barista or Manager, then follow the terminal prompts. Some actions write to local data files, so consider using a copy of the sample `.txt` files while experimenting.

## Automated Testing

The project uses **GoogleTest** with **CMake/CTest**. The current suite contains **21 tests** across three components:

| Component | Tests | Coverage focus |
| --- | ---: | --- |
| `StrategiePret` | 5 | Standard pricing, discounts, weekend surcharge, modifiers, zero price |
| `Depozit<T>` | 6 | Empty state, insertion, ordering, clearing, template instantiation |
| `Ingredient` | 10 | Initialization, stock consumption, restocking, insufficient-stock exceptions, boundaries |

Run all registered tests:

```bash
ctest --test-dir build --output-on-failure
```

Alternatively, run the GoogleTest executable directly after building. Passing 21 tests does **not** mean 100% code coverage; other modules and integration paths remain candidates for future tests.

### Continuous Integration

The workflow in [`.github/workflows/ci.yml`](.github/workflows/ci.yml) runs on pushes and pull requests, using GitHub Actions to:

1. Check out the repository.
2. Configure the CMake project.
3. Build the application and test target on Ubuntu.
4. Run the registered automated tests through CTest.

[View GitHub Actions](https://github.com/elizageorgiana0920/POO-tema-3/actions)

## File-Based Data

The program uses text files rather than a database server.

| File | Purpose |
| --- | --- |
| `ingrediente.txt`, `toppinguri.txt` | Ingredient and topping inventory |
| `bauturi.txt`, `patiserie.txt`, `sandwichuri.txt` | Product catalog input |
| `registru.txt` | Order and transaction history |
| `statistici.txt` | Data for popularity and peak-hour reporting |
| `profit_total.txt` | Accumulated profit across runs, when generated |
| `reaprovizionare.txt` | Restocking-related data |

Some generated output files may appear only after the corresponding application functionality has run.

## Current Limitations and Future Improvements

This is an **academic console application**, not a production-ready point-of-sale system.

- Staff passwords are currently stored directly in the source code; this is a demonstration of role-based navigation, **not secure production authentication**.
- Pickup references derived from a short timestamp suffix are not guaranteed to be globally unique.
- Text-file persistence is intended for learning purposes and does not provide transactional guarantees.
- Further work could expand automated test coverage to order processing, persistence, and end-to-end workflows.
- A future refactor could separate persistence from business logic and introduce stronger input validation.

## Background

Developed by **Eliza-Georgiana Boroș** as part of university coursework in Object-Oriented Programming at the **University of Bucharest**.

The project evolved from an OOP assignment into an application with automated unit testing, CMake integration, and a GitHub Actions CI workflow.

## References

- [GoogleTest documentation](https://google.github.io/googletest/)
- [CMake documentation](https://cmake.org/documentation/)
- [GitHub Actions documentation](https://docs.github.com/en/actions)
