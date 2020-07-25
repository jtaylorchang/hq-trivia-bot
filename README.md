# HolmesQ - HQ Trivia Bot
Holmes is a bot that solves trivia questions. It can act as a standalone system that connects with the HQ Trivia websocket (available only during a live game), or as a tool to be used by another system via commandline, for instance an OCR application that can work with any trivia game, not just HQ, and passes the information to Holmes to solve. Holmes is only compatible with Mac OSX due to the Web Socket library having an OSX dependency (in Swift) for reasons which I will explain, however the vast majority of the code is platform independent and in C++. The bot has won over 50 games across HQ Trivia and Cash Show.

# Why did I make this

Growing up, my mother would always watch Jeopardy. Seeing these people who knew seemingly boundless amounts of information about anything, I developed a fascination with trivia. I knew I could never be a trivia master. As a CS major, I am constantly looking for ways to make computers enhance my own abilities. So, when I was introduced to HQ Trivia by a friend a few months ago, the gears started turning in my head. What if I didn't have to know everything. I built the original version using OCR to read questions off the live stream and make simple search queries in 4 hours on a thursday night while laying in bed Freshman year, it was called TessOCR. This is the new version built completely from scratch over the course of 3 weeks. Unlike the original simple OCR version, this bot detects a live game and makes requests to the server as if it is a mobile HQ Trivia client, reading the questions from the established web socket. It also supports an override mode that allows it to use the OCR method on any trivia game of a similar format.

# How to use
_Note: running the application from the commandline may require that you cd into the actual .app package._

## Building - Mac OSX
1. Download the project and necessary addons (see "Languages and Libraries" below)
2. Place the entire project folder in the myApps directory in OpenFrameworks
3. Open the project by double clicking the `Holmes.xcodeproj` file on a Mac
4. Select the build target to be `Holmes-Release`
5. Build either by using the dropdown menu `Product -> Build`, or by hitting `⌘+B` (CMD+B)
6. The built `Holmes.app` file is in the bin folder in the root of the project

## Running
The application can be run in four modes:

1. Bot Mode - Automatically connects to web socket and updates live
    #### Commandline
    ```ruby
    ./Holmes
    ```
    #### Executable
    Alternatively, you can just run the .app file built by Xcode. The project must be run in this mode once the countdown timer starts on HQ live, as this is when the socket will be open. The application will let you know if it has successfully connected to the socket via the WiFi/LTE indicator appearing in the top right corner alongside the battery if a connection was successful. If they are not present, close and reopen the application once the game is actually live.

2. Manual Mode - Accepts 1 question and 3 possible answers and predicts which one is right
    #### Commandline
    ```ruby
    ./Holmes "$question" "$answer1" "$answer2" "$answer3"
    ```
    #### Shell script
    Run `HolmesCMD` script in the `scripts` folder in the root of the project which will then prompt you to enter your desired questions and answers and then will run the application automatically.

3. Single Test Mode - Can run predefined questions and answers via shell scripts
    #### Shell script
    In the `autotests` folder, there are 20 shell scripts that are numbered corresponding to actual trivia questions selected from various trivia games. To see what question and answers will be used, you can read them in `QUESTIONS.md`.

4. Automatic Test Mode - Can run a large bank of actual questions and check the accuracy of the bot
    #### Commandline
    ```ruby
    ./Holmes "test" "$url_or_path"
    ```
    #### Shell script
    In the `scripts` folder there is a file called `HolmesAutoTest` which will automatically pull JSON data for a list of actual questions and answers from my web server. This includes 50+ questions from recent live games. Holmes will launch and run through each scenario simulating a live game and provide comprehensive results at the end for any questions it gets incorrect. I chose a sampling of questions that I thought were both reasonable and unreasonable for a bot to get correct to be realistic, so don't expect 100% accuracy.

# How it works

- ### Web Socket

    The obvious first question is, how do I get the question data from HQ's servers. The answer is that they have next to no actual security. Using a `MITM` approach, it was very simple to pull out the necessary headers and web calls that HQ client devices used to authenticate with the HQ API, and some quick probing of the server revealed their external API pretty nicely. Once I understood how they processed authentication, it was fairly simple to modify an HTTP request to simulate authentication, and in response they send information on the socket location which changes each game. Using Swift, I hook into the web socket and pass back any relevant JSON data to the C++ portion of the project for processing. The Swift bridge simply facilitates and filters the stream of constant JSON from HQ's server.

