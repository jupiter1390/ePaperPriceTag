// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0
#define COLORED
#define ESP32_C3_SUPERMINI
#define EPD_23in

#include <GxEPD2_3C.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <ArduinoBLE.h>
#include <u8g2_gulim12_mx.c>
#include <u8g2_gulim18_tx.c>
U8G2_FOR_ADAFRUIT_GFX ug82;

BLEService readESLdata("c319717b-0890-4537-aae5-7fce28699a1d");

BLEIntCharacteristic getESLName("f1803239-2460-474f-b3f1-efbbcbcdd2a4", BLERead | BLEWrite);    //ESLName
BLEIntCharacteristic getESLOrigin("4cc0aa76-3074-4cda-b8b5-cc0204f70947", BLERead | BLEWrite);  //ESLOrigin
BLEIntCharacteristic getESLUnit("32e8634f-aac8-4862-9c30-26810463ceef", BLERead | BLEWrite);    //ESLUnit
BLEIntCharacteristic getESLDate("45bdad12-2a23-4012-b3c7-168f85ea3209", BLEWrite);              //ESLDate
BLEIntCharacteristic getESLPriceOrig("59f97297-c504-4d02-93f6-62f5a683e2de", BLEWrite);         //ESLPriceOrig
BLEIntCharacteristic getESLPriceFinal("9c01385e-c103-4d8e-906f-971973ff80f4", BLEWrite);        //ESLPriceFinal
BLEIntCharacteristic getESLBarcodeData("70a984b3-38e9-4d23-a0b7-a9541463629b", BLEWrite);       //ESLBarcodeData
BLEByteCharacteristic dataStreamFin("b8132efa-54f2-4ab1-b986-52be67d7d174", BLEWrite);          //Data Stream Finish

String streamBLE_ESLName;
String streamBLE_ESLOrigin;
String streamBLE_ESLUnit;
String streamBLE_ESLDate;
String streamBLE_ESLPriceOrig;
String streamBLE_ESLPriceFinal;
String streamBLE_ESLBarcodeData;

#define LED_BUILTIN 8
#define SCL 4
#define SDA 6
#define SS 7
#define BUSY 3
#define RST 2
#define DC 1

GxEPD2_3C<GxEPD2_213_Z98c, GxEPD2_213_Z98c::HEIGHT> display(GxEPD2_213_Z98c(/*CS=5*/ SS, /*DC=*/1, /*RST=*/2, /*BUSY=*/3));  // GDEY0213Z98 122x250, SSD1680

void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);

  while (!Serial)
    ;
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1)
      ;
  }
  BLE.setLocalName("NK-BLE210");
  BLE.setAdvertisedService(readESLdata);

  readESLdata.addCharacteristic(getESLName);
  readESLdata.addCharacteristic(getESLOrigin);
  readESLdata.addCharacteristic(getESLUnit);
  readESLdata.addCharacteristic(getESLDate);
  readESLdata.addCharacteristic(getESLPriceOrig);
  readESLdata.addCharacteristic(getESLPriceFinal);
  readESLdata.addCharacteristic(getESLBarcodeData);
  readESLdata.addCharacteristic(dataStreamFin);

  BLE.addService(readESLdata);
  BLE.advertise();
  Serial.println("BLE ESL Data Reciever");
}


