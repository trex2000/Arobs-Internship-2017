print("Init Start")

ssid = "ArobsTgM"
psw = "Ar0b$Wirele$$"
--ssid = "HTC"
--psw = "12344321"
--ssid = "SMC"
--psw = "ember"
TimerInUse = {}
MainTime = 60000
MainSleepTime = 60000
MainVoltage = 0

gpio.mode(7, gpio.OUTPUT);  --13
gpio.mode(6, gpio.OUTPUT);  --12
gpio.mode(2, gpio.OUTPUT); --4
gpio.mode(1, gpio.OUTPUT); --5

gpio.write(7, gpio.LOW);  --13 UP
gpio.write(6, gpio.LOW);  --12  DOWN
gpio.write(2, gpio.LOW); --4   LEFT
gpio.write(1, gpio.LOW); --5   RIGHT


require("wificonnect")
require("http_server")

for i=0,6 do
     TimerInUse[i] = 0;
end

SafeWifiConnect()

-- verify connection IP != nil
if (wifi.sta.getip() == nil) then
     if (TimerInUse[1] == 0) then
          tmr.alarm(1, 5000, 1,function() SafeGetIP() end)
     end
else
     print("IP :"..wifi.sta.getip())
     print("Heap:"..node.heap())
     MainVoltage = adc.read(0) -- ADC Value
     MainVoltage = (MainVoltage * 9765) / 10000 -- mV Divided Voltage
     MainVoltage = (MainVoltage * 57) / 10 --mV Input Voltage
     print("Main Voltage : "..MainVoltage)
     httpserver()     
end

print("Init Stop")
