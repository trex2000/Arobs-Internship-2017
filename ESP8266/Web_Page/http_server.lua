sendFileContents = function(conn, filename) 
    if file.open(filename, "r") then 
        --conn:send(responseHeader("200 OK","text/html")); 
        repeat  
        local line=file.readline()  
        if line then  
            conn:send(line); 
        end  
        until not line  
        file.close(); 
        print("File sent");
    else 
        print("File not found");
        conn:send(responseHeader("404 Not Found","text/html")); 
        conn:send("Page not found"); 
    end 
end 

responseHeader = function(code, type) 
    return "HTTP/1.1 " .. code .. "\r\nConnection: close\r\nServer: nunu-Luaweb\r\nContent-Type: " .. type .. "\r\n\r\n";  
end 

httpserver = function () 
print("HTTP Server function is started");
 srv=net.createServer(net.TCP,60)  
     print("HTTP Server is created"); 
    srv:listen(80,function(conn)    
      conn:on("receive",function(conn,request)
        print("Request received");  
        conn:send(responseHeader("200 OK","text/html"));
        if string.find(request,"gpio=0") then             
            print("onDown Up");
            gpio.write(7, gpio.HIGH);  --13 UP
        elseif string.find(request,"gpio=1") then 
            print("onUp Up");
            gpio.write(7, gpio.LOW);  --13 UP
        elseif string.find(request,"gpio=2") then 
            print("onDown Down");
            gpio.write(6, gpio.HIGH);  --12  DOWN
        elseif string.find(request,"gpio=3") then 
            print("onUp Down");
            gpio.write(6, gpio.LOW);  --12  DOWN
        elseif string.find(request,"gpio=4") then 
            print("onDown Left");
            gpio.write(2, gpio.HIGH); --4   LEFT
        elseif string.find(request,"gpio=5") then 
            print("onUp Left");
            gpio.write(2, gpio.LOW); --4   LEFT
        elseif string.find(request,"gpio=6") then 
            print("onDown Right");
            gpio.write(1, gpio.HIGH); --5   RIGHT
        elseif string.find(request,"gpio=7") then 
            print("onUp Right");
            gpio.write(1, gpio.LOW); --5   RIGHT
        else 
            sendFileContents(conn,"header.htm"); 
        end 
       
      end)
      print(request); 
      conn:on("sent",function(conn)  
        conn:close();  
        print("Connection closed");         
        conn = nil;      
      end) 
    end) 
end