void PriceTag() {
  display.setRotation(3);
  display.setFullWindow();
  display.firstPage();
  do {
    // Redraw Background
    display.fillScreen(GxEPD_WHITE);

    // Sale Box
    display.fillRect(4, 28, 64, 52, GxEPD_RED);
    display.fillRect(4, 80, 64, 12, GxEPD_BLACK);
    display.drawLine(68, 28, 245, 28, GxEPD_BLACK);

    //ㅎ
    display.fillRect(13, 30, 6, 1, GxEPD_WHITE);
    display.fillRect(10, 33, 12, 1, GxEPD_WHITE);
    display.fillRect(13, 35, 6, 1, GxEPD_WHITE);
    display.fillRect(12, 36, 3, 1, GxEPD_WHITE);
    display.fillRect(11, 37, 3, 3, GxEPD_WHITE);
    display.fillRect(12, 40, 3, 1, GxEPD_WHITE);
    display.fillRect(13, 41, 6, 1, GxEPD_WHITE);
    display.fillRect(17, 36, 3, 1, GxEPD_WHITE);
    display.fillRect(18, 37, 3, 3, GxEPD_WHITE);
    display.fillRect(17, 40, 3, 1, GxEPD_WHITE);

    //ㅐ
    display.fillRect(22, 30, 3, 12, GxEPD_WHITE);
    display.fillRect(25, 36, 2, 1, GxEPD_WHITE);
    display.fillRect(27, 30, 3, 13, GxEPD_WHITE);

    //ㅇ
    display.fillRect(16, 44, 11, 1, GxEPD_WHITE);
    display.fillRect(14, 45, 4, 1, GxEPD_WHITE);
    display.fillRect(13, 46, 3, 3, GxEPD_WHITE);
    display.fillRect(14, 49, 4, 1, GxEPD_WHITE);
    display.fillRect(16, 50, 11, 1, GxEPD_WHITE);
    display.fillRect(25, 45, 4, 1, GxEPD_WHITE);
    display.fillRect(27, 46, 3, 3, GxEPD_WHITE);
    display.fillRect(25, 49, 4, 1, GxEPD_WHITE);

    //ㅅ
    display.fillRect(47, 31, 3, 6, GxEPD_WHITE);
    display.fillRect(46, 37, 5, 2, GxEPD_WHITE);
    display.fillRect(45, 39, 3, 2, GxEPD_WHITE);
    display.fillRect(44, 41, 3, 2, GxEPD_WHITE);
    display.fillRect(43, 43, 3, 2, GxEPD_WHITE);
    display.fillRect(42, 45, 3, 1, GxEPD_WHITE);
    display.fillRect(41, 46, 3, 1, GxEPD_WHITE);
    display.fillRect(40, 47, 3, 1, GxEPD_WHITE);
    display.fillRect(49, 39, 3, 2, GxEPD_WHITE);
    display.fillRect(50, 41, 3, 2, GxEPD_WHITE);
    display.fillRect(51, 43, 3, 2, GxEPD_WHITE);
    display.fillRect(52, 45, 3, 2, GxEPD_WHITE);

    //ㅏ
    display.fillRect(56, 30, 3, 21, GxEPD_WHITE);
    display.fillRect(59, 39, 3, 1, GxEPD_WHITE);

    //ㅅ
    display.fillRect(16, 57, 3, 3, GxEPD_WHITE);
    display.fillRect(15, 60, 4, 1, GxEPD_WHITE);
    display.fillRect(15, 61, 5, 1, GxEPD_WHITE);
    display.fillRect(14, 62, 3, 1, GxEPD_WHITE);
    display.fillRect(13, 63, 3, 1, GxEPD_WHITE);
    display.fillRect(12, 64, 3, 1, GxEPD_WHITE);
    display.fillRect(11, 65, 3, 1, GxEPD_WHITE);
    display.fillRect(10, 66, 3, 1, GxEPD_WHITE);
    display.fillRect(18, 62, 3, 1, GxEPD_WHITE);
    display.fillRect(19, 63, 3, 1, GxEPD_WHITE);
    display.fillRect(20, 64, 3, 1, GxEPD_WHITE);
    display.fillRect(21, 65, 3, 1, GxEPD_WHITE);

    //ㅏ
    display.fillRect(26, 56, 3, 13, GxEPD_WHITE);
    display.fillRect(29, 62, 3, 1, GxEPD_WHITE);

    //ㅇ
    display.fillRect(15, 70, 11, 1, GxEPD_WHITE);
    display.fillRect(13, 71, 4, 1, GxEPD_WHITE);
    display.fillRect(12, 72, 3, 3, GxEPD_WHITE);
    display.fillRect(13, 75, 4, 1, GxEPD_WHITE);
    display.fillRect(15, 76, 11, 1, GxEPD_WHITE);
    display.fillRect(24, 71, 4, 1, GxEPD_WHITE);
    display.fillRect(26, 72, 3, 3, GxEPD_WHITE);
    display.fillRect(24, 75, 4, 1, GxEPD_WHITE);

    //ㅍ
    display.fillRect(42, 56, 19, 1, GxEPD_WHITE);
    display.fillRect(45, 58, 3, 3, GxEPD_WHITE);
    display.fillRect(46, 61, 3, 1, GxEPD_WHITE);
    display.fillRect(42, 62, 19, 1, GxEPD_WHITE);
    display.fillRect(55, 58, 3, 3, GxEPD_WHITE);
    display.fillRect(54, 61, 3, 1, GxEPD_WHITE);

    //ㅜ
    display.fillRect(41, 65, 21, 1, GxEPD_WHITE);
    display.fillRect(50, 66, 3, 4, GxEPD_WHITE);

    //ㅁ
    display.fillRect(43, 70, 17, 7, GxEPD_WHITE);
    display.fillRect(46, 71, 11, 5, GxEPD_RED);

    // Barcode
    String BinaryRaw = Encode128(streamBLE_ESLBarcodeData);
    Binary2Bar(BinaryRaw, 113, 98, 18);
    display.fillRect(133, 107, 84, 9, GxEPD_WHITE);

    //int16_t tbx, tby;
    uint16_t tbw, tbh;
    uint16_t x = 0;
    ug82.setForegroundColor(GxEPD_BLACK);
    ug82.setBackgroundColor(GxEPD_WHITE);

    //ESLName
    ug82.setFont(u8g2_gulim18_tx);
    ug82.setFontMode(1);
    ug82.drawUTF8(5, 22, streamBLE_ESLName.c_str());
    //Thickness with transparency
    ug82.drawUTF8(6, 22, streamBLE_ESLName.c_str());

    //ESLOrigin
    ug82.setFont(u8g2_gulim12_mx);
    ug82.drawUTF8(72, 42, streamBLE_ESLOrigin.c_str());

    //ESLUnit
    ug82.drawUTF8(72, 56, streamBLE_ESLUnit.c_str());

    //ESLPriceOrig
    ug82.setFont(u8g2_font_logisoso16_tn);
    tbw = ug82.getUTF8Width(streamBLE_ESLPriceOrig.c_str());
    x = 243 - tbw;
    ug82.drawStr(x, 52, streamBLE_ESLPriceOrig.c_str());

    //ESLPriceStrikethrough
    display.fillRect(x, 43, tbw + 2, 2, GxEPD_RED);

    //ESLPriceFinal
    ug82.setFont(u8g2_font_logisoso30_tn);
    tbw = ug82.getUTF8Width(streamBLE_ESLPriceFinal.c_str());
    x = 245 - tbw;
    ug82.drawStr(x, 87, streamBLE_ESLPriceFinal.c_str());

    //ESLBarcodeData
    ug82.setFont(u8g2_font_5x7_tn);
    tbw = ug82.getUTF8Width(streamBLE_ESLBarcodeData.c_str());
    x = 175 - tbw / 2;
    ug82.drawUTF8(x, 115, streamBLE_ESLBarcodeData.c_str());

    //ESLDate
    ug82.setForegroundColor(GxEPD_WHITE);
    ug82.setBackgroundColor(GxEPD_BLACK);
    tbw = ug82.getUTF8Width(streamBLE_ESLDate.c_str());
    x = 36 - tbw / 2;
    ug82.drawUTF8(x, 89, streamBLE_ESLDate.c_str());
  } while (display.nextPage());
}


