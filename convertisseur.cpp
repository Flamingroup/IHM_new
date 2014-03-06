#include "convertisseur.hpp"

#include <iostream>
using std::cerr;
using std::endl;

double Convertisseur::convertFromTo(double value, char from, char to){
    switch(to) {
/*    case 'n':
        return convertToBase(value, from);
    case 'u':
        return convertToBase(value, from);
  */
        case 'm':
            return convertToMilli(value, from);
        case 'b': // base
            return convertToBase(value, from);
        case 'k':
            return convertToKilo(value, from);
        case 'M':
            return convertToMega(value, from);
 /*       case 'G':
            return convertToBase(value, from);
            */
        case '#':
            cerr << "Invalid data" << endl;
            return value;
        default:
            cerr << "Error, unknown argument '" << to << "', correct : m, b, k, M" << endl;
            return value;
    }
}

double Convertisseur::convertToBase(double value, char from) {
    switch(from) {
        case 'n':
            return value / 1000000000.0;
        case 'u':
            return value / 1000000.0;
        case 'm':
            return value / 1000.0;
        case 'k':
            return value * 1000.0;
        case'M':
            return value * 1000000.0;
        case 'G':
            return value * 1000000000.0;
        default:
            cerr << "Error, unknown argument '" << from << "', correct : n, u, m, k, M, G" << endl;
            return value;
    }
}

double Convertisseur::convertToMilli(double value, char from)
{
    switch(from) {
        case 'n':
            return value / 1000000.0;
        case 'u':
            return value / 1000.0;
        case 'b':
            return value * 1000.0;
        case 'k':
            return value * 1000000.0;
        case'M':
            return value * 1000000000.0;
        case 'G':
            return value * 1000000000000.0;
        default:
            cerr << "Error, unknown argument '" << from << "', correct : n, u, m, k, M, G" << endl;
            return value;
    }
}

double Convertisseur::convertToKilo(double value, char from)
{
    switch(from) {
        case 'n':
            return value / 1000000000000.0;
        case 'u':
            return value / 1000000000.0;
        case 'm':
            return value / 1000000.0;
        case 'b':
            return value / 1000.0;
        case'M':
            return value * 1000.0;
        case 'G':
            return value * 1000000.0;
        default:
            cerr << "Error, unknown argument '" << from << "', correct : n, u, m, k, M, G" << endl;
            return value;
    }
}

double Convertisseur::convertToMega(double value, char from)
{
    switch(from) {
        case 'n':
            return value / 1000000000000000.0; // 10^15
        case 'u':
            return value / 1000000000000.0;
        case 'm':
            return value / 1000000000.0;
        case'b':
            return value / 1000000.0;
        case 'k':
            return value / 1000.0;
        case 'G':
            return value * 1000.0;
        default:
            cerr << "Error, unknown argument '" << from << "', correct : n, u, m, k, M, G" << endl;
            return value;
    }
}



/**
  Pression
  */
double Convertisseur::convertPression(double value, char from, char to)
{
    switch(to) {
        case 'P':
            return convertToPascal(value, from);
        case 'B': // bar
            return convertToBar(value, from);
        case '#':
            cerr << "Invalid data" << endl;
            return value;
        default:
        cerr << "Error, unknown argument '" << to << "', correct : P (Pascal), B (bar)" << endl;
            return value;
    }
}


double Convertisseur::convertToPascal(double value, char from)
{
    switch(from) {
        case 'B': // bar
            return value * 100000.0; // 1 bar = 10^5 Pa
        case 'H': // hPa
            return value * 100.0;
        case 'M': // mmHg
            return value * 133.322;
        case 'I': // inHg
            return value * 3386.38816;
        default:
        cerr << "Error, unknown argument '" << from << "', correct : H (hPa), B (bar), M (mmHg), I(inHg)" << endl;
            return value;
    }
}

double Convertisseur::convertToBar(double value, char from)
{
    switch(from) {
        case 'P': // Pascal
            return value / 100000.0; // 1 Pa = 10^-5 bar
        case 'H': // hPa
            return value / 100.0; // 1 hPa = 10^-3 bar
        case 'M': // mmHg
            return value * 133.322 / 100000;
        case 'I': // inHg
            return value * 3386.38816 / 100000;

        default:
            cerr << "Error, unknown argument '" << from << "', correct : H (hPa), P (Pa), M (mmHg), I(inHg)" << endl;
            return value;
    }
}


