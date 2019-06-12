#include <Arduino.h>
#include <ESPectro32_Board.h>
#include <ESPectro32_LedMatrix_Animation.h>
ESPectro32_LedMatrix_Animation ledMatrixAnim;

#include <ESPectro32_RGBLED_Animation.h>
RgbLedColor_t aCol(254, 0, 0);
ESPectro32_RGBLED_GlowingAnimation glowAnim(ESPectro32.RgbLed(), aCol);


#include <Wire.h>
#include <AloraSensorKit.h>
// Use 13 for Alora board v2.2
#define ENABLE_PIN 16

// Use LOW for Alora board v2.2
#define ENABLE_PIN_ACTIVE_LOGIC HIGH

AloraSensorKit sensorKit(ENABLE_PIN, ENABLE_PIN_ACTIVE_LOGIC);


void setup() {
	ESPectro32.begin();
    ESPectro32.begin();
	ESPectro32.LED().setAnimation(ESPectro_LED_Animation_Fading, 3000, 3);

	glowAnim.start(3000, 3);
    

	ledMatrixAnim.setLedMatrix(ESPectro32.LedMatrix());
	ledMatrixAnim.addFrameWithData((uint8_t*)LED_MATRIX_ICON_HEART);
	ledMatrixAnim.addFrameWithData((uint8_t*)LED_MATRIX_ICON_HEART_OUTLINE);
	ledMatrixAnim.addFrameWithData((uint8_t*)LED_MATRIX_ICON_HEART);
	ledMatrixAnim.addFrameWithData((uint8_t*)LED_MATRIX_ICON_HEART_OUTLINE);
	ledMatrixAnim.addFrameWithDataCallback([](ESPectro32_LedMatrix &ledM) {
		ledM.drawCircle(3, 3, 3, 1000);
	});
	ledMatrixAnim.addFrameWithDataCallback([](ESPectro32_LedMatrix &ledM) {
		ledM.fillCircle(3, 3, 3, 1000);
	});

	ledMatrixAnim.start(3000);


    // NOTE: in case the process hang right after initializing alora library, uncomment this line below:
    // Wire.begin();
    Serial.begin(9600);
    sensorKit.begin();
}
void loop() {
    // read all sensors
    sensorKit.run();

    // get sensor values
    SensorValues sensorData = sensorKit.getLastSensorData();

    // sensorData.T1 and sensorData.T2 are temperature sensor data
    Serial.print("Temperature data:");
    Serial.println(sensorData.T1);

    // sensorData.H1 and sensorData.H2 are humidity sensor data
    Serial.println("Humidity data:");
    Serial.println(sensorData.H1);

    delay(1000);

}