class Convertisseur {
	public:
		static double convertFromTo(double value, char from, char to);
		static double convertPression(double value, char from, char to);
		static double convertTemperature(double value, char from, char to);
		static double convertSpeed(double value, char from, char to);
		static double convertDistance(double value, char from, char to);
		static double convertHail(double value, char from, char to);

	private :
		static double convertToBase(double value, char from);
		static double convertToMilli(double value, char from);
		static double convertToKilo(double value, char from);
		static double convertToMega(double value, char from);

		/** Pressure */
		static double convertToPascal(double value, char from);
		static double convertToHectoPascal(double value, char from);
		static double convertToBar(double value, char from);

		/** Temperature */
		static double convertToCelsius(double value, char from);
		static double convertToFahrenheit(double value, char from);
		static double convertToKelvin(double value, char from);

		/** Speed */
		static double convertToMeterSec (double value, char from);

		static double convertToMillimeters(double value, char from);

		static double convertToHpC(double value, char from);
};
