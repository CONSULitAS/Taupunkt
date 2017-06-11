#include "Cosa/IOStream/Driver/UART.hh"
#include "Cosa/Trace.hh"

#include "Cosa/Math.hh"

// Taupunkt(Phi=Feuchte in %, Theta=Temperatur) in Celsius
// Quelle: https://de.wikipedia.org/wiki/Taupunkt#Abh.C3.A4ngigkeit_der_Taupunkttemperatur_von_relativer_Luftfeuchtigkeit_und_Lufttemperatur
double Tau(double Phi, double Theta) {
  trace << "Phi: " << Phi << " Theta: " << Theta << endl;

  Phi /= 100.0; // Wikipedia-Formel rechnet Anteile in Brüchen, nicht in Prozent
  
  //  const double K1=6.112; // wird für Berechnung aus relativer Fechte nicht benötigt
  if (Theta>0) {
    //mit0 < Theta < 60 Grad (über Wasser): K1=6,112 hPa, K2=17,62, K3=243,12 Grad)
    const double K2=17.62;
    const double K3=243.12;

    return ( K3 * ( ( ( K2*Theta/(K3+Theta) ) + log (Phi) ) / ( ( K2*K3/(K3+Theta) ) - log (Phi) ) ) );
  }
  else {
    // und-65 < Theta <= 0 Grad (über Eis): K1=6,112 hPa, K2=22,46, K3=272,62 Grad)
    // vereinfachende Annahme: kein flüssiges Wasser ab 0°C, also keine unterkühlte Schmelze in der Natur
    const double K2=22.46;
    const double K3=272.62;

    return ( K3 * ( ( ( K2*Theta/(K3+Theta) ) + log (Phi) ) / ( ( K2*K3/(K3+Theta) ) - log (Phi) ) ) );
  }
}

void setup() {
  // put your setup code here, to run once:

  double tau;
  
  uart.begin(9600);
  trace.begin(&uart, PSTR("Taupunkt_roh: started"));

  tau=Tau(60.0, 20.0); // Test 60% bei 20°
  trace << PSTR("Taupunkt_roh: ") << tau << PSTR("°C bei 60% bei 20°") << endl;
  trace << PSTR("Taupunkt_roh: ") << Tau(61.7, 24.3) << PSTR("°C bei 61.7% bei 24.3°") << endl;
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
