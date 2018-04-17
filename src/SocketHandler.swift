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
     * @param message the message from the socket
     * @return if the message was question data
     */
    class func isQuestionData(message : String) -> Bool {
        let isQuestion : Bool = false
        
        // Check if socket data is a question
        
        return isQuestion
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
            print("Received message: \(message)")
            self.latest_message = message
        }
    }
    
    
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
