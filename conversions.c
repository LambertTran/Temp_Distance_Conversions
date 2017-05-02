#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool VALIDATE_FORMAT(int  numInputEnter, int numInputWant, char lastChar);
bool VALIDATE_VALUE(char choice, char keyword[20]);
bool VALIDATE_INPUT(int numInputEnter,int numInputWant, char lastChar, char choice,char keyword[20]);

void CONVERSIONS(char choice);

void TEMP_CONVERSION();
void DIST_CONVERSION();

double F_TO_C (double value);
double C_TO_K (double value);
double K_TO_F (double value);
double CONVERT_TEMP_F (double value, char suffix);
double CONVERT_TEMP_NEW_UNIT (double value, char newUnit);

double I_To_F (double value);
double F_To_Y (double value);
double Y_To_M (double value);
double M_To_I (double value);
double CONVERT_DIST_IN (double value, char suffix);
double CONVERT_DIST_NEW_UNIT (double value, char newUnit);


int main(void) {
   /*
    * User input either t for temperature and d for distance in upper or lower case
    * Validate the input
    * Use function Conversion to calculate either temperature and distance
    */

   char choice;
   char lastChar; 
   int  numInputEnter; 
   
   printf("Pick the type of conversion that you would like to do.\n");
   printf("T or t for temperature\n");
   printf("D or d for distance\n");
   printf("Enter your choice: ");

   numInputEnter = scanf(" %c%c",&choice,&lastChar);

   VALIDATE_INPUT(numInputEnter,2,lastChar,choice,"first choice");

   CONVERSIONS(choice);

   return 0;
}


bool VALIDATE_FORMAT(int numInputEnter,int numInputWant, char lastChar) {

   /*
    * If user number of user input matched with the number of input need
    * and the last character entered is an enter 
    * Return true, otherwise, return false
    */

   return numInputEnter == numInputWant && lastChar == '\n';
}



bool VALIDATE_VALUE(char choice, char keyword[20]) {
   
   /* 
    * Check the input with a keyword
    * Return true if
    *    keyword: 
    *       first choices: t for temperature or d for distance
    *       temperature choices : f, c or k 
    *       distance choices: f, m, i or y       
    */

   if (strcmp(keyword,"first choice")==0 ) {
      return (choice =='T' || choice =='t' || choice =='D' || choice =='d');
   }
   
   else if (strcmp(keyword,"temp choice") ==0) {
      return (choice == 'F'|| choice =='f' || choice =='C'|| choice =='c' || choice =='K' || choice =='k' );
   }
   
   else if (strcmp(keyword,"dist choice") ==0) {
      return (choice == 'F'|| choice =='f' || choice =='I'|| choice =='i' || choice =='Y' || choice =='y'|| choice =='M' ||choice =='m');
   }
   return 0;
}    


bool VALIDATE_INPUT(int numInputEnter,int numInputWant, char lastChar, char choice, char keyword[20]) {
   
   /*
    * Validate user input along with keyword
    * return true if the inputs are properly inputted
    * otherwise, print error and end program 
    */

   if ( VALIDATE_FORMAT(numInputEnter,numInputWant,lastChar)) {
      if (VALIDATE_VALUE(choice,keyword)){
       return true;
      }

      else if (strcmp(keyword,"first choice") == 0) {
         printf("Unknown conversion type %c chosen. Ending program.\n",choice);
         exit(0);
      } 
   
      else if (strcmp(keyword,"temp choice") == 0) {
         printf("%c is not a valid temperature type. Ending program.\n",choice);
         exit(0);
      }
      
      else if (strcmp(keyword,"dist choice") == 0) {
         printf("%c is not a valid distance type. Ending program.\n",choice);
         exit(0);
      }
   }
   else { 
      printf("Invalid formatting. Ending program.\n");
      exit(0);
   }
  return 0;
}

void CONVERSIONS(char choice){
  
   /*
    * If user enter T or t, use temperature Convertion
    * otherwiese, use distance convertion
    */

   if (choice == 'T' || choice =='t') {
      TEMP_CONVERSION();
   }
   else 
      DIST_CONVERSION();
   return;
}


/*
 * Converting Temperature between different units
 */

double F_TO_C (double value) {
   return ((value - 32.0) * 5.0 / 9.0);
}

