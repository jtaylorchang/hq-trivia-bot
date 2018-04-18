import Foundation

@objc public class SocketHandler : NSObject {
    
    static var socket : WebSocket = WebSocket();
    @objc public static var connected : Bool = false
    
    @objc public static var url : String = ""
    @objc public static var custom_header_keys : [String] = []
    @objc public static var custom_header_values : [String] = []
    
    @objc public static var latest_message : String = ""
    
    /**
     * Alter the provided URL to have proper web socket format
     */
    @objc class func processUrl() {
        url = url.replacingOccurrences(of: "https://", with: "wss://");
    }
    
    /**
     * Check if the given message from the web socket was question data
     *
     * Sample data:
     * {"type":"question","ts":"2018-04-18T19:08:51.899Z","totalTimeMs":10000,"timeLeftMs":10000,"questionId":35483,"question":"The MLB World Series determines the winner of what sport?","category":"Sports","answers":[{"answerId":108506,"text":"Tetherball"},{"answerId":108507,"text":"Foosball"},{"answerId":108508,"text":"Baseball"}],"questionNumber":2,"questionCount":12,"askTime":"2018-04-18T19:08:51.899Z","c":2,"sent":"2018-04-18T19:08:52.011Z"}
     *
     *
     * @param message the message from the socket
     * @return if the message was question data
     */
    class func isQuestionData(message : String) -> Bool {
        if (message.contains("\"type\":\"question\"")) {
            return true;
        } else {
            return true;
        }
    }
    
    /**
     * Check if the broadcast has timed out and needs to be reconnected
     *
     * Sample data:
     * {"type":"broadcastEnded","ts":"2018-04-18T19:12:23.098Z","reason":"You are no longer in the game. Please join again.","sent":"2018-04-18T19:12:23.098Z"}
     */
    class func isBroadcastEnded(message : String) -> Bool {
        return false;
    }
    
    /**
     * Apply the custom headers to the given URLRequest object passed by reference
     *
     * @param request the request object to apply headers to
     */
    class func applyHeaders(request : inout URLRequest) {
        request.timeoutInterval = 5
        
        for i in 0 ..< custom_header_keys.count {
            request.addValue(custom_header_values[i], forHTTPHeaderField: custom_header_keys[i])
        }
    }
    
    class func processMessage(message : String) {
        if (isQuestionData(message: message)) {
            print("Received message:")
            print("\(message)")
            self.latest_message = message
        } else if (isBroadcastEnded(message: message)) {
            
        }
    }
    
    /**
     * Connect to the web socket
     */
    @objc public class func connect() {
        // replace https:// with wss://
        processUrl()
        
        var request : URLRequest = URLRequest(url: URL(string: url)!);
        applyHeaders(request: &request)
        
        // code derived from exampls:
        // https://github.com/tidwall/SwiftWebSocket
        socket = WebSocket(request: request)
        print("Attemping connection: \(url)")
        
        socket.event.open = {
            print("Opened connection \(self.url)")
            self.connected = true
        }
        
        socket.event.close = { code, reason, clean in
            self.connected = false
        }
        
        socket.event.error = { error in
            print("Encountered error: \(error)")
            self.connected = false
        }
        
        socket.event.message = { message in
            if let text = message as? String {
                processMessage(message: text)
            }
        }
    }
    
}
