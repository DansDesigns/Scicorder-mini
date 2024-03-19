
void ButtonTone() {
  //tone(Tones, 1276);
  dac1.enable();
  dac1.outputCW(1276);
  delay(20);
  dac1.disable();
  //noTone(Tones);
  //delay(500);
}



//EOF
