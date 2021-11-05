void screen1() {
  if (menustate == 1) {
      display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(display_traveled_distance, 2);
  display.setCursor(10, 18);
  display.println(distance_puls);
  display.display();
  }
}

void screen2() {
  if (menustate == 2) {
      display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 0);
  display.println("fuelAVG:");
  display.setCursor(10, 18);
  display.println("8.3");
  display.setTextSize(1); // Draw 2X-scale text
  display.setCursor(50, 25);
  display.println("l/100km");
  display.display();
  }
}

void screen3() {
  if (menustate == 3) {
      display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 0);
  display.println("fuelINST:");
  display.setCursor(10, 18);
  display.println("7.5");
  display.setTextSize(1); // Draw 2X-scale text
  display.setCursor(50, 25);
  display.println("l/100km");
  display.display();
  }
}

void screen4() {
  if (menustate == 4) {
      display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 0);
  display.println("spdAVG");
  display.setCursor(10, 18);
  display.println(avg_speed,1);
  display.setTextSize(1); // Draw 2X-scale text
  display.setCursor(90, 25);
  display.println("km/h");
  display.display();
  }
}

void screen5() {
  if (menustate == 5) {
      display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 0);
  display.println("spdINST");
   display.setCursor(10, 18);
  display.println(display_speed,1);
  display.setTextSize(1); // Draw 2X-scale text
  display.setCursor(90, 18);
  display.println("km/h");
  display.display();
  }
}

void screen6() {
  if (menustate == 6) {
      display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 0);
  display.println("ON TIME");
   display.setCursor(10, 18);
  display.println(sekunda/60);
  display.setCursor(50, 18);
  display.println("min");
  display.display();
  }
}
