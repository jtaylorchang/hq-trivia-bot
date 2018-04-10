# Project Proposal - `Holmes`
Watson may have won Jeopardy, but Jeopardy is our parents game. `Holmes` will win live trivia.

## Requirements
- openFrameworks: `Holmes` will have a graphical interface that allows users to select active areas (for purposes of OCR) and/or view the statistical breakdown of answers
- Windowed application: as described above, `Holmes` will have a visual interface of windowed GUI
- Significant library: `Holmes` will either use OCR (most likely via either an openFrameworks library or by Tesseract or both) or it will rely on mitmproxy to read questions and answers directly from traffic. It will also use a JSON library to read the results from the Google Custom Search REST API.

## The What
Apps like HQ and Cash Show have taken the internet, and our phones, by storm. They now boast millions of users, giving out thousands of dollars a day. As a person who has won both trivia shows before, I can verify that you can make money (for me, over $100 so far) if you're good at it. However, I say that machines can do it better. I threw together a very quick and dirty, hacked-together application in Java over a single weekend that has won games before but it has no graphical interface, no robustness, no customizable active areas, and everything is hard coded, and its search relies entirely on the user, simply opening a google page to look at. I hope to make an application using C++ and openFrameworks that blows it out of the waters, boasting a graphical interface, answer suggestions, automated web-searching, and a definable active area.

## The How
Two possible strategies:
1. Use Optical Character Recognition, OCR for short, to read questions and answers from a pre-defined "active area" as dictated by the user via a graphical interface. The application would then be capable of reading and then searching the internet for the most likely answer to the question, ideally fast enough that it can win a game of trivia without a human.
2. Use mitmproxy to detect the external API used by the show using a Man-In-The-Middle strategy in order to read the https calls. Hook into the websocket by faking authentication as a device with custom headers and then getting the questions through the API. It would then apply the same search mechanism as the OCR strategy which would likely require either API calls via Google, or web-crawling using a sever side script written in PHP that returns usable JSON.
- I will start by attempting to implement the OCR functionality first, and then, time-permitting, attempt to additionally add web-socket support.

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
- https://github.com/robotconscience/ofxLibwebsockets
##### Both:
- https://github.com/jeffcrouse/ofxJSON