CAN-HAT from seengreat:www.seengreat.com
  ======================================
# Instructions
## Overview
CAN bus can realize high reliability serial communication with its high communication rate and good anti-electromagnetic interference ability. Therefore, it has high application value in practical applications. However, with the continuous development of integrated technology, in order to save power consumption and reduce the circuit size, the Logical Electrical Level of some new CAN bus controllers adopts LVTTL, which requires a bus transceiver suitable for it. And the SN65HVD230 type circuit produced by TI solves this problem very well.<br>  
## Specifications
◆Fully compatible with the ISO11898 standard;<br>  
◆High input impedance, allowing 120 nodes;<br>  
◆Low current standby mode, typical current is 370μA;<br>  
◆Signal transmission rate up to 1Mb/s;<br>  
◆With thermal protection, open circuit failure protection function;<br>  
◆With the anti-instantaneous interference and protecting the bus function;<br>  
◆Slope control,and reduce radio frequency interference (RFI);<br>  
◆Differential receiver with anti - wide range of common - mode interference and electromagnetic interference ( EMI ) capacity.<br>  
## Dimensions
34mm(length)*10.5mm(width)
# Usage
## Instructions of Hard Interface Configuration
We provide the communication routines of STM32F103 Microcontrollers for CAN HAT, and use  the CAN controller that comes with STM32 to realize communication control of CAN transceiver. If multi-node communication is performed, it is necessary to check whether should remove the terminal matching resistance (120Ω) by unplugging the jumper cap according to the site conditions.<br>  
 * Hardware Connection :STM32F103 -> CAN HAT<br>  
 *          3V3  -> 3V3                 PA11 -> CANRX<br>  
 *          GND  -> GND                 PA12 -> CANTX<br>  
## Demo Codes
The development environment of this demo codes is KeiluVision5, which provides two modes, LoopBack and Normal. LoopBack is the debugging mode, it allows the data on the CAN bus to be sent and received spontaneously. "Normal" is the normal transceiver mode, and two STM32F103+CAN HATs are required for CAN communication experiments.<br>  