double C_TO_K (double value) {
   return (value + 273.15);
}

double K_TO_F (double value) {
   return ((value - 273.15) * 9.0 / 5.0 + 32);
}


double CONVERT_TEMP_F (double value, char suffix) {
   
   /* 
    * Convert the inputted temperature to F
    */
  
   if (suffix == 'C' || suffix == 'c') {   
      value = C_TO_K(value);
      value = K_TO_F(value);
   }
   else if (suffix == 'K' || suffix == 'k') {  
      value = K_TO_F(value);
   }

   return value;
}

double CONVERT_TEMP_NEW_UNIT (double value, char newUnit) {
  
  /*
   * Convert the inputted temperature at F to the new unit
   */

  if (newUnit == 'C' || newUnit == 'c') {   
      value = F_TO_C(value);
  }
  else if (newUnit == 'K' || newUnit == 'k') {  
      value = F_TO_C(value);
      value = C_TO_K(value);
  }

   return value;
}

void TEMP_CONVERSION() {

   /*
    * Ask user to input a value along with a suffix needed to be converted
    * Validate user input
    * Ask user to input a new unit of interest
    * Validate user input
    * print the result
    */
   char suffix, newUnit, lastChar;
   double value, newValue;
   int numInputEnter;

   printf ("Enter the temperature followed by its suffix (F, C, or K): ");
   numInputEnter = scanf(" %lf %c%c",&value,&suffix,&lastChar);

   VALIDATE_INPUT(numInputEnter,3,lastChar,suffix,"temp choice");
   
   printf("Enter the new unit type (F, C, or K): ");
   numInputEnter = scanf(" %c%c",&newUnit,&lastChar);

   VALIDATE_INPUT(numInputEnter,2,lastChar,newUnit,"temp choice");

   newValue = CONVERT_TEMP_F(value,suffix);

   newValue = CONVERT_TEMP_NEW_UNIT(newValue, newUnit);

   printf("%0.2lf%c is %0.2lf%c\n",value,toupper(suffix),newValue,toupper(newUnit));
   
   return;
   
}

/*
 * Repeat the same step for distance conversion
 */

void DIST_CONVERSION() {
   char suffix, newUnit, lastChar;
   double value, newValue;
   int numInputEnter;

   printf ("Enter the distance followed by its suffix (I,F,Y,M): ");
   numInputEnter = scanf(" %lf %c%c",&value,&suffix,&lastChar);

   VALIDATE_INPUT(numInputEnter,3,lastChar,suffix,"dist choice");
   
   printf("Enter the new unit type (I,F,Y,M): ");
   numInputEnter = scanf(" %c%c",&newUnit,&lastChar);

   VALIDATE_INPUT(numInputEnter,2,lastChar,newUnit,"dist choice");

   newValue = CONVERT_DIST_IN(value,suffix);

   newValue = CONVERT_DIST_NEW_UNIT(newValue, newUnit);
    
   printf("%0.2lf%c is %0.2lf%c\n",value,toupper(suffix),newValue,toupper(newUnit));
   
   return;
   
}         


double I_TO_F (double value) {
   return (value / 12.0);
}

double F_TO_Y (double value) {
   return (value /3.0);
}

double Y_TO_M (double value) {
   return (value / 1760.0);
}

double M_TO_I (double value) {
   return (value *63360.0);
}


double CONVERT_DIST_IN(double value, char suffix) { 
   if (suffix == 'F' || suffix == 'f') {
      value = F_TO_Y(value);
      value = Y_TO_M(value);
      value = M_TO_I(value);
   }
   else if (suffix == 'Y' || suffix == 'y') {
      value = Y_TO_M(value);
      value = M_TO_I(value);
   } 
   else if (suffix == 'M' || suffix == 'm') {
      value = M_TO_I(value);
   }

   return value;
}


double CONVERT_DIST_NEW_UNIT (double value, char newUnit) {
   if (newUnit == 'F' || newUnit == 'f') {
      value = I_TO_F(value);
   }
   else if (newUnit == 'Y' || newUnit == 'y') {
      value = I_TO_F(value);
      value = F_TO_Y(value);
   }
   else if (newUnit == 'M' || newUnit == 'm') {
      value = I_TO_F(value);
      value = F_TO_Y(value);
      value = Y_TO_M(value);
   }
   
   return value;
}




