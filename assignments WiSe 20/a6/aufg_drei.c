/*
 *  Stephan Jokiel
 *  Maxine Rahlfes
 */


#include "base.h"

/*
Eine Klimaanlage soll bei Temperaturen unter 21 °C heizen, bei 21-23.7 °C nichts tun und bei Temperaturen ab 23.7 °C kühlen. Entwickeln Sie eine Funktion zur Regelung der Klimaanlage, die abhängig von der Temperatur heizt, ausschaltet oder kühlt.
*/

const double HEAT_LIMIT = 21;
const double COOL_LIMIT = 23.7;

enum OperatingMode {
    HEATING,
    OFF,
    COOLING
};

typedef enum OperatingMode OperatingMode; // optional, could use the enum keyword each time

// double -> OperatingMode
// Return the operating mode of the climate control unit given the temperature.
OperatingMode climate_control(double temperature);

static void climate_control_test() {
    test_equal_i(climate_control(17.1), HEATING);
    test_equal_i(climate_control(20.8), HEATING);
    test_equal_i(climate_control(20.9), HEATING);
    test_equal_i(climate_control(21.0), OFF);
    test_equal_i(climate_control(22.4), OFF);
    test_equal_i(climate_control(23.0), OFF);
    test_equal_i(climate_control(23.6), OFF);
    test_equal_i(climate_control(23.7), OFF);
    test_equal_i(climate_control(23.8), COOLING);
    test_equal_i(climate_control(24.2), COOLING);
}

// Return the operating mode of the climate control unit given the temperature.
OperatingMode climate_control(double temperature) {
    while (temperature < HEAT_LIMIT) {
        return HEATING;
    }
    while (temperature > COOL_LIMIT) {
        return COOLING;
    }
    return OFF;
}

int main(void) {
    climate_control_test();
    return 0;
}