/**
  Temperature
  */
double Convertisseur::convertTemperature(double value, char from, char to)
{
    switch(to) {
        case 'K': // kalvin
            return convertToKelvin(value, from);
        case 'C':
            return convertToCelsius(value, from);
        case 'F': // fahrenheit
            return convertToFahrenheit(value, from);
        case '#':
            cerr << "Invalid data" << endl;
            return value;
        default:
        cerr << "Error, unknown argument '" << to << "', correct : K (Kalvin), C (Celsius), F (fahrenheit)" << endl;
            return value;
    }
}



double Convertisseur::convertToCelsius(double value, char from)
{
    switch(from) {
        case 'K': // kalvin
            return value - 273.15;
        case 'F': // fahrenheit
        return (value - 32.0) / 1.8; // T(°C) = (T(°F) - 32)/1,8
        default:
        cerr << "Error, unknown argument '" << from << "', correct : K (Kalvin), F (fahrenheit)" << endl;
            return value;
    }
}

double Convertisseur::convertToFahrenheit(double value, char from)
{

    switch(from) {
        case 'K': // kelvin
            return value * 1.8 - 459.67; // °F = K × 1,8 − 459,67
        case 'C': // celsius
            return value * 1.8 + 32.0; // T(F°) = T(°C)×1,8 + 32
        default:
        cerr << "Error, unknown argument '" << from << "', correct : K (Kalvin), C (Celsius)" << endl;
            return value;
    }
}

double Convertisseur::convertToKelvin(double value, char from)
{
    switch(from) {
        case 'C': // celsius
            return value + 273.15;
        case 'F': // fahrenheit
        return (value + 459.67)/1.8; // K = (°F + 459,67) / 1,8
        default:
        cerr << "Error, unknown argument '" << from << "', correct : C (Celsius), F (fahrenheit)" << endl;
            return value;
    }
}


/**
  Vitesse
  */
double Convertisseur::convertSpeed(double value, char from, char to)
{
    switch(to) {
        case 'M': // m/s
            return convertToMeterSec(value, from);
        case '#':
            cerr << "Invalid data" << endl;
            return value;
        default:
        cerr << "Error, unknown argument '" << to << "', correct : M (m/s)" << endl;
            return value;
    }
}

double Convertisseur::convertToMeterSec(double value, char from)
{
    switch(from) {
        case 'K': // km/h
        return value*1000/ 3600;
        case 'S': // miles per hour (mph)
            return value*1609.344/ 3600;;
        case 'N': // knots
            return (value * 1.51 * 1609.344) / 3600; // -> mph -> m/s
        default:
        cerr << "Error, unknown argument '" << from << "', correct :  K (km/h), S(mph), N(knots)" << endl;
            return value;
    }
}




/**
  Distance
  */
double Convertisseur::convertDistance(double value, char from, char to) {
    switch(to) {
        case 'M': // mm (/h)
            return convertToMillimeters(value, from);
        case '#':
            cerr << "Invalid data" << endl;
            return value;
        default:
        cerr << "Error, unknown argument '" << to << "', correct : M(mm)" << endl;
            return value;
    }
}

double Convertisseur::convertToMillimeters(double value, char from)
{
    switch(from) {
        case 'I': // inch
            return value*25.4;

        default:
        cerr << "Error, unknown argument '" << from << "', correct : I (inch)" << endl;
            return value;
    }
}


/**
  Hail
  */
double Convertisseur::convertHail(double value, char from, char to)
{
    switch(to) {
        case 'M': // hits/cm²
            return convertToHpC(value, from);
        case '#':
            cerr << "Invalid data" << endl;
            return value;
        default:
        cerr << "Error, unknown argument '" << to << "', correct : M(hits/cm²)" << endl;
            return value;
    }
}

double Convertisseur::convertToHpC(double value, char from)
{
    switch(from) {
        case 'I': // hits/in²
            return value*6.4516;

        default:
        cerr << "Error, unknown argument '" << from << "', correct : I (hits/in²)" << endl;
            return value;
    }
}




