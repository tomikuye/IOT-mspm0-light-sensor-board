#include <ecc608.h>
#include <flash_string.h>
#include <http_client.h>
#include <led_ctrl.h>
#include <log.h>
#include <low_power.h>
#include <lte.h>
#include <mqtt_client.h>
#include <security_profile.h>
#include <sequans_controller.h>
#include <timeout_timer.h>
#include <Arduino.h>


/**
 * @brief This example demonstrates HTTP GET and POST request as well as reading
 * out the the response of the POST message.
 */


#define DOMAIN "xz2dbb5of0.execute-api.us-east-2.amazonaws.com"
int index = 0;
char uartBuffer[18];
char txt = 'k';

void setup() {
    LedCtrl.begin();
    LedCtrl.startupCycle();

    Log.begin(115200);
    Serial2.swap(1);
    Serial2.begin(9600);  // Use for your UART device=
    Log.info(F("Starting HTTP example"));

    // Start modem and connect to the operator
    if (!Lte.begin()) {
        Log.error(F("Failed to connect to the operator"));
        return;
    }

    Log.infof(F("Connected to operator: %s\r\n"), Lte.getOperator().c_str());

    // --- HTTP ---

    Log.info(F("---- Testing HTTP ----"));

    if (!HttpClient.configure(DOMAIN, 443, true)) {
        Log.info(F("Failed to configure http client\r\n"));
    }

    Log.info(F("Configured to HTTP"));

    HttpResponse response = HttpClient.post("/submit_data", "{\"Lux\": \"Hello World\"}", "Content-Type: application/json");
    Log.infof(F("POST - HTTP status code: %u, data size: %u\r\n"),
              response.status_code,
              response.data_size);

    // Add some extra bytes for termination
    String body = HttpClient.readBody(response.data_size + 16);

    if (body != "") {
        Log.infof(F("Body: %s\r\n"), body.c_str());
    }
    }

void loop() {
  while (Serial2.available()) {
    char c = Serial2.read();

    // Add to buffer if not overflowing
    if (index < sizeof(uartBuffer) - 1) {
      uartBuffer[index++] = c;

      // If end of message detected
      if (c == '\n') {
        uartBuffer[index] = '\0'; 
        Log.infof("Received UART data: %s\r\n", uartBuffer);
        String payload = String("{\"Lux\": \"") + uartBuffer + "\"}";
        HttpResponse response = HttpClient.post("/submit_data", payload.c_str(), "Content-Type: application/json");
        Log.infof(F("POST - HTTP status code: %u, data size: %u\r\n"),
              response.status_code,
              response.data_size);

    // Add some extra bytes for termination
    String body = HttpClient.readBody(response.data_size + 16);

        // Reset index for next message
        index = 0;
      }
    } else {
      // Overflow case: reset
      Log.warn(F("UART buffer overflow, resetting"));
      index = 0;
    }
  }
}
