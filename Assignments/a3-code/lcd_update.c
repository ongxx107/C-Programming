// Ren Jeik Ong ongxx107
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "lcd.h"

/*
this function is called to get hour, minute, second, and am/pm from time_of_day_sec
int set_tod_from_secs(int time_of_day_sec, tod_t *tod){
  if (time_of_day_sec > 86400 || time_of_day_sec <0){
      return 1;
  }
  short remainder = time_of_day_sec % 3600;
  short hour = (time_of_day_sec-remainder)/3600;
  short minute = (remainder-(remainder%60))/60;
  short second = remainder%60;
  char isPm = 0;
  if (time_of_day_sec < 60*60){ // if the time is before 1am
    hour = 12;
    minute = (time_of_day_sec-(time_of_day_sec % 60)) / 60;
    second = time_of_day_sec % 60;
    isPm = 0;
  }

  if (hour > 12){           // if the time is after 12pm
    hour = hour%12;
  }

  if (time_of_day_sec < 12*60*60){  // if the time is after 12pm
    isPm = 0;
  }
  else{
    isPm = 1;
  }
  tod -> hours = hour;
  tod -> minutes = minute;
  tod -> seconds = second;
  tod -> ispm = isPm;
  return 0;
}
*/
/*
int set_display_bits_from_tod(tod_t tod, int *display){
  // if the hout/minute/second is out of bound
  if (tod.hours > 12 || tod.hours < 0 || tod.minutes >= 60 || tod.minutes < 0 || tod.seconds >= 60 || tod.seconds < 0){
    return 1;
  }
  // set the number 0-9 in binary form
  int array[10];
  array[0] = 0b0111111;
  array[1] = 0b0000110;
  array[2] = 0b1011011;
  array[3] = 0b1001111;
  array[4] = 0b1100110;
  array[5] = 0b1101101;
  array[6] = 0b1111101;
  array[7] = 0b0000111;
  array[8] = 0b1111111;
  array[9] = 0b1101111;

  int min_ones = array[(tod.minutes)] ;
  int min_tens = array[0]; //leaq
  int hour_ones = array[(tod.hours)] ;
  int hour_tens = array[0];
  int isPm ;
  int result = 0b00000000000000000000000000000000; //set result to blank mask

  if ( tod.minutes >=10){           // set the hour_ten separately
    min_ones =  array[(tod.minutes) %10] ;
    min_tens = array[(tod.minutes) /10];
  }
  if ( tod.hours >=10){             // set the hour_ten separately
    hour_ones = array[(tod.hours) %10] ;
    hour_tens = array[1];
  }
  else{                             // nothing is added to hour_ten
    hour_ones = array[(tod.hours)] ;
    hour_tens = 0b0000000;
  }

  if (tod.ispm == 0){               // set the clock in am
    isPm = 0b01;
  }
  else{                             // set the clock in pm
    isPm = 0b10;
  }

  result = result | min_ones;       //shifting for min_one
  result = result | min_tens << 7;  //shifting for min_tem
  result = result | hour_ones << 14;//shifting for hour_one
  result = result | hour_tens <<21; //shifting for hour_ten
  result = result | isPm << 28;     //shifting for am/pm

  *display = result;                //pointer to result which contains 32bits
  return 0;                         //display success
}
*/
/*
int lcd_update(){
    tod_t tod;
    // if the time od second is out of bound
    if (TIME_OF_DAY_SEC > 86400 || TIME_OF_DAY_SEC <0){
        return 1;
    }
    else{}
      set_tod_from_secs(TIME_OF_DAY_SEC, &tod);           //set the hour/minute/second to tod struct
      set_display_bits_from_tod(tod, &LCD_DISPLAY_PORT);  //display in lcd
      return 0;                                           //return success

}
*/
