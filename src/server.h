#ifndef SERVER_WEB_H
#define SERVER_WEB_H

#include <WiFi.h>
#include <WebServer.h>
#include <functional>

// FIXME: xDDDDDDDDD ????????
typedef void (*ToggleFunction)();
// ezebarti pour un autre
typedef std::function<bool()> ToggleMusicFunction;

class server_web
{
public:
    server_web(const char *ssid, const char *password, int port,
               ToggleFunction sensorCallback, ToggleMusicFunction musicCallback)
        : network_ssid(ssid), network_password(password), server(port),
          toggleSensor(sensorCallback), toggleMusic(musicCallback),
          isMusicPlaying(false) {}

    void begin()
    {
        WiFi.begin(network_ssid, network_password);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nConnected to WiFi. IP address: ");
        Serial.println(WiFi.localIP());

        server.on("/", [this]()
                  { server.send(200, "text/html", getHTML()); });

        server.on("/toggleMotion", [this]()
                  {
            toggleSensor();
            server.send(200, "text/plain", "Motion Detection Toggled"); });

        server.on("/playMusic", [this]()
                  {
                bool musicState = toggleMusic();
                server.send(200, "text/plain", musicState ? "Music Playing" : "Music Stopped"); });

        server.begin();
    }

    void handleClient()
    {
        server.handleClient();
    }

private:
    const char *network_ssid;
    const char *network_password;
    WebServer server;

    String getHTML()
    {
        String html = "<!DOCTYPE html>";
        html += "<html>";
        html += "  <head>";
        html += "    <style>";
        html += "      body {";
        html += "        margin: 0;";
        html += "        background-color: rgb(26, 26, 26);";
        html += "        font-family: \" Segoe UI \", Tahoma, Geneva, Verdana, sans-serif;";
        html += "      }";
        html += "      h1 {";
        html += "        color: white;";
        html += "        text-align: center;";
        html += "      }";
        html += "      button {";
        html += "        margin: 10px;";
        html += "        padding: 10px;";
        html += "        border-radius: 4px;";
        html += "      }";
        html += "      .title_section {";
        html += "        color: rgb(185, 185, 185);";
        html += "      }";
        html += "      .sections {";
        html += "        margin-left: 15px;";
        html += "      }";
        html += "";
        html += "      .button {";
        html += "        background-color: #222;";
        html += "        border-radius: 4px;";
        html += "        border-style: none;";
        html += "        box-sizing: border-box;";
        html += "        color: #fff;";
        html += "        cursor: pointer;";
        html += "        display: inline-block;";
        html += "        font-family: \" Farfetch Basis \", \" Helvetica Neue \", Arial, sans-serif;";
        html += "        font-size: 16px;";
        html += "        font-weight: 700;";
        html += "        line-height: 1.5;";
        html += "        margin: 0;";
        html += "        min-height: 44px;";
        html += "        min-width: 240px;";
        html += "        max-width: 240px;";
        html += "        outline: none;";
        html += "        overflow: hidden;";
        html += "        padding: 9px 20px 8px;";
        html += "        position: relative;";
        html += "        text-align: center;";
        html += "        text-transform: none;";
        html += "        user-select: none;";
        html += "        -webkit-user-select: none;";
        html += "        touch-action: manipulation;";
        html += "      }";
        html += "";
        html += "      .button:hover,";
        html += "      .button:focus {";
        html += "        opacity: 0.75;";
        html += "      }";
        html += "";
        html += "      hr {";
        html += "        height: 1px;";
        html += "        background-color: #3a3a3a;";
        html += "        border: none;";
        html += "        margin-left: -15px;";
        html += "      }";
        html += "    </style>";
        html += "    <title>ESP32 Web Server</title>";
        html += "  </head>";
        html += "  <body>";
        html += "    <h1>Welcome to our project Dashboard!</h1>";
        html += "    <hr />";
        html += "    <div class=\" sections \">";
        html += "      <h3 class=\" title_section \">Manage Components</h3>";
        html += "      <button";
        html += "        class=\" button \"";
        html += "        id=\" motionButton \"";
        html += "        onclick=\" toggleMotionDetection() \"";
        html += "      >";
        html += "        Disable Motion Detection";
        html += "      </button>";
        html += "      <button class=\" button \" id=\" musicButton \" onclick=\" togglePlayMusic() \">";
        html += "        Play Music";
        html += "      </button>";
        html += "      <hr />";
        html += "      <h3 class=\" title_section \">Be an artist</h3>";
        html += "    </div>";
        html += "";
        html += "    <script>";
        html += "      var isMotionDetectionEnabled = true;";
        html += "      var isMusicPlaying = false;";
        html += "";
        html += "      function toggleMotionDetection() {";
        html += "        isMotionDetectionEnabled = !isMotionDetectionEnabled;";
        html += "        fetch(\"/toggleMotion\");";
        html += "        document.getElementById(\"motionButton\").innerText =";
        html += "          isMotionDetectionEnabled";
        html += "            ? \" Disable Motion Detection \"";
        html += "            : \" Enable Motion Detection \";";
        html += "      }";
        html += "";
        html += "      function togglePlayMusic() {";
        html += "        isMusicPlaying = !isMusicPlaying;";
        html += "        fetch(\"/playMusic \");";
        html += "        document.getElementById(\"musicButton\").innerText = isMusicPlaying";
        html += "          ? \" Stop Music \"";
        html += "          : \" Play Music \";";
        html += "      }";
        html += "    </script>";
        html += "  </body>";
        html += "</html>";
        return html;
    }

    bool isMusicPlaying;
    ToggleFunction toggleSensor;
    ToggleMusicFunction toggleMusic;
};

#endif // SERVER_WEB_H
