// rps32.ino - sketch used to check the test data with the TensorFlow Lite model
#include <EloquentTinyML.h> // From https://github.com/eloquentarduino/EloquentTinyML
#include "model.h"          // From https://github.com/maarten-pennings/MachineLearning/tree/main/rock-paper-scissors
#include "test.h"           // From https://github.com/maarten-pennings/MachineLearning/tree/main/rock-paper-scissors

#define NUMBER_OF_INPUTS    (TEST_HEIGHT*TEST_WIDTH)
#define NUMBER_OF_OUTPUTS   4
#define TENSOR_ARENA_SIZE   (50*1024) // Trial and error

Eloquent::TinyML::TfLite<
    NUMBER_OF_INPUTS, 
    NUMBER_OF_OUTPUTS, 
    TENSOR_ARENA_SIZE
> tflu;

void setup() {
  Serial.begin(115200);
  while( !Serial ) delay(100);
  Serial.printf("\nrps32\n");
  tflu.begin(model_data);
}

int count = 0;

void loop() {
  if( count>=TEST_COUNT ) return;
  
  Serial.printf("image %04d ", count); 

  float output[NUMBER_OF_OUTPUTS];
  uint32_t time0 = micros();
  tflu.predict((float*)&test_data[count],output);
  uint32_t time1 = micros();
  Serial.printf("n=%.4f p=%.4f r=%.4f s=%.4f time=%uus\n",output[0],output[1],output[2],output[3], time1-time0);

  count++;
}
