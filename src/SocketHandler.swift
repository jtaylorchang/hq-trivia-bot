import Foundation

@objc public class SocketHandler : NSObject {
    
    static var socket : WebSocket = WebSocket();
    @objc public static var connected : Bool = false
    
    @objc public static var url : String = ""
    @objc public static var custom_header_keys : [String] = []
    @objc public static var custom_header_values : [String] = []
    
    @objc public static var latest_message : String = ""
    @objc public static var payload : String = ""
    
    @objc public class func send() {
        if (payload.isEmpty) {
            print("No payload was chosen");
            socket.send("no payload");
        } else {
            print("Attempting to send: \(payload)");
            socket.send(payload);
            payload = "";
        }
    }
    
    @objc public class func connect() {
        // replace https:// with wss://
        var request : URLRequest = URLRequest(url: URL(string: url)!);
        request.timeoutInterval = 5
        request.addValue("iOS/1.3.2 b84", forHTTPHeaderField: "x-hq-client")
        request.addValue("Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VySWQiOjEwMDk4MDUzLCJ1c2VybmFtZSI6IjEyMzQ1Njc4OTEwMTEiLCJhdmF0YXJVcmwiOiJzMzovL2h5cGVzcGFjZS1xdWl6L2RlZmF1bHRfYXZhdGFycy9VbnRpdGxlZC0xXzAwMDRfZ29sZC5wbmciLCJ0b2tlbiI6bnVsbCwicm9sZXMiOltdLCJjbGllbnQiOiIiLCJndWVzdElkIjpudWxsLCJ2IjoxLCJpYXQiOjE1MTk1MTE5NTksImV4cCI6MTUyNzI4Nzk1OSwiaXNzIjoiaHlwZXF1aXovMSJ9.AoMWU1tj7w0KXYcrm0a8UwxjA0g_xuPehOAAMlPnWNY", forHTTPHeaderField: "Authorization")
        request.addValue("MQ==", forHTTPHeaderField: "x-hq-stk")
        request.addValue("api-quiz.hype.space", forHTTPHeaderField: "Host")
        request.addValue("Keep-Alive", forHTTPHeaderField: "Connection")
        request.addValue("gzip", forHTTPHeaderField: "Accept-Encoding")
        request.addValue("okhttp/3.8.0", forHTTPHeaderField: "User-Agent")
        socket = WebSocket(request: request);
        print("Attemping connection: \(url)");
        
        socket.event.open = {
            print("Opened connection \(self.url)");
            self.connected = true
        }
        
        socket.event.close = { code, reason, clean in
            self.connected = false
        }
        
        socket.event.error = { error in
            print("Encountered error: \(error)");
            self.connected = false
        }
        
        socket.event.message = { message in
            if let text = message as? String {
                print("Received message: \(text)");
                self.latest_message = text
            }
        }
    }
    
}
