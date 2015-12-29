#define VERSION               "0.0.1"
#define SERIAL_SPEED          115200
#define INPUT_ROW_0           2
#define INPUT_ROW_1           3
#define OUTPUT_COL_0          4
#define OUTPUT_COL_1          5
#define ROWS_COUNT            2
#define COLS_COUNT            2


void setup() {
  pinMode(INPUT_ROW_0, INPUT);
  pinMode(INPUT_ROW_1, INPUT);
  pinMode(OUTPUT_COL_0, OUTPUT);
  pinMode(OUTPUT_COL_1, OUTPUT);

  Serial.begin(SERIAL_SPEED);

  Serial.println("keyboard " VERSION " OK");
}

void loop() {
  int ir = 0;
  int ic = 0;

  for (ic = 0; ic < COLS_COUNT; ic += 1) {
    digitalWrite(OUTPUT_COL_0 + ic, HIGH);

    for (ir = 0; ir < ROWS_COUNT; ir += 1) {
      if (digitalRead(INPUT_ROW_0 + ir)) {
        Serial.print("KEY: ");
        Serial.print(ic);
        Serial.print("*");
        Serial.print(ir);
        Serial.println("");
      }
    }

    digitalWrite(OUTPUT_COL_0 + ic, LOW);
  }

  delay(8);
}
