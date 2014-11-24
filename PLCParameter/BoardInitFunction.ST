(*@PROPERTIES_EX@
TYPE: POU
LOCALE: 0
IEC_LANGUAGE: ST
PLC_TYPE: independent
PROC_TYPE: independent
*)
(*@KEY@:DESCRIPTION*)

(*@KEY@:END_DESCRIPTION*)
PROGRAM BoardInitFunction

(*Group:Default*)


VAR_EXTERNAL
SystemConf :	AXIS_CONFIG_CONST_TR;
AxisConf1 :	AXIS_CONFIG_CONST_TR;
END_VAR


(*@KEY@: WORKSHEET
NAME: BoardInitFunction
IEC_LANGUAGE: ST
*)
(*System configuration, do not edit here*)


AxisConf1.Kv := REAL#1.02;(*Speed gain factor of the P controller*)
AxisConf1.Kf := REAL#0.72;(*Evaluation factor of the speed precontrol*)
AxisConf1.Impulse := REAL#10000.02;(*Number of pulses for pulse evaluation*)
AxisConf1.Road := REAL#50.02;(*Equivalent path for pulse evaluation*)
AxisConf1.SwLimitNeg := REAL#0.02;(*Negative software limit switch*)
AxisConf1.SwLimitPos := REAL#0.02;(*Positive software limit switch*)
AxisConf1.MaxVelocity := REAL#2500.02;(*Maximum speed*)
AxisConf1.MaxAcceleration := REAL#10000.02;(*Maximum acceleration*)
AxisConf1.MaxDeceleration := REAL#10000.02;(*Maximum deceleration*)
AxisConf1.MaxJerk := REAL#100000.02;(*Maximum jerk*)
AxisConf1.VelocityTechUnitsDenom := REAL#1.02;(*Denominator for velocity conversion factor*)
							                 (*from Calculation data into technical units*)
AxisConf1.VelocityTechUnitsNum := REAL#1.02;(*Numerator for velocity conversion factor*)
										   (*from Calculation data into technical units*)
AxisConf1.T2 := REAL#0.02;(*Timer constant of actual position filter*)
AxisConf1.TestMode := USINT#02;(*Test mode without drives*)
AxisConf1.ReglerMode := USINT#22;(*Controlled or not controlled*)
AxisConf1.AxisType := USINT#02;(*Axis type*)
AxisConf1.ProfileCurveChoose := BOOL#02;(*Curve type choose*)
AxisConf1.AxisModMax := REAL#360.02;(*Maximum For rotary axis*)
AxisConf1.AxisModMin := REAL#0.02;(*Minimum For rotary axis*)


SystemConf.TnCyc := REAL#1.02;(*System cycle*)
SystemConf.Multi := REAL#1.02;(*System cycle scale*)
(*@KEY@: END_WORKSHEET *)
END_PROGRAM
