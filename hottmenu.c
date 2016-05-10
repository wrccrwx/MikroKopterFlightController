// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + www.MikroKopter.com
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + Software Nutzungsbedingungen (english version: see below)
// + der Fa. HiSystems GmbH, Flachsmeerstrasse 2, 26802 Moormerland - nachfolgend Lizenzgeber genannt -
// + Der Lizenzgeber r�umt dem Kunden ein nicht-ausschlie�liches, zeitlich und r�umlich* unbeschr�nktes Recht ein, die im den
// + Mikrocontroller verwendete Firmware f�r die Hardware Flight-Ctrl, Navi-Ctrl, BL-Ctrl, MK3Mag & PC-Programm MikroKopter-Tool 
// + - nachfolgend Software genannt - nur f�r private Zwecke zu nutzen.
// + Der Einsatz dieser Software ist nur auf oder mit Produkten des Lizenzgebers zul�ssig.
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + Die vom Lizenzgeber gelieferte Software ist urheberrechtlich gesch�tzt. Alle Rechte an der Software sowie an sonstigen im
// + Rahmen der Vertragsanbahnung und Vertragsdurchf�hrung �berlassenen Unterlagen stehen im Verh�ltnis der Vertragspartner ausschlie�lich dem Lizenzgeber zu.
// + Die in der Software enthaltenen Copyright-Vermerke, Markenzeichen, andere Rechtsvorbehalte, Seriennummern sowie
// + sonstige der Programmidentifikation dienenden Merkmale d�rfen vom Kunden nicht ver�ndert oder unkenntlich gemacht werden.
// + Der Kunde trifft angemessene Vorkehrungen f�r den sicheren Einsatz der Software. Er wird die Software gr�ndlich auf deren
// + Verwendbarkeit zu dem von ihm beabsichtigten Zweck testen, bevor er diese operativ einsetzt.
// + Die Haftung des Lizenzgebers wird - soweit gesetzlich zul�ssig - begrenzt in H�he des typischen und vorhersehbaren
// + Schadens. Die gesetzliche Haftung bei Personensch�den und nach dem Produkthaftungsgesetz bleibt unber�hrt. Dem Lizenzgeber steht jedoch der Einwand 
// + des Mitverschuldens offen.
// + Der Kunde trifft angemessene Vorkehrungen f�r den Fall, dass die Software ganz oder teilweise nicht ordnungsgem�� arbeitet.
// + Er wird die Software gr�ndlich auf deren Verwendbarkeit zu dem von ihm beabsichtigten Zweck testen, bevor er diese operativ einsetzt.
// + Der Kunde wird er seine Daten vor Einsatz der Software nach dem Stand der Technik sichern.
// + Der Kunde ist dar�ber unterrichtet, dass der Lizenzgeber seine Daten im zur Vertragsdurchf�hrung erforderlichen Umfang
// + und auf Grundlage der Datenschutzvorschriften erhebt, speichert, verarbeitet und, sofern notwendig, an Dritte �bermittelt.
// + *) Die r�umliche Nutzung bezieht sich nur auf den Einsatzort, nicht auf die Reichweite der programmierten Software.
// + #### ENDE DER NUTZUNGSBEDINGUNGEN ####'
// +  Hinweis: Informationen �ber erweiterte Nutzungsrechte (wie z.B. Nutzung f�r nicht-private Zwecke) sind auf Anfrage per Email an info(@)hisystems.de verf�gbar.
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + Software LICENSING TERMS
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + of HiSystems GmbH, Flachsmeerstrasse 2, 26802 Moormerland, Germany - the Licensor -
// + The Licensor grants the customer a non-exclusive license to use the microcontroller firmware of the Flight-Ctrl, Navi-Ctrl, BL-Ctrl, and MK3Mag hardware 
// + (the Software) exclusively for private purposes. The License is unrestricted with respect to time and territory*.
// + The Software may only be used with the Licensor's products.
// + The Software provided by the Licensor is protected by copyright. With respect to the relationship between the parties to this
// + agreement, all rights pertaining to the Software and other documents provided during the preparation and execution of this
// + agreement shall be the property of the Licensor.
// + The information contained in the Software copyright notices, trademarks, other legal reservations, serial numbers and other
// + features that can be used to identify the program may not be altered or defaced by the customer.
// + The customer shall be responsible for taking reasonable precautions
// + for the safe use of the Software. The customer shall test the Software thoroughly regarding its suitability for the
// + intended purpose before implementing it for actual operation. The Licensor's liability shall be limited to the extent of typical and
// + foreseeable damage to the extent permitted by law, notwithstanding statutory liability for bodily injury and product
// + liability. However, the Licensor shall be entitled to the defense of contributory negligence.
// + The customer will take adequate precautions in the case, that the software is not working properly. The customer will test
// + the software for his purpose before any operational usage. The customer will backup his data before using the software.
// + The customer understands that the Licensor collects, stores and processes, and, where required, forwards, customer data
// + to third parties to the extent necessary for executing the agreement, subject to applicable data protection and privacy regulations.
// + *) The territory aspect only refers to the place where the Software is used, not its programmed range.
// + #### END OF LICENSING TERMS ####
// + Note: For information on license extensions (e.g. commercial use), please contact us at info(@)hisystems.de.
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "libfc.h"
#include "printf_P.h"
#include "main.h"
#include "spi.h"
#include "capacity.h"

unsigned char NaviData_WaypointIndex = 0;
unsigned char NaviData_WaypointNumber = 0, NaviData_TargetHoldTime = 0, ToNC_Load_WP_List = 0, NaviData_MaxWpListIndex = 0;
unsigned char ToNC_Load_SingePoint = 0, ToNC_Store_SingePoint = 0, Show_Load_Time = 0, Show_Load_Value = 0, Show_Store_Time = 0, Show_Store_Value = 0;
char WPL_Name[10];// = {"         \0"};

#if (defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__))

#define HoTT_printf(format, args...)        		{  _printf_P(&LIBFC_HoTT_Putchar, PSTR(format) , ## args);}
#define HoTT_printfxy(x,y,format, args...)  		{ LIBFC_HoTT_SetPos((y) * 21 + (x)); _printf_P(&LIBFC_HoTT_Putchar, PSTR(format) , ## args);}
#define HoTT_printfxy_INV(x,y,format, args...)  	{ LIBFC_HoTT_SetPos((y) * 21 + (x)); _printf_P(&LIBFC_HoTT_Putchar_INV, PSTR(format) , ## args);}
#define HoTT_printfxy_BLINK(x,y,format, args...)   	{ LIBFC_HoTT_SetPos((y) * 21 + (x)); _printf_P(&LIBFC_HoTT_Putchar_BLINK, PSTR(format) , ## args);}
#define HoTT_printf_BLINK(format, args...)       	{ _printf_P(&LIBFC_HoTT_Putchar_BLINK, PSTR(format) , ## args);}
#define HoTT_printf_INV(format, args...)  			{ _printf_P(&LIBFC_HoTT_Putchar_INV, PSTR(format) , ## args);}

#define VOICE_MINIMALE_EINGANSSPANNUNG    16
#define VOICE_BEEP                         5
#define HoTT_GRAD  	96
#define HoTT_LINKS 	123
#define HoTT_RECHTS 124
#define HoTT_OBEN 	125
#define HoTT_UNTEN	126

#define HOTT_KEY_RIGHT	1
#define HOTT_KEY_DOWN	2
#define HOTT_KEY_UP 	4
#define HOTT_KEY_SET	6
#define HOTT_KEY_LEFT 	8

#define VARIO_ZERO 30000
unsigned int NaviData_TargetDistance = 0;

unsigned char MaxBlTemperture = 0;
unsigned char MinBlTemperture = 0;
unsigned char HottestBl = 0;

GPSPacket_t GPSPacket;
VarioPacket_t VarioPacket;
ASCIIPacket_t ASCIIPacket;
ElectricAirPacket_t ElectricAirPacket;
HoTTGeneral_t HoTTGeneral;
unsigned char SpeakHoTT = SPEAK_MIKROKOPTER; 
unsigned char ToNC_SpeakHoTT = 0, ShowSettingNameTime = 0;
int HoTTVarioMeter = 0;
const char PROGMEM MIKROKOPTER[] = 	{"     MikroKopter     "};
const char PROGMEM UNDERVOLTAGE[] =	{" !! LiPo voltage !!  "};
const char PROGMEM LANDING[] =	    {" !!   LANDING    !!  "};
const char PROGMEM SIMULATION[] = 	{"  SIMULATION active  "};
const char PROGMEM BOAT_MODE[] = 	{" MikroKopter (Boat)  "}; 
const char PROGMEM STORE[] = 		{" Store Position SP1  "}; 
const char PROGMEM LOAD[] = 		{" Load Position SP1   "}; 
const char PROGMEM SETTING[] =	{"Set  :"};
const char PROGMEM NC_ERROR_TEXT[MAX_ERR_NUMBER][17] = 
{
//0123456789123456
 "No Error        \0",  // 0
 "Not compatible  \0",  // 1
 "MK3Mag not compa\0",  // 2
 "No FC communicat\0",  // 3
 "Compass communic\0",  // 4
 "GPS communicatio\0",  // 5
 "compass value   \0",  // 6
 "RC Signal lost  \0",  // 7
 "FC spi rx error \0",  // 8
 "No NC communicat\0",  // 9
 "FC Nick Gyro    \0",  // 10
 "FC Roll Gyro    \0",  // 11
 "FC Yaw Gyro     \0",  // 12
 "FC Nick ACC     \0",  // 13
 "FC Roll ACC     \0",  // 14
 "FC Z-ACC        \0",  // 15
 "Pressure sensor \0",  // 16
 "I2C FC->BL-Ctrl \0",  // 17
 "Bl Missing      \0",  // 18
 "Mixer Error     \0",  // 19
 "Carefree Error  \0",  // 20
 "GPS Fix lost    \0",  // 21
 "Magnet Error    \0",  // 22
 "Motor restart   \0",  // 23
 "BL Limitation   \0",  // 24
 "GPS Range       \0",  // 25
 "No SD-Card      \0",  // 26
 "SD-Logging error\0",  // 27
 "Flying range!   \0", 	// 28
 "Max Altitude!   \0",  // 29
 "No GPS fix      \0", 	// 30
 "compass not cal.\0",  // 31
 "BL-Selftest     \0",  // 32
 "no ext. compass \0",  // 33
 "compass sensor  \0",  // 34
 "Failsafe postion\0",  // 35
 "No Redundancy!  \0",  // 36
 "Redundancy test \0",  // 37
 "GPS Update Rate \0"   // 38
 };


