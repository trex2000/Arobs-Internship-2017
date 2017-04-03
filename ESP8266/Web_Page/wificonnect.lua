function SafeWifiConnect(ssid,psw)
     if (wifi.getmode()==1) then
          if (wifi.sta.getip() == nil) then
               wifi.sta.config(ssid,psw)
               return 0               
          end
     else
          return nil       
     end
end

function SafeGetIP() 
    if wifi.sta.getip()== nil then 
         print("IP unavaiable, Waiting...".."Wifi Status : "..wifi.sta.status())
    else 
          tmr.stop(1)
          TimerInUse[1] = 0
          print("Config done, IP is "..wifi.sta.getip())
--          dofile ("main.lua")
    end 
end
