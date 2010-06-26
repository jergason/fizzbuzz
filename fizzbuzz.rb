#!/usr/bin/env ruby
(1..100).each do |x|
  print "Fizz" if 0 == (x % 3)
  print "Buzz" if 0 == (x % 5) 
  print "\n" if 0 == (x % 3) || 0 == (x % 5)
end
