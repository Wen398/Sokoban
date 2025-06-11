# 倉庫番遊戲 (C++)

這是一個用 C++ 實現的簡單基於命令列的倉庫番益智遊戲。

## 遊戲說明

這是一個經典的倉庫番益智遊戲，玩家在迷宮中推動箱子，將它們移動到指定的儲存位置。遊戲特色包括：

* 從文字檔案載入關卡。
* 玩家移動和推箱子的邏輯。
* 當所有箱子都到達目標點時的遊戲結束條件。
* 可以重置地圖或退出遊戲。

## 如何編譯與執行

要編譯和執行這個遊戲，你需要一個 C++ 編譯器 (例如 g++)。

### Windows (使用 MinGW/g++)

1.  **安裝 MinGW**: 如果你還沒有 g++，請從 [https://mingw-w64.org/](https://mingw-w64.org/) 下載並安裝 MinGW。請確保將 g++ 添加到你的系統 PATH 中。
2.  **導航到專案目錄**: 打開命令提示字元或 PowerShell，並進入你儲存 `main.cpp` 和地圖檔案的目錄。
    ```bash
    cd path/to/your/Sokoban-Game-CPP
    ```
3.  **編譯**:
    ```bash
    g++ main.cpp -o Sokoban.exe -static -std=c++11
    ```
    * `-o Sokoban.exe`: 指定輸出執行檔的名稱。
    * `-static`: 靜態連結函式庫，使執行檔更具可移植性。
    * `-std=c++11`: 確保支援 C++11 功能 (如 `std::vector` 初始化)。
    * 如果你遇到 `conio.h` (這是 Windows 特有的) 的問題，你可能需要為其他作業系統調整 `getch()` 部分，或在 Windows 上編譯。

4.  **執行**:
    ```bash
    ./Sokoban.exe
    ```

### Linux/macOS (使用 g++)

1.  **安裝 g++**: 如果你還沒有 g++，請透過你的套件管理器安裝它 (例如，Ubuntu 上使用 `sudo apt-get install build-essential`，macOS 上使用 `xcode-select --install`)。
2.  **導航到專案目錄**: 打開終端機，並進入你儲存 `main.cpp` 和地圖檔案的目錄。
    ```bash
    cd path/to/your/Sokoban-Game-CPP
    ```
3.  **編譯**:
    ```bash
    g++ main.cpp -o Sokoban -static -std=c++11
    ```
    * 注意：`conio.h` 和 `system("cls")`/`system("pause")` 主要是在 Windows 上使用。為了跨平台相容性，你可能需要將 `getch()` 替換為 `ncurses` 或 `termios` 來實現 `kbhit`/`getch` 功能，並以不同的方式處理螢幕清除 (例如，使用 `printf("\033[2J\033[H");` 來清除螢幕並將游標移動到左上角)。對於這個簡單的遊戲，它可能可以直接在 Linux/macOS 上與某些編譯器一起使用，但請注意這些平台差異。

4.  **執行**:
    ```bash
    ./Sokoban
    ```

## 遊戲控制

* **W / A / S / D**: 向上、左、下、右移動玩家角色 (0)。
* **R**: 將當前地圖重置為初始狀態。
* **ESC**: 退出遊戲。

## 地圖檔案格式

地圖檔案是純文字檔案。第一行會被忽略。後續的行代表地圖的行。

* `0`: 玩家
* `1`: 箱子
* `2`: 目標位置
* `/`: 牆壁
* `-`: 空格

**`map1.txt` 範例:**

## 貢獻

歡迎隨時 Fork 此儲存庫，進行改進並提交 Pull Request！