const char PROGMEM HOTT_ERROR[MAX_ERR_NUMBER][2] = 
{       // 1 -> only in flight   0 -> also on ground
//0123456789123456
	 {0,0},// "No Error        \0",  // 0
	 {SPEAK_ERROR,0},		// "Not compatible  \0",  	// 1
	 {SPEAK_ERROR,0},		// "MK3Mag not compa\0",  	// 2
	 {SPEAK_ERR_NAVI,1},	// "No FC communicat\0",  	// 3
	 {SPEAK_ERR_COMPASS,1},	// "MK3Mag communica\0",  	// 4
	 {SPEAK_ERR_GPS,0},		// "GPS communicatio\0",  	// 5
	 {SPEAK_ERR_COMPASS,1},	// "compass value   \0",  	// 6
	 {SPEAK_ERR_RECEICER,0},// "RC Signal lost  \0",  	// 7
	 {SPEAK_ERR_NAVI,0},	// "FC spi rx error \0",  	// 8
	 {SPEAK_ERR_NAVI,0},	// "No NC communicat\0",  	// 9
	 {SPEAK_ERR_SENSOR,0},	// "FC Nick Gyro    \0",  	// 10
	 {SPEAK_ERR_SENSOR,0},	// "FC Roll Gyro    \0",  	// 11
	 {SPEAK_ERR_SENSOR,0},	// "FC Yaw Gyro     \0",  	// 12
	 {SPEAK_ERR_SENSOR,0},	// "FC Nick ACC     \0",  	// 13
	 {SPEAK_ERR_SENSOR,0},	// "FC Roll ACC     \0",  	// 14
	 {SPEAK_ERR_SENSOR,0},	// "FC Z-ACC        \0",  	// 15
	 {SPEAK_ERR_SENSOR,0},	// "Pressure sensor \0",  	// 16
	 {SPEAK_ERR_DATABUS,1},	// "I2C FC->BL-Ctrl \0",  	// 17
	 {SPEAK_ERR_DATABUS,1},	// "Bl Missing      \0",  	// 18
	 {SPEAK_ERROR,0},		// "Mixer Error     \0",  	// 19
	 {SPEAK_CF_OFF,1},		// "Carefree Error  \0",  	// 20
	 {SPEAK_GPS_FIX,1},		// "GPS Fix lost    \0",  	// 21
	 {SPEAK_ERR_COMPASS,0},	// "Magnet Error    \0",  	// 22
	 {SPEAK_ERR_MOTOR,1},	// "Motor restart   \0",  	// 23
	 {SPEAK_MAX_TEMPERAT,1},// "BL Limitation   \0",  	// 24
	 {SPEAK_MAX_RANGE,1},	// "GPS Range       \0",  	// 25
	 {SPEAK_ERROR,1},		// "No SD-Card      \0",  	// 26
	 {SPEAK_ERROR,1},		// "SD-Logging error\0",  	// 27
	 {SPEAK_MAX_RANGE,1},	// "Flying range!   \0",  	// 28
	 {SPEAK_MAX_ALTITUD,1},	// "Max Altitude!   \0"   	// 29
	 {SPEAK_GPS_FIX,1},		// "No GPS fix      \0"   	// 30
	 {SPEAK_ERR_CALIBARTION,0},// "compass not cal." 	// 31
	 {SPEAK_ERR_MOTOR,0},	// "BL-Selftest     \0"   	// 32
	 {SPEAK_ERR_COMPASS,0}, // "no ext. compass"     	// 33
	 {SPEAK_ERR_COMPASS,0}, // "compass sensor"      	// 34
	 {SPEAK_ERROR,1},		// "Failsafe postion0",  	// 35
	 {SPEAK_ERROR,0},		// "No Redundancy!",  	  	// 36
	 {0,0},					// "Redundancy test",  		// 37
	 {SPEAK_ERR_GPS,0},		// "GPS Update Rate",  	  	// 38
};

/* 
//------------------------------------------------------------------------------------------
// HoTT-Plus
//------------------------------------------------------------------------------------------
char dummy=0;
const Parameter_List_t Parameter_List[] =
{ //offset,min,max,name,variable
	{127, 0, 247,"SP1", (unsigned char *) &PPM_in[13] }, 
	{127, 0, 247,"SP2", (unsigned char *) &PPM_in[14] },	
	{127, 0, 247,"SP3", (unsigned char *) &PPM_in[15] },	
	{127, 0, 247,"SP4", (unsigned char *) &PPM_in[16] },	
	{  0, 0, 247,"HD ", (unsigned char *) &EE_Parameter.Luftdruck_D },
	{  0, 0, 247,"HP ", (unsigned char *) &EE_Parameter.Hoehe_P },
	{  0, 0, 247,"HA ", (unsigned char *) &EE_Parameter.Hoehe_ACC_Wirkung },
	{  0, 0, 247,"HM ", (unsigned char *) &EE_Parameter.Hoehe_MinGas },
	{  0, 0, 247,"HV ", (unsigned char *) &EE_Parameter.Hoehe_HoverBand },
	{  0, 0, 247,"HG ", (unsigned char *) &EE_Parameter.Hoehe_Verstaerkung },
	{  0, 0, 247,"NG ", (unsigned char *) &EE_Parameter.NotGas },
	{  0, 0, 247,"StP", (unsigned char *) &EE_Parameter.Stick_P },
	{  0, 0, 247,"StD", (unsigned char *) &EE_Parameter.Stick_D },
	{  0, 0, 247,"SGP", (unsigned char *) &EE_Parameter.StickGier_P },
	{  0, 0, 247,"DrC", (unsigned char *) &EE_Parameter.Driftkomp },
	{  0, 0, 247,"GYP", (unsigned char *) &EE_Parameter.Gyro_P },
	{  0, 0, 247,"GYD", (unsigned char *) &EE_Parameter.Gyro_D },
	{  0, 0, 247,"GYI", (unsigned char *) &EE_Parameter.Gyro_I },
	{  0, 0, 247,"MaI", (unsigned char *) &EE_Parameter.I_Faktor },
	{  0, 0, 247,"GGP", (unsigned char *) &EE_Parameter.Gyro_Gier_P },
	{  0, 0, 247,"GGI", (unsigned char *) &EE_Parameter.Gyro_Gier_I },
	{  0, 0,  15,"GSt", (unsigned char *) &EE_Parameter.Gyro_Stability },
	{  0, 0, 247,"DSt", (unsigned char *) &EE_Parameter.DynamicStability },
	{  0, 0, 247,"NGG", (unsigned char *) &EE_Parameter.NaviGpsGain },
	{  0, 0, 247,"NWC", (unsigned char *) &EE_Parameter.NaviWindCorrection },
	{  0, 0, 247,"NSC", (unsigned char *) &EE_Parameter.NaviAccCompensation },
	{  0, 0, 247,"NAL", (unsigned char *) &EE_Parameter.NaviAngleLimitation },
	{  0, 0, 247,"NP ", (unsigned char *) &EE_Parameter.NaviGpsP },
	{  0, 0, 247,"ND ", (unsigned char *) &EE_Parameter.NaviGpsI },
	{  0, 0, 247,"NI ", (unsigned char *) &EE_Parameter.NaviGpsD },
	{  0, 0, 247,"LGL", (unsigned char *) &EE_Parameter.LoopGasLimit },
	{  0, 0, 247,"LHy", (unsigned char *) &EE_Parameter.LoopHysterese },
	{  0, 0, 247,"LTh", (unsigned char *) &EE_Parameter.LoopThreshold },
	{  0, 0,   0,"   ", (unsigned char *) &dummy },
	{  0, 0, 247,"FGP", (unsigned char *) &EE_Parameter.AchsKopplung1},
	{  0, 0, 247,"FNR", (unsigned char *) &EE_Parameter.AchsKopplung2},
	{  0, 0, 247,"CYC", (unsigned char *) &EE_Parameter.CouplingYawCorrection},
	{  0, 0, 247,"MSH", (unsigned char *) &EE_Parameter.MotorSmooth},
	{  0, 0, 247,"NCT", (unsigned char *) &EE_Parameter.ServoNickControl },
	{  0, 0, 247,"NCP", (unsigned char *) &EE_Parameter.ServoNickComp },
	{  0, 0, 247,"RCT", (unsigned char *) &EE_Parameter.ServoRollControl },
	{  0, 0, 247,"RCP", (unsigned char *) &EE_Parameter.ServoRollComp }
};
unsigned char settingdest = 0;
//------------------------------------------------------------------------------------------
// HoTT-Plus
//------------------------------------------------------------------------------------------
*/
void GetHottestBl(void)
{
 static unsigned char search = 0,tmp_max,tmp_min,who;
		if(Motor[search].Temperature > tmp_max) { tmp_max = Motor[search].Temperature; who = search;}
		else
		if(Motor[search].Temperature) if(Motor[search].Temperature < tmp_min) tmp_min = Motor[search].Temperature;
		if(++search >= MAX_MOTORS) 
		{ 
		 search = 0; 
		 if(tmp_min != 255) MinBlTemperture = tmp_min; else MinBlTemperture = 0;
		 MaxBlTemperture = tmp_max; 
		 HottestBl = who;
		 tmp_min = 255; 
		 tmp_max = 0;
		 who = 0;
		 }
}

//---------------------------------------------------------------
void Hott_ClearLine(unsigned char line)
{
 HoTT_printfxy(0,line,"                     ");
}
//---------------------------------------------------------------


