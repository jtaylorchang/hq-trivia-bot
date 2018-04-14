# Project Proposal - `Holmes`
Watson may have won Jeopardy, but Jeopardy is our parents game. `Holmes` will win live trivia.

## Requirements
- openFrameworks: `Holmes` will have a graphical interface that shows the statistical breakdown of various answers as well as the question it received.
- Windowed application: as described above, `Holmes` will have a visual interface of windowed GUI
- Significant library: First, `Holmes` will use a JSON/HTTP library to access HQ's external API and pretend to be a phone, as well as using that library to call searches with Google Custom Search REST API. Furthermore, `Holmes` will use Objective-C++ wrapped by OpenFrameworks code, to call to a Swift WebSocket library that gets live trivia data once passing authentication. It will then attempt to guess the correct answer to a given question and display all the information in a visual window.

## The What
Apps like HQ and Cash Show have taken the internet, and our phones, by storm. They now boast millions of users, giving out thousands of dollars a day. As a person who has won both trivia shows before, I can verify that you can make money (for me, over $100 so far) if you're good at it. However, I say that machines can do it better. I threw together a very quick and dirty, hacked-together application in Java over a single weekend that has won games before but it has no graphical interface, no robustness, no customizable active areas, and everything is hard coded, and its search relies entirely on the user, simply opening a google page to look at. I hope to make an application using C++ and openFrameworks that focuses primarily on knowledge gathering, and by that I mean it will take a question and three possible answers (one of them being guaranteed to be correct) and, via searches, determine the likelihood of each answer being the correct one. It will also then automatically pull questions and potential answers straight from the game in order to automatically play, but again, the main focus is the question/answer GUI and searching algorithm.

## The How
I will start by implementing the C++ to Swift bridge component, allowing me to write both the code to answer questions as well as the code to get the questions in two different languages and then mesh them properly. Once questions are being streamed from Swift to C++, I will write the question/answer code (or as I am calling "Sleuth") which will simply accept a question, the three possible answers, and then rate the likelihood of each answer being correct. This will be the core of the program. Finally, using OpenFrameworks ofxGUI, I will render a representation of the results.

##### The How: Sleuth:
Use mitmproxy to detect the external API used by the app using a Man-In-The-Middle strategy in order to read the https calls. The idea is that in order for your phone to display live trivia, they must be sending live data. So if we position ourselves in between the HQ server and the HQ client, we can read this data before it is even displayed. Once the data has been received, we will hook into the websocket by faking authentication as a device with custom headers and then filter the incoming traffic to just look at questions and answers.

## The Why
Computers are smarter than people in many ways. When it comes to our smartphones, our most cherished devices and potentially best friends, I intend to show that computers are still our superior. Knowledge is knowledge regardless of where it comes from. The question is, in an age where information is at our fingertips, is Computer Science the most valuable knowledge of all?

## The Who
Name based off of Sherlock `Holmes` (not Pete Townshend), both a pun on the fact that IBM built the machine Watson, and that Sherlock `Holmes` was supposed to be a deductive genius.

## Goals
##### Base Goal (things that definitely will be included)
- Connect to HQ server as proof of concept
- Provide basic guess based on single Google search and simple weighting based on frequency of answer occurring
- Display result visually

##### Stretch Goals (things that may be either impossible or too time-consuming)
- Connect to HQ server and receive live question data
- Provide enhanced guess using multiple searches as well as using more than just Google
  - Wikipedia
  - Yahoo
  - etc
- Handle different kinds of questions like "which of the following" vs "what"
- Accept questions and answers over commandline as well as socket

### Links
##### MITM (Man-In-The-Middle):
- https://mitmproxy.org
- https://github.com/tidwall/SwiftWebSocket
- https://github.com/bakercp/ofxHTTP
- https://github.com/bakercp/ofxIO
- https://github.com/bakercp/ofxMediaType
- https://github.com/bakercp/ofxNetworkUtils
- https://github.com/bakercp/ofxSSLManager
- https://github.com/bakercp/ofxTaskQueue
##### Sleuth:
- http://openframeworks.cc/documentation/ofxGui/
- https://github.com/jeffcrouse/ofxJSON