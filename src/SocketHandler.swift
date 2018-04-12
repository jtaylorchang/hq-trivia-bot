import Foundation

@objc public class SocketHandler : NSObject {
    
    @objc public static var url : String = ""
    @objc public static var custom_headers : [String] = []
    @objc public static var latest_message : String = ""
    static var socket : WebSocket = WebSocket();
    
    @objc public static var payload : String = ""
    
    public override init() {
        super.init();
    }
    
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
        socket = WebSocket(url);
        print("Attemping connection: \(url)");
        
        socket.event.open = {
            print("Opened connection \(self.url)");
        }
        
        socket.event.close = { code, reason, clean in
            
        }
        
        socket.event.error = { error in
            print("Encountered error: \(error)");
        }
        
        socket.event.message = { message in
            if let text = message as? String {
                print("Received message: \(text)");
                self.latest_message = text
            }
        }
    }
    
}
