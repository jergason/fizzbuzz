#!/usr/bin/env ruby
#http://www.tutorialspoint.com/ruby/ruby_socket_programming.htm

require 'socket'
host, port = ARGV[0..1]
unless host && port
  print("USAGE: ./TCPClient.rb host port\n")
  exit
end

server = TCPSocket.open(host, port)

@connections = [server, STDIN]
stop = false
loop {
  res = select(@connections, nil, nil)
  res[0].each do |socket|
    if socket == server
      puts socket.gets
    end
    if socket == STDIN
      line = socket.gets
      server.puts line
      stop = ("quit" == line.chomp || "exit" == line.chomp || "q" == line.chomp)
    end
    break if stop
  end
  break if stop
}

server.close
