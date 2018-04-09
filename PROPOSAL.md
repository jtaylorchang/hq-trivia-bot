# Project Proposal - `Holmes`
Watson may have won Jeopardy, but Jeopardy is our parents game. `Holmes` will win live trivia.

## Requirements
- openFrameworks: `Holmes` will have a graphical interface that allows users to select active areas (for purposes of OCR) and/or view the statistical breakdown of answers
- Windowed application: as described above, `Holmes` will have a visual interface of windowed GUI
- Significant library: `Holmes` will either use OCR (most likely via either an openFrameworks library or by Tesseract) or it will rely on mitmproxy to read questions and answers directly from traffic

## The What
Apps like HQ and Cash Show have taken the internet, and our phones, by storm. They now boast millions of users, giving out thousands of dollars a day. As a person who has won both trivia shows before, I can verify that you can make money (for me, over $100 so far) if you're good at it. However, I say that machines can do it better. I threw together a very quick and dirty, hacked-together application in Java over a single weekend that has won games before but it has no graphical interface, no robustness, no customizable active areas, and everything is hard coded. I hope to make an application using C++ and openFrameworks that blows it out of the waters, boasting a graphical interface, answer suggestions, automated web-searching, and a definable active area.

## The How
Two possible strategies:
1. Use Optical Character Recognition, OCR for short, to read questions and answers from a pre-defined "active area" as dictated by the user via a graphical interface. The application will then be capable of reading and then searching the internet for the most likely answer to the question, ideally fast enough that it can win a game of trivia without a human.
2. Use mitmproxy with a Python script that communicates with the C++ application via IPC in order to read the https calls (using a Man-In-The-Middle strategy) from the trivia show instead of relying on OCR. It would then apply the same search mechanism as the OCR strategy which would likely require either API calls via Google, or web-crawling using a sever side script written in PHP that returns usable JSON.

## The Why
Computers are smarter than people in many ways. When it comes to our smartphones, some of our most cherished devices and potentially best friends, I intend to show that computers are still our superior. Knowledge is knowledge regardless of where it comes from, so is Computer Science the most valuable of them all?

## The Who
Sherlock `Holmes`, or Pete Townshend

### Links
https://github.com/tesseract-ocr/tesseract
https://github.com/kylemcdonald/ofxTesseract
https://mitmproxy.org