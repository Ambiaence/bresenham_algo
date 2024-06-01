start_x = 0
start_y = 0

height = 50 
width = 50 
image_number = 50 

function name(id)
	local name = id .. ".pmg"
	return name
end

function command(x0, y0, x1, y1, file_name) 
	local line = x0 .. " " .. y0 .. " " .. x1 .. " " .. y1
	local executable = "./a.out"
	local join = executable .. " " .. line .. " > " .. file_name
	return join
end

print(command(start_x, start_y, 49, 49, name(1)))

for column=0,width-1,1 do 
	for row=0,height-1,1 do 
		number = column*height + row
		file_name = name(number)
		input = command(start_x, start_y, column, row, file_name)
		os.execute(input)
	end
end
