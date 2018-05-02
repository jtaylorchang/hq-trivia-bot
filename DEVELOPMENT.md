# CS 126 FinalProject

## Timeline
A (somewhat) flexible order of events and ideal deadlines

## Week 1 - (April 10 - April 17)
- [x] Objective-C++ to Swift bridge (requires conversion to .mm files for OpenFrameworks)
- [x] Gather data on appropriate headers using MITM
- [x] Send http request to HQ to get socket url
- [x] Connect to socket and send question JSON back to C++ code
- [x] Render basic GUI in OpenFrameworks

## Week 2 - (April 17 - April 24)
- [x] Get JSON search results using Google Custom Search REST API
- [x] Generate a weighting for each answer
- [x] Try to distribute searches over multiple API's
- [x] Improve rendering of results as GUI
- [x] Accept data over commandline arguments (makes testing easier)
- [x] Create shell script to run command line questions
- [x] Create shell auto test scripts to run question answer scenarios

## Week 3 - (April 24 - May 1)
- [x] Write script to automatically determine accuracy of Holmes with larger sample set
- [x] Tested weighting based on how early a result comes up
- [x] Convert number answers to english representations and check for those as well
- [x] More complex weighting using multiple sources like Wikipedia
- [x] Filter some simple small words to avoid result confusion
- [x] Handles negation questions and chooses least results
- [x] Provide comprehensive results after automated accuracy testing
- [x] Added basic tests to check utility functions operated properly
- [x] Update README.md to have final project information and how-to guide