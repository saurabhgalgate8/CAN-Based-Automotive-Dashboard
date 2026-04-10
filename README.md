🚗 Overview :

ECU1 is responsible for acquiring vehicle speed and gear position, and transmitting this data to the dashboard ECU (ECU3) using the CAN protocol.

⚙️ Functionality :
Reads speed using ADC (potentiometer input)
Reads gear position using keypad
Converts analog signal to digital value
Sends formatted data over CAN bus

🔌 Peripherals Used:
ADC (Analog to Digital Converter) → for speed input
Potentiometer → simulates vehicle speed
Keypad → gear selection
CAN Module → data transmission

🔄 Working Principle:
ADC reads analog voltage from potentiometer
ADC value is scaled to speed range (0–99)
Keypad input updates gear position
Speed and gear are packed into a CAN frame
Data is transmitted directly to ECU3

📊 Data Details:
Speed Range: 0 – 99
Gear Input: User-controlled via keypad
Transmission: Direct to ECU3 via CAN

🧠 Key Concept :
Analog signal → ADC → Digital value → Scaled → Sent via CAN

🎯 Role in System:
ECU1 acts as a data source node, providing real-time speed and gear information to the dashboard.

⚠️ Notes :
Ensure proper ADC scaling for accurate speed values
Keypad input should be debounced for stable gear selection
CAN message format must match ECU3 expectations
