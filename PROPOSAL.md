# Project Proposal - `Holmes`
Watson may have won Jeopardy, but Jeopardy is our parents game. `Holmes` will win live trivia.

## Requirements
- openFrameworks: `Holmes` will have a graphical interface that shows the statistical breakdown of various answers as well as the question it received.
- Windowed application: as described above, `Holmes` will have a visual interface of windowed GUI
- Significant library: `Holmes` will use a JSON/HTTP library to interface with the Google Custom Search REST API. It will then attempt to guess the correct answer to a given question and display all the information in a visual window. (Additionally I hope to hook into websockets using another library but that is a side project).

## The What
Apps like HQ and Cash Show have taken the internet, and our phones, by storm. They now boast millions of users, giving out thousands of dollars a day. As a person who has won both trivia shows before, I can verify that you can make money (for me, over $100 so far) if you're good at it. However, I say that machines can do it better. I threw together a very quick and dirty, hacked-together application in Java over a single weekend that has won games before but it has no graphical interface, no robustness, no customizable active areas, and everything is hard coded, and its search relies entirely on the user, simply opening a google page to look at. I hope to make an application using C++ and openFrameworks that focuses primarily on knowledge gathering, and by that I mean it will take a question and three possible answers (one of them being guaranteed to be correct) and, via searches, determine the likelihood of each answer being the correct one. If I have time, this will extend to then automatically pulling questions and answers straight from the game in order to automatically play, but again, the main focus is the question/answer GUI and searching algorithm.

## The How
- I will start by implementing the Knowledge component, which will simply accept a question, the three possible answers, and then rate the likelihood of each answer being correct. This will be the core of the program. Time-permitting, I shall move on to implementing question/answer feeding via one of three methods. Based on preliminary research, it seems that OpenFrameworks and Tesseract's connections are no longer properly maintained and so that may be extremely difficult if not impossible to recover. Direct feeding will be simple enough to incorporate. The real question comes down to if I have enough time to probe a trivia app's external API to determine how to trick it into believing I am a phone and getting it to stream me answers.

##### Three possible strategies for question/answer feeding:
1. Direct feed via command line arguments.
2. Use Optical Character Recognition, OCR for short, to read questions and answers from a pre-defined "active area" as dictated by the user via a graphical interface. The application would then be capable of reading and then searching the internet for the most likely answer to the question, ideally fast enough that it can win a game of trivia without a human.
3. Use mitmproxy to detect the external API used by the show using a Man-In-The-Middle strategy in order to read the https calls. Hook into the websocket by faking authentication as a device with custom headers and then getting the questions through the API. It would then apply the same search mechanism as the OCR strategy which would likely require either API calls via Google, or web-crawling using a sever side script written in PHP that returns usable JSON.

## The Why
Computers are smarter than people in many ways. When it comes to our smartphones, our most cherished devices and potentially best friends, I intend to show that computers are still our superior. Knowledge is knowledge regardless of where it comes from. The question is, in an age where information is at our fingertips, is Computer Science the most valuable knowledge of all?

## The Who
Name based off of Sherlock `Holmes` (not Pete Townshend), both a pun on the fact that IBM built the machine Watson, and that Sherlock `Holmes` was supposed to be a deductive genius.

### Links
##### OCR:
- https://github.com/tesseract-ocr/tesseract
- https://github.com/kylemcdonald/ofxTesseract
##### WebSocket:
- https://mitmproxy.org
- https://github.com/bakercp/ofxHTTP
- https://github.com/bakercp/ofxIO
- https://github.com/bakercp/ofxMediaType
- https://github.com/bakercp/ofxNetworkUtils
- https://github.com/bakercp/ofxSSLManager
- https://github.com/bakercp/ofxTaskQueue
##### Both:
- http://openframeworks.cc/documentation/ofxGui/
- https://github.com/jeffcrouse/ofxJSON