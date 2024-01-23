#ifndef SERVER_WEB_H
#define SERVER_WEB_H

#include <WiFi.h>
#include <WebServer.h>

class server_web {
public:
    server_web(const char* ssid, const char* password, int port)
    : network_ssid(ssid), network_password(password), server(port) {}

    void begin() {
        WiFi.begin(network_ssid, network_password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nConnected to WiFi. IP address: ");
        Serial.println(WiFi.localIP());

        server.on("/", [this]() {
            
            server.send(200, "text/html", getHTML());
        });

        server.begin();
    }

    void handleClient() {
        server.handleClient();
    }

private:
    const char* network_ssid;
    const char* network_password;
    WebServer server;

    String getHTML() {
        String html = "<!DOCTYPE html><html><head><title>ESP32 Web Server</title></head><body>";
        html += "<h1>Welcome to the ESP32 Web Server!</h1>";
        html += "<p>This is a simple web page served from an ESP32.</p>";
        html += "</body></html>";
        return html;
    }
};

#endif // SERVER_WEB_H