- ### Trivia Solving

    The real meat of the project is in solving trivia questions, regardless of how they are received, as the project supports many ways of getting trivia questions as detailed above. In order to solve questions, `Holmes` aggregates data from Google CSE and Wikimedia API and processes the data looking for relevant parts of answers. It filters out confusion data, that is words that are unlikely to be relevant to the answer and just add noise, and it checks for simple negations. Ultimately, it generates 3 confidence values which represent how often each answer was found when looking for the question. If the question is not negated, it simply chooses the answer with the highest confidence, otherwise it chooses the question with the lowest confidence. In the even of two answers being equal, it can decide both which indicates it is unsure which.

# Languages and libraries

## Languages
You may have noticed that the makeup of the project is very diverse, as the GitHub repo lists large chunks of Swift, C++, C, Objective-C, Objective-C++, and Shell. Due to restrictions in libraries, I conferred with my moderator about the possibility of writing in more than one language due to a library I needed being in Swift rather than C++ (I looked for a C++ one and tested many but none worked the way I needed), and he gave the go ahead. Note that the Swift component of the code is not the core of the project. The project is still primarily an OpenFrameworks application and the vast majority of the code is in C++, however the additional functionality of the web socket required a Swift library which accounts for the majority of the Swift code. Only a tiny rider is in Swift that lets C++ interface with the Swift library. Swift and C++ do NOT communicate directly which meant I had to write the main files in Objective-C++ which more or less means I wrote C++ code with a few lines of Objective-C code which can communicate with Swift. This required modifying some files from .hpp to .h (cross language header rather than pure C++ header), and some .cpp files to .mm to allow compiling Objective-C inside the C++ code. The Swift bridge is compiled into a pseudo C++ header which can then be used. Because of this dependency, the project only runs on Mac OSX 10.11+. Ultimately, only a tiny fraction of the code I wrote was in Swift or Objective-C, and the Shell code is for automated testing. Also, do to limitations in writing cross-language code, most of the Objective-C / Swift dependent code had to be written in the ofApp file or else it wouldn't compile properly.

## Libraries
Besides the Swift WebSocket library, multiple OpenFrameworks libraries were used. As far as addons go, I used ofxGUI, ofxHTTP, ofxIO, ofxJSON, ofxMediaType, ofxNetworkUtils, ofxSSLManager, ofxTaskQueue. These are all on the stable build and compatible with eachother. I only directly interface with ofxGUI, ofxHTTP, and ofxJSON and the rest are helper libraries. I used ofxHTTP in order to make specialized HTTP requests to HQ servers, and I also used OpenFrameworks built in networking libraries to make asynchronous requests during trivia answering, allowing for both the Google and Wikipedia results to be run at the same time rather than waiting for one to finish before running the next. I used ofxJSON in order to read the results from both the ofxHTTP requests and the async requests and process the JSON for virtually all data, that is search data, HQ live stream data, questions and answer data from the socket, question banks for testing, and more.

# Testing

## Functionality
To test functionality, there are multiple small sample tests as well as the option to run a manual question and answers and see the results. Finally there is also the option to run a large question bank of a variety of questions and see the overall accuracy and success.

## Utility testing
Since the majority of the code requires making actual calls or contacting a server, I have written large scope tests as Shell scripts which simulate an actual game to verify that it is working. To test fundamental utility methods however, I didn't want to incorporate the entire Catch framework into the environment since I already had a volatile project with Swift being compiled as well, and it was playing nicely with Catch. To get around this and still have some testing, I made the project accept a commandline argument that tells it to run a few tests to just verify the integrity of the utility methods and print out the results. These can be run using the Shell script called `HolmesTests` in the `scripts` folder.

# The future

 While the project may be done, and I'd argue a relatively decent bot, I think it has much more potential. If I were to continue working on the project, there are a few things I'd implement:
 - Classify questions into specific categories and using different searching methods depending on the type
 - Weight results based on how much of the answer it holds
 - Use Natural Language Processing to determine what parts of the answer and question are important
 - Check for singular as well as plural words
 - Do independent searches for the answers and check the question against the results
 - Provide the user with more control over how the search is implemented on the fly

 # Links and credits
 - Fonts:
    - https://fonts.google.com/specimen/Cabin
 - Libraries:
    - https://github.com/bakercp/ofxHTTP/tree/stable
    - https://github.com/bakercp/ofxIO/tree/stable
    - https://github.com/bakercp/ofxMediaType/tree/stable
    - https://github.com/bakercp/ofxSSLManager/tree/stable
    - https://github.com/bakercp/ofxTaskQueue/tree/stable
    - https://github.com/bakercp/ofxNetworkUtils/tree/stable
    - https://github.com/jeffcrouse/ofxJSON
    - https://github.com/tidwall/SwiftWebSocket

# Disclaimer

I do __NOT__ endorse cheating. Using a bot like this during a live game for the purposes of making money is strictly against HQ's Terms of Service and will result in your account being banned if you are caught. Using a bot that connects to their server is allowed but using it to win a live trivia game for money is a strict violation.
