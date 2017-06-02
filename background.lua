-- 백그라운드에서 작동할 서비스
function split(inputstr, sep)
  if sep == nil then
          sep = "%s"
  end
  local t={} ; i=1
  for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
          t[i] = str
          i = i + 1
  end
  return t
end

function table.findByMac(t, mac)
  for k, v in pairs(t, mac) do
    if v["MAC"] == mac 
      return v
    end
  end
end


function testread() 
  local result = {}
  local command = "cat D:\\Tool\\LUA\\myprograms\\OpenWRT\\test"
  local handle = io.popen(command)
  for line in handle:lines() do 
    local ip = split(line, " ")[3]
    local mac = split(line, " ")[2]
    local temp = {}
    temp["IP"] = ip
    temp["MAC"] = mac
    result[#result + 1] = temp  
  end
  handle:close()
  return result
end 


function test2read() 
  local result = {}
  local command = "cat D:\\Tool\\LUA\\myprograms\\OpenWRT\\test2"
  local handle = io.popen(command)
  for line in handle:lines() do 
    local mac = split(line, " ")[1]
    local name = split(line, " ")[5]
    local power = tonumber(split(line, " ")[2])
    local temp = {}
    temp["MAC"] = mac
    temp["NAME"] = name
    temp["POWER"] = power
    result[#result + 1] = temp
  end
  handle:close()
  return result
end 

function test3read() 
  local result = {}
  local command = "cat D:\\Tool\\LUA\\myprograms\\OpenWRT\\test3"
  local handle = io.popen(command)
  for line in handle:lines() do 
    local one = split(line, " ")[1]
    local two = split(line, " ")[2]
    local temp = {}
    temp["ONE"] = one
    temp["TWO"] = two
    result[#result + 1] = temp
  end
  handle:close()
  return result
end 

function infoResult(ips, macs) 
  local result = {}
  for q, ip in pairs(ips) do 
    for w, mac in pairs(macs) do 
      if string.upper(ip["MAC"]) == string.upper(mac["MAC"]) then
        local temp = {}
        temp["MAC"] = ip["MAC"]
        temp["IP"] = ip["IP"]
        temp["NAME"] = mac["NAME"]
        temp["POWER"] = mac["POWER"]
        table.insert(result, temp)
      end
    end
  end
  return result
end

totalInfo = infoResult(testread(), test2read())
for q, v in pairs(totalInfo) do 
  for q2, v2 in pairs(test3read()) do
    local one = table.findByMac(totalInfo, v2["ONE"])
    local two = table.findByMac(totalInfo, v2["TWO"]) 
    local dif = one["POWER"] - two["POWER"]
    if dif < 5 or dif > -5
      -- 소캣 전송!
    end
  end
  print("IP : ", v["IP"])
  print("MAC : ", v["MAC"])
  print("NAME : ", v["NAME"])
  print("POWER : ", v["POWER"])
end

