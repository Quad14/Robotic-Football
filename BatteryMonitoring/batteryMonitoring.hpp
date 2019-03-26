#pragma once
#include <stdint.h>

#define LOW_THRESHHOLD          11500
#define MEDIUM_THRESHHOLD       12300
#define CHARGED_THRESHHOLD      12900

enum BatteryLevel {
    NEAR_DEAD = 0b00,
    LOW = 0b01,
    MEDIUM = 0b10,
    CHARGED = 0b11
};

BatteryLevel getBatteryLevelFromVoltage(uint16_t voltageMilliVolts) {
    if (voltageMilliVolts > CHARGED_THRESHHOLD) { return CHARGED;}
    if (voltageMilliVolts > MEDIUM_THRESHHOLD)  { return MEDIUM;}
    if (voltageMilliVolts > LOW_THRESHHOLD)     { return LOW;}
    else                                        { return NEAR_DEAD;}
}

uint16_t getBatteryVoltageFromDivider() {
	/*
			 R1      V_A15     R2
	VBat ---\/\/\/-----------\/\/\/---GND
	         2.7Ω    I-->     1.0Ω
	
	V_A15 = I * R2 
	I = V_A15 / R2 
	
	VBat = I * (R1 + R2)
	VBat = (V_A15 / R2) * (R1 + R2)
	VBat = (V_A15 * R1 / R2) + (V_A15 * R2 / R2)
	VBat = (V_A15 * R1 / R2) + V_A15
	
	VBat = V_A15 * 2.7 / 1.0 + V_A15
	VBat = V_A15 * 3.7
	
	*/	
	
  return (3.7*5.0*analogRead(A15))/1024);
}

void setLedsBasedOnBatteryLevel (PS3BT& PS3) {
	uint16_t batteryVoltage = getBatteryVoltageFromDivider();
	BatteryLevel batteryLevel = getBatteryLevelFromVoltage(batteryVoltage);
	if (batteryLevel == NEAR_DEAD) {PS3.setLedOff(LED2), PS3.setLedOff(LED3)};
	if (batteryLevel == LOW)	   {PS3.setLedOn(LED2) , PS3.setLedOff(LED3)};
	if (batteryLevel == MEDIUM) {PS3.setLedOff(LED2), PS3.setLedOn (LED3)};
	if (batteryLevel == CHARGED) {PS3.setLedOn(LED2) , PS3.setLedOn (LED3)};
	
}