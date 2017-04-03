
function Task_1()
     print("T1 Start Heap: "..node.heap().." Time: "..tmr.now())
     tmr.delay(10000000)
     print("T1 Stop Heap: "..node.heap().." Time: "..tmr.now())
end

function Task_2()
     print("   T2 Start Heap: "..node.heap().." Time: "..tmr.now())

     print("   T2 Stop Heap: "..node.heap().." Time: "..tmr.now())
end

print("Init Start")
tmr.alarm(1,5000,1,function() Task_1()end)
tmr.alarm(2,1000,1,function() Task_2() end)
print("Init Stop")

