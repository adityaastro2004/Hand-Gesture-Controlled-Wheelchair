#include <esp_now.h>
#include <WiFi.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu;
bool dmpReady = false;
uint8_t devStatus;
uint8_t fifoBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];
uint8_t receiverMacAddress[] = {0xCC,0xDB,0xA7,0x54,0x8A,0x20};
struct PacketData {
  byte xAxisValue;
  byte yAxisValue;
  byte zAxisValue;  
};
PacketData data;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{}

void setupMPU()
{
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      Wire.setClock(400000);
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif

  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  if (devStatus == 0) 
  {
      mpu.CalibrateAccel(6);
      mpu.CalibrateGyro(6);
      mpu.setDMPEnabled(true);
      dmpReady = true;
  } 
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(peerInfo));
  memcpy(peerInfo.peer_addr, receiverMacAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }    

  setupMPU();  
}

void loop() 
{
  if (!dmpReady) return;
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) 
  {  
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    int xAxisValue = constrain(ypr[2] * 180/M_PI, -90, 90);
    int yAxisValue = constrain(ypr[1] * 180/M_PI, -90, 90);
    int zAxisValue = constrain(ypr[0] * 180/M_PI, -90, 90);    
    data.xAxisValue = map(xAxisValue, -90, 90, 0, 254); 
    data.yAxisValue = map(yAxisValue, -90, 90, 0, 254);
    data.zAxisValue = map(zAxisValue, -90, 90, 0, 254);    

    esp_err_t result = esp_now_send(receiverMacAddress, (uint8_t *) &data, sizeof(data));

    String inputData = "values " + String(xAxisValue) + "  " + String(yAxisValue) + "  " + String(zAxisValue);
    Serial.println(inputData);
    delay(50);            
  }
}