String i32t(int stream) {
  char hexRaw[10];
  String UTF8;
  itoa(stream, hexRaw, 16);
  String hexString = String(hexRaw);

  if (hexString.length() == 6) {
    char hexA[6] = {hexString.charAt(4), hexString.charAt(5), hexString.charAt(2), hexString.charAt(3)};
    char hexB[6] = {hexString.charAt(0), hexString.charAt(1)};
    uint16_t hex1 = (int)strtol(hexA, NULL, 16);
    uint16_t hex2 = (int)strtol(hexB, NULL, 16);
    uint16_t I32[] = {hex1, hex2};
    Serial.println(hexA);
    Serial.println(hexB);
    UTF8 += (char)highByte(I32[0]);
    UTF8 += (char)lowByte(I32[0]);
    UTF8 += (char)I32[1];
  }

  else if (hexString.length() == 4) {
    char hexA[6] = {hexString.charAt(2), hexString.charAt(3), hexString.charAt(0), hexString.charAt(1)};
    uint16_t hex1 = (int)strtol(hexA, NULL, 16);
    uint16_t I32[] = {hex1};
    Serial.println(hexA);
    UTF8 += (char)highByte(I32[0]);
    UTF8 += (char)lowByte(I32[0]);
  }

  else if (hexString.length() == 2) {
    char hexA[4] = {hexString.charAt(0), hexString.charAt(1)};
    uint16_t hex1 = (int)strtol(hexA, NULL, 16);
    uint16_t I32[] = {hex1};
    Serial.println(hexA);
    UTF8 = (char)I32[0];
  }

  return UTF8;
}


