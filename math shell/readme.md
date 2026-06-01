# Math Shell (Toy REPL in Modern C++)

**Math Shell** is a small command-line REPL (Read-Eval-Print Loop) designed to explore modern C++ basics, including input handling, tokenization, simple parsing, error handling, and the use of `std::string_view`.

---

## Features

- **REPL loop** with prompt (`>`) that reads full lines from stdin.
- **Supported commands:**
  - `echo <text...>` — Prints the arguments joined by spaces.
  - `add <int> <int>` — Integer addition.
  - `sub <int> <int>` — Integer subtraction.
  - `mul <int> <int>` — Integer multiplication.
  - `div <int> <int>` — Integer division (with division-by-zero check).
  - `help` — Lists available commands.
  - `exit` / `quit` — Exits the shell.

---

## Implementation Journey

### 1. Basic REPL and IO

- Started with a minimal loop:
  - Print prompt.
  - Read a line with `std::getline`.
  - Exit on `exit`/`quit` or EOF.
  - Initially echoed the raw line back.
- This sets up the pattern for line-oriented CLI programs and avoids C-style APIs.

### 2. Tokenization (String-Owning Version)

- Added a `tokenize(const std::string&) -> std::vector<std::string>` function:
  - Splits on spaces.
  - Ignores multiple spaces by only pushing non-empty tokens.
  - Replaced “print whole line” with “print each token” to verify parsing.
- This step separates concerns: input vs parsing vs behavior.

### 3. Command Dispatch

- Introduced a command dispatcher:
  - `tokens[0]` is treated as the command name.
  - `echo` joins and prints `tokens[1..]`.
  - Unknown commands print an error message.
- This is where the shell becomes a real REPL.

### 4. Math Commands & Basic Error Handling

- Added `add`, `sub`, `mul`, `div`:
  - Initially used `std::stoi` directly in each branch.
  - Refactored repeated logic into `parse_two_ints`, which:
    - Checks argument count.
    - Uses `std::stoi` inside a try/catch.
    - Returns `std::optional<std::pair<int, int>>`.
- Introduced `std::optional` to represent “might fail” cases cleanly.
- Added:
  - Usage message for wrong argument counts.
  - Division by zero check for `div`.

### 5. Refactor to `std::string_view`

- Optimized tokenization:
  - Changed `tokenize` to take `std::string_view` and return `std::vector<std::string_view>`.
  - Implemented zero-copy tokenization using views into the original input buffer.
- In `parse_two_ints`, converted `string_view` back to `std::string` only where needed for `std::stoi`.

---

## Concepts Practiced

- **RAII and ownership for I/O:** Using `std::string` and `std::getline` instead of manual buffer management.
- **Function design:** Splitting code into tokenizer, parser, and command dispatcher.
- **Error handling:**
  - Exceptions via `std::stoi` + try/catch.
  - Non-exceptional results via `std::optional`.
- **`std::string_view`:**
  - Using it as a non-owning view into `std::string` data.
  - Understanding lifetime constraints: views cannot outlive their source.
