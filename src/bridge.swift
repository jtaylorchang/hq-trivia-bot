import Foundation

@objc open class TestClass : NSObject {
    
    @objc public var message : String? = ""
    
    public override init() {
        
    }
    
    /**
     * Example code from WebSocket library
     */
    func echoTest(){
        var messageNum = 0
        let ws = WebSocket("wss://echo.websocket.org")
        let send : ()->() = {
            messageNum += 1
            let msg = "\(messageNum): \(NSDate().description)"
            print("send: \(msg)")
            ws.send(msg)
        }
        ws.event.open = {
            print("opened")
            send()
        }
        ws.event.close = { code, reason, clean in
            print("close")
        }
        ws.event.error = { error in
            print("error \(error)")
        }
        ws.event.message = { message in
            if let text = message as? String {
                print("recv: \(text)")
                if messageNum == 10 {
                    self.message = "Received 10 bytes via Web Socket from echo target";
                    ws.close()
                } else {
                    send()
                }
            }
        }
    }
}
