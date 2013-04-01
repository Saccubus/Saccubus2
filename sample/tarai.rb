$maxdepth = 0;

def tarai(depth, x,y,z)
	if depth > $maxdepth
		puts "max: #{depth}"
		$maxdepth = depth;
	end
	if x<=y
		return y;
	else
		return tarai(depth+1, tarai(depth+1, x-1, y, z), tarai(depth+1, y-1, z, x), tarai(depth+1, z-1, x,y));
	end
end

puts "result: #{tarai(0, 12, 6,0)}"

puts "maxdepth: #{$maxdepth}"
