# CS 126 FinalProject - Holmes
Holmes is a bot that solves trivia questions. It can act as a standalone system that connects with the HQ Trivia websocket (available only during a live game), or as a tool to be used by another system via commandline, for instance an OCR application that can work with any trivia game, not just HQ, and passes the information to Holmes to solve. Holmes is only compatible with Mac OSX due to the Web Socket library having a OSX dependency (in Swift), however the vast majority of the code is cross-platform in C++.

# How to use

## Building - Mac OSX
1. Download the project
2. Place the entire project folder in the myApps directory in OpenFrameworks
3. Open the project by double clicking the Holmes.xcodeproj file on a Mac
4. Select the build target to be Holmes-Release
5. Build either by using the dropdown menu Product -> Build, or by hitting ⌘+B (CMD+B)
6. The built Holmes.app file is in the bin folder in the root of the project

## Running
The application can be run in three modes:

1. Bot Mode - Automatically connects to web socket and updates live
    #### Commandline
    ```ruby
    ./Holmes
    ```
    #### Executable
    Alternatively, you can just run the .app file built by Xcode.

2. Manual Mode - Accepts 1 question and 3 possible answers and predicts which one is right
    #### Commandline
    ```ruby
    ./Holmes "question" "answer1" "answer2" "answer3"
    ```
    #### Shell script
    Run `HolmesCMD` script in the root of the project which will then prompt you to enter your desired questions and answers and then will run the application automatically.

3. Test Mode - Can run predefined questions and answers via shell scripts
    #### Shell script
    In the `autotests` folder, there are 20 shell scripts that are numbered corresponding to actual trivia questions selected from various trivia games. To see what question and answers will be used, you can read them in `QUESTIONS.md`.

# How it works

- ### Web Socket

    To be continued.

- ### Trivia Solving

    To be continued.