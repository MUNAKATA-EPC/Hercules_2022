void control_LED() {
  if (digitalRead(switch_program) == HIGH) {
    digitalWrite(LED, HIGH);

  } else {
    digitalWrite(LED, LOW);
    
  }
}