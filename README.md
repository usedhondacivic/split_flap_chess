# split_flap_chess

The code and design files for my custom split flap display chess board. 
All mechanical, electrical, and software design is custom made.

Project structure

* esp_code
    - Code for the ESP-32, commanding the display drivers and handing wireless communication
    - Built using the [ESP-IDF (Espressif IoT Development Framework)](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html), which requires its own installation. 
* mux_board
    - KiCad design files for the multiplexer / power distribution boards that control each row of the display
* CAD files
    - I use cloud computing based CAD program called OnShape. The project is publicly available and can be [found here.]( https://cad.onshape.com/documents/1a9f395bc655ed8cafb5152a/w/ca5dd87f244eee9edc291fc1/e/8a1b6aab0341456eb098d42a)