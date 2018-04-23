//@TODO: Do something with this code
// struct Pedal {
//     int state[2]; //{0,1}
//     int port; //PORTB
//     int pins[2]; // {PB3, PB4}
// };
//
// void setPedalOrder(uint8_t byte) {
//     Pedal pedals[LOOP_COUNT] = createPedalsFromByte(byte);
//
//     //Set the input loop
//     setLoop(0, pedals[0]);
//
//     for(int i = 1; i < LOOP_COUNT; i++) {
//         setLoop(pedals[i]);
//     }
//
//     //Set the output loop
//     setLoop(LOOP_COUNT + 1, pedals[LOOP_COUNT]);
// }
//
// void setLoop(int loop, Pedal pedal) {
//     for(int i = 0; i < 2; i++) {
//         pedal.port |= pedal.state[i] << pedal.ports[i];
//     }
// }
