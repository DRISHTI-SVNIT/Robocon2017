#ifndef ENCODERGREY_H
#define ENCODERGREY_H
#define max_encoders 8

struct encoder
{
    int pin_a;
    int pin_b;
    volatile long value;
    volatile int lastEncoded;
};


//Pre-allocate encoder objects on the stack so we don't have to 
//worry about freeing them

/*
  Should be run for every rotary encoder you want to control
  Returns a pointer to the new rotary encoder structer
  The pointer will be NULL is the function failed for any reason
*/
struct encoder *setupencoder(int pin_a, int pin_b);

void resetEncoder(struct encoder *encoder_);

#endif 
