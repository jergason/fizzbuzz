#!/usr/bin/env ruby
require 'socket'                # Get sockets from stdlib

MAX_CLIENTS = 20
num_clients = 0

host = '0.0.0.0'
port = 7886

puts "Starting server on #{host}:#{port}. Allowing #{MAX_CLIENTS} connections"
server = TCPServer.open(host, port)
loop {                          # Servers run forever
  Thread.start(server.accept) do |client|
    num_clients += 1
    if MAX_CLIENTS >= num_clients
      client.puts "(#{Time.now.ctime}) Hello Client ##{num_clients}!"
      puts "(#{Time.now.ctime}) Hello Client ##{num_clients}!"
      while !client.nil? && line = client.gets
        puts "Client says:" + line.inspect
        c_msg = case line
          when /^q\W/
          when /^quit\W/
          when /^exit\W/
          else line
        end
        if c_msg.nil?
          client.puts "Adios Muchacho! (you didn't close your connection, I'll do it for you)"
          puts "Client Left"
          client.close
          client = nil
        else
          client.puts c_msg
        end
      end
    else
      client.puts "(#{Time.now.ctime}) Too many connections (#{num_clients}). Bye!"
    end
    num_clients -= 1
  end
}