unsigned char HoTT_Waring(void)
{
  unsigned char status = 0;
  static char old_status = 0;
  static int repeat;
//if(Parameter_UserParam1) SpeakHoTT = Parameter_UserParam1;
  ToNC_SpeakHoTT = SpeakHoTT;
  if(FC_StatusFlags & FC_STATUS_LOWBAT) 
   {
    if(LowVoltageLandingActive && (EE_Parameter.Receiver == RECEIVER_HOTT)) status = SPEAK_LANDING;
	else status = VOICE_MINIMALE_EINGANSSPANNUNG; // Jeti hat kein wort: "LANDEN"
	if(SpeakHoTT && old_status == VOICE_MINIMALE_EINGANSSPANNUNG) status = SpeakHoTT; // das soll auch noch durch kommen
   }	
  else
  if(NC_ErrorCode && NC_ErrorCode < MAX_ERR_NUMBER) 	// Fehlercodes
   {
    if(MotorenEin || !pgm_read_byte(&HOTT_ERROR[NC_ErrorCode][1])) status = pgm_read_byte(&HOTT_ERROR[NC_ErrorCode][0]);
   }
  if(!status)    // Sprachansagen
   {
//	if(!(GetParamByte(PID_SPEAK_HOTT_CFG) & 0x01)) SpeakHoTT = 0;  // is the voice wanted?
    if(!(EE_Parameter.GlobalConfig3 & CFG3_SPEAK_ALL)) SpeakHoTT = 0;  // is the voice wanted?
    else status = SpeakHoTT; 
   }
   else ToNC_SpeakHoTT = status;

  if(old_status == status) // Gleichen Fehler nur alle 4 sek bringen
   {
    if(!CheckDelay(repeat)) return(0);
	repeat = SetDelay(4000);
   }
   else repeat = SetDelay(2000);

  if(status) 
   {
    if(status == SpeakHoTT) SpeakHoTT = 0;
   }	
  old_status = status;
//  DebugOut.Analog[16] = status;
  return(status);
}

//---------------------------------------------------------------
void NC_Fills_HoTT_Telemety(void)
{
 unsigned char *ptr = NULL;
 unsigned char max = 0,i,z;
 switch(FromNaviCtrl.Param.Byte[11])
  {
   case HOTT_VARIO_PACKET_ID: 
		ptr = (unsigned char *) &VarioPacket;
		max = sizeof(VarioPacket);
		break;
   case HOTT_GPS_PACKET_ID: 
		ptr = (unsigned char *) &GPSPacket;
		max = sizeof(GPSPacket);
		break;
   case HOTT_ELECTRIC_AIR_PACKET_ID: 
		ptr = (unsigned char *) &ElectricAirPacket;
		max = sizeof(ElectricAirPacket);
		break;
   case HOTT_GENERAL_PACKET_ID: 
		ptr = (unsigned char *) &HoTTGeneral;
		max = sizeof(HoTTGeneral);
		break;
   case JETI_GPS_PACKET_ID1: 
		ptr = (unsigned char *) &JetiExData[14].Value;
		max = sizeof(JetiExData[14].Value);
		break;
   case JETI_GPS_PACKET_ID2: 
		ptr = (unsigned char *) &JetiExData[15].Value;
		max = sizeof(JetiExData[15].Value);
		break;
   case HOTT_WPL_NAME: 
		ptr = (unsigned char *) WPL_Name;
		max = sizeof(WPL_Name)-1;
		break;

  }
 z = FromNaviCtrl.Param.Byte[0]; // Data allocation

 for(i=0; i < FromNaviCtrl.Param.Byte[1]; i++)
  {
   if(z >= max) break;
   ptr[z] = FromNaviCtrl.Param.Byte[2+i];
   z++;
  }
}

unsigned int BuildHoTT_Vario(void)
{
 unsigned int tmp = VARIO_ZERO;
 if(VarioCharacter == '+' || VarioCharacter == '-')
  { 
   tmp = VARIO_ZERO + (AltitudeSetpointTrimming * EE_Parameter.Hoehe_Verstaerkung) / 3;
   if(tmp < VARIO_ZERO && tmp > VARIO_ZERO - 50) tmp = VARIO_ZERO - 50; // weil es sonst erst bei < 0,5m/sek piept
  } 
 else
 if((VarioCharacter == ' ') && (FC_StatusFlags & FC_STATUS_FLY))
  {
   tmp = VARIO_ZERO + HoTTVarioMeter;
   if(tmp > VARIO_ZERO)
    {
     if(tmp < VARIO_ZERO + 100) tmp = VARIO_ZERO; 
	 else tmp -= 100; 
	} 
   if(tmp < VARIO_ZERO)
    {
     if(tmp > VARIO_ZERO - 100) tmp = VARIO_ZERO; 
	 else tmp += 100; 
	} 
  }
 else
 if(VarioCharacter == '^') tmp = VARIO_ZERO + FromNC_AltitudeSpeed * 10;
 else 
 if(VarioCharacter == 'v') tmp = VARIO_ZERO - FromNC_AltitudeSpeed * 10;
 return(tmp);
}

