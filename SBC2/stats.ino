void saveData(){
    EEPROM.write(2, max_speed);
    EEPROM.write(3, avg_speed);
    EEPROM.write(4, average_fuel_consumption);
    EEPROM.write(5, display_traveled_distance);
  }
  
  void loadData(){
    EEPROM.read(2);
    EEPROM.read(2);
    EEPROM.read(3);
    EEPROM.read(4);
    EEPROM.read(5);
    max_speed= EEPROM.read(2);
    if (isnan (EEPROM.read(2))) max_speed=0;

    avg_speed= EEPROM.read(3);
    if (isnan (EEPROM.read(3))) avg_speed=0;

    average_fuel_consumption= EEPROM.read(4);
    if (isnan (EEPROM.read(4))) average_fuel_consumption=0;

    display_traveled_distance= EEPROM.read(5);
    if (isnan (EEPROM.read(5))) display_traveled_distance=0;
    
    
  }
  
  void maxSpeed(){
    if (speed > max_speed) max_speed = speed;
  }
  
  void avgSpeed(){
    all_speed_values += speed;
    avg_speed = all_speed_values / avg_speed_divider;
    
  }
  
  
   void distance_count(){
    distance_puls++;
    distance_pulse_count++;
    traveled_distance += pulse_distance;
    temp_distance_pulse_count++;
    
  }
  
  void injector_count(){
    
    if (digitalRead(1) == LOW) {
    injTime1 = micros();
    }
    else {
    injTime2=micros();
    injector_pulse_time= injector_pulse_time + (injTime2 - injTime1);
    temp_injector_pulse_time = temp_injector_pulse_time + (injTime2 - injTime1);
    digitalWrite(1, HIGH);
    }
  
  }
  
  
  void currentSpeed(){
    if(speed ==0 && distance_pulse_count >20){
      traveled_distance -= pulse_distance * distance_pulse_count;
    }
    speed = pulse_distance* distance_pulse_count *3600;
  }
  
  void fuel_consumption(){
    injector_open_time = ((double)injector_pulse_time / 1000000);
    
    if (speed>3){
      instant_fuel_consumption = (100 * (((injector_open_time * injector_value)*3600)*4)) / speed;
      all_fuel_consumption_values += instant_fuel_consumption;
      average_fuel_consumption = all_fuel_consumption_values / avg_speed_divider;
    }
    else instant_fuel_consumption = ((injector_open_time * injector_value)*3600) * 4;
    
    if(speed ==0 && instant_fuel_consumption >5 || instant_fuel_consumption > 80){
      instant_fuel_consumption = 0;
      injector_open_time = 0;
      
    }
    
    used_fuel += ((injector_open_time * injector_value)*4);
    if (tank_capacity > 0) tank_capacity = 45 - used_fuel;
  }
  
  
  
  
ISR(TIMER1_OVF_vect) { 
    counter++;
    
    if (temp_injector_pulse_time <800 && temp_distance_pulse_count ==0 && to_be_saved ==1) saveData();
    if (save_counter > 45 && speed ==0 && to_be_saved ==1 ) saveData();
    temp_injector_pulse_time=0;
    temp_distance_pulse_count =0;
    
    if(counter>3){ 
      sekunda++;
      currentSpeed();
      fuel_consumption();
      
      if (instant_fuel_consumption >0.3) to_be_saved=1;
     
      if (speed >3) {
       avg_speed_divider++;
       avgSpeed();
       maxSpeed();
     }
      save_counter++;
      distance_pulse_count = 0;
      counter = 0;
      injector_pulse_time=0;
      
      display_instant_fuel_consumption = instant_fuel_consumption;
      display_traveled_distance = traveled_distance;
      display_speed = speed;
  } 
    TCNT1 = 3036; 
  }
  