String Encode128(String rawdata) {
  int SecA = tenone(rawdata.charAt(0), rawdata.charAt(1));
  int SecB = tenone(rawdata.charAt(2), rawdata.charAt(3));
  int SecC = tenone(rawdata.charAt(4), rawdata.charAt(5));
  int SecD = tenone(rawdata.charAt(6), rawdata.charAt(7));
  int SecE = tenone(rawdata.charAt(8), rawdata.charAt(9));
  int SecF = tenone(rawdata.charAt(10), rawdata.charAt(11));
  char secGRaw = rawdata.charAt(12);
  int SecG = secGRaw;
  int Checksum = Checksum128(rawdata);

  String BinaryRaw = "11010011100" + Value128(SecA) + Value128(SecB) + Value128(SecC) + Value128(SecD) + Value128(SecE) + Value128(SecF) + "10111101110" + Value128(SecG) + Value128(Checksum) + "1100011101011";
  return BinaryRaw;
}


int Checksum128(String rawdata) {
  int count = 1;
  char SecM = rawdata.charAt(12);
  int SecM_int = SecM;
  int sum = 933 + SecM_int * 8;

  while (count < 7) {
    sum += (tenone(rawdata.charAt(count * 2 - 1), rawdata.charAt(count * 2))) * count;
    count += 1;
  }

  int checksum = sum % 103;

  return checksum;
}


int tenone(char ten, char one) {
  String combi = String(ten) + String(one);
  int resolve = combi.toInt();
  return resolve;
}


void Binary2Bar(String straw, int startx, int starty, int height) {
  int count = 0;
  int total = straw.length();
  int offx = startx;
  int offy = starty;

  while (count < total) {
    char currentp = straw.charAt(count);

    if (currentp != '0') {
      display.fillRect(offx, offy, 1, height, GxEPD_BLACK);
    } else {
      display.fillRect(offx, offy, 1, height, GxEPD_WHITE);
    }

    offx += 1;
    count += 1;
  }
}


char* insertX(int n, char arr[], int x, int pos) {
  int i;
  // increase the size by 1
  n++;
  // shift elements forward
  for (i = n; i >= pos; i--)
    arr[i] = arr[i - 1];
  // insert x at pos
  arr[pos - 1] = x;
  return arr;
}


String tSeparator(int input) {
  String intstr = String(input);
  char buf[32];
  intstr.toCharArray(buf, 16);
  for(int i = intstr.length() - 2; i > 0; i -= 3) {
    insertX(16, buf, ',', i);
  }
  return String(buf);
}


