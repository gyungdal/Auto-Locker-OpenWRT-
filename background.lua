-- 백그라운드에서 작동할 서비스
--  crontab -e
-- 1분마다 실행
--  */1 * * * * /usr/bin/lua /root/background.lua
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
	print(v["MAC"])
	if string.upper(v["MAC"]) == string.upper(mac) then
	  return v
	end
  end
end


function testread() 
  result = {}
  local command = "cat /proc/net/arp"
  local loop = 0
  local handle = io.popen(command)
  for line in handle:lines() do 
    if loop ~= 0 then
      local ip = split(line, " ")[1]
      local mac = split(line, " ")[4]
      local temp = {}
      temp["IP"] = ip
      temp["MAC"] = mac
      result[#result + 1] = temp  
      print(ip, mac)
    end
    loop = loop + 1
  end
  handle:close()
  return result
end 


function test2read() 
  result = {}
  local command = "iwinfo wlan0 assoclist"
  local handle = io.popen(command)
  local loop = 0
  for line in handle:lines() do 
    if loop % 2 == 0 then
      local mac = split(line, " ")[1]
      local name = split(line, " ")[5]
      local power = tonumber(split(line, " ")[2])
      local temp = {}
      temp["MAC"] = mac
      temp["NAME"] = name
      temp["POWER"] = power
      result[#result + 1] = temp
      print(line)
      print(mac, name, power)
    end
    loop = loop + 1
  end
  handle:close()
  return result
end 

function test3read() 
  result = {}
  local command = "cat /www/DeviceList"
  local handle = io.popen(command)
  for line in handle:lines() do
    local name = split(line, " ")[1]
    local one = split(line, " ")[2]
    local two = split(line, " ")[3]
	if name ~= nil and one ~= nil and two ~= nil then
		local temp = {}
		temp["NAME"] = name
		temp["ONE"] = one
		temp["TWO"] = two
		print(name, one, two)
		result[#result + 1] = temp
	end
  end
  handle:close()
  print("test3 end")
  return result
end 

function infoResult(ips, macs) 
  result = {}
  for q, ip in pairs(ips) do 
    for w, mac in pairs(macs) do 
      if ip["MAC"] ~= nil and mac["MAC"] ~= nil then
        if string.upper(ip["MAC"]) == string.upper(mac["MAC"]) then
	      print(ip["MAC"], mac["MAC"])
          local temp = {}
          temp["MAC"] = ip["MAC"]
          temp["IP"] = ip["IP"]
          temp["NAME"] = mac["NAME"]
          temp["POWER"] = mac["POWER"]
		  print(temp["IP"], temp["MAC"], temp["NAME"], temp["POWER"])
          table.insert(result, temp)
        end
      end
    end
  end
  print("INFO DONE")
  return result
end

totalInfo = infoResult(testread(), test2read())
for q2, v2 in pairs(test3read()) do
  print(v2["ONE"], v2["TWO"])
  local one = table.findByMac(totalInfo, v2["ONE"])
  local two = table.findByMac(totalInfo, v2["TWO"])
  if one ~= nil and two ~= nil then 
	  local dif = one["POWER"] - two["POWER"]
	  print(dif, "CATCH")
	  if dif < 5 and dif > -5 then
	    local tt = "nc " .. two["IP"] .. " 8000 < unlock"
		print(tt)
		os.execute(tt)
		tt = "nc " .. one["IP"] .. " 8000 < unlock"
		print(tt)
		os.execute(tt)
	  else
	    local tt = "nc " .. two["IP"] .. " 8000 < lock"
		print(tt)
		os.execute(tt)
		tt = "nc " .. one["IP"] .. " 8000 < lock"
		print(tt)
		os.execute(tt)
	  end
	end
end

