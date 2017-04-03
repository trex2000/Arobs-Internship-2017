-- mainprog.lua
function main(MainTime)

     print("Heap:"..node.heap())
     
     tmr.stop(0)
     TimerInUse[0] = 0
     
-- verify Station Mode
     if (wifi.getmode() == 2) then
          print("Wifi Mode: AP")
          print("Set Wifi Mode to the STATION...")
          wifi.setmode(wifi.STATION)
          if (wifi.getmode()==1) then
               print("OK")
          else          
               print("NOT OK")
               if (TimerInUse[0] ==0) then
                    TimerInUse[0] = 1          
                    tmr.alarm(0,MainTime,0,function() main() end)
                    return
               else
                    print("Timer 0 ERROR in main.lua -- verify Station Mode ")
                    node.restart()
               end
          end
     else
         print("Wifi Mode: STATION")     
     end
     
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
          SendTemp(MainVoltage)
          --SendTemp(GetTemp())
          --SendTemp2(GetTemp())
     end
     --node.dsleep(MainSleepTime)
     
     
     tmr.alarm(0,MainTime,0,function() main(MainTime) end)
end