String Value128(int Value) {
  String Array128[] = {
    "11011001100",
    "11001101100",
    "11001100110",
    "10010011000",
    "10010001100",
    "10001001100",
    "10011001000",
    "10011000100",
    "10001100100",
    "11001001000",
    "11001000100",
    "11000100100",
    "10110011100",
    "10011011100",
    "10011001110",
    "10111001100",
    "10011101100",
    "10011100110",
    "11001110010",
    "11001011100",
    "11001001110",
    "11011100100",
    "11001110100",
    "11101101110",
    "11101001100",
    "11100101100",
    "11100100110",
    "11101100100",
    "11100110100",
    "11100110010",
    "11011011000",
    "11011000110",
    "11000110110",
    "10100011000",
    "10001011000",
    "10001000110",
    "10110001000",
    "10001101000",
    "10001100010",
    "11010001000",
    "11000101000",
    "11000100010",
    "10110111000",
    "10110001110",
    "10001101110",
    "10111011000",
    "10111000110",
    "10001110110",
    "11101110110",
    "11010001110",
    "11000101110",
    "11011101000",
    "11011100010",
    "11011101110",
    "11101011000",
    "11101000110",
    "11100010110",
    "11101101000",
    "11101100010",
    "11100011010",
    "11101111010",
    "11001000010",
    "11110001010",
    "10100110000",
    "10100001100",
    "10010110000",
    "10010000110",
    "10000101100",
    "10000100110",
    "10110010000",
    "10110000100",
    "10011010000",
    "10011000010",
    "10000110100",
    "10000110010",
    "11000010010",
    "11001010000",
    "11110111010",
    "11000010100",
    "10001111010",
    "10100111100",
    "10010111100",
    "10010011110",
    "10111100100",
    "10011110100",
    "10011110010",
    "11110100100",
    "11110010100",
    "11110010010",
    "11011011110",
    "11011110110",
    "11110110110",
    "10101111000",
    "10100011110",
    "10001011110",
    "10111101000",
    "10111100010",
    "11110101000",
    "11110100010",
    "10111011110",
    "10111101110",
    "11101011110",
    "11110101110",
    "11010000100",
    "11010010000",
    "11010011100"
  };
  return Array128[Value];
}


void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    while (central.connected()) {
      if (getESLName.written()) {
        Serial.println(getESLName.value());
        streamBLE_ESLName = streamBLE_ESLName + i32t(getESLName.value());
        Serial.println(streamBLE_ESLName);
        getESLName.writeValue(0);
      }
      if (getESLOrigin.written()) {
        streamBLE_ESLOrigin = streamBLE_ESLOrigin + i32t(getESLOrigin.value());
        Serial.println(streamBLE_ESLOrigin);
        getESLOrigin.writeValue(0);
      }
      if (getESLUnit.written()) {
        streamBLE_ESLUnit = streamBLE_ESLUnit + i32t(getESLUnit.value());
        Serial.println(streamBLE_ESLUnit);
        getESLUnit.writeValue(0);
      }
      if (getESLDate.written()) {
        streamBLE_ESLDate = String(getESLDate.value());

        if (streamBLE_ESLDate.length() == 7) {
          streamBLE_ESLDate = "0" + streamBLE_ESLDate;
        }
        char formatDate[13] = "";
        strcpy(formatDate, streamBLE_ESLDate.c_str());
        insertX(13, formatDate, '.', 3);
        insertX(13, formatDate, '-', 6);
        insertX(13, formatDate, '.', 9);
        streamBLE_ESLDate = formatDate;
        Serial.println(streamBLE_ESLDate);
      }
      if (getESLPriceOrig.written()) {
        streamBLE_ESLPriceOrig = tSeparator(getESLPriceOrig.value());
        Serial.println(streamBLE_ESLPriceOrig);
      }
      if (getESLPriceFinal.written()) {
        streamBLE_ESLPriceFinal = tSeparator(getESLPriceFinal.value());
        Serial.println(streamBLE_ESLPriceFinal);
      }
      if (getESLBarcodeData.written()) {
        //data split in 11
        streamBLE_ESLBarcodeData += String(getESLBarcodeData.value());
        Serial.println(streamBLE_ESLBarcodeData);
      }
      if (dataStreamFin.written()) {
        display.init(115200, true, 50, false);
        ug82.begin(display);
        PriceTag();
        display.hibernate();
        streamBLE_ESLName = "";
        streamBLE_ESLOrigin = "";
        streamBLE_ESLUnit = "";
        streamBLE_ESLDate = "";
        streamBLE_ESLPriceOrig = "";
        streamBLE_ESLPriceFinal = "";
        streamBLE_ESLBarcodeData = "";
      }
    }

    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}