#include "ev3dev.h"

using namespace ev3dev;

int main() {
    sound::speak("Let's go home", true);
    sound::tone({
            {392, 350, 100}, {392, 350, 100}, {392, 350, 100}, {311.1, 250, 100},
            {466.2, 25, 100}, {392, 350, 100}, {311.1, 250, 100}, {466.2, 25, 100},
            {392, 700, 100}, {587.32, 350, 100}, {587.32, 350, 100},
            {587.32, 350, 100}, {622.26, 250, 100}, {466.2, 25, 100},
            {369.99, 350, 100}, {311.1, 250, 100}, {466.2, 25, 100}, {392, 700, 100},
            {784, 350, 100}, {392, 250, 100}, {392, 25, 100}, {784, 350, 100},
            {739.98, 250, 100}, {698.46, 25, 100}, {659.26, 25, 100},
            {622.26, 25, 100}, {659.26, 50, 400}, {415.3, 25, 200}, {554.36, 350, 100},
            {523.25, 250, 100}, {493.88, 25, 100}, {466.16, 25, 100}, {440, 25, 100},
            {466.16, 50, 400}, {311.13, 25, 200}, {369.99, 350, 100},
            {311.13, 250, 100}, {392, 25, 100}, {466.16, 350, 100}, {392, 250, 100},
            {466.16, 25, 100}, {587.32, 700, 100}, {784, 350, 100}, {392, 250, 100},
            {392, 25, 100}, {784, 350, 100}, {739.98, 250, 100}, {698.46, 25, 100},
            {659.26, 25, 100}, {622.26, 25, 100}, {659.26, 50, 400}, {415.3, 25, 200},
            {554.36, 350, 100}, {523.25, 250, 100}, {493.88, 25, 100},
            {466.16, 25, 100}, {440, 25, 100}, {466.16, 50, 400}, {311.13, 25, 200},
            {392, 350, 100}, {311.13, 250, 100}, {466.16, 25, 100},
            {392.00, 300, 150}, {311.13, 250, 100}, {466.16, 25, 100}, {392, 700}
            },
            true
            );
}