//---------------------------------------------------------------
unsigned char HoTT_Telemety(unsigned char packet_request)
{
 unsigned char i = 0;
 static unsigned char SpeechMessage = 0;
  //Debug("rqst: %02X",packet_request);

 switch(packet_request)
 {
  case HOTT_VARIO_PACKET_ID:
		if(GPSPacket.WarnBeep == SpeechMessage) SpeechMessage = HoTT_Waring(); // Achtung: das ist richtig hier, damit der Varioton schon vorher abgestellt wird

		VarioPacket.Altitude = HoehenWert/100 + 500;  
		if(!SpeechMessage) VarioPacket.m_sec = BuildHoTT_Vario(); else VarioPacket.m_sec = VARIO_ZERO;
		VarioPacket.m_3sec = VarioPacket.m_sec;
		VarioPacket.m_10sec = VarioPacket.m_sec;
		if (VarioPacket.Altitude < VarioPacket.MinAltitude) VarioPacket.MinAltitude = VarioPacket.Altitude;
		if (VarioPacket.Altitude > VarioPacket.MaxAltitude) VarioPacket.MaxAltitude = VarioPacket.Altitude;		
		VarioPacket.WarnBeep = 0;//HoTT_Waring();
		HoTT_DataPointer = (unsigned char *) &VarioPacket;
	VarioPacket.FreeCharacters[0] = VarioCharacter;
    if(FC_StatusFlags2 & FC_STATUS2_CAREFREE) VarioPacket.FreeCharacters[1] = 'C'; else VarioPacket.FreeCharacters[1] = ' ';
//	VarioPacket.FreeCharacters[2] = ' ';
    if(NC_ErrorCode)
	 {
		VarioPacket.Text[0] = NC_ErrorCode/10 + '0';
		VarioPacket.Text[1] = NC_ErrorCode%10 + '0';
		VarioPacket.Text[2] = ':';
		for(i=0; i<16;i++) VarioPacket.Text[i+3] = pgm_read_byte(&NC_ERROR_TEXT[NC_ErrorCode][i]);
		VarioPacket.Text[19] = ' '; 
		VarioPacket.Text[20] = ' '; 
	 }
	 else 
	 if(LowVoltageLandingActive) for(i=0; i<21;i++) VarioPacket.Text[i] = pgm_read_byte(&LANDING[i]); // no Error
     else
	 if(FC_StatusFlags & FC_STATUS_LOWBAT) for(i=0; i<21;i++) VarioPacket.Text[i] = pgm_read_byte(&UNDERVOLTAGE[i]); // no Error
	 else
	 if(ShowSettingNameTime) // no Error
	 {                   
	  for(i=0; i<sizeof(SETTING);i++) VarioPacket.Text[i] = pgm_read_byte(&SETTING[i]); 
      VarioPacket.Text[4] = '0' + ActiveParamSet;
	  for(i=0; i<sizeof(EE_Parameter.Name);i++) VarioPacket.Text[i+7] = EE_Parameter.Name[i]; // no Error
      if(FC_StatusFlags3 & FC_STATUS3_BOAT)
		{
         VarioPacket.Text[17] = 'B'; 
         VarioPacket.Text[18] = 'O'; 
         VarioPacket.Text[19] = 'A'; 
         VarioPacket.Text[20] = 'T'; 
		}
	  else
		{
         VarioPacket.Text[18] = ' '; 
         VarioPacket.Text[19] = ' '; 
         VarioPacket.Text[20] = ' '; 
		} 
	 } 
	 else
	 if(Show_Store_Time)
	 {
	  for(i=0; i<21;i++) VarioPacket.Text[i] = pgm_read_byte(&STORE[i]); // no Error and not calibrated
	  if(Show_Store_Value < 10) VarioPacket.Text[18] = Show_Store_Value + '0';
	  else
	  { 
	   VarioPacket.Text[18] = Show_Store_Value/10 + '0';
	   VarioPacket.Text[19] = Show_Store_Value%10 + '0';
	  } 
	 }
	 else	 
	 if(Show_Load_Time)
	 {
	  for(i=0; i<21;i++) VarioPacket.Text[i] = pgm_read_byte(&LOAD[i]); // no Error and not calibrated
	  if(Show_Load_Value < 10) VarioPacket.Text[17] = Show_Load_Value + '0';
	  else
	  { 
	   VarioPacket.Text[17] = Show_Load_Value/10 + '0';
	   VarioPacket.Text[18] = Show_Load_Value%10 + '0';
	  } 
	 }
	 else	 
     if(NaviData_WaypointNumber)
	 {    
	  unsigned int tmp_int;
      unsigned char tmp;
      VarioPacket.Text[0] = 'W'; VarioPacket.Text[1] = 'P';
      VarioPacket.Text[2] = ' '; 
      VarioPacket.Text[3] = '0'+(NaviData_WaypointIndex) / 10;
      VarioPacket.Text[4] = '0'+(NaviData_WaypointIndex) % 10;
      VarioPacket.Text[5] = '/'; 
      VarioPacket.Text[6] = '0'+(NaviData_WaypointNumber) / 10;
      VarioPacket.Text[7] = '0'+(NaviData_WaypointNumber) % 10;
      VarioPacket.Text[8] = ' '; 
	  tmp_int = NaviData_TargetDistance;
      if(tmp_int > 1000) { VarioPacket.Text[9] = '0'+(tmp_int) / 1000; tmp_int %= 1000;}
	  else VarioPacket.Text[9] = ' ';
      if(tmp_int > 100) { VarioPacket.Text[10] = '0'+(tmp_int) / 100; tmp_int %= 100;}
	  else VarioPacket.Text[10] = ' ';
      VarioPacket.Text[11] = '0'+(tmp_int) / 10; 
      VarioPacket.Text[12] = '0'+(tmp_int) % 10; 
      VarioPacket.Text[13] = 'm'; 
      VarioPacket.Text[14] = ' '; 
      tmp = NaviData_TargetHoldTime;
	  if(tmp > 100) { VarioPacket.Text[15] = '0'+(tmp) / 100; tmp %= 100;} else VarioPacket.Text[15] = ' '; 
      VarioPacket.Text[16] = '0'+(tmp) / 10; 
      VarioPacket.Text[17] = '0'+(tmp) % 10; 
      VarioPacket.Text[18] = 's'; 
      VarioPacket.Text[19] = ' '; 
      VarioPacket.Text[20] = ' '; 
	 }
	 else
	 if(NC_To_FC_Flags & NC_TO_FC_SIMULATION_ACTIVE)
	 {
	  for(i=0; i<21;i++) VarioPacket.Text[i] = pgm_read_byte(&SIMULATION[i]); 
	 }
	 else
	 if(!CalibrationDone)
	 {
	  for(i=0; i<17;i++) VarioPacket.Text[i] = pgm_read_byte(&MIKROKOPTER[i+2]); // no Error and not calibrated
      VarioPacket.Text[16] = '0'+VERSION_MAJOR; 
      VarioPacket.Text[17] = '.'; 
      VarioPacket.Text[18] = '0'+VERSION_MINOR/10; 
      VarioPacket.Text[19] = '0'+VERSION_MINOR%10; 
      VarioPacket.Text[20] = 'a'+VERSION_PATCH; 
	 }
	 else
	 {
	  if(FC_StatusFlags3 & FC_STATUS3_BOAT) for(i=0; i<21;i++) VarioPacket.Text[i] = pgm_read_byte(&BOAT_MODE[i]); // no Error
	  else  for(i=0; i<21;i++) VarioPacket.Text[i] = pgm_read_byte(&MIKROKOPTER[i]); // no Error
	  if(FC_StatusFlags3 & FC_STATUS3_REDUNDANCE_AKTIVE)  VarioPacket.Text[0] = 'R';
	 } 
		return(sizeof(VarioPacket)); 
		break;

  case HOTT_GPS_PACKET_ID:
		GPSPacket.Altitude = HoehenWert/100 + 500;  
//		GPSPacket.Distance = GPSInfo.HomeDistance/10;  // macht die NC
//		GPSPacket.Heading = GPSInfo.HomeBearing/2;     // macht die NC
//		GPSPacket.Speed = (GPSInfo.Speed * 36) / 10;   // macht die NC
		GPSPacket.WarnBeep = SpeechMessage;
		if(!GPSPacket.WarnBeep) GPSPacket.m_sec = BuildHoTT_Vario(); else GPSPacket.m_sec = VARIO_ZERO;
		GPSPacket.m_3sec = 120;
		GPSPacket.NumOfSats = GPSInfo.NumOfSats;
		if(GPSInfo.Flags & FLAG_DIFFSOLN) GPSPacket.SatFix = 'D';
		else
        if(GPSInfo.SatFix == SATFIX_3D) GPSPacket.SatFix = ' '; 
		else GPSPacket.SatFix = '!';
		HoTT_DataPointer = (unsigned char *) &GPSPacket;
		GPSPacket.FreeCharacters[0] = NC_GPS_ModeCharacter;
		GPSPacket.FreeCharacters[2] = GPSPacket.SatFix;
		GPSPacket.HomeDirection = GPSInfo.HomeBearing / 2;//230;
		return(sizeof(GPSPacket));  
		break;
  case HOTT_ELECTRIC_AIR_PACKET_ID:
		GetHottestBl();
		ElectricAirPacket.Altitude = HoehenWert/100 + 500; 
		ElectricAirPacket.Battery1 = UBat;
		ElectricAirPacket.Battery2 = UBat;
		ElectricAirPacket.VoltageCell1 = CompassCorrected / 2;
		ElectricAirPacket.VoltageCell8 = ElectricAirPacket.VoltageCell1;
		ElectricAirPacket.VoltageCell6 = GPSInfo.HomeBearing / 2;
		ElectricAirPacket.VoltageCell7 = GPSInfo.HomeDistance/20;
		ElectricAirPacket.VoltageCell13 = ElectricAirPacket.VoltageCell6;
		ElectricAirPacket.VoltageCell14 = ElectricAirPacket.VoltageCell7;
        if(!SpeechMessage) ElectricAirPacket.m_sec = BuildHoTT_Vario(); else ElectricAirPacket.m_sec = VARIO_ZERO;
		ElectricAirPacket.m_3sec = 120;
		ElectricAirPacket.InputVoltage = UBat;
		ElectricAirPacket.Temperature1 = MinBlTemperture + 20;
		ElectricAirPacket.Temperature2 = MaxBlTemperture + 20;
		ElectricAirPacket.Capacity = Capacity.UsedCapacity/10;
		ElectricAirPacket.WarnBeep = 0;//HoTT_Waring();
//ElectricAirPacket.WarnBeep = SpeechMessage;
		ElectricAirPacket.Current = Capacity.ActualCurrent;
		HoTT_DataPointer = (unsigned char *) &ElectricAirPacket;
		ElectricAirPacket.FlightTimeMinutes = FlugSekunden / 60;
		ElectricAirPacket.FlightTimeSeconds = FlugSekunden % 60; 
		return(sizeof(ElectricAirPacket)); 
		break;
  case HOTT_GENERAL_PACKET_ID:
		GetHottestBl();
		HoTTGeneral.Rpm = GPSInfo.HomeDistance/100;
		HoTTGeneral.VoltageCell1 = CompassCorrected / 2;
		HoTTGeneral.VoltageCell2 = KompassValue / 2;
		//HoTTGeneral.VoltageCell3 = Magnetstaerke -> macht NC
		//HoTTGeneral.VoltageCell4 = Inclinition -> macht NC
		HoTTGeneral.VoltageCell5 = DebugOut.Analog[28]; // I2C ErrorCounter
		HoTTGeneral.VoltageCell6 = GPSInfo.HomeBearing / 2;
		if(UBat > BattLowVoltageWarning + 2) HoTTGeneral.FuelPercent = (UBat - (BattLowVoltageWarning + 2)) * 3;
		else HoTTGeneral.FuelPercent = 0;
		if(HoTTGeneral.FuelPercent > 100) HoTTGeneral.FuelPercent = 100;
		HoTTGeneral.FuelCapacity = NC_ErrorCode;//HoehenWert/100; // Oelpegel
//		if(HoTTGeneral.FuelCapacity < 0) HoTTGeneral.FuelCapacity = 0;
		HoTTGeneral.Altitude = HoehenWert/100 + 500; 
		HoTTGeneral.Battery1 = UBat;
		HoTTGeneral.Battery2 = UBat;
		if(!SpeechMessage) HoTTGeneral.m_sec =  BuildHoTT_Vario(); else  HoTTGeneral.m_sec = VARIO_ZERO;
		HoTTGeneral.m_3sec = 120 + SpeechMessage;
		HoTTGeneral.InputVoltage = UBat;
		HoTTGeneral.Temperature1 = MinBlTemperture + 20;
		HoTTGeneral.Temperature2 = MaxBlTemperture + 20;
		HoTTGeneral.Capacity = Capacity.UsedCapacity/10;
HoTTGeneral.WarnBeep = 0;
		HoTTGeneral.Current = Capacity.ActualCurrent;
//HoTTGeneral.ErrorNumber = HoTTErrorCode();
		HoTT_DataPointer = (unsigned char *) &HoTTGeneral;
		return(sizeof(HoTTGeneral)); 
		break;
  default: return(0);
  }		
}

