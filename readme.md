# Next TTC
Next TTC displays when the next TTC vehicles will be arriving at a given stop. 2 x twelve MAX7219 LED displays are attached to a wifi-enabled ESP8266 microcontroller.

## Supplies
- 24 MAX7219 LED Displays ([2xCAD$16](https://2ly.link/1yXWO))
- Header pins ([CAD$10](https://2ly.link/1yXWU))
- ESP8266 Microcontroller ([CAD$12](https://2ly.link/1yXWR))
- KeeYees breakout board ([CAD$15](https://amzn.to/3RCGdrc))
- Jumper wires ([CAD$13](https://2ly.link/1yXWT))
- MicroUSB to electrical outlet

The MAX7219 displays have to be soldered together with the help of the header pins. See this [video](https://www.youtube.com/watch?v=gNjKy5nY64k&t=423s) for more information. Instead of buying male-to-male header pins like in the video, you could also buy male-to-female right angled pins, which is less soldering and lets you more easily take them apart.

If you'd prefer not to solder, I'd look into a display like the [P10](https://2ly.link/1yXUD). It has benefit of different colours but note that it's also considerably more expensive.

Additionally, for the Canadians, the KeeYee microcontroller I've linked is too wide to fit on a traditional breadboard. You could look into breaking one into two or buy the breakout development board I've linked above to make things easy. From pictures from reviews, the American one does not seem to have this problem.

## Circuit set-up
This circuit uses 2 x twelve MAX7219 display set up in parallel. Display 1 is the first row of twelve and shows the route title, Display 2 is the second row of twelve and shows the predictions.

Display 1 | DIN | D7 (GPIO13)
Display 1 | CLK | D5 (GPIO14)
Display 1 | CS | D8 (GPIO15)
Display 2 | DIN | D2 (GPIO4)
Display 2 | CLK | D1 (GPIO5)
Display 2 | CS | D3 (GPIO0)

## IDE set-up
I would recommend watching this [video](https://www.youtube.com/watch?v=la-yGpXZ6sU), which walks you through:
- Installing the appropriate [driver](https://github.com/nodemcu/nodemcu-devkit/tree/master/Drivers) for the microcontroller
- Adding the following URL to Additional Boards Manager for the board to be recognized by the IDE: http://arduino.esp8266.com/stable/package_esp8266com_index.json

## Code set-up
- Add your wifi credentials 
- Add the stops in format `&stops=<routeTag>|<stopTag>`. See command for `predictionsForMultiStops`in TTC API documentation for more info.
- Change the amount of time before displaying the next route prediction (optional)


## Helpful videos and resources
- [ESP8266 Pinout Reference](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
- [MD_Parola documentation](https://majicdesigns.github.io/MD_Parola/)
- [ArduinoJson documentation](https://arduinojson.org/v7/tutorial/deserialization/)
- [TTC API documentation](https://open.toronto.ca/dataset/ttc-real-time-next-vehicle-arrival-nvas/)