//---------------------------------------------------------------
void HoTT_Menu(void)
{
 static unsigned char line, page = 0,show_current = 0,show_mag = 0, show_poti = 0,hyterese = 1;
 unsigned char tmp; 
 HoTTVarioMeter = (HoTTVarioMeter * 7 + VarioMeter) / 8;
 static int delay;

// if(HottKeyboard) {beeptime = 1000;};  
 
 switch(page)
 {
  case 0:
  switch(line++)
  {
	case 0:  
	        if(FC_StatusFlags & FC_STATUS_LOWBAT) 
			 HoTT_printfxy_BLINK(0,0,"  %2i.%1iV  ",UBat/10, UBat%10)
			else 
			 HoTT_printfxy(0,0,"  %2i.%1iV  ",UBat/10, UBat%10)

			if(Parameter_GlobalConfig & CFG_HOEHENREGELUNG)
			  {
			   if(HoehenReglerAktiv) 	HoTT_printfxy_INV(10,0,"ALT:%4im %c", (int16_t)(HoehenWert/100),VarioCharacter)
			   else						HoTT_printfxy(10,0,"ALT:%4im  ", (int16_t)(HoehenWert/100))
			   }
            else    HoTT_printfxy(10,0,"ALT:---- ");
			break;
	case 1:  
	        if(FC_StatusFlags & FC_STATUS_LOWBAT) 
			 HoTT_printfxy_BLINK(0,1,"  %2i:%02i  ",FlugSekunden/60,FlugSekunden%60)
            else   HoTT_printfxy(0,1,"  %2i:%02i  ",FlugSekunden/60,FlugSekunden%60);			   
			HoTT_printfxy(10,1,"DIR: %3d%c",CompassCorrected, HoTT_GRAD);
			if(FC_StatusFlags2 & FC_STATUS2_CAREFREE) HoTT_printfxy_INV(20,1,"C") else HoTT_printfxy(20,1," ");
            break;
	case 2:
	        if(FC_StatusFlags & FC_STATUS_LOWBAT) 
			 HoTT_printfxy_BLINK(0,2,"  %5i  ",Capacity.UsedCapacity)
            else   HoTT_printfxy(0,2,"  %5i  ",Capacity.UsedCapacity);			   
			HoTT_printfxy(12,2,"I:%2i.%1iA ",Capacity.ActualCurrent/10, Capacity.ActualCurrent%10);
			break;
	case 3: 
  			HoTT_printfxy(9,0,":");
  			HoTT_printfxy(9,1,":");
  			HoTT_printfxy(9,2,":");
			HoTT_printfxy(0,3,"---------+-----------");

//			HoTT_printfxy(0,3,"---------------------");
			HoTT_printfxy(0,6,"---------------------");
			break;
	case 4:  
			if(NaviDataOkay)
			{
				HoTT_printfxy(9,4,":");
				HoTT_printfxy(0,4,"SAT:%2d ",GPSInfo.NumOfSats);
			    HoTT_printfxy(10,4,"DIST:%3dm",GPSInfo.HomeDistance/10);
				switch (GPSInfo.SatFix)
				{
					case SATFIX_3D:
							if(GPSInfo.Flags & FLAG_DIFFSOLN) HoTT_printfxy(7,4,"D ")
							else HoTT_printfxy(7,4,"3D");
						break;
					default:
						HoTT_printfxy_BLINK(7,4,"!!");
						break;
				}	
			}
			else
			{                    
				Hott_ClearLine(4);
			}
			break;
	case 5:
			if(NaviDataOkay)
			{
			if(show_mag)
			  { 
				HoTT_printfxy(0,5,"MAG:%3u%% ",EarthMagneticField);
			    HoTT_printfxy(12,5,"HM:%3d%c %c", GPSInfo.HomeBearing, HoTT_GRAD, NC_GPS_ModeCharacter);
				HoTT_printfxy(9,5,"incl:%2d%c(%2i)",EarthMagneticInclination, HoTT_GRAD,EarthMagneticInclinationTheoretic);
              }
			 else 
			  {
				HoTT_printfxy(0,5,"    %2um/s:  HM:%3d%c %c",GPSInfo.Speed, GPSInfo.HomeBearing, HoTT_GRAD, NC_GPS_ModeCharacter);
			  }	
            }
			else Hott_ClearLine(5);
			break;
	case 6: 
			break;
	case 7: if(NC_ErrorCode) 
	          {
			   if(HoTTBlink && NC_ErrorCode < MAX_ERR_NUMBER)
			    {
			     Hott_ClearLine(7); 
			     HoTT_printfxy_INV(0,7,"ERR: %2d !",NC_ErrorCode);
			    }
				else 
				{
				 HoTT_printfxy(0,7,"ERR: ");	 _printf_P(&LIBFC_HoTT_Putchar, NC_ERROR_TEXT[NC_ErrorCode] , 0);};
				} 
			else 
			if(FC_StatusFlags & FC_STATUS_LOWBAT) HoTT_printfxy(1,7,"!! LiPo voltage !!") 
			else HoTT_printfxy(0,7," www.MikroKopter.de  ");
			break;
	case 8: //ASCIIPacket.WarnBeep = HoTT_Waring();
			// ASCIIPacket.WarnBeep = Parameter_UserParam1;
	case 9: 
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:  
	case 15:  
	case 16:  
			if(HottKeyboard == HOTT_KEY_DOWN) { LIBFC_HoTT_Clear(); page = 5; line = 0;}
			else
			if(HottKeyboard == HOTT_KEY_SET) { if(show_mag) show_mag = 0; else show_mag = 1;}
			else
			if(HottKeyboard == HOTT_KEY_LEFT) { LIBFC_HoTT_Clear(); page = 1; line = 0;};
			HottKeyboard = 0;
			break;
   default:  line = 0;
			break;
  }
  break;
  case 1:
  switch(line++)
  {
	case 0:  
	        if(FC_StatusFlags & FC_STATUS_LOWBAT) 
			 HoTT_printfxy_BLINK(0,0," %2i:%02i  %2i.%1iV %4imAh",FlugSekunden/60,FlugSekunden%60,UBat/10, UBat%10,Capacity.UsedCapacity)
            else   HoTT_printfxy(0,0," %2i:%02i  %2i.%1iV %4imAh",FlugSekunden/60,FlugSekunden%60,UBat/10, UBat%10,Capacity.UsedCapacity);			   
			break;
	case 1:  
			HoTT_printfxy(0,1,"DIR:%3d%c",CompassCorrected, HoTT_GRAD);
			if(Parameter_GlobalConfig & CFG_HOEHENREGELUNG)
			  {
			   if(HoehenReglerAktiv) 	HoTT_printfxy_INV(10,1,"ALT:%4im", (int16_t)(HoehenWert/100))
			   else						HoTT_printfxy(10,1,"ALT:%4im", (int16_t)(HoehenWert/100))
			   }
            else    HoTT_printfxy(10,1,"ALT:---- ");
			HoTT_printfxy(20,1,"%c",VarioCharacter);
            break;
	case 2:
			if(NaviDataOkay)
			{
			  HoTT_printfxy(1,2,"HM:%3d%c  DIST:%3dm %c", GPSInfo.HomeBearing, HoTT_GRAD, GPSInfo.HomeDistance/10, NC_GPS_ModeCharacter);
            }
			else
			{
			 Hott_ClearLine(2);
			}
			break;
	case 3:
			HoTT_printfxy(0,3,"PWR:%2i.%1iA (%iW) ",Capacity.ActualCurrent/10, Capacity.ActualCurrent%10,Capacity.ActualPower);
			if(FC_StatusFlags2 & FC_STATUS2_CAREFREE) HoTT_printfxy_INV(19,3,"CF") else HoTT_printfxy(19,3,"  ");
			break;
	case 4:  
			if(NaviDataOkay)
			{
				HoTT_printfxy(0,4,"GPS:%2um/s SAT:%d ",GPSInfo.Speed,GPSInfo.NumOfSats);
				switch (GPSInfo.SatFix)
				{
					case SATFIX_3D:
						HoTT_printfxy(16,4,"  3D ");
						break;
					//case SATFIX_2D:
					//case SATFIX_NONE:
					default:
						HoTT_printfxy_BLINK(16,4,"NOFIX");
						break;
				}	
				if(GPSInfo.Flags & FLAG_DIFFSOLN)
				{
					HoTT_printfxy(16,4,"DGPS ");
				}
			}
			else
			{                    //012345678901234567890
				HoTT_printfxy(0,4,"   No NaviCtrl       ");
			}
			break;
	case 5:
			if(show_current)
			 {
//				HoTT_printfxy(0,5,"%2i.%i %2i.%i %2i.%i %2i.%iA", Motor[0].Current/10,Motor[0].Current%10,Motor[1].Current/10,Motor[1].Current%10,Motor[2].Current/10,Motor[2].Current%10,Motor[3].Current/10,Motor[3].Current%10);
				HoTT_printfxy(0,5,"%2i.%i %2i.%i %2i.%i %2i.%iA", BL3_Current(0)/10,BL3_Current(0)%10,BL3_Current(1)/10,BL3_Current(1)%10,BL3_Current(2)/10,BL3_Current(2)%10,BL3_Current(3)/10,BL3_Current(3)%10);
			 }
			 else
			 {
				HoTT_printfxy(0,5,"%3i %3i %3i %3i%cC", Motor[0].Temperature, Motor[1].Temperature, Motor[2].Temperature, Motor[3].Temperature,HoTT_GRAD);
			 }
			break;
	case 6: 
			if(show_current)
			 {
	            if(RequiredMotors == 4) Hott_ClearLine(6);
				else
//				if(RequiredMotors == 6)	 HoTT_printfxy(0,6,"%2i.%i %2i.%iA", Motor[4].Current/10,Motor[4].Current%10,Motor[5].Current/10,Motor[5].Current%10)
				if(RequiredMotors == 6)	 HoTT_printfxy(0,6,"%2i.%i %2i.%iA", BL3_Current(4)/10,BL3_Current(4)%10, BL3_Current(5)/10,BL3_Current(5)%10)
				else
//				if(RequiredMotors > 6)	 HoTT_printfxy(0,6,"%2i.%i %2i.%i %2i.%i %2i.%iA", Motor[4].Current/10,Motor[4].Current%10,Motor[5].Current/10,Motor[5].Current%10,Motor[6].Current/10,Motor[6].Current%10,Motor[7].Current/10,Motor[7].Current%10);
				if(RequiredMotors > 6)	 HoTT_printfxy(0,6,"%2i.%i %2i.%i %2i.%i %2i.%iA", BL3_Current(4)/10,BL3_Current(4)%10,BL3_Current(5)/10,BL3_Current(5)%10,BL3_Current(6)/10,BL3_Current(6)%10,BL3_Current(7)/10,BL3_Current(7)%10,BL3_Current(8)/10,BL3_Current(8)%10);
             }
			 else
			 {
	            if(RequiredMotors == 4) Hott_ClearLine(6);
				else
				if(RequiredMotors == 6)	 HoTT_printfxy(0,6,"%3i %3i%cC        ", Motor[4].Temperature, Motor[5].Temperature,HoTT_GRAD)
				else
				if(RequiredMotors > 6)	 HoTT_printfxy(0,6,"%3i %3i %3i %3i%cC", Motor[4].Temperature, Motor[5].Temperature, Motor[6].Temperature, Motor[7].Temperature,HoTT_GRAD);
             }
			break;
	case 7: if(NC_ErrorCode) 
	          {
			   if(HoTTBlink && NC_ErrorCode < MAX_ERR_NUMBER)
			    {
			     Hott_ClearLine(7); 
			     HoTT_printfxy_INV(0,7,"ERR: %2d !",NC_ErrorCode);
			    }
				else 
				{
				 HoTT_printfxy(0,7,"ERR: ");	 _printf_P(&LIBFC_HoTT_Putchar, NC_ERROR_TEXT[NC_ErrorCode] , 0);};
				} 
			else 
			if(FC_StatusFlags & FC_STATUS_LOWBAT) HoTT_printfxy(1,7,"!! LiPo voltage !!") 
			else HoTT_printfxy(0,7," www.MikroKopter.de  ");
			break;
	case 8: // ASCIIPacket.WarnBeep = HoTT_Waring();
			// ASCIIPacket.WarnBeep = Parameter_UserParam1;
	case 9: 
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:  
	case 15:  
	case 16:  
			if(HottKeyboard == HOTT_KEY_SET) { if(show_current) show_current = 0; else show_current = 1;   Hott_ClearLine(5);  Hott_ClearLine(6);}
			else
			if(HottKeyboard == HOTT_KEY_LEFT) { LIBFC_HoTT_Clear(); page++; line = 0;}
			else
			if(HottKeyboard == HOTT_KEY_RIGHT) { LIBFC_HoTT_Clear(); page--; line = 0;}
//if(HottKeyboard) HoTT_printfxy(15,6,"%KEY:%02x ",HottKeyboard);
			HottKeyboard = 0;
			break;
   default:  line = 0;
			break;
  }
  break;
  case 2:
  switch(line++)
  {
	case 0:  
			HoTT_printfxy_INV(0,0,"Setting:%u %s ",ActiveParamSet,EE_Parameter.Name); 
			break;
    case 1: HoTT_printfxy(0,1,"Min:%2i.%1iV %s ",BattLowVoltageWarning/10, BattLowVoltageWarning%10, Mixer.Name); 
			break;
    case 2:  HoTT_printfxy(0,2,"ALT:");
	         if(Parameter_GlobalConfig & CFG_HOEHENREGELUNG) 
	         {
			  if(!(EE_Parameter.GlobalConfig & CFG_HOEHEN_SCHALTER)) HoTT_printf("POTI:%3u ", Parameter_HoehenSchalter)
			  else 
			  {
			   if(Parameter_HoehenSchalter > 50) HoTT_printf("(ON)  ") else HoTT_printf("(OFF) ");
			   if((Parameter_ExtraConfig & CFG2_HEIGHT_LIMIT)) HoTT_printf("LIMIT", Parameter_HoehenSchalter)
			   else HoTT_printf("VARIO", Parameter_HoehenSchalter);
			  }
			 }
			else 
				HoTT_printf("DISABLED");
			break;
    case 3: HoTT_printfxy(0,3,"CF:");
			if(!EE_Parameter.CareFreeChannel) HoTT_printf("DISABLED")
			else 
			 {
			  if(CareFree)  HoTT_printf(" (ON) ") else HoTT_printf(" (OFF)");
			  if(EE_Parameter.ExtraConfig & CFG_LEARNABLE_CAREFREE) HoTT_printf(" TEACH");
			 } 
			break;
    case 4: HoTT_printfxy(0,4,"GPS:");
		    if(!(Parameter_GlobalConfig & CFG_GPS_AKTIV)) HoTT_printf("DISABLED")
			else 
			 {
			  tmp = GetChannelValue(EE_Parameter.NaviGpsModeChannel);
			  if(tmp < 50) HoTT_printf("(FREE)")
			  else 
			  if(tmp >= 180) HoTT_printf("(HOME)") 
			  else 
			  if(EE_Parameter.ExtraConfig & CFG_GPS_AID) HoTT_printf("(AID) ") 
			  else HoTT_printf("(HOLD)") 
			 }
			if(EE_Parameter.FailSafeTime) HoTT_printfxy(10,4," FS:%usek ",EE_Parameter.FailSafeTime)

			break;
    case 5: HoTT_printfxy(0,5,"HOME ALT:");
			if(EE_Parameter.ComingHomeAltitude) HoTT_printf("%um",EE_Parameter.ComingHomeAltitude) else HoTT_printf("HOLD ");
			break;
	case 6:
			if(!show_poti)
			 {
              HoTT_printfxy(0,6,"Ni:%4i Ro:%4i C:%3i",ChannelNick,ChannelRoll, Parameter_ServoNickControl);
		      HoTT_printfxy(0,7,"Gs:%4i Ya:%4i ",ChannelGas+127,ChannelYaw);
			 }
			else
			 {
              HoTT_printfxy(0,6,"P1:%4i P2:%4i 3:%3i",Poti1,Poti2, Poti3);
		      HoTT_printfxy(0,7,"P4:%4i P5:%4i 6:%3i",Poti4,Poti5, Poti6);
			 }
 
			break;
    case 7: //HoTT_printfxy(0,6,"WARNINGS:");
			if(HoTTBlink)
			{
			 LIBFC_HoTT_SetPos(6 * 21);
//			 if(!(Parameter_GlobalConfig & CFG_ACHSENKOPPLUNG_AKTIV)) HoTT_printf_BLINK("COUPLING OFF! ");
			 if(EE_Parameter.BitConfig & (CFG_LOOP_LINKS | CFG_LOOP_RECHTS | CFG_LOOP_UNTEN | CFG_LOOP_OBEN)) HoTT_printf_BLINK("LOOPING! ");
			 if(Parameter_GlobalConfig & CFG_HEADING_HOLD) HoTT_printf_BLINK("HH! ");
			 if(!(Parameter_GlobalConfig & CFG_KOMPASS_AKTIV)) HoTT_printf_BLINK("COMPASS OFF! ");
			}
			break;
    case 8: //ASCIIPacket.WarnBeep = HoTT_Waring();
			break;
    case 9: 
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
			if(HottKeyboard == HOTT_KEY_SET) { if(show_poti) show_poti = 0; else show_poti = 1;   Hott_ClearLine(6);  Hott_ClearLine(7);}
			else
			if(HottKeyboard == HOTT_KEY_LEFT) { LIBFC_HoTT_Clear(); page++; line = 0;}
			else
			if(HottKeyboard == HOTT_KEY_RIGHT) { LIBFC_HoTT_Clear(); page--; line = 0;};
			HottKeyboard = 0;
			break;
   default:  line = 0;
			break;
  }
  break;
  case 3:
  switch(line++)
  {
	static unsigned char load_waypoint_tmp2 = 1, changed2;
	case 0:  
			HoTT_printfxy(0,0,"Load Waypoints"); 
			HoTT_printfxy(0,1,"(Relative Positions)"); 
//			HoTT_printfxy(0,1,"(Absolute)"); 
			break;
    case 1: 
			if(NaviData_WaypointNumber)	HoTT_printfxy(0,6,"Active WP:%2d/%d ",NaviData_WaypointIndex,NaviData_WaypointNumber)
			else HoTT_printfxy(0,6,"No WPs active     ")
			break;
    case 2: 
			 HoTT_printfxy(0,7,"%2i.%1iV ",UBat/10, UBat%10)
			 HoTT_printfxy(11,7,"%s",WPL_Name)
    case 3: 
    case 4: 
    case 5: 
			if(load_waypoint_tmp2) 
			 {
			  if(changed2 && HoTTBlink) HoTT_printfxy(10,3,"   ")
			  else HoTT_printfxy(10,3,"%2i   ",load_waypoint_tmp2); 
			  HoTT_printfxy(0,3,"Load list:")
			 } 
			else 
			 { 
			  HoTT_printfxy(0,3,"Load list: -- ");
			 } 
			 if(NaviData_MaxWpListIndex == 0) HoTT_printfxy(0,4,"No SD-Card   ") 
			 else
			 {
			  if(GPSInfo.SatFix == SATFIX_3D) 
			   {
  			    if(changed2 && load_waypoint_tmp2) HoTT_printfxy(0,4,"(Set -> Load)") 
			    else HoTT_printfxy(0,4,"             "); 
				if(HottKeyboard == HOTT_KEY_SET) { if(load_waypoint_tmp2) ToNC_Load_WP_List = load_waypoint_tmp2 | 128; changed2 = 0;}
			   } else HoTT_printfxy(0,4,"!No GPS-Fix! "); 
			 } 
			if(HottKeyboard == HOTT_KEY_UP && load_waypoint_tmp2 < NaviData_MaxWpListIndex) { changed2 = 1; load_waypoint_tmp2++;HoTTBlink = 0;}
			if(HottKeyboard == HOTT_KEY_DOWN && load_waypoint_tmp2 > 1) { changed2 = 1; load_waypoint_tmp2--;HoTTBlink = 0;};
			if(HottKeyboard == HOTT_KEY_LEFT) { LIBFC_HoTT_Clear(); page++; line = 0;}
			if(HottKeyboard == HOTT_KEY_RIGHT) { LIBFC_HoTT_Clear(); page--; line = 0;};
			HottKeyboard = 0;
			break;
   default:  line = 0;
			break;
  }
  break;
  case 4:
  switch(line++)
  {
	static unsigned char load_waypoint_tmp = 1, changed;
	case 0:  
			HoTT_printfxy(0,0,"Load Waypoints"); 
			HoTT_printfxy(0,1,"(Fixed Positions)"); 
			break;
    case 1: 
			if(NaviData_WaypointNumber)	HoTT_printfxy(0,6,"Active WP:%2d/%d ",NaviData_WaypointIndex,NaviData_WaypointNumber)
			else HoTT_printfxy(0,6,"No WPs active    ")
			break;
    case 2: 
			 HoTT_printfxy(0,7,"%2i.%1iV ",UBat/10, UBat%10)
			 HoTT_printfxy(11,7,"%s",WPL_Name)
    case 3: 
    case 4: 
    case 5: 
			HoTT_printfxy(0,3,"Load list:")
			if(load_waypoint_tmp) 
			 {
			  if(changed && HoTTBlink) HoTT_printfxy(10,3,"   ")
			  else HoTT_printfxy(10,3,"%2d (FIX)",load_waypoint_tmp);
			 } 
			else 
			 { 
			  HoTT_printfxy(10,3," --")
			 } 
  			
			 if(NaviData_MaxWpListIndex == 0) HoTT_printfxy(0,4,"No SD-Card   ") 
			 else
			 {
  			    if(changed && load_waypoint_tmp) HoTT_printfxy(0,4,"(Set -> Load)") 
			    else HoTT_printfxy(0,4,"             "); 
			 } 
			if(HottKeyboard == HOTT_KEY_UP && load_waypoint_tmp < NaviData_MaxWpListIndex) { changed = 1; load_waypoint_tmp++; HoTTBlink = 0;}
			if(HottKeyboard == HOTT_KEY_DOWN && load_waypoint_tmp > 1) { changed = 1; load_waypoint_tmp--; HoTTBlink = 0;};
			if(HottKeyboard == HOTT_KEY_SET) { if(load_waypoint_tmp) ToNC_Load_WP_List = load_waypoint_tmp; changed = 0;}
			if(HottKeyboard == HOTT_KEY_LEFT) { LIBFC_HoTT_Clear(); page++; line = 0;}
			if(HottKeyboard == HOTT_KEY_RIGHT) { LIBFC_HoTT_Clear(); page--; line = 0;};
			HottKeyboard = 0;
			break;
   default:  line = 0;
			break;
  }
  break;
  case 5:
  switch(line++)
  {
    static unsigned char wp_tmp, changed;
	case 0:  
			HoTT_printfxy(0,0,"Store single Position"); 
//			HoTT_printfxy(0,1,"(Fixed Positions)"); 
			break;
    case 1: 
  		    HoTT_printfxy(0,2," %2i.%1iV ",UBat/10, UBat%10)
			HoTT_printfxy(0,3," %2i:%02i ",FlugSekunden/60,FlugSekunden%60);			   
//			HoTT_printfxy(0,4,"Dist:%3dm",NaviData_TargetDistance)
			break;
    case 2: 
			HoTT_printfxy(11,2,"ALT:%4im", (int16_t)(HoehenWert/100))              
			HoTT_printfxy(11,3,"DIR: %3d%c",CompassCorrected, HoTT_GRAD);
			HoTT_printfxy(11,4,"Cam: %3i",Parameter_ServoNickControl);
			break;
    case 3: 
    case 4: 
    case 5: 
 		    HoTT_printfxy(0,6,"Store point:")
			if(wp_tmp) 
			 {
			  if(changed && HoTTBlink) HoTT_printfxy(13,6,"   ")
			  else HoTT_printfxy(13,6,"%2d ",wp_tmp);
			 } 
			else 
			 { 
			  HoTT_printfxy(13,6,"--")
			 } 
 			
		    if(GPSInfo.SatFix == SATFIX_3D) 
		    {
			 if(NaviData_MaxWpListIndex == 0) HoTT_printfxy(0,7,"No SD-Card   ") 
			 else
			 {
  			    if(changed && wp_tmp) HoTT_printfxy(0,7,"(Set -> Store)") 
			    else Hott_ClearLine(7);
			 } 
			 if(HottKeyboard == HOTT_KEY_SET) { if(wp_tmp) ToNC_Store_SingePoint = wp_tmp; changed = 0;}
		    }
            else HoTT_printfxy(0,7,"!No GPS-Fix! "); 
			
			if(HottKeyboard == HOTT_KEY_UP && wp_tmp < NaviData_MaxWpListIndex) { changed = 1; wp_tmp++; HoTTBlink = 0;}
			if(HottKeyboard == HOTT_KEY_DOWN && wp_tmp > 1) { changed = 1; wp_tmp--; HoTTBlink = 0;};
			if(HottKeyboard == HOTT_KEY_LEFT) { LIBFC_HoTT_Clear(); page++; line = 0;}
			if(HottKeyboard == HOTT_KEY_RIGHT) { LIBFC_HoTT_Clear(); page--; line = 0;};
			HottKeyboard = 0;
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Bedienung per Taster am Sender
  if(PPM_in[EE_Parameter.MenuKeyChannel] > 50)  // 
   {
    hyterese = 2;
    if(CheckDelay(delay)) { wp_tmp = 0; hyterese = 1;}
   }
  else
  if(PPM_in[EE_Parameter.MenuKeyChannel] < -50)  
   {
	delay = SetDelay(2500);
	if(hyterese == 2 && (wp_tmp < NaviData_MaxWpListIndex))
	 {
	  wp_tmp++;
	  ToNC_Store_SingePoint = wp_tmp;
	  changed = 0;
	 }
    hyterese = 0; 
   }
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			break;
   default:  line = 0;
			break;
  }
  break;
  case 6:
  switch(line++)
  {
    static unsigned char wp_tmp, changed;
	case 0:  
			HoTT_printfxy(0,0,"Load single Position"); 
//			HoTT_printfxy(0,1,"(Fixed Positions)"); 
			break;
    case 1: 
  		    HoTT_printfxy(0,2," %2i.%1iV ",UBat/10, UBat%10)
			HoTT_printfxy(0,3," %2i:%02i ",FlugSekunden/60,FlugSekunden%60);			   
//			HoTT_printfxy(0,4,"Dist:%3dm",NaviData_TargetDistance)
		    if(NaviData_WaypointNumber)	HoTT_printfxy(0,5,"WP:%2d/%d Dist:%3dm ",NaviData_WaypointIndex,NaviData_WaypointNumber,NaviData_TargetDistance)
		    else Hott_ClearLine(5);
			break;
    case 2: 
			if(FromNC_AltitudeSpeed)
			  HoTT_printfxy(8,2,"ALT:%4i/%im ", (int16_t)(HoehenWert/100),(int16_t)(FromNC_AltitudeSetpoint/100))
			else
			  HoTT_printfxy(8,2,"ALT:%4im    ",(int16_t)(HoehenWert/100))
 
			HoTT_printfxy(8,3,"DIR: %3d%c",CompassCorrected, HoTT_GRAD);
			HoTT_printfxy(8,4,"Cam: %3i",Parameter_ServoNickControl);
			break;
//			 HoTT_printfxy(11,7,"%s",WPL_Name)
    case 3: 
    case 4:                                       
    case 5: 
		  if(HottKeyboard) DebugOut.Analog[17]++;
		  HoTT_printfxy(0,6,"load point:")
			if(wp_tmp) 
			 {
			  if(changed && HoTTBlink) HoTT_printfxy(11,6,"   ")
			  else HoTT_printfxy(11,6,"%2d",wp_tmp);
			 } 
			else 
			 { 
			  HoTT_printfxy(11,6,"--")
			 } 
  			
			 if(NaviData_MaxWpListIndex == 0) HoTT_printfxy(0,7,"No SD-Card   ") 
			 else
			 {
  			    if(changed && wp_tmp) HoTT_printfxy(0,7,"(Set -> Load)") 
			    else 
				{ 
				 Hott_ClearLine(7);
				 if(NaviData_WaypointNumber) HoTT_printfxy(0,7,"%s",WPL_Name);
				} 
			 } 
			if(HottKeyboard == HOTT_KEY_UP && wp_tmp < NaviData_MaxWpListIndex) { changed = 1; wp_tmp++; HoTTBlink = 0;}
			if(HottKeyboard == HOTT_KEY_DOWN && wp_tmp > 1) { changed = 1; wp_tmp--; HoTTBlink = 0;};
			if(HottKeyboard == HOTT_KEY_SET) { if(wp_tmp) ToNC_Load_SingePoint = wp_tmp; changed = 0;}
			if(HottKeyboard == HOTT_KEY_LEFT) { LIBFC_HoTT_Clear(); page++; line = 0;}
			if(HottKeyboard == HOTT_KEY_RIGHT) { LIBFC_HoTT_Clear(); page--; line = 0;};
			HottKeyboard = 0;
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Bedienung per Taster am Sender
  if(PPM_in[EE_Parameter.MenuKeyChannel] > 50)  // 
   {
    hyterese = 2;
    if(CheckDelay(delay)) { wp_tmp = 0; hyterese = 1;}
   }
  else
  if(PPM_in[EE_Parameter.MenuKeyChannel] < -50)  
   {
	delay = SetDelay(2500);
	if(hyterese == 2 && (wp_tmp < NaviData_MaxWpListIndex))
	 {
	  wp_tmp++;
	  ToNC_Load_SingePoint = wp_tmp;
	  changed = 0;
	 }
    hyterese = 0; 
   }
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			break;
   default:  line = 0;
			break;
  }
  break;
  case 7:
  switch(line++)
  {
	static unsigned char i=0,test=0,set=0; 
		
	case 0: HoTT_printfxy(0,0,"Motortest / Setpoints");break;
	case 1: //HoTT_printfxy(0,1,"Motor Setpoint Strom ");
    case 2:
    case 3: 
	case 4: i=((line-2)*2)+1;
			if(MotorenEin)
			{
				HoTT_printfxy(0,line,"M%i=%2i%2i.%iA M%i=%2i%2i.%iA",i,Motor[i-1].SetPoint,Motor[i-1].Current/10,Motor[i-1].Current%10,i+1,Motor[i].SetPoint,Motor[i].Current/10,Motor[i].Current%10);
			}
			else
			{
				HoTT_printfxy(0,line,"M%i=%2i%2i.%iA M%i=%2i%2i.%iA",i,MotorTest[i-1],Motor[i-1].Current/10,Motor[i-1].Current%10,i+1,MotorTest[i],Motor[i].Current/10,Motor[i].Current%10);
			}
			break;
    case 5: if(test)
			{
				HoTT_printfxy(0,6,"!!!Motortest Aktiv!!!");
			}
	case 6: if(test)
			{
				PC_MotortestActive = 254;
				HoTT_printfxy(0,7,"Motor %i",test);
				MotorTest[test-1]=set;
			}
    case 7:
    case 8: 
    case 9: 
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
			if(HottKeyboard == HOTT_KEY_RIGHT) 
			{
				if(test)
				{
					set=0;
					MotorTest[test-1]=set;
					if(test<8) test++;
				}
				else
				{
					LIBFC_HoTT_Clear();
					page--;
					line=0;
				}
			}				
			else
			if(HottKeyboard == HOTT_KEY_LEFT)
			{
				if(test)
				{
					set=0;
					MotorTest[test-1]=set;
					if(test>1) test--;
				}
				else
				{
					LIBFC_HoTT_Clear();
					page++;
					line = 0;
				}
			}
			else
			if((HottKeyboard == HOTT_KEY_UP) && (set <98 ) && test) set+=2;//GESCHW
			else
			if((HottKeyboard == HOTT_KEY_DOWN) && (set >0  ) && test) set-=2;
			else
			if((HottKeyboard == HOTT_KEY_SET) &&  !MotorenEin)
			{
				if(test) test = 0; else test = 1;
				set=0;
				Hott_ClearLine(6);  Hott_ClearLine(7);
			}
			HottKeyboard = 0;
			break;
   default:  line = 0;
			break;
	//HoTT_printfxy(10 ,line,"I");
	//line++;
  }
  break;
  case 8:
  switch(line++)
  {
#define MD_OFF 1
#define MD_CAL 2
#define MD_SAV 3
	static unsigned char mode=MD_OFF,cursor=MD_OFF; 

	case 0: HoTT_printfxy(0,0,"ACC calibration");break;
	case 1: HoTT_printfxy(0,2,"ACC:   N:%3i R:%3i ",NeutralAccX,NeutralAccY);
	case 2: HoTT_printfxy(0,3,"Stick:   (%i/%i)     ",ChannelNick,ChannelRoll);
	case 3: if(ChannelNick || ChannelRoll)	HoTT_printfxy(7,3,"!!");
			break;
	case 4: HoTT_printfxy(2,4,"Off");break;
    case 5: HoTT_printfxy(2,5,"Calibrate");break;
	case 6: HoTT_printfxy(2,6,"Save          ");
			if(mode == MD_SAV && cursor == MD_SAV) 
			 { 
			  HoTT_printfxy(7,6,"(SET)");
			 } 
			else if((mode == MD_CAL) && !((NC_GPS_ModeCharacter == ' ') || (NC_GPS_ModeCharacter == '/') || (NC_GPS_ModeCharacter == '-')))
			 {
				HoTT_printfxy(2,6,"Swich GPS off!");	
			 }	
			break;
    case 7: 
    case 8: HoTT_printfxy(0,cursor+3,">");break;
    case 9: HoTT_printfxy(1,mode+3,"*");break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
			if(HottKeyboard == HOTT_KEY_RIGHT)
			{
				switch(mode)
				{
					case MD_OFF: LIBFC_HoTT_Clear(); 
							page--; // leave menu
							line = 0;
							break;
					case MD_CAL: NeutralAccY++;
							break;
					case MD_SAV: break;
					default: mode=MD_OFF;break;
				}
			}
			else
			if(HottKeyboard == HOTT_KEY_LEFT)
			{
				switch(mode)
				{
					case MD_OFF: LIBFC_HoTT_Clear(); 
							page++;  // leave menu
							line = 0;
							break;
					case MD_CAL: NeutralAccY--;
							break;
					case MD_SAV: break;
					default: mode=MD_OFF;
							break;
				}				
			}
			else
			if(HottKeyboard == HOTT_KEY_UP)
			{
				switch(mode)
				{
					case MD_CAL: NeutralAccX++;
							break;
					case MD_OFF:
					case MD_SAV: if(cursor>1) {HoTT_printfxy(0,cursor+3," ");cursor--;}
							HoTT_printfxy(2,6,"     ");
							break;
					default: mode=MD_OFF;
							break;
				}
			}
			else
			if(HottKeyboard == HOTT_KEY_DOWN)
			{
				switch(mode)
				{
					case MD_CAL: 	NeutralAccX--;
								break;
					case MD_SAV: 
					case MD_OFF: 	if(cursor<MD_SAV) {HoTT_printfxy(0,cursor+3," ");cursor++;}
								break;
					default: 	mode=MD_OFF;
								break;
				}
			}
			else
			if(HottKeyboard == HOTT_KEY_SET)
			{
				switch(mode)
				{
					case MD_OFF: HoTT_printfxy(1,mode+3," ");
							mode = cursor;
							if(mode == MD_CAL && !EE_Parameter.Driftkomp) EE_Parameter.Driftkomp = 6; // enables the Gyro-Drift compensation to make sure that a litlte calibration error won't effect the attitude
							break;
					case MD_CAL: HoTT_printfxy(1,mode+3," ");
							mode = MD_OFF;
							break;
					case MD_SAV: 
							Hott_ClearLine(7);
							if(cursor == MD_SAV)
							{
								if(!MotorenEin)
								{
/*									BoatNeutralNick = AdNeutralNick;
									BoatNeutralRoll = AdNeutralRoll;
									BoatNeutralGier = AdNeutralGier;
									SetParamWord(PID_ACC_NICK, (uint16_t)NeutralAccX);
									SetParamWord(PID_ACC_ROLL, (uint16_t)NeutralAccY);
									SetParamWord(PID_GYRO_NICK,(uint16_t)BoatNeutralNick);
									SetParamWord(PID_GYRO_ROLL,(uint16_t)BoatNeutralRoll);
									SetParamWord(PID_GYRO_YAW,(uint16_t)BoatNeutralGier);
*/
									StoreNeutralToEeprom();
									HoTT_printfxy(7,6," okay ");
									HoTT_printfxy(1,mode+3," ");
									mode = MD_OFF;
								}
								else
								{
									HoTT_printfxy(0,7,"Motors running!!!");
									mode = MD_OFF;
								}
							}
							else
							{
								HoTT_printfxy(1,mode+3," ");
								mode=cursor;
							}
							break;
					default: mode=MD_OFF;
							break;
				}
			}
			HottKeyboard = 0;
			break;
   default:  line = 0;
			break;
	//HoTT_printfxy(10 ,line,"I");
	//line++;
  }
  break;
/*
//------------------------------------------------------------------------------------------
// HoTT-Plus
//------------------------------------------------------------------------------------------
  case 9:
  switch(line++)
  {
	case 0: HoTT_printfxy(0,0,"I2C Schwerpunkt GAS");
			break;
	case 1: HoTT_printfxy(0,1,"I2C%3i%3i%3i%3i",Motor[0].State & MOTOR_STATE_ERROR_MASK,Motor[1].State & MOTOR_STATE_ERROR_MASK, Motor[2].State & MOTOR_STATE_ERROR_MASK, Motor[3].State & MOTOR_STATE_ERROR_MASK);
			break;
    case 2: HoTT_printfxy(0,2,"   %3i%3i%3i%3i",Motor[4].State & MOTOR_STATE_ERROR_MASK,Motor[5].State & MOTOR_STATE_ERROR_MASK, Motor[6].State & MOTOR_STATE_ERROR_MASK, Motor[7].State & MOTOR_STATE_ERROR_MASK);
			break;
    
	case 3:  {                       //0123456789ABCDEF
				int r=0;
				int n=0;
				int g=0;
				n=SummeNick >> 9;
				r=SummeRoll >> 9;
				g=Mess_Integral_Gier >> 9;

				HoTT_printfxy(0,5,"%3iN   %3iR   %3iG",n ,r ,g);
			}

			break;
    case 4: {                       //0123456789ABCDEF
				HoTT_printfxy(0,4,"+  ^   +  <");
			}
			break;
    case 5: {                       //0123456789ABCDEF
				HoTT_printfxy(0,6,"-  v   -  >");
			}
			break;
	case 6: HoTT_printfxy(0,7,"%3i=HG/4 %3i=Gas",HoverGas/4,StickGas);

			break; 
    case 7:
    case 8: 
    case 9: 
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
			if(HottKeyboard == HOTT_KEY_RIGHT) { LIBFC_HoTT_Clear(); page--; line = 0;}
			else
			if(HottKeyboard == HOTT_KEY_LEFT) { LIBFC_HoTT_Clear(); page++; line = 0;}
			HottKeyboard = 0;
			break;
   default:  line = 0;
			break;
  }
  break;
//---------------------------------------------------------------------------------------------------
  case 10:
{   
	static signed char i=0,j=0,Changepos=0;                   
	
	if(line==9)
	{
		line=0;
		if(HottKeyboard == HOTT_KEY_SET   ) { if(Changepos) Changepos = 0; else Changepos = 1;}
		else
		if(Changepos)
		{
			unsigned char temp=0;
			temp=(Changepos+j)-1;
			if((HottKeyboard == HOTT_KEY_RIGHT) && !((unsigned char)(*Parameter_List[temp].Variable + Parameter_List[temp].offset) >= Parameter_List[temp].max )) {*Parameter_List[temp].Variable += 1;}
			else
			if((HottKeyboard == HOTT_KEY_LEFT) && !((unsigned char)(*Parameter_List[temp].Variable + Parameter_List[temp].offset) <= Parameter_List[temp].min )) {*Parameter_List[temp].Variable -= 1;}
			else
			if(HottKeyboard == HOTT_KEY_UP  )
			{
				Changepos--;
				line = Changepos/2;
				if(Changepos< 1       ) {Changepos=16;}
			}
			else
			if(HottKeyboard == HOTT_KEY_DOWN)
			{
				Changepos++;
				line = Changepos/2;
				if(Changepos >= 17       ) {Changepos=1;}
			}
		}
		else
		{
			if(HottKeyboard == HOTT_KEY_RIGHT) { LIBFC_HoTT_Clear(); page--; line = 0;}
			else
			if(HottKeyboard == HOTT_KEY_LEFT) { LIBFC_HoTT_Clear(); page++; line = 0;}
			else
			if(HottKeyboard == HOTT_KEY_UP  )
			{
				j-=16;
				line = 0;
				if(j< 0       ) {j=0;}
			}
			else
			if(HottKeyboard == HOTT_KEY_DOWN)
			{
				LIBFC_HoTT_Clear();
				j+=16;
				line = 0;
				if(j+14> MAXPARAM       ) {j=MAXPARAM-15;}
			}
		}
		
		Debug("line=%i Changepos=%i j=%i Key=%i",line,Changepos,j,HottKeyboard);
		HottKeyboard = 0;
	}
	
	HoTT_printfxy(10 ,line,"I");
	i=(line*2)+(j);
	if(Changepos==(line*2)+1)
	{
		HoTT_printfxy(0 ,line,">%3i=%-5.5s%",(unsigned char)(*Parameter_List[i  ].Variable + Parameter_List[i  ].offset),&Parameter_List[i  ].name);
	}
	else
	{
		HoTT_printfxy(0 ,line," %3i=%-5.5s%",(unsigned char)(*Parameter_List[i  ].Variable + Parameter_List[i  ].offset),&Parameter_List[i  ].name);
	}
	if(Changepos==(line*2)+2)
	{
		HoTT_printfxy(11,line,">%3i=%-5.5s%",(unsigned char)(*Parameter_List[i+1].Variable + Parameter_List[i+1].offset),&Parameter_List[i+1].name);
	}
	else
	{
		HoTT_printfxy(11,line," %3i=%-5.5s%",(unsigned char)(*Parameter_List[i+1].Variable + Parameter_List[i+1].offset),&Parameter_List[i+1].name);
	}

	line++;	
	
}
  break;
  case 11:
  switch(line++)
  {
	case 0: HoTT_printfxy(0,0,"Setting speichern");
			break;
	case 1: HoTT_printfxy(0,1,"Setting%1i= %-11.11s",GetActiveParamSet(),EE_Parameter.Name);
			break;			  //123456789012345678901
    case 2: HoTT_printfxy(0,2,"Speichern nach Set %i",settingdest);
			break;
    case 3: HoTT_printfxy(0,4,"\"SET\" zum speichern");
			break;
    case 4: HoTT_printfxy(0,5,"^ v zum auswaehlen");
			break;
    case 5:  
	case 6:  
    case 7:
    case 8: 
    case 9: 
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
			if(HottKeyboard == HOTT_KEY_RIGHT) { LIBFC_HoTT_Clear(); page--; line = 0;}
			else
			if(HottKeyboard == HOTT_KEY_LEFT) { LIBFC_HoTT_Clear(); page++; line = 0;}
			else
			if((HottKeyboard == HOTT_KEY_UP) & (settingdest <5 )) settingdest++;
			else
			if((HottKeyboard == HOTT_KEY_DOWN) & (settingdest >1  )) settingdest--;
			else
			if((HottKeyboard == HOTT_KEY_SET) &&  !MotorenEin)
			{
				ParamSet_WriteToEEProm(settingdest);
				//JetiBeep = jetibeepcode[GetActiveParamSet()-1];
				Piep(GetActiveParamSet(),120);
				HoTT_printfxy(0,7,"Gespeichert!");  
			}
			HottKeyboard = 0;
			break;
   default:  line = 0;
			break;
  }
  break;
//------------------------------------------------------------------------------------------
 // HoTT-Plus
//------------------------------------------------------------------------------------------
*/
  default:  page = 0;
  break;
 } 
}

#endif